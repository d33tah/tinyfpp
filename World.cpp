#include <cstdio>
#include "GL/gl.h"
#include "World.h"

void readstr(FILE *f, char *string)
{
    do {
        fgets(string, 255, f);
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

void World::SetupWorld() 
{
    FILE *filein;
    char oneline[255];

    filein = fopen("Data/world.txt", "rt");

    readstr(filein, oneline);
    int numtriangles;
    sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

    this->numtriangles = numtriangles;
    this->triangle = new Triangle[numtriangles];

    for (int loop = 0; loop < numtriangles; loop++) {
        for (int vert = 0; vert < 3; vert++) {
            readstr(filein,oneline);

            float x, y, z, u, v;
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            this->triangle[loop].vertex[vert].x = x;
            this->triangle[loop].vertex[vert].y = y;
            this->triangle[loop].vertex[vert].z = z;
            this->triangle[loop].vertex[vert].u = u;
            this->triangle[loop].vertex[vert].v = v;
        }
    }

    fclose(filein);
    return;
}

