#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>

class Image
{
    /*
     * Image
     *
     * This class is supposed to load a texture from a graphics file
     * and store it in a raw format.
     *
     */
    public:
        int fromBMP(std::string filename);
        unsigned long sizeX;
        unsigned long sizeY;
        char *data;
};

#endif
