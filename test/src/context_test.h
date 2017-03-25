/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective: 
    - test default init
    - test copy init
    - test on_swap
 
to_do: 
    - test arithmetic operators (on_inc, on_dec .... )
    - test I/O operators
*/

#include <tuple>
#include <sstream>

#include <lib/context/src/fwd.h>
#include <lib/context/src/interface.h>
#include <lib/context/src/default_subject.h>

namespace om636
{
    template<class T>
    struct context_test_policy
    : om636::default_subject::policy< T >
    {
        typedef T context_type;
        typedef om636::default_subject::policy< T > base_type;
        typedef typename std::tuple_element< 0, typename base_type::value_type >::type value_type;
        
        using base_type::on_read; 
        using base_type::on_write; 

        template<class V>
        static value_type on_init( V & s )
        {
            return s.m_value = 123;
        }
        
        template<class V, class W>
        static value_type on_init( V & s, const W & value )
        {
            return s.m_value = value;
        }
        
        void on_swap( const context_type & lhs, const context_type & rhs)
        {
            m_value = 7777;
        }
        
        value_type m_value;
    };

    void run_context_test()
    {
        using namespace om636;
        using namespace std;
        typedef context< tuple< int >, context_test_policy > context_type;
        
        // check default constructor
        context_type a;
        ASSERT( a.m_value == 123 );
        
        // check copy constructor
        context_type b( 321 );
        ASSERT( b.m_value == 321 );
        
        // Check on_swap
        a = b;
        ASSERT( a.m_value == 7777 );

        FOOTER;
    }
    
    template<class T>
    void run_io_test()
    {
        using namespace std;
        using namespace om636;
        
        typedef context< tuple< int, int >, default_subject::policy > number_type;
        number_type a( make_tuple(0, 0) );

        stringstream( "1 2" ) >> a;
        ASSERT( get<0>(a.value_ref()) == 1 )(get<0>(a.value_ref()));
        ASSERT( get<1>(a.value_ref()) == 2 )(get<1>(a.value_ref()));
        
        stringstream tmp;
        tmp << a;
        
        ASSERT( tmp.str() == "1 2" );
        
        FOOTER;
    }

    template<class T>
    void run_io_quad_test()
    {
        using namespace std;
        using namespace om636;
        
        typedef context< tuple< int, int, int, int >, default_subject::policy > number_type;
        number_type a( make_tuple(0, 0, 0, 0) );
        stringstream( "2 3 5 7" ) >> a;
        
        ASSERT( get<0>(a.value_ref()) == 2 )(get<0>(a.value_ref()));
        ASSERT( get<1>(a.value_ref()) == 3 )(get<1>(a.value_ref()));
        ASSERT( get<2>(a.value_ref()) == 5 )(get<2>(a.value_ref()));
        ASSERT( get<3>(a.value_ref()) == 7 )(get<3>(a.value_ref()));
        
        stringstream tmp;
        tmp << a;
        
        ASSERT( tmp.str() == "2 3 5 7" );
        
        FOOTER;
    }

}    // om636