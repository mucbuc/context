#include <sstream>

#include <tmp/src/test.h>

#include <lib/traverse/interface.h>

void test_binary_combinations()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int> a = make_tuple(5, 7);
    tuple<int, int, int> b = make_tuple(11, 13, 17);
    auto r = traverse::combinations(a, b, [&](int a, int b) {
        result << "f(" << a << ", " << b << ") ";
        return a + b;
    });

    ASSERT(result.str() == "f(5, 11) f(5, 13) f(5, 17) f(7, 11) f(7, 13) f(7, 17) ")
    (result.str());

    FOOTER;
}

void test_binary_parallel()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int> a = make_tuple(11, 13);
    tuple<int, int, int> b = make_tuple(3, 5, 7);
    auto r = traverse::parallel(a, b, [&](int a, int b) {
        result << "f(" << a << ", " << b << ") ";
        return a + b;
    });

    ASSERT(result.str() == "f(11, 3) f(13, 5) ")
    (result.str());

    FOOTER;
}

void test_reduce_example()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int, int> t = make_tuple(2, 4, 4);
    auto r = traverse::reduce<int>(t, [&](int a, int b) {
        result << "f(" << a << ", " << b << ") ";
        return a + b;
    });

    ASSERT(result.str() == "f(4, 4) f(2, 8) ")
    (result.str());

    FOOTER;
}

void test_pairs_example()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int> t = make_tuple(2, 3);
    auto r = traverse::pairs(t, [&](auto a, auto b) {
        result << "f(" << a << ", " << b << ") ";
    });

    ASSERT(result.str() == "f(2, 3) ");

    FOOTER;
}

void test_elements_example()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    tuple<int, int> t = make_tuple(2, 3);
    auto r = traverse::elements(t, [&](auto a) {
        result << "f(" << a << ") ";
    });

    ASSERT(result.str() == "f(2) f(3) ");

    FOOTER;
}

void test_combinations_example()
{
    using namespace std;
    using namespace om636;
    stringstream result;
    auto t = make_tuple(3, 5, 7);
    auto r = traverse::combinations(t, [&](auto a, auto b) {
        result << "f(" << a << ", " << b << ") ";
    });
    ASSERT(result.str() == "f(3, 5) f(3, 7) f(5, 7) ")
    (result.str());

    FOOTER;
}

int main()
{
    test_binary_combinations();
    test_binary_parallel();
    test_reduce_example();
    test_pairs_example();
    test_elements_example();
    test_combinations_example();
    return 0;
}
