/*
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc
*/

namespace om636 {
namespace traverse {
    namespace Private {
        // type trait
        template <class T>
        struct remove_reference_wrapper {
            typedef T type;
        };

        template <class T>
        struct remove_reference_wrapper<std::reference_wrapper<T>> {
            typedef T type;
        };

        // elements_impl
        template <int, int>
        struct elements_impl;

        template <int M>
        struct elements_impl<M, M>;

        // combinations_impl
        template <int, int, int>
        struct combinations_impl;

        template <int M, int N>
        struct combinations_impl<M, N, N>;

        template <int M, int N>
        struct combinations_impl<M, N, M>;

        // pairs_impl
        template <int, int>
        struct pairs_impl;

        template <int M>
        struct pairs_impl<2, M>;

        template <int M>
        struct pairs_impl<M, M>;

        template <>
        struct pairs_impl<2, 2>;

        // reduce_impl
        template <int, int, class>
        struct reduce_impl;

        template <int M, class T>
        struct reduce_impl<M, M, T>;

        template <class T>
        struct reduce_impl<2, 1, T>;

        // parallel_impl
        template <int, int>
        struct parallel_impl;

        template <int M>
        struct parallel_impl<M, M>;

        // combinations_binary_impl
        template <int, int, int, int>
        struct combinations_binary_impl;

        template <int M, int N, int O>
        struct combinations_binary_impl<M, N, O, N>;

