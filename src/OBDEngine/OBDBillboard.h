//#ifndef OBDBILLBOARD_H
//#define OBDBILLBOARD_H
//
//#include "OBDSceneNode.h"
//
//#include "Graphics/TBillboard.h"
//#include "../MathEngine/Vector3.h"
//
//class OBDBillboard : public OBDEntity {
//    public:
//        /**
//         * @brief 
//         * 
//         */
//        OBDBillboard();
//
//        /**
//         * @brief 
//         * 
//         * @param parent 
//         */
//        OBDBillboard(OBDSceneNode*, i32, Vector3<f32>);
//
//        /**
//         * @brief 
//         * 
//         */
//        ~OBDBillboard();
//
//        /**
//         * @brief 
//         * 
//         */
//        void setPosition(Vector3<f32>);
//
//        /**
//         * @brief 
//         * 
//         */
//        void setColor(OBDColor*, OBDColor*);
//
//        /**
//         * @brief 
//         * 
//         */
//        Vector3<f32> getPosition();
//
//        /**
//         * @brief 
//         * 
//         */
//        i32 getID();
//
//        /**
//         * @brief 
//         * 
//         */
//        OBDColor* getTopColor();
//
//        /**
//         * @brief
//         */
//        OBDColor* getBottomColor();
//
//         /**
//         * @brief Get the First Node object
//         * 
//         * @return TNode* 
//         */
//        TNode *getFirstNode();
//
//    private:
//        TNode* billboardNode;
//        TNode* rotationNode;
//        TNode* translationNode;
//        TNode* scaleNode;
//        i32 ID;
//        Vector3<f32> position;
//        
//};
//
//#endif