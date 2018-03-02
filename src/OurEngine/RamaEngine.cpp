#include "RamaEngine.h"

#include <IOEngine/ResourceManager/ResourceManager.h>
#include <IOEngine/ResourceManager/ResourceGLSL.h>

RamaEngine::RamaEngine() {
    rootNode = new TNode();
    // Create default layer
    defaultSceneNode = createRESceneNode();
}

RamaEngine::~RamaEngine() {
    delete rootNode;
    cameras . clear();
    lights . clear();
    sceneNodes . clear();
    
	glDeleteProgram(programID);
}

void RamaEngine::Init(ResourceGLSL*, ResourceGLSL*) {
    // Resource Manager
    ResourceManager *r = new ResourceManager();

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(0);
    }

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //ToDo: configurable?

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

    // Create vertexArray
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    
	// Create and compile our GLSL program from the shaders
    ResourceGLSL *s = (ResourceGLSL*)r->getResource("vertexShader.glsl", true);
    ResourceGLSL *s2 = (ResourceGLSL*)r->getResource("fragmentShader.glsl", true);

    // Link the program
	programID = glCreateProgram();
	glAttachShader(programID, s->getShaderID());
	glAttachShader(programID, s2->getShaderID());
	glLinkProgram(programID);

	// Check the program
    GLint Result = GL_FALSE;
    int InfoLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(programID, s->getShaderID());
	glDetachShader(programID, s2->getShaderID());
	
	glDeleteShader(s->getShaderID());
	glDeleteShader(s2->getShaderID());

	// Get a handle for our "MVP" uniform
	MVPID = glGetUniformLocation(programID, "MVP");
}

RELight* RamaEngine::createRELight() {
    RELight* rel = new RELight(sceneNodes . at(0));
    registerLight(rel -> getLightNode());
    return rel;
}

RELight* RamaEngine::createRELight(RESceneNode* layer) {
    RELight* rel = new RELight(layer -> getSceneNode());
    registerLight(rel -> getLightNode());
    return rel;
}

RECamera* RamaEngine::createRECamera() {
    RECamera* rec = new RECamera(sceneNodes . at(0));
    registerCamera(rec -> getCameraNode());
    return rec;
}

RECamera* RamaEngine::createRECamera(RESceneNode* layer) {
    RECamera* rec = new RECamera(layer -> getSceneNode());
    registerCamera(rec -> getCameraNode());
    return rec;
}

REMesh* RamaEngine::createREMesh() {
    return new REMesh(rootNode);
}

REMesh* RamaEngine::createREMesh(RESceneNode* layer) {
    return new REMesh(layer -> getSceneNode());
}

REAnimation* RamaEngine::createREAnimation() {
    return new REAnimation(rootNode);
}

REAnimation* RamaEngine::createREAnimation(RESceneNode* layer) {
    return new REAnimation(layer -> getSceneNode());
}

RESceneNode* RamaEngine::createRESceneNode() {
    RESceneNode* resn = new RESceneNode(rootNode);
    registerSceneNode(resn ->getSceneNode());
    return resn;
}

void RamaEngine::draw() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // Draw our tree
    rootNode -> draw();
}

TNode* RamaEngine::getRootNode() {
    return rootNode;
}

RESceneNode* RamaEngine::getDefaultLayer() {
    return defaultSceneNode;
}

void RamaEngine::registerCamera(TNode* cameraNode) {
    cameras . push_back(cameraNode);
}

void RamaEngine::registerLight(TNode* lightNode) {
    lights . push_back(lightNode);
}

void RamaEngine::registerSceneNode(TNode* sceneNode) {
    sceneNodes . push_back(sceneNode);
}