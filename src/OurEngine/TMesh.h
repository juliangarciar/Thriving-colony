#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "TResourceMesh.h"
#include <IOEngine/IO.h>

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh();

        /**
         * @brief 
         * 
         */
        virtual ~TMesh();


        /**
         * @brief 
         * 
         * @param TFile 
         */
        void loadMesh(std::string);


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
        TResourceMesh *mesh;
};

#endif