namespace om636 {
/////////////////////////////////////////////////////////////////////////////////////////////
// track_policy<T>
/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
template <class V>
auto track_policy<T>::on_init(V& v) -> value_type 
{
    log_ref() = "0";
    return base_type::on_init(v);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
template <class V, class W>
auto track_policy<T>::on_init(V& v, const W& i) -> value_type 
{
    std::stringstream s; 
    s << i;
    v.log_ref() = s.str();
    return base_type::on_init(v, i);
}

// modifiers
/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_swap(context_type& lhs, context_type& rhs) const
{
    using om636::swap;
    using std::swap;
    
    base_type::on_swap(lhs, rhs);
    swap(lhs.log_ref(), rhs.log_ref());
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_add(context_type& lhs, const context_type& rhs) const
{
   lhs.log_ref() = "(" + lhs.log_ref() + "+" + rhs.log_ref() + ")"; 
   base_type::on_add(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_subtract(context_type& lhs, const context_type& rhs) const
{
  lhs.log_ref() = "(" + lhs.log_ref() + "-" + rhs.log_ref() + ")";
  base_type::on_subtract(lhs, rhs); 
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_mult(context_type& lhs, const context_type& rhs) const
{
  lhs.log_ref() += "*" + rhs.log_ref(); 
  base_type::on_mult(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_divide(context_type& lhs, const context_type& rhs) const
{
  lhs.log_ref() += "/" + rhs.log_ref();
  base_type::on_divide(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_remainder(context_type& lhs, const context_type& rhs) const
{
  lhs.log_ref() += "%" + rhs.log_ref(); 
  base_type::on_remainder(lhs, rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_inc(context_type& lhs) const
{
  lhs.log_ref() = "(" + lhs.log_ref() + "+1)";
  base_type::on_inc(lhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_dec(context_type& lhs) const
{
  lhs.log_ref() = "(" + lhs.log_ref() + "-1)";
  base_type::on_dec(lhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void track_policy<T>::on_invert(context_type& lhs) const
{
  base_type::on_invert(lhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
auto track_policy<T>::log_ref() -> string_type &
{
  return m_log;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
auto track_policy<T>::log_ref() const -> string_type
{
  return m_log;
}
} // om636
