/* Copyright 2010-2011 Ilkka Halila
             2020-2023 Nikolay Shaplov (aka dhyan.nataraj)
This file is part of Goblins' Lot (former Goblin Camp)

Goblin Camp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Goblin Camp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.*/
#include "stdafx.hpp"

#include "MapRenderer.hpp"

MapRenderer::~MapRenderer() {}

void MapRenderer::SetViewportSize(int width, int height)
{
  viewportWidth = width;
  viewportHeight = height;
}
void MapRenderer::GetViewportSize(int& width, int& height)
{
  width = viewportWidth;
  height = viewportHeight;
}
