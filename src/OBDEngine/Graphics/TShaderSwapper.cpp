#include "TShaderSwapper.h"

TShaderSwapper::TShaderSwapper(GLuint p) {
	programID = p;
}

TShaderSwapper::~TShaderSwapper() {

}

void TShaderSwapper::beginDraw() {
	if (programID != 0) glUseProgram(programID);
}

void TShaderSwapper::endDraw() {
    if (programID != 0) glUseProgram(TEntity::cache.getID(OBDEnums::OpenGLIDs::CURRENT_PROGRAM_ID));
}

void TShaderSwapper::setProgramID(GLuint p) {
	programID = p;
}

GLuint TShaderSwapper::getProgramID() {
	return programID;
}