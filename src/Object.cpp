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

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Object.h"

using namespace std;

void readstr(FILE *f, char *string)
{
    do {
        if(!feof(f))
            fgets(string, 255, f);
        else
            break;
    } while ((string[0] == '/') || (string[0] == '\n') );
    return;
}

void Object::loadFile(string modelname)
{
    FILE *filein;
    char oneline[255];

    string filename = "Data/Models/"+modelname+".txt";
    filein = fopen(filename.c_str(), "rt");
    if(!filein)
    {
        cerr << "File " << filename << " does not exist!" << endl;
        exit(1);
    }

    while(!feof(filein))
    {
        Triangle tr;
        for (int vert = 0; vert < 3; vert++) {
            readstr(filein,oneline);
            if(feof(filein))
            {
                break;
            }

            float x, y, z, u, v;
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            tr.vertex[vert].x = x;
            tr.vertex[vert].y = y;
            tr.vertex[vert].z = z;
            tr.vertex[vert].u = u;
            tr.vertex[vert].v = v;
        }
        triangles.push_back(tr);
    }

    fclose(filein);
    return;
}

void Object::rotateDegrees(double degrees)
{
    for(vector<Triangle>::iterator it = triangles.begin() ; it!=triangles.end(); ++it)
    {
        Triangle tr = *it;
        for(int i=0; i<3; i++)
        {
            Vertex v = tr.vertex[i];
            double r = sqrt((v.x*v.x)+(v.y*v.y));
            v.x = r * cos(degrees);
            v.z = r * sin(degrees);
            tr.vertex[i] = v;
        }
        *it = tr;
    }
}

vector<Triangle> Object::getTriangles()
{
    return triangles;
}
