#include <tuple>

#include <tmp/src/test.h>
#include "context_test.h"
#include "math_test.h"

/*    using namespace om636;

*/

int main(int argc, const char * argv[])
{
    using namespace std;
    using namespace om636;

    run_context_test();
	run_math_test<void>();
	run_io_test<void>();
	run_io_quad_test<void>();

	return 0;
}
