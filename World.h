#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "Triangle.h"

class World
{
    public:
        int numtriangles;
        Triangle* triangle;
        void SetupWorld();
};

#endif
