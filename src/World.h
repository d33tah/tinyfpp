/*
This file is part of tinyfpp.

tinyfpp is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __SECTOR_H__
#define __SECTOR_H__

#include <vector>
#include <string>

#include "Triangle.h"

using namespace std;

class World
{
    /*
     * World
     *
     * This class stores the description of the world and can load it from
     * a .txt file.
     *
     */
    public:
        static vector<Triangle> triangle;
        static void setupWorld();
        static int max_z;
        static int max_x;
        static vector<string> lines;
};

#endif
