#ifndef TROOT_H
#define TROOT_H

#include <GL/gl.h>
#include "TEntity.h"

class TRoot : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TRoot(GLuint programID);

        /**
         * @brief 
         * 
         */
        virtual ~TRoot();

        /**
         * @brief 
         * 
         */
        virtual void beginDraw();

        /**
         * @brief 
         * 
         */
        virtual void endDraw();
    private:
        std::map<OBDEEnums::Matrices, GLuint> matrixIDs;
};

#endif