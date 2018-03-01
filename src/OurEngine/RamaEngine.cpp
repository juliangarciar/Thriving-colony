#include "RamaEngine.h"

#include <IOEngine/ResourceManager/ResourceManager.h>
#include <IOEngine/ResourceManager/ResourceGLSL.h>

RamaEngine::RamaEngine() {
    rootNode = new TNode();
    // Create default layer
    defaultSceneNode = createRESceneNode();
    initializeOpenGL();
}

RamaEngine::~RamaEngine() {
    delete rootNode;
    cameras . clear();
    lights . clear();
    sceneNodes . clear();
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
	GLuint programID = glCreateProgram();
	glAttachShader(programID, s->getShaderID());
	glAttachShader(programID, s2->getShaderID());
	glLinkProgram(programID);

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