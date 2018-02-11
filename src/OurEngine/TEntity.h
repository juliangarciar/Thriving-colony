#ifndef TENTITY_H
#define TENTITY_H

class TEntity {
    public:
        TEntity();
        virtual ~TEntity();

        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

    private:
};

#endif