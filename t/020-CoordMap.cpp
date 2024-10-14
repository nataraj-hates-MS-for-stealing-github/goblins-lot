#define WANT_TEST_EXTRAS
#include <tap++/tap++.h>

#include "Coordinate.hpp"
#include "CoordExtra.hpp"

using namespace TAP;

int main() {
	TEST_START(19);

	{
		Coordinate size(10,20);
		CoordMap<int> int_map(size);
		for(int i=0; i<10; i++)
		for(int j=0; j<20; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=0; i<10; i++)
		for(int j=0; j<20; j++)
		{
			Coordinate c(i,j);
			if (int_map[c] != j*100+i)
				good = false;

			if (! int_map.is_in_range(c))
				good = false;

		}
		std::string test_name = "data [0..10, 0..20]";
		ok(good, test_name + " stored ok");
		not_ok(int_map.is_in_range(Coordinate(-10, -10)), test_name + " is in range ok 1");
		not_ok(int_map.is_in_range(Coordinate(5,   -10)), test_name + " is in range ok 2");
		not_ok(int_map.is_in_range(Coordinate(-10, 5)),   test_name + " is in range ok 3");
		not_ok(int_map.is_in_range(Coordinate(30, 30)),   test_name + " is in range ok 4");
		not_ok(int_map.is_in_range(Coordinate(5,  30)),   test_name + " is in range ok 5");
		not_ok(int_map.is_in_range(Coordinate(30,  5)),   test_name + " is in range ok 6");
		not_ok(int_map.is_in_range(Coordinate(-10, 30)),  test_name + " is in range ok 7");
		not_ok(int_map.is_in_range(Coordinate(30, -10)),  test_name + " is in range ok 8");
	}

	{
		Coordinate c1(100, 100);
		Coordinate c2(109, 119);

		CoordMap<int> int_map(c1,c2);
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			Coordinate c(i,j);
			if (int_map[c] != j*100+i)
				good = false;

			if (! int_map.is_in_range(c))
				good = false;

		}
		std::string test_name = "data [100..110, 100..120]";
		ok(good, test_name + " stored ok");
		not_ok(int_map.is_in_range(Coordinate(-10, -10)),  test_name + " is in range ok 1");
		not_ok(int_map.is_in_range(Coordinate(105, -10)),  test_name + " is in range ok 2");
		not_ok(int_map.is_in_range(Coordinate(-10, 105)),  test_name + " is in range ok 3");
		not_ok(int_map.is_in_range(Coordinate(130, 130)),  test_name + " is in range ok 4");
		not_ok(int_map.is_in_range(Coordinate(105, 130)),  test_name + " is in range ok 5");
		not_ok(int_map.is_in_range(Coordinate(130, 105)),  test_name + " is in range ok 6");
		not_ok(int_map.is_in_range(Coordinate(-10, 130)),  test_name + " is in range ok 7");
		not_ok(int_map.is_in_range(Coordinate(130, -10)),  test_name + " is in range ok 8");
	}

	{
		Coordinate c1(100, 100);
		Coordinate c2(109, 119);

		CoordMap<int> int_map(c2, c1);
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			Coordinate c(i,j);
			if (int_map[c] != j*100+i)
				good = false;

			if (! int_map.is_in_range(c))
				good = false;

		}
		ok(good, "data [110..100, 120..100] stored ok");
	}


	TEST_END;
}
