#include <iostream>
#include <string>
#include <tuple>

#include <tmp/src/test.h>

#include <lib/traverse/interface.h>

struct HitCounter {

    template <class T, class U>
    bool operator()(const T& e, const U& p)
    {
        ++m_hitCount;
        return false;
    }

    HitCounter(const HitCounter&) = default;

    HitCounter()
        : m_hitCount(0)
    {
    }

    size_t m_hitCount;
};

void test_parallel_if()
{
    using namespace std;
    using namespace om636;

    const tuple<int, int> a(3, 22);
    auto counter = traverse::parallel_if(a, a, HitCounter{});
    ASSERT(counter.m_hitCount == 1);
}

void test_combinations_if()
{
    using namespace std;
    using namespace om636;

    const tuple<int, int> a(3, 22);
    auto counter = traverse::combinations_if(a, a, HitCounter{});
    ASSERT(counter.m_hitCount == 1);
}

int main(int argc, const char* argv[])
{
    test_parallel_if();
    test_combinations_if();
    return 0;
}
