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
        static int numtriangles;
        static vector<Triangle*> triangle;
        static void SetupWorld();
        static int max_z;
        static int max_x;
        static vector<string> lines;
};

#endif
