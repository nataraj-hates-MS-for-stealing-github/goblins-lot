/* Copyright 2024 Nikolay Shaplov

This file is part of Goblins' Lot Engine.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.


THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS AND ITS CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KTH OR ITS CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*
 * CoordExtra.hpp: Extended classes for processing Coordinates
 * Stored in separate file as it is publushed on more relaxed license
 */


/*
 *  CoordMap class is about creatind 2D array object with Coordinate var
 *  as array index
 */

#pragma once


#include <iterator> // For std::input_iterator_tag
#include <algorithm>
#include "Coordinate.hpp"


class CoordRange
{
public:
	struct Iterator
	{
		using iterator_category = std::input_iterator_tag;
		using value_type = Coordinate;
		using pointer = Coordinate;
		using reference = Coordinate;
	protected:
		CoordRange & range;
		Coordinate value;
	public:
		reference operator*() {return value;};
		pointer operator->() {return value;};

		Iterator(Coordinate v, CoordRange & r):
			   value(v), range(r) {};
		Iterator& operator++() 	{
									value.X(value.X() + 1);
									if (value.X() > range.corner_max.X())
									{
										value.Y(value.Y() + 1);
										value.X(range.corner_min.X());
									}
									return *this;
								};
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.value == b.value; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.value != b.value; };
	};

protected:
	Coordinate corner_a, corner_b;
	Coordinate corner_min, corner_max;
	int width, height;

public:
	inline Coordinate CornerA() {return corner_a;};
	inline Coordinate CornerB() {return corner_b;};
	inline Coordinate CornerMin() {return corner_min;};
	inline Coordinate CornerMax() {return corner_max;};

	inline int Width()  {return width;};
	inline int Height() {return height;};

	bool is_in_range(Coordinate xy);


	CoordRange(Coordinate c_a, Coordinate c_b):
			corner_a(c_a),
			corner_b(c_b),
			width(abs(c_a.X() - c_b.X()) + 1), // + 1 because 9..9 range width is 1
			height(abs(c_a.Y() - c_b.Y()) + 1)

		{
		corner_min = Coordinate(
						 std::min(c_a.X(), c_b.X()),
						 std::min(c_a.Y(), c_b.Y()));
		corner_max = Coordinate(
						 std::max(c_a.X(), c_b.X()),
						 std::max(c_a.Y(), c_b.Y()));

	};
	Iterator begin() { return Iterator(corner_min, *this); };
	Iterator end()   { return ++Iterator(corner_max, *this); }; /* Item that goes after actula last item */
};

bool CoordRange::is_in_range(Coordinate xy)
{
	if ( (xy.X() < corner_min.X()) ||
		 (xy.Y() < corner_min.Y()) ||
		 (xy.X() > corner_max.X()) ||
		 (xy.Y() > corner_max.Y())
	   )
	{
		return false;
	}
	return true;
}


template<class T> class CoordMap
{
protected:
	CoordRange range;
	std::vector<T> data;
public:
	T& operator[](Coordinate xy);
	CoordMap(CoordRange r):
			range(r),
			data(std::vector<T>(r.Width() * r.Height())) /* Allocate full range in advance*/
			{};

	CoordMap(Coordinate size): CoordMap({0,0}, size - Coordinate(1,1)) {};
	CoordMap(Coordinate c_a, Coordinate c_b): CoordMap(CoordRange(c_a, c_b)) {};
	bool is_in_range(Coordinate xy);

};

template<class T>
T& CoordMap<T>::operator[](Coordinate xy)
{
	Coordinate ij;
	ij = xy - range.CornerMin();
	/* FIXME add range checks? */
	return data[ij.Y() * range.Width() + ij.X()];
}

template<class T>
bool CoordMap<T>::is_in_range(Coordinate xy)
{
	return range.is_in_range(xy);
}

