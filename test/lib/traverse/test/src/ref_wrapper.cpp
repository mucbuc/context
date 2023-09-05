#include <sstream>

#include <tmp/src/test.h>

#include <lib/traverse/interface.h>

void test_parallel_ref()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int> a = make_tuple(11, 13);
    tuple<int, int, int> b = make_tuple(3, 5, 7);
    auto r = traverse::parallel(ref(a), ref(b), [&](int& a, int& b) {
        a = b = 321;
        return 0;
    });

    ASSERT(get<0>(a) == 321);
    ASSERT(get<1>(a) == 321);
    ASSERT(get<0>(b) == 321);
    ASSERT(get<1>(b) == 321);
    ASSERT(get<2>(b) != 321);

    FOOTER;
}

int main()
{
    test_parallel_ref();
    return 0;
}
