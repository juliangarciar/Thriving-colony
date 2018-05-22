#include "Video.h"
#include "Window.h"

Video::Video(std::string path){
	video = Window::Instance() -> getEngine() -> createVideo(
		Window::Instance()->getVideoLayer(), 
		Window::Instance()->getVideoProgram(), 
		path
	);
}

Video::~Video(){
	delete video;
	video = nullptr;
}

void Video::play(){
	video -> play();
}

void Video::pause(){
	video -> pause();
}

void Video::setLoop(bool l){
	video -> setLoop(l);
}