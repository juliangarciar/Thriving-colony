#ifndef TTEXTURE_H
#define TTEXTURE_H

#include <string>

class TTexture {
    public:
        TTexture();
        ~TTexture();

        void setTexture(std::string);
        std::string getTexture();

    private:
        std::string textureName;
};
    
#endif