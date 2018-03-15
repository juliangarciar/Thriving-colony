#ifndef TMATRIXCACHE_H
#define TMATRIXCACHE_H

#include "../RETypes.h"
#include "../REEnums.h"

class TMatrixCache {
    public:
        /**
		 * @brief Crea una Instancia de Game
		 */
        static TMatrixCache* Instance();

        void setMatrix(REEnums::Matrices, glm::mat4*);
        glm::mat4 *getMatrix(REEnums::Matrices);

        void setMatrixID(REEnums::Matrices, GLuint);
        GLuint getMatrixID(REEnums::Matrices);

    protected:
        TMatrixCache();
        ~TMatrixCache();

    private:
        static TMatrixCache* pinstance;

        glm::mat4 identityMatrix;

        std::vector<GLuint> matrixIDs;
        std::vector<glm::mat4*> matrices;
};

#endif