/* Copyright 2010-2011 Ilkka Halila
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

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
namespace py = boost::python;

#include "NPC.hpp"
#include "Construction.hpp"
#include "Item.hpp"
#include "scripting/Engine.hpp"
#include "scripting/Event.hpp"
#include "scripting/API.hpp"
#include "scripting/_gcampapi/PyItem.hpp"
#include "scripting/_gcampapi/PyConstruction.hpp"

namespace Script { namespace Event {
	void GameStart() {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::InvokeListeners("onGameStart");
		}
		PyGILState_Release(gstate);
	}
	
	void GameEnd() {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::InvokeListeners("onGameEnd");
		}
		PyGILState_Release(gstate);
	}
	
	void GameSaved(const std::string& filename) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::InvokeListeners("onGameSaved", "(s)", filename.c_str());
		}
		PyGILState_Release(gstate);
	}
	
	void GameLoaded(const std::string& filename) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::InvokeListeners("onGameLoaded", "(s)", filename.c_str());
		}
		PyGILState_Release(gstate);
	}
	
	void BuildingCreated(boost::weak_ptr<Construction> cons, int x, int y) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::API::PyConstruction pyconstruction(cons);
			py::object obj(boost::ref(pyconstruction));
			Script::InvokeListeners("onBuildingCreated", "(Oii)", obj.ptr(), x, y);
		}
		PyGILState_Release(gstate);
	}
	
	void BuildingDestroyed(boost::weak_ptr<Construction> cons, int x, int y) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::API::PyConstruction pyconstruction(cons);
			py::object obj(boost::ref(pyconstruction));
			Script::InvokeListeners("onBuildingDestroyed", "(Oii)", obj.ptr(), x, y);
		}
		PyGILState_Release(gstate);
	}
	
	void ItemCreated(boost::weak_ptr<Item> item, int x, int y) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::API::PyItem pyitem(item);
		
			py::object obj(boost::ref(pyitem));
			Script::InvokeListeners("onItemCreated", "(Oii)", obj.ptr(), x, y);
		}
		PyGILState_Release(gstate);
	}
	
	void TierChanged(int tier, const std::string& campName) {
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure(); // Grab Global Interpreter Log before doing python stuff
		{
			Script::InvokeListeners("onTierChanged", "(is)", tier, campName.c_str());
		}
		PyGILState_Release(gstate);
	}
	
	/*void ItemDestroyed(Item*, int, int) {
	
	}
	
	void NPCSpawned(NPC*, Construction*, int, int) {
	
	}
	
	void NPCKilled(NPC*, NPC*, int, int) {
	
	}*/
}}
