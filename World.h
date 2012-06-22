#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "Triangle.h"

class World
{
    public:
        static int numtriangles;
        static Triangle* triangle;
        static void SetupWorld();
};

#endif
