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