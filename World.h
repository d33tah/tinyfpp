#ifndef __SECTOR_H__
#define __SECTOR_H__

#include <vector>

#include "Triangle.h"

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
        static std::vector<Triangle*> triangle;
        static void SetupWorld();
};

#endif
