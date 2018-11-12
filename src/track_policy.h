
#ifndef TRACK_POLICY_H_GGFDH8900700
#define TRACK_POLICY_H_GGFDH8900700

#include <lib/context/src/forward_policy.h>
#include <lib/drop/interface.h>

namespace om636 {
template <class T>
struct track_policy : forward_policy<T> {
    typedef forward_policy<T> base_type; 
    using typename base_type::context_type;
    using typename base_type::value_type;
/* 
    template <class V>
    static value_type on_init(V&);

    template <class V, class W>
    static value_type on_init(V&, const W&);

    template <class V>
    static V to_value(const context_type&);

    // comparisons
    virtual bool on_equal(const context_type&, const context_type&) const;
    virtual int on_cmp(const context_type&, const context_type&) const;
    virtual int on_sign(const context_type&) const;

    // modifiers
    virtual void on_swap(context_type&, context_type&) const;
    virtual void on_add(context_type&, const context_type&) const;
    virtual void on_subtract(context_type&, const context_type&) const;
    virtual void on_mult(context_type&, const context_type&) const;
    virtual void on_divide(context_type&, const context_type&) const;
    virtual void on_remainder(context_type&, const context_type&) const;
    virtual void on_inc(context_type&) const;
    virtual void on_dec(context_type&) const;
    virtual void on_invert(context_type&) const;*/
};

} // om636

//#include "track_policy.hxx"

#endif // TRACK_POLICY_H_GGFDH8900700
