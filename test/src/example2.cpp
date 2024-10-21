#include <tuple>
#include <tmp/src/test.h>

#include <lib/context/src/interface.h>
#include <lib/context/src/track_policy.h>

int main(int argc, const char* argv[])
{
    using namespace std;
    using namespace om636;

    typedef context<int, track_policy> number_type;

    number_type a(1), b(2); 
    a += b; 
    cout << a.subject_ref().log_ref() << endl;

    a -= b;
    cout << a.subject_ref().log_ref() << endl;
    
    a = number_type(1) * 17; 
    cout << a.subject_ref().log_ref() << endl;

    return 0;
}
