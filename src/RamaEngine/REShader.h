#ifndef RESHADER_H
#define RESHADER_H

#include "RETypes.h"
#include "REEnums.h"

#include "Graphics/TShader.h"

class REShader {
    public:
        /**
         * @brief 
         * @param path ruta
         */
        REShader(std::string);

        /**
         * @brief 
         * 
         */
        ~REShader();

        TShader *loadShader();
    private:
        TShader *shader;
};

#endif