        template <int M, int N, int O>
        struct combinations_binary_impl<M, N, M, O>;

    } // namespace Private

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U elements(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::elements_impl<0, std::tuple_size<type>::value>::visit(
            t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U elements_if(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::elements_impl<0, std::tuple_size<type>::value>::visit_if(
            t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U combinations(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::combinations_impl<0, 1, std::tuple_size<type>::value>::visit(t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U combinations_if(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::combinations_impl<0, 1, std::tuple_size<type>::value>::
            visit_if(t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U pairs(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::pairs_impl<2, std::tuple_size<type>::value>::visit(t,
            visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    U pairs_if(T t, U visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::pairs_impl<2, std::tuple_size<type>::value>::visit_if(
            t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, class V>
    std::tuple<T, V>
    reduce(U t, V visitor)
    {
        typedef typename Private::remove_reference_wrapper<U>::type type;
        return Private::reduce_impl<2, std::tuple_size<type>::value, T>::visit(
            t, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, class V>
    V parallel(T lhs, U rhs, V visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::parallel_impl<0, std::tuple_size<type>::value>::visit(
            lhs, rhs, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, class V>
    V parallel_if(T lhs, U rhs, V visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type type;
        return Private::parallel_impl<0, std::tuple_size<type>::value>::visit_if(
            lhs, rhs, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, class V>
    V combinations(T lhs, U rhs, V visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type l_type;
        typedef typename Private::remove_reference_wrapper<U>::type r_type;
        return Private::combinations_binary_impl<0,
            0,
            std::tuple_size<l_type>::value,
            std::tuple_size<r_type>::value>::visit(lhs, rhs, visitor);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U, class V>
    V combinations_if(T lhs, U rhs, V visitor)
    {
        typedef typename Private::remove_reference_wrapper<T>::type l_type;
        typedef typename Private::remove_reference_wrapper<U>::type r_type;
        return Private::combinations_binary_impl<0,
            0,
            std::tuple_size<l_type>::value,
            std::tuple_size<r_type>::value>::visit_if(lhs, rhs, visitor);
    }

    namespace Private {

#pragma mark - elements_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // elements_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N>
        struct elements_impl {
            enum {
                index = M,
                size = N
            };
            typedef elements_impl<index + 1, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                visitor(std::get<index>(t));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                visitor(std::get<index>(t.get()));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                if (visitor(std::get<index>(t)))
                    return permutation::visit(t, visitor);
                return visitor;
            }

            template <class T, class U>
            static U visit_if(std::reference_wrapper<T> t, U visitor)
            {
                if (visitor(std::get<index>(t.get())))
                    return permutation::visit(t, visitor);
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M>
        struct elements_impl<M, M> {
            template <class T, class U>
            static U visit(T, U visitor)
            {
                return visitor;
            }

            template <class T, class U>
            static U visit_if(T, U visitor)
            {
                return visitor;
            }
        };

#pragma mark - combinations_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // combinations_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N, int L>
        struct combinations_impl {
            enum {
                l_index = M,
                r_index = N,
                size = L
            };
            typedef combinations_impl<l_index, r_index + 1, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                using std::get;
                visitor(get<l_index>(t), get<r_index>(t));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                using std::get;
                visitor(get<l_index>(t.get()), get<r_index>(t.get()));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                using std::get;
                if (visitor(get<l_index>(t), get<r_index>(t)))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }

            template <class T, class U>
            static U visit_if(std::reference_wrapper<T> t, U visitor)
            {
                using std::get;
                if (visitor(get<l_index>(t.get()), get<r_index>(t.get())))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N>
        struct combinations_impl<M, N, N> {
            enum {
                l_index = M,
                r_index = N,
                size = N
            };
            typedef combinations_impl<l_index + 1, l_index + 2, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                return permutation::visit_if(t, visitor);
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N>
        struct combinations_impl<M, N, M> {
            template <class T, class U>
            static U visit(T, U visitor)
            {
                return visitor;
            }

            template <class T, class U>
            static U visit_if(T, U visitor)
            {
                return visitor;
            }
        };

#pragma mark - pairs_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // pairs_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N>
        struct pairs_impl {
            enum {
                index = M,
                size = N
            };
            typedef pairs_impl<index + 1, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                using namespace std;
                visitor(get<index - 2>(t), get<index - 1>(t));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                visitor(get<index - 2>(t.get()), get<index - 1>(t.get()));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                using namespace std;
                if (visitor(get<index - 2>(t), get<index - 1>(t)))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }

            template <class T, class U>
            static U visit_if(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                if (visitor(get<index - 2>(t.get()), get<index - 1>(t.get())))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M>
        struct pairs_impl<2, M> {
            enum {
                index = 2,
                size = M
            };
            typedef pairs_impl<index + 1, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t), get<1>(t));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t.get()), get<1>(t.get()));
                return permutation::visit(t, visitor);
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                using namespace std;
                if (visitor(get<0>(t), get<1>(t)))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }

            template <class T, class U>
            static U visit_if(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                if (visitor(get<0>(t.get()), get<1>(t.get())))
                    return permutation::visit_if(t, visitor);
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M>
        struct pairs_impl<M, M> {
            enum {
                index = M,
                size = M
            };

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                using namespace std;
                visitor(get<index - 2>(t), get<index - 1>(t));
                return visitor;
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                visitor(get<index - 2>(t.get()), get<index - 1>(t.get()));
                return visitor;
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                return visit(t, visitor);
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <>
        struct pairs_impl<2, 2> {
            enum {
                index = 2,
                size = 2
            };
            typedef pairs_impl<index + 1, size> permutation;

            template <class T, class U>
            static U visit(T t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t), get<1>(t));
                return visitor;
            }

            template <class T, class U>
            static U visit(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t.get()), get<1>(t.get()));
                return visitor;
            }

            template <class T, class U>
            static U visit_if(T t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t), get<1>(t));
                return visitor;
            }
 
            template <class T, class U>
            static U visit_if(std::reference_wrapper<T> t, U visitor)
            {
                using namespace std;
                visitor(get<0>(t.get()), get<1>(t.get()));
                return visitor;
            }
        };

#pragma mark - reduce_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // reduce_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N, class T>
        struct reduce_impl {
            enum {
                index = M,
                size = N
            };
            typedef reduce_impl<index + 1, size, T> permutation;

            template <class U, class V>
            static std::tuple<T, V> visit(U t, V visitor)
            {
                using namespace std;

                tuple<T, V> r(permutation::visit(t, visitor));
                auto nextVisitor = get<1>(r);
                T value(nextVisitor(get<index - 2>(t), get<0>(r)));
                return make_tuple(value, nextVisitor);
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, class T>
        struct reduce_impl<M, M, T> {
            enum {
                index = M,
                size = M
            };

            template <class U, class V>
            static std::tuple<T, V> visit(U t, V visitor)
            {
                using namespace std;
                T value(visitor(get<index - 2>(t), get<index - 1>(t)));
                return make_tuple(value, visitor);
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        struct reduce_impl<2, 1, T> {
            template <class U, class V>
            static std::tuple<T, V> visit(U t, V visitor)
            {
                using namespace std;
                T value(visitor(get<0>(t)));
                return make_tuple(value, visitor);
            }
        };

#pragma mark - parallel_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // parallel_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N>
        struct parallel_impl {
            enum {
                index = M,
                size = N
            };
            typedef parallel_impl<index + 1, size> permutation;

            template <class T, class U, class V>
            static V visit(T lhs, U rhs, V visitor)
            {
                using namespace std;
                visitor(get<index>(lhs), get<index>(rhs));
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit(T lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                visitor(get<index>(lhs), get<index>(rhs.get()));
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit(std::reference_wrapper<T> lhs, U rhs, V visitor)
            {
                using namespace std;
                visitor(get<index>(lhs.get()), get<index>(rhs));
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit(std::reference_wrapper<T> lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                visitor(get<index>(lhs.get()), get<index>(rhs.get()));
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit_if(T lhs, U rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<index>(lhs), get<index>(rhs))) {
                    return permutation::visit_if(lhs, rhs, visitor);
                }
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(std::reference_wrapper<T> lhs, U rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<index>(lhs.get()), get<index>(rhs))) {
                    return permutation::visit_if(lhs, rhs, visitor);
                }
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(T lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<index>(lhs), get<index>(rhs.get()))) {
                    return permutation::visit_if(lhs, rhs, visitor);
                }
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(std::reference_wrapper<T> lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<index>(lhs), get<index>(rhs))) {
                    return permutation::visit_if(lhs, rhs, visitor);
                }
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M>
        struct parallel_impl<M, M> {
            template <class T, class U, class V>
            static V visit(T, U, V visitor)
            {
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(T, U, V visitor)
            {
                return visitor;
            }
        };

#pragma mark - combinations_binary_impl

        /////////////////////////////////////////////////////////////////////////////////////////////
        // combinations_binary_impl
        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N, int O, int P>
        struct combinations_binary_impl {
            enum {
                l_index = M,
                r_index = N,
                l_size = O,
                r_size = P
            };
            typedef combinations_binary_impl<l_index, r_index + 1, l_size, r_size>
                permutation;

            template <class T, class U, class V>
            static V visit(T lhs, U rhs, V visitor)
            {
                using namespace std;
                visitor(get<l_index>(lhs), get<r_index>(rhs));
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit(std::reference_wrapper<T> lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                visitor(get<l_index>(lhs.get()), get<r_index>(rhs.get()));
                return permutation::visit(lhs, rhs, visitor);
            }


            template <class T, class U, class V>
            static V visit(std::reference_wrapper<T> lhs, U rhs, V visitor)
            {
                using namespace std;
                visitor(get<l_index>(lhs.get()), get<r_index>(rhs));
                return permutation::visit(lhs, rhs, visitor);
            }


            template <class T, class U, class V>
            static V visit(T lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                visitor(get<l_index>(lhs), get<r_index>(rhs.get()));
                return permutation::visit(lhs, rhs, visitor);
            }
 
            template <class T, class U, class V>
            static V visit_if(T lhs, U rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<l_index>(lhs), get<r_index>(rhs))) {
                    return permutation::visit(lhs, rhs, visitor);
                }
                return visitor;
            }
  
            template <class T, class U, class V>
            static V visit_if(std::reference_wrapper<T> lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<l_index>(lhs.get()), get<r_index>(rhs.get()))) {
                    return permutation::visit(lhs, rhs, visitor);
                }
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(std::reference_wrapper<T> lhs, U rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<l_index>(lhs.get()), get<r_index>(rhs))) {
                    return permutation::visit(lhs, rhs, visitor);
                }
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(T lhs, std::reference_wrapper<U> rhs, V visitor)
            {
                using namespace std;
                if (visitor(get<l_index>(lhs), get<r_index>(rhs.get()))) {
                    return permutation::visit(lhs, rhs, visitor);
                }
                return visitor;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N, int O>
        struct combinations_binary_impl<M, N, O, N> {
            enum {
                l_index = M,
                r_index = N,
                l_size = O,
                r_size = N
            };
            typedef combinations_binary_impl<l_index + 1, 0, l_size, r_size>
                permutation;

            template <class T, class U, class V>
            static V visit(T lhs, U rhs, V visitor)
            {
                return permutation::visit(lhs, rhs, visitor);
            }

            template <class T, class U, class V>
            static V visit_if(T lhs, U rhs, V visitor)
            {
                return permutation::visit_if(lhs, rhs, visitor);
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////
        template <int M, int N, int O>
        struct combinations_binary_impl<M, N, M, O> {
            template <class T, class U, class V>
            static V visit(T, U, V visitor)
            {
                return visitor;
            }

            template <class T, class U, class V>
            static V visit_if(T, U, V visitor)
            {
                return visitor;
            }
        };

    } // Private
} // namespace traverse

} // namespace om636
