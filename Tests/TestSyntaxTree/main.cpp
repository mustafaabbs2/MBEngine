#include "gtest/gtest.h"
#include <chrono>
#include <thread>
int main(int argc, char** argv)
{
	for (int n = 1; n < argc; ++n)
	{
		if (strcmp(argv[n], "--wait") == 0)
		{
			++n;
			const auto time = atoi(argv[n]);
			std::cout << "sleeping for " << time << " seconds.." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(time));
		}
	}
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}