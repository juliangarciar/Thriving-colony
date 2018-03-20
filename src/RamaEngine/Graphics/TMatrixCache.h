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

        glm::mat4& getCurrentMatrix();
        void setCurrentMatrix(const glm::mat4& m);

        std::deque<glm::mat4>& getMatrixStack();
        

    protected:
        TMatrixCache();
        ~TMatrixCache();

    private:
        static TMatrixCache* pinstance;

        glm::mat4 identityMatrix;

        std::vector<GLuint> matrixIDs;
        std::vector<glm::mat4*> matrices;

        glm::mat4 currentMatrix; //Matriz modelo
        std::deque<glm::mat4> matrixStack;
};

#endif