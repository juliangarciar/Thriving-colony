#ifndef OBDVIDEO_H
#define OBDVIDEO_H

#ifdef USEVIDEO

#include "OBDShaderProgram.h"
#include "OBDSceneNode.h"

#include "Graphics/TNode.h"

class OBDVideo {
    public:
		/**
		 * @brief Construct a new OBDVideo object
		 * 
		 * @param parent parent node
		 * @param program shader to render the video
		 * @param path 
		 */
		OBDVideo(OBDSceneNode* parent, OBDShaderProgram *program, std::string path);

		/**
		 * @brief Destroy the OBDVideo object
		 * 
		 */
		~OBDVideo();

		/**
		 * @brief Play the video
		 * 
		 */
		void play();

		/**
		 * @brief Pause the video
		 * 
		 */
		void pause();
		/**
		 * @brief Set wether or not the video should loop
		 * 
		 */
		void setLoop(bool);
	private:
		VideoData *data;
		TNode *videoNode;
};

#endif
#endif