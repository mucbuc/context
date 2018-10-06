#ifndef FWD_H_34232L4K3J24L3K2J423LPAFALF
#define FWD_H_34232L4K3J24L3K2J423LPAFALF

namespace om636 {
template <class>
struct forward_policy;

// default_subject.h
namespace default_subject {
    template <class>
    struct policy;
    template <class>
    struct traits;
}

// interface.h
template <class, template <class> class = default_subject::policy>
class context;
}

#endif // FWD_H_34232L4K3J24L3K2J423LPAFALF