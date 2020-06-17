
#ifndef TRACK_POLICY_H_GGFDH8900700
#define TRACK_POLICY_H_GGFDH8900700

#include <sstream>
#include <string>

#include <lib/context/src/forward_policy.h>
#include <lib/drop/interface.h>

namespace om636 {
template <class T>
struct track_policy : forward_policy<T> {
    typedef forward_policy<T> base_type;
    using typename base_type::context_type;
    using typename base_type::value_type;

    typedef std::string string_type;
    using base_type::on_write;
    using base_type::to_value;

    template <class V>
    static value_type on_init(V&);

    template <class V, class W>
    static value_type on_init(V&, const W&);

    template <class V>
    static value_type&& on_init(V&, context_type&&);

    template <class V, class W>
    static W&& on_init(V&, W&&);

    // modifiers
    virtual void on_swap(context_type&, context_type&) const;
    virtual void on_add(context_type&, const context_type&) const;
    virtual void on_subtract(context_type&, const context_type&) const;
    virtual void on_mult(context_type&, const context_type&) const;
    virtual void on_divide(context_type&, const context_type&) const;
    virtual void on_remainder(context_type&, const context_type&) const;
    virtual void on_inc(context_type&) const;
    virtual void on_dec(context_type&) const;
    virtual void on_invert(context_type&) const;

    string_type& log_ref();
    string_type log_ref() const;

private:
    string_type m_log;
};

} // om636

#include "track_policy.hxx"

#endif // TRACK_POLICY_H_GGFDH8900700
