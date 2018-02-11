#ifndef TCAMERA_H
#define TCAMERA_H

class TCamera : public TEntity {
    public:
        TCamera();
        ~TCamera();

        void beginDraw();
        void endDraw();

        void setPerspective(float, float);
        void setParallel(float, float);
    private:
        bool isPerspective;
        float zDepth;
};

#endif