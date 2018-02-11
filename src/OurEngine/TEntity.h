#ifndef TENTITY_H
#define TENTITY_H

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
    private:
};

#endif