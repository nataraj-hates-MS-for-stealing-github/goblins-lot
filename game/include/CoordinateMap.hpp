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
 *  CoordinateMap class is about creatind 2D array object with Coordinate var
 *  as array index
 *  */

#pragma once

#include <algorithm>
#include "Coordinate.hpp"

template<class T> class CoordinateMap
{
protected:
	Coordinate corner_min;
	Coordinate corner_max;
	int width, height;
	std::vector<T> data;
public:
	T& operator[](Coordinate xy);
	CoordinateMap(Coordinate size): CoordinateMap({0,0}, size - Coordinate(1,1)) {};
	CoordinateMap(Coordinate c_a, Coordinate c_b);
	bool is_in_range(Coordinate xy);

};

template<class T>
CoordinateMap<T>::CoordinateMap(Coordinate c_a, Coordinate c_b)
{
	corner_min = Coordinate(
					 std::min(c_a.X(), c_b.X()),
					 std::min(c_a.Y(), c_b.Y()));
	corner_max = Coordinate(
					 std::max(c_a.X(), c_b.X()),
					 std::max(c_a.Y(), c_b.Y()));
	width = corner_max.X() - corner_min.X() + 1;
	height = corner_max.Y() - corner_min.Y() + 1;

	data = std::vector<T>(width*height); // Allocate full range

}

template<class T>
T& CoordinateMap<T>::operator[](Coordinate xy)
{
	Coordinate ij;
	ij = xy - corner_min;
	/* FIXME add range checks? */
	return data[ij.Y() * width + ij.X()];
}

template<class T>
bool CoordinateMap<T>::is_in_range(Coordinate xy)
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

