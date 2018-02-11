#ifndef TMESH_H
#define TMESH_H

#include "TEntity"

class TMesh : public TEntity{
    public:
        TMesh();
        virtual ~TMesh();

        void loadMesh(TFile)

        virtual void beginDraw();
        virtual void endDraw();

    private:
        TResourceMesh * mesh
};

#endif