#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <string>

#include "Triangle.h"

using namespace std;

class Object
{
    private:
        vector<Triangle> triangles;
    public:
        Vertex point;
        void loadFile(string);
        vector<Triangle> getTriangles();
};

#endif
