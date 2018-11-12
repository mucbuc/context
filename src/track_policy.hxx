namespace om636 {
/*
/////////////////////////////////////////////////////////////////////////////////////////////
// track_policy<T>
/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
template <class V>
typename track_policy<T>::value_type forward_policy<T>::on_init(V&)
{
    return value_type();
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
template <class V, class W>
typename track_policy<T>::value_type forward_policy<T>::on_init(V&, const W& i)
{
    return value_type(i);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
template <class V>
V track_policy<T>::to_value(const context_type& c)
{
    return c.value_ref();
}
*/
// modifiers
/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_swap(context_type& lhs, context_type& rhs) const
{
    using om636::swap;
    using std::swap;

    swap(lhs.value_ref(), rhs.value_ref());
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_add(context_type& lhs, const context_type& rhs) const
{
   base_type::on_add(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_subtract(context_type& lhs, const context_type& rhs) const
{
  base_type::on_subtract(lhs, rhs); 
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_mult(context_type& lhs, const context_type& rhs) const
{
  base_type::on_mult(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_divide(context_type& lhs, const context_type& rhs) const
{
  base_type::on_divide(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_remainder(context_type& lhs, const context_type& rhs) const
{
  base_type::on_remainder(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_inc(context_type& lhs) const
{
  base_type::on_inc(lhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_dec(context_type& lhs) const
{
  base_type::on_dec(lhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_invert(context_type& lhs) const
{
  base_type::on_invert(lhs);
}

} // om636
