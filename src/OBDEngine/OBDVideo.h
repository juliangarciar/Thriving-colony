#ifndef OBDVIDEO_H
#define OBDVIDEO_H

#ifdef USEVIDEO

#include "OBDShaderProgram.h"
#include "OBDSceneNode.h"

#include "Graphics/TNode.h"

class OBDVideo {
    public:
		OBDVideo(OBDSceneNode* parent, OBDShaderProgram *program, std::string path);
		~OBDVideo();

		void play();
		void pause();

		void setLoop(bool);
	private:
		VideoData *data;
		TNode *videoNode;
};

#endif
#endif