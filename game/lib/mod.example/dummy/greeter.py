# Copyright 2010-2011 Ilkka Halila
# This file is part of Goblin Camp.
# 
# Goblin Camp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Goblin Camp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License 
# along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.
#

import gcamp
import gcamp.config
import gcamp.events

def greetingMessage():
    gcamp.ui.messageBox("Greetings from Dummy Mod!")

class Greeter (gcamp.events.EventListener):
    def onGameStart(self):
            gcamp.delay(10, greetingMessage)

    def onGameLoaded(self, name):
            gcamp.delay(10, greetingMessage)

gcamp.events.register(Greeter())
