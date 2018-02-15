#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "TFile.h"
#include "TResourceMesh.h"

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
        void loadMesh(TFile *);


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