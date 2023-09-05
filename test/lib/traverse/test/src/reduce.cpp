#include <tmp/src/test.h>

#include <lib/traverse/interface.h>

void test_reduce()
{
    using namespace std;
    using namespace om636;

    tuple<int, int> t = make_tuple(2, 3);
    auto r = traverse::reduce<int>(t, [&](auto a, auto b) {
        return a + b;
    });

    ASSERT(get<0>(r) == 5);

    FOOTER;
}

int main()
{
    test_reduce();
    return 0;
}
