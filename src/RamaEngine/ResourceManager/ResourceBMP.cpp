#include "ResourceBMP.h"

ResourceBMP::ResourceBMP(){

}

ResourceBMP::~ResourceBMP(){
	
}

void ResourceBMP::load(const char *path){
    setIdentifier(path);

	// Open the file
	FILE * file = fopen(path,"rb");
	if (!file){
		std::cout << path << " could not be opened. Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
		exit(0);
		return;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){ 
		std::cout << "Not a correct BMP file" << std::endl;
		fclose(file);
		exit(0);
		return;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		std::cout << "Not a correct BMP file" << std::endl;
		fclose(file);
		exit(0);
		return;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E])!=0){
        std::cout << "Not a correct BMP file" << std::endl;
        fclose(file);
		exit(0);
		return;
    }
	if (*(int*)&(header[0x1C])!=24){
        std::cout << "Not a correct BMP file" << std::endl;
        fclose(file);
		exit(0);
		return;
    }

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file can be closed.
	fclose (file);
}

void ResourceBMP::release(){
	delete [] data;
}

void ResourceBMP::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceBMP::getIdentifier(){
    return identifier;
}

unsigned char *ResourceBMP::getResource(){
    return data;
}

unsigned int ResourceBMP::getWidth(){
    return width;
}

unsigned int ResourceBMP::getHeight(){
    return height;
}