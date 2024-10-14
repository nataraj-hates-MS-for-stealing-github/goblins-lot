#define WANT_TEST_EXTRAS
#include <tap++/tap++.h>

#include "Coordinate.hpp"
#include "CoordExtra.hpp"

using namespace TAP;

int main() {
	TEST_START(1);

	CoordRange range{{3,5},{6,8}};

	std::string res = "";
	for(Coordinate c : range)
	{
	  if (!res.empty()) res += ";";
	  res += std::to_string(c.X()) + "," + std::to_string(c.Y());
	}
	is(res, "3,5;4,5;5,5;6,5;3,6;4,6;5,6;6,6;3,7;4,7;5,7;6,7;3,8;4,8;5,8;6,8");
	TEST_END;
}
