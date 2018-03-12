#ifndef RESOURCEBMP_H
#define RESOURCEBMP_H

#include <stdio.h>

#include "Resource.h"

class ResourceBMP : public Resource {
    public:
        ResourceBMP();
        ~ResourceBMP();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        unsigned char *getResource();
        unsigned int getWidth();
        unsigned int getHeight();
    private:
    // Data read from the header of the BMP file
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned int width, height;
        // Actual RGB data
        unsigned char * data;
};

#endif