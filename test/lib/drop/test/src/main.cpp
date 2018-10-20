#include <iostream>
#include <lib/drop/interface.h>
#include <tmp/src/test.h>

void test_sign()
{
	using namespace om636;
	ASSERT( sign(-2) == -1 );
	FOOTER;
}

int main(int argc, const char * argv[])
{
	test_sign();	
	return 0;
}