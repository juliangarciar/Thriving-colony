#ifndef TBILLBOARD_H
#define TBILLBOARD_H

#include "TEntity.h"

class TBillboard : public TEntity {
    public:
        TBillboard(f32, f32, f32);

        ~TBillboard();

    private:
        glm::vec4 worldPosition;
};

#endif