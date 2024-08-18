#define WANT_TEST_EXTRAS
#include <tap++/tap++.h>

#include "Coordinate.hpp"
#include "CoordinateMap.hpp"

using namespace TAP;

int main() {
	TEST_START(3);

	{
		Coordinate size(10,20);
		CoordinateMap<int> int_map(size);
		for(int i=0; i<10; i++)
		for(int j=0; j<20; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=0; i<10; i++)
		for(int j=0; j<20; j++)
		{
			if (int_map[Coordinate(i,j)] != j*100+i)
				good = false;

		}
		is(good, "data [0..10, 0..20] stored ok");
	}

	{
		Coordinate c1(100, 100);
		Coordinate c2(109, 119);

		CoordinateMap<int> int_map(c1,c2);
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			if (int_map[Coordinate(i,j)] != j*100+i)
				good = false;

		}
		is(good, "data [100..110, 100..120] stored ok");
	}

	{
		Coordinate c1(100, 100);
		Coordinate c2(109, 119);

		CoordinateMap<int> int_map(c2, c1);
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			int_map[Coordinate(i,j)] = j*100+i;
		}
		bool good = true;
		for(int i=100; i<110; i++)
		for(int j=100; j<120; j++)
		{
			if (int_map[Coordinate(i,j)] != j*100+i)
				good = false;

		}
		is(good, "data [100..110, 100..120] stored ok");
	}


	TEST_END;
}
