//#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include "World.h"

using namespace std;

int World::numtriangles;
int World::max_x;
int World::max_z;
vector<Triangle*> World::triangle;
vector<string> World::lines;


/*
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

void World::SetupWorld() 
{
    FILE *filein;
    char oneline[255];

    filein = fopen("Data/world.txt", "rt");

    numtriangles=0;
    while(!feof(filein))
    {
        Triangle* tmp = new Triangle;
        triangle.push_back(tmp);
        bool stop=false;
        for (int vert = 0; vert < 3; vert++) {
            readstr(filein,oneline);
            if(feof(filein))
            {
                stop=true;
                break;
            }

            float x, y, z, u, 0.0;
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            Triangle* tr = triangle[numtriangles];
            tr->vertex[vert].x = x;
            tr->vertex[vert].y = 0.0;
            tr->vertex[vert].z = z;
            tr->vertex[vert].u = 0.0;
            tr->vertex[vert].v = 0.0;
        }
        if(!stop)
            numtriangles++;
    }

    fclose(filein);
    return;
}
*/

void World::SetupWorld()
{
    ifstream file("Data/maze.txt");
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
                if(line[z]=='x')
                {
                    Triangle* tr = new Triangle;
                    tr->vertex[0].x = x;
                    tr->vertex[0].y = 0.0;
                    tr->vertex[0].z = z;
                    tr->vertex[0].u = 0.0;
                    tr->vertex[0].v = 0.0;

                    tr->vertex[1].x = x+1.0;
                    tr->vertex[1].y = 0.0;
                    tr->vertex[1].z = z;
                    tr->vertex[1].u = 0.0;
                    tr->vertex[1].v = 0.0;

                    tr->vertex[2].x = x+1.0;
                    tr->vertex[2].y = 0.0;
                    tr->vertex[2].z = z+1.0;
                    tr->vertex[2].u = 0.0;
                    tr->vertex[2].v = 0.0;
                    triangle.push_back(tr);


                    tr = new Triangle;
                    tr->vertex[0].x = x;
                    tr->vertex[0].y = 0.0;
                    tr->vertex[0].z = z;
                    tr->vertex[0].u = 0.0;
                    tr->vertex[0].v = 0.0;

                    tr->vertex[1].x = x;
                    tr->vertex[1].y = 0.0;
                    tr->vertex[1].z = z+1.0;
                    tr->vertex[1].u = 0.0;
                    tr->vertex[1].v = 0.0;

                    tr->vertex[2].x = x+1.0;
                    tr->vertex[2].y = 0.0;
                    tr->vertex[2].z = z+1.0;
                    tr->vertex[2].u = 0.0;
                    tr->vertex[2].v = 0.0;
                    triangle.push_back(tr);

                    numtriangles+=2;
                }
        }
        else
            break;
        x++;
    }
    max_x = x;

}
