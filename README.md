# context

State access manager

## Interface
```
#pragma once

#include <type_traits>

#include <lib/context/src/fwd.h>

namespace om636 {
template <class T, template <class> class U>
class context
    : public U<context<T, U>> {
    template <class, template <class> class>
    friend class context;

public:
    // types
    typedef U<context<T, U>> subject_policy;
    typedef typename subject_policy::value_type value_type;

    // resources
    context();
    context(const context&);

    template <class W>
    context(W);
    template <class W, class X>
    context(W, X);
    virtual ~context() = default;
    context& operator=(context);
    template <class W>
    context& operator=(W);
    context& operator=(const value_type&);
    void swap(context&);

    // access
    typename std::add_lvalue_reference<value_type>::type value_ref();
    typename std::add_lvalue_reference<typename std::add_const<value_type>::type>::type value_ref() const;

    subject_policy& subject_ref();
    const subject_policy& subject_ref() const;

    template <class I>
    typename I::template traits<context>::result_type operator[](I);

    template <class I>
    typename I::template traits<const context>::result_type operator[](I) const;

    // conversion
    template <class W>
    W to_value() const;
    template <class W, class X>
    static W to_value(const X&);
    template <class W, class X, template <class> class Y>
    static W to_value(const context<X, Y>&);
    template <class W>
    static W to_value(const context&);

    template <class W, class X, template <class> class Y>
    static W converter(const context<X, Y>&);

    template <class W, class X>
    static W converter(const X&);

    // arithmetic
    template <class W>
    context operator+(const W&) const;
    context operator+(const context&) const;
    template <class W>
    context operator-(const W&) const;
    context operator-(const context&) const;
    template <class W>
    context operator*(const W&)const;
    context operator*(const context&)const;
    template <class W>
    context operator/(const W&) const;
    context operator/(const context&) const;
    template <class W>
    context operator%(const W&) const;
    context operator%(const context&) const;
    context operator-() const;

    template <class W>
    context& operator+=(const W&);
    context& operator+=(const context&);
    template <class W>
    context& operator-=(const W&);
    context& operator-=(const context&);
    template <class W>
    context& operator*=(const W&);
    context& operator*=(const context&);
    template <class W>
    context& operator/=(const W&);
    context& operator/=(const context&);
    template <class W>
    context& operator%=(const W&);
    context& operator%=(const context&);

    context operator++(int);
    context& operator++();
    context operator--(int);
    context& operator--();

    // comparisons
    bool operator==(const context&) const;
    bool operator!=(const context&) const;
    bool operator>=(context) const;
    bool operator>(context) const;
    bool operator<=(context) const;
    bool operator<(context) const;

    bool operator!() const;
    /*  TODO:
    context & operator<<(int);
    context & operator=<<(int);
    context & operator<<(int);
    context & operator=<<(int);
    */

private:
    value_type m_state;
};

// non members
template <class T, template <class> class U>
void swap(context<T, U>&, context<T, U>&);

template <class T, template <class> class U>
int sign(const context<T, U>&);

template <class T, class U, template <class> class V>
T& operator<<(T& s, const context<U, V>&);

template <class T, class U, template <class> class V>
T& operator>>(T& s, context<U, V>&);

} // om636

#include "interface.hxx"


```

## Examples

### Example 1
#### Source code
```
#include <tuple>
#include <sstream>
#include <iostream>

#include <lib/context/src/interface.h>
#include <lib/context/src/default_subject.h>

int main(int argc, const char* argv[])
{
    using namespace std;
    using namespace om636;
    typedef context<tuple<int, int, int, int>, default_subject::policy> number_type;

    number_type a(make_tuple(0, 0, 0, 0));
    stringstream("2 3 5 7") >> a;

    cout << a << endl;

    return 0;
}

```
#### Output
```
"2 3 5 7\n"
```
### Example 2
#### Source code
```
#include <tuple>
#include <iostream>

#include <lib/context/src/interface.h>
#include <lib/context/src/track_policy.h>

int main(int argc, const char* argv[])
{
    using namespace std;
    using namespace om636;

    typedef context<int, track_policy> number_type;

    number_type a(1), b(2); 
    a += b; 
    cout << a.subject_ref().log_ref() << endl;

    a -= b;
    cout << a.subject_ref().log_ref() << endl;
    
    a = number_type(1) * 17; 
    cout << a.subject_ref().log_ref() << endl;

    return 0;
}

```
#### Output
```
"(1+2)\n((1+2)-2)\n1*17\n"
```
