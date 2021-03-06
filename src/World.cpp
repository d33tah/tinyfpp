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

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "World.h"

using namespace std;

int World::max_x;
int World::max_z;
vector<Triangle> World::triangle;
vector<string> World::lines;

void World::setupWorld()
{
    ifstream file("Data/maze.txt");
    if (!file) {
        cerr << "FATAL: Could not open Data/maze.txt." << endl;
        exit(1);
    }
    string line;
    int x=0;
    for(;;)
    {
        getline(file,line);
        if(file.good())
        {
            lines.push_back(line);
            if((int)line.size()>max_z)
                max_z=line.size();
            for(unsigned int z=0; z<line.size(); z++)
            {
                Triangle tr;

                tr.vertex[0].x = x;
                tr.vertex[0].y = 0.0;
                tr.vertex[0].z = z;
                tr.vertex[0].u = 0.0;
                tr.vertex[0].v = 0.0;

                tr.vertex[1].x = x+1.0;
                tr.vertex[1].y = 0.0;
                tr.vertex[1].z = z;
                tr.vertex[1].u = 0.0;
                tr.vertex[1].v = 0.0;

                tr.vertex[2].x = x+1.0;
                tr.vertex[2].y = 0.0;
                tr.vertex[2].z = z+1.0;
                tr.vertex[2].u = 0.0;
                tr.vertex[2].v = 0.0;
                triangle.push_back(tr);


                tr.vertex[0].x = x;
                tr.vertex[0].y = 0.0;
                tr.vertex[0].z = z;
                tr.vertex[0].u = 0.0;
                tr.vertex[0].v = 0.0;

                tr.vertex[1].x = x;
                tr.vertex[1].y = 0.0;
                tr.vertex[1].z = z+1.0;
                tr.vertex[1].u = 0.0;
                tr.vertex[1].v = 0.0;

                tr.vertex[2].x = x+1.0;
                tr.vertex[2].y = 0.0;
                tr.vertex[2].z = z+1.0;
                tr.vertex[2].u = 0.0;
                tr.vertex[2].v = 0.0;
                triangle.push_back(tr);


                tr.vertex[0].x = x;
                tr.vertex[0].y = 1.0;
                tr.vertex[0].z = z;
                tr.vertex[0].u = 0.0;
                tr.vertex[0].v = 0.0;

                tr.vertex[1].x = x+1.0;
                tr.vertex[1].y = 1.0;
                tr.vertex[1].z = z;
                tr.vertex[1].u = 0.0;
                tr.vertex[1].v = 0.0;

                tr.vertex[2].x = x+1.0;
                tr.vertex[2].y = 1.0;
                tr.vertex[2].z = z+1.0;
                tr.vertex[2].u = 0.0;
                tr.vertex[2].v = 0.0;
                triangle.push_back(tr);


                tr.vertex[0].x = x;
                tr.vertex[0].y = 1.0;
                tr.vertex[0].z = z;
                tr.vertex[0].u = 0.0;
                tr.vertex[0].v = 0.0;

                tr.vertex[1].x = x;
                tr.vertex[1].y = 1.0;
                tr.vertex[1].z = z+1.0;
                tr.vertex[1].u = 0.0;
                tr.vertex[1].v = 0.0;

                tr.vertex[2].x = x+1.0;
                tr.vertex[2].y = 1.0;
                tr.vertex[2].z = z+1.0;
                tr.vertex[2].u = 0.0;
                tr.vertex[2].v = 0.0;
                triangle.push_back(tr);


                if(line[z]=='x')
                {
                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x+1.0;
                    tr.vertex[1].y = 0.0;
                    tr.vertex[1].z = z;
                    tr.vertex[1].u = 0.0;
                    tr.vertex[1].v = 0.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x;
                    tr.vertex[1].y = 1.0;
                    tr.vertex[1].z = z;
                    tr.vertex[1].u = 1.5;
                    tr.vertex[1].v = 1.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x+1.0;
                    tr.vertex[1].y = 0.0;
                    tr.vertex[1].z = z+1.0;
                    tr.vertex[1].u = 0.0;
                    tr.vertex[1].v = 0.0;

                    tr.vertex[2].x = x+1.0;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x+1.0;
                    tr.vertex[1].y = 1.0;
                    tr.vertex[1].z = z;
                    tr.vertex[1].u = 1.5;
                    tr.vertex[1].v = 1.0;

                    tr.vertex[2].x = x+1.0;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x;
                    tr.vertex[1].y = 0.0;
                    tr.vertex[1].z = z+1.0;
                    tr.vertex[1].u = 0.0;
                    tr.vertex[1].v = 0.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x;
                    tr.vertex[1].y = 1.0;
                    tr.vertex[1].z = z;
                    tr.vertex[1].u = 1.5;
                    tr.vertex[1].v = 1.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x+1.0;
                    tr.vertex[1].y = 0.0;
                    tr.vertex[1].z = z+1.0;
                    tr.vertex[1].u = 0.0;
                    tr.vertex[1].v = 0.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z+1.0;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    tr.vertex[0].x = x+1.0;
                    tr.vertex[0].y = 1.0;
                    tr.vertex[0].z = z+1.0;
                    tr.vertex[0].u = 0.0;
                    tr.vertex[0].v = 1.0;

                    tr.vertex[1].x = x;
                    tr.vertex[1].y = 1.0;
                    tr.vertex[1].z = z+1.0;
                    tr.vertex[1].u = 1.5;
                    tr.vertex[1].v = 1.0;

                    tr.vertex[2].x = x;
                    tr.vertex[2].y = 0.0;
                    tr.vertex[2].z = z+1.0;
                    tr.vertex[2].u = 1.5;
                    tr.vertex[2].v = 0.0;
                    triangle.push_back(tr);

                }
            }
        }
        else
            break;
        x++;
    }
    max_x = x-1;
}

