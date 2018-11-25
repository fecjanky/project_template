#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <headeronly.h>

#include <sstream>

TEST_CASE("test hello","[hello]")
{
	std::stringstream ss;
	Sample::hello(ss,4);
	REQUIRE(ss.str() == "Hello with value:4\n");
}