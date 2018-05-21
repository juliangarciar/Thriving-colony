#ifndef OBDVIDEO_H
#define OBDVIDEO_H

#include "OBDShaderProgram.h"
#include "OBDSceneNode.h"

#include "Graphics/TNode.h"

class OBDVideo {
    public:
		OBDVideo(OBDSceneNode* parent, OBDShaderProgram *program, std::string path);
		~OBDVideo();
	private:
		VideoData *data;
		TNode *videoNode;
};

#endif