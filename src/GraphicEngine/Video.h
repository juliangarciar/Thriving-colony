#ifndef VIDEO_H
#define VIDEO_H

#include <Types.h>
#include <OBDEngine/OBDVideo.h>

class Video {
    public:
		Video(std::string);
		~Video();

		void play();
		void pause();

		void setLoop(bool);
	private:
		OBDVideo *video;
};

#endif