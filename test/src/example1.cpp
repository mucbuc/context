#include <tuple>
#include <sstream>
#include <tmp/src/test.h>

#include <lib/context/src/interface.h>
#include <lib/context/src/default_subject.h>

int main(int argc, const char* argv[])
{
    using namespace std;
    using namespace om636;
    typedef context<tuple<int, int, int, int>, default_subject::policy> number_type;

    number_type a(make_tuple(0, 0, 0, 0));
    stringstream("2 3 5 7") >> a;

    cout << a << endl;

    return 0;
}
