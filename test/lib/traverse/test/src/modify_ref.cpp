
#include <tmp/src/test.h>
#include <lib/traverse/interface.h>

struct dummy3 {

    template <class T>
    bool operator()(T& e) const
    {
        e = 2;
        return false;
    }

    template <class T, class U>
    bool operator()(T& e, U& d) const
    {
        e = 2;
        return false;
    }
};

void test_pairs_if_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int, int> a(1, 11, 111);
    traverse::pairs_if(std::ref(a), dummy3{});
    ASSERT(get<0>(a) == 2);
    ASSERT(get<1>(a) != 2);
}

void test_pairs_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int, int> a(1, 11, 111);
    traverse::pairs(std::ref(a), dummy3{});
    ASSERT(get<0>(a) == 2);
    ASSERT(get<1>(a) == 2);
}

void test_combinations_if_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int, int> a(1, 11, 111);
    traverse::combinations_if(std::ref(a), dummy3{});
    traverse::combinations_if(std::ref(a), std::ref(a), dummy3{});
    traverse::combinations_if(std::ref(a), a, dummy3{});
    traverse::combinations_if(a, std::ref(a), dummy3{});
    ASSERT(get<0>(a) == 2);
    ASSERT(get<2>(a) != 2);
}

void test_combinations_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int, int> a(1, 11, 111);
    traverse::combinations(std::ref(a), dummy3{});
    traverse::combinations(std::ref(a), std::ref(a),  dummy3{});
    traverse::combinations(a, std::ref(a),  dummy3{});
    traverse::combinations(std::ref(a), a,  dummy3{});
    traverse::combinations(a, a,  dummy3{});
 
    ASSERT(get<0>(a) == 2);
    ASSERT(get<1>(a) == 2);
}

void test_modify_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int> a(3, 22);
    traverse::elements(std::ref(a), dummy3{});
    ASSERT(get<0>(a) == 2);
    ASSERT(get<1>(a) == 2);
}

void test_traverse_elements_ref()
{
    using namespace std;
    using namespace om636;
    tuple<int, int> a(3, 22);
    traverse::elements_if(std::ref(a), dummy3{});
    ASSERT(get<0>(a) == 2);
    ASSERT(get<1>(a) == 22);
}

int main(int argc, const char* argv[])
{
    test_modify_ref();
    test_traverse_elements_ref();
    test_combinations_ref();
    test_combinations_if_ref();
    test_pairs_ref();
    test_pairs_if_ref();
    return 0;
}
