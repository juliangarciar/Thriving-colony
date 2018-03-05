#include "TBillboard.h"

TBillboard::TBillboard(f32 x, f32 y, f32 z) : TEntity() {
    glm::vec4 BillboardPos_worldspace(x, y, z, 1.0f);
    worldPosition = BillboardPos_worldspace;
}

TBillboard::~TBillboard() {

}