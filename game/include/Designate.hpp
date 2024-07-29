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

#pragma once

#include <libtcod.hpp>

#include "data/Serialization.hpp"
#include "Coordinate.hpp"
#include "MapRenderer.hpp"

#include <boost/shared_ptr.hpp>

#include "TCODMapRenderer.hpp"
#include "tileRenderer/sdl/SDLTilesetRenderer.hpp"


//class MapRenderer;
class TCODMapRenderer;
class SDLTilesetRenderer;


/* Structure that specifies how part of Designation Cursor should be rendered */
struct DCursorSpec
{
	std::optional<TCOD_ColorRGB> fg;  // Foreground color
	std::optional<TCOD_ColorRGB> bg;  // Background color
	std::optional<char> c;            // Cursor character
};

class Designate {
	GC_SERIALIZABLE_CLASS
protected:
	char blueprit_char = '?';
	boost::shared_ptr<TCODMapRenderer> tcod_renderer;
	boost::shared_ptr<SDLTilesetRenderer> sdl_renderer;

	boost::function<bool(Coordinate)> placeConstructionCallback;

	void PutDCursorChar(Coordinate pos, DCursorSpec c_spec);
public:
	virtual void Draw(TCODConsole* console, Coordinate pos, Coordinate upleft) = 0;
	virtual void MouseLClickProcess(int x, int y) = 0;

	void SetPlaceConstructionCallback(boost::function<bool(Coordinate)> newCallback) {placeConstructionCallback = newCallback;}

	Designate (boost::shared_ptr<MapRenderer> renderer) :
			tcod_renderer((renderer->GetRendereType() == GLOT_RENDERER_TCOD) ? boost::dynamic_pointer_cast<TCODMapRenderer>   (renderer)  : boost::shared_ptr<TCODMapRenderer>()),
			sdl_renderer((renderer->GetRendereType() == GLOT_RENDERER_SDL)   ? boost::dynamic_pointer_cast<SDLTilesetRenderer>(renderer) : nullptr)
			{}
	Designate (boost::shared_ptr<MapRenderer> renderer, char bc):
			tcod_renderer((renderer->GetRendereType() == GLOT_RENDERER_TCOD) ? boost::dynamic_pointer_cast<TCODMapRenderer>   (renderer) : nullptr),
			sdl_renderer((renderer->GetRendereType() == GLOT_RENDERER_SDL)   ? boost::dynamic_pointer_cast<SDLTilesetRenderer>(renderer) : nullptr),
			blueprit_char(bc)
			{}
};

class DesignateConstruction : public Designate {
  Coordinate size;

  public:
	DesignateConstruction(boost::shared_ptr<MapRenderer> renderer, Coordinate sz): size(sz), Designate(renderer, 'C') {};

	virtual void Draw(TCODConsole* console, Coordinate pos, Coordinate upleft) override;
	virtual void MouseLClickProcess(int tile_x, int tile_y) override;

};

class DesignateArea : public Designate {

protected:
	std::shared_ptr<Coordinate> corner_a;

public:
	virtual void Draw(TCODConsole* console, Coordinate pos, Coordinate upleft) override;
	virtual void MouseLClickProcess(int tile_x, int tile_y) override;

	DesignateArea(boost::shared_ptr<MapRenderer> renderer): Designate(renderer) {};

};

BOOST_CLASS_VERSION(Designate, 0)
