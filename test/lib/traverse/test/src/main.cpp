#include <iostream>
#include <string>
#include <tuple>

#include <tmp/src/test.h>

#include <lib/traverse/interface.h>

struct dummy {
    template <class T>
    void operator()(const T& e) const
    {
        std::cout << e << " ";
    }

    template <class T, class U>
    void operator()(const T& e, const U& p) const
    {
        std::cout << e << "," << p << " ";
    }
};

int main(int argc, const char* argv[])
{
    using namespace std;
    using namespace om636;

    const tuple<int, string> t(5, "hello");

    traverse::elements(t, dummy{});

    cout << endl;

    tuple<int, int> a(3, 22);
    traverse::combinations(a, tuple<int, int, int, int>(2, 4, 5, 6), dummy{});
    return 0;
}
