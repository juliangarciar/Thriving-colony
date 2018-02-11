#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "TFile.h"
#include "TResourceMesh.h"

class TMesh : public TEntity {
    public:
        TMesh();
        virtual ~TMesh();

        void loadMesh(TFile *);

        virtual void beginDraw();
        virtual void endDraw();

    private:
        TResourceMesh *mesh;
};

#endif