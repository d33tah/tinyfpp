#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>

class Image
{
    public:
        int FromBMP(std::string filename);
        unsigned long sizeX;
        unsigned long sizeY;
        char *data;
};

#endif
