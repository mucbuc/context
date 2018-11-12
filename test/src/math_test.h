#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include "base.h"
#include <lib/context/src/interface.h>
#include <lib/context/src/forward_policy.h>
#include <lib/context/src/track_policy.h>

namespace {
template <class T>
void run_math_test()
{
    using namespace std;
    using namespace om636;

    typedef context<int, forward_policy> number_type;
    tools::tester<number_type>::test_number();

    typedef context<int, track_policy> number2_type;
    tools::tester<number2_type>::test_number();

    number2_type a(1), b(2); 
    a += b; 

    ASSERT( a.subject_ref().log_ref() == "(1+2)" );

    a -= b;
    ASSERT( a.subject_ref().log_ref() == "((1+2)-2)" );

    a = 1;
    a *= 17; 
    ASSERT( a.subject_ref().log_ref() == "1*17" ); 

    cout << a.subject_ref().log_ref() << endl;

    FOOTER;
}
}
