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

#include "Game.hpp"
#include "Designate.hpp"
#include "Color.hpp"

void Designate::Draw(TCODConsole* console, Coordinate pos, Coordinate upleft)
{
	TCOD_ColorRGB fg = GCampColor::green;
	TCOD_ColorRGB bg = GCampColor::black;
	auto g = Game::Inst();
	int width = 3;
	int height = 3;

	bool placeable;

	placeable = g->CheckPlacement(pos,{height,width}, std::set<TileType>());

	for(int i=0; i < width; i++)
	{
		for (int j=0; j < height; j++)
		{
			int x = pos.X() - upleft.X() + i;
			int y = pos.Y() - upleft.Y() + j;
			if (! placeable)
			{
				if (g->CheckPlacement({pos.X()+i,pos.Y()+j},{1,1}, std::set<TileType>()))
				{
				  fg = GCampColor::yellow;
				} else
				{
				  fg = GCampColor::red;
				}
			}
			console->putCharEx(x, y, blueprit_char, fg, bg );
		}
	}
}

