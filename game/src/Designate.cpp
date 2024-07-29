/* Copyright 2024 Nikolay Shaplov
This file is part of Goblin Camp Engine.

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

#include "stdafx.hpp"

#include "TCODMapRenderer.hpp"
#include "tileRenderer/sdl/SDLTilesetRenderer.hpp"

#include "Game.hpp"
#include "Designate.hpp"
#include "Color.hpp"


#include "Logger.hpp"

void Designate::PutDCursorChar(Coordinate pos, DCursorSpec c_spec)
{
	Coordinate upleft = tcod_renderer->upleft;
	TCODConsole * cons  = tcod_renderer->console;

	int x = (pos - upleft).X();
	int y = (pos - upleft).Y();
	if (c_spec.c)
	{
		cons->putCharEx(x,y, *(c_spec.c), *(c_spec.fg), *(c_spec.bg));
	} else
	{
		if (c_spec.fg)
			cons->setCharForeground(x, y, *(c_spec.fg));
		if (c_spec.bg)
			cons->setCharBackground(x, y, *(c_spec.bg));
	}
}

void DesignateConstruction::Draw(TCODConsole* console, Coordinate pos, Coordinate upleft)
{
	DCursorSpec c_placable =    {GCampColor::green,  GCampColor::black, blueprit_char};
	DCursorSpec c_notplacable = {GCampColor::yellow, GCampColor::black, blueprit_char};
	DCursorSpec c_obstacle =    {GCampColor::red,    GCampColor::black, blueprit_char};

	DCursorSpec * c_current = &c_placable;
	auto g = Game::Inst();

	bool placeable;

	placeable = g->CheckPlacement(pos, size, std::set<TileType>());

	for(int i = pos.X(); i < (pos + size).X(); i++)
	{
		for (int j = pos.Y(); j < (pos + size).Y() ; j++)
		{
			if (! placeable)
			{
				if (g->CheckPlacement({i,j},{1,1}, std::set<TileType>()))
				{
				  c_current = &c_notplacable;
				} else
				{
				  c_current = &c_obstacle;
				}
			}
			PutDCursorChar({i,j}, *c_current);
		}
	}
}

void DesignateConstruction::MouseLClickProcess(int x, int y)
{
	if ( Game::Inst()->CheckPlacement({x,y},size, std::set<TileType>()))
		placeConstructionCallback({x,y});
}

void DesignateArea::MouseLClickProcess(int x, int y)
{
	if (! corner_a)
	{
		corner_a = std::make_shared<Coordinate>(x,y);
	}
//	placeConstructionCallback({x,y});
}

void DesignateArea::Draw(TCODConsole* console, Coordinate pos, Coordinate upleft)
{
	DCursorSpec c_mouse_on_obstacle = {GCampColor::yellow,     GCampColor::black, '~'};
	DCursorSpec c_suitable =          {GCampColor::green,      GCampColor::black, '~'};
	DCursorSpec c_noaccess =          {GCampColor::darkGrey,   GCampColor::black, '~'};
	DCursorSpec c_obstacle =          {GCampColor::darkerGrey, GCampColor::black,  std::nullopt};

	DCursorSpec *c_current = &c_suitable;

	auto g = Game::Inst();

	Coordinate c_a = corner_a ? *corner_a : pos;
	Coordinate c_b = pos;

	Coordinate c_min = Coordinate::min(c_a, c_b);
	Coordinate c_max = Coordinate::max(c_a, c_b);

	int width =  (c_max-c_min).X() + 1;
	int height = (c_max-c_min).Y() + 1;

	std::vector<bool> obstacle_map(width * height);
	for (int i = 0; i < width; i++)
	for (int j = 0; j < height; j++)
	{
		Coordinate xy = c_min + Coordinate(i,j);
		obstacle_map[i + j*width] = ! Game::Inst()->CheckPlacement(xy, {1,1}, std::set<TileType>());
	}

	std::vector<bool> flooded_map(width * height);

	Coordinate initial = c_a - c_min;
	flooded_map[initial.X()+initial.Y()*width] = 1;
	std::list<Coordinate> l = {initial};

	while(l.size())
	{
		Coordinate c = l.front();
		l.pop_front();
		int i = c.X();
		int j = c.Y();

		if ((i>0) && (! obstacle_map[i-1+j*width]) && (! flooded_map[i-1+j*width]))
		{
		   flooded_map[i-1+j*width] = 1;
		   Coordinate n = {i-1,j};
		   l.push_back(n);
		}
		if ((i<width-1) && (! obstacle_map[i+1+j*width]) && (! flooded_map[i+1+j*width]))
		{
		   flooded_map[i+1+j*width] = 1;
		   Coordinate n = {i+1,j};
		   l.push_back(n);
		}
		if ((j>0) && (! obstacle_map[i+(j-1)*width]) && (! flooded_map[i+(j-1)*width]))
		{
		   flooded_map[i+(j-1)*width] = 1;
		   Coordinate n = {i,j-1};
		   l.push_back(n);
		}
		if ((j<height-1) && (! obstacle_map[i+(j+1)*width]) && (! flooded_map[i+(j+1)*width]))
		{
		   flooded_map[i+(j+1)*width] = 1;
		   Coordinate n = {i,j+1};
		   l.push_back(n);
		}
	}

	for (int i = 0; i < width; i++)
	for (int j = 0; j < height; j++)
	{
		Coordinate xy = c_min + Coordinate(i,j);

		if (! obstacle_map[i + j * width])
		{
			if (flooded_map[i + j * width])
				c_current = &c_suitable;
			else
				c_current = &c_noaccess;

		} else
		{
		if(xy == pos)
			c_current = &c_mouse_on_obstacle;
		else
			c_current = &c_obstacle;
		}
		Designate::PutDCursorChar(xy, *c_current);
	}
}

