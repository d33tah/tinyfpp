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

#include "Image.h"

#include <cstdio>
#include <cstdlib>

static unsigned int getint(FILE* fp)
{
    int c, c1, c2, c3;

    c = getc(fp);
    c1 = getc(fp);
    c2 = getc(fp);
    c3 = getc(fp);

    return ((unsigned int) c) +
        (((unsigned int) c1) << 8) +
        (((unsigned int) c2) << 16) +
        (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE* fp)
{
    int c, c1;

    c = getc(fp);
    c1 = getc(fp);

    return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

int Image::fromBMP(std::string filename)
{
    FILE* file = fopen(filename.c_str(), "rb");
    if (!file) {
        fprintf(stderr, "Fatal: could not open %s\n", filename.c_str());
        exit(1);
    }
    fseek(file, 18, SEEK_CUR);

    this->sizeX = getint (file);
    this->sizeY = getint (file);

    unsigned long size = this->sizeX * this->sizeY * 3;

    unsigned short int planes = getshort(file);
    unsigned short int bpp = getshort(file);
    planes+=0; bpp+=0; //just so the compiler shuts up

    fseek(file, 24, SEEK_CUR);
    this->data = new char[size];
    fread(this->data, size, 1, file);

    for (unsigned long i=0;i<size;i+=3) {
        char temp = this->data[i];
        this->data[i] = this->data[i+2];
        this->data[i+2] = temp;
    }

    return 1;
}

