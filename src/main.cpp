
#include <config.h>
#include <gtest/gtest.h>
#include <a_load_of_rubish.h>


int test_main() {
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}


int main(int argc, char * const argv[])
{
	Config config(Args(argc, argv));
	if(config.help)
	{
		config.PrintHelp();
		return 0;
	}
	if(config.test) 
	{
		return test_main();
	}
	else
	{
		return normal_main(config);
	}
}
