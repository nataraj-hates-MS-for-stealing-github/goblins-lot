#define WANT_TEST_EXTRAS
#include <tap++/tap++.h>

#include "Coordinate.hpp"

using namespace TAP;

int main() {
	TEST_START(6);

	Coordinate c(1,2);
	Coordinate c1(1,2);
	Coordinate c2(3,4);

	is(c.X(), 1, "Can get X()");
	is(c.Y(), 2, "Can get Y()");
	ok(c == c1, "operator== works 1");
	not_ok(c == c2, "operator== works 2");
	ok(c != c2, "operator!= works 1");
	not_ok(c != c1, "operator!= works 2");



	TEST_END;
}
