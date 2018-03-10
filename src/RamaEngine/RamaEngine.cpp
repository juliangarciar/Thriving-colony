#include "RamaEngine.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/ResourceGLSL.h"

RamaEngine::RamaEngine() {
    rootNode = new TNode();
    // Create default layer
    defaultSceneNode = createRESceneNode();
}

RamaEngine::~RamaEngine() {
    delete rootNode;

    //ToDo: recorrer vaciando
    cameras . clear();
    lights . clear();
    
	glDeleteProgram(programID);
}

void RamaEngine::Init() {
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
    //Back face culling
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT, GL_FILL);

    // Create vertexArray
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Get a handle for our "MVP" uniform
	MVPID = glGetUniformLocation(programID, "MVP");
    projectionMatrixID = glGetUniformLocation(programID, "P");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	
	// Get a handle for our "myTextureSampler" uniform
	textureID = glGetUniformLocation(programID, "Texture");

    // Use our shader
    glUseProgram(programID);
}

RELight* RamaEngine::createRELight() {
    RELight* lightNode = new RELight(rootNode);
    lights . push_back(lightNode);
    return lightNode;
}

RECamera* RamaEngine::createRECamera() {
    RECamera* cameraNode = new RECamera(rootNode);
    cameras . push_back(cameraNode);
    return cameraNode;
}

RESceneNode* RamaEngine::createRESceneNode() {
    return new RESceneNode(rootNode);
}

RESceneNode* RamaEngine::createRESceneNode(RESceneNode* layer) {
    return new RESceneNode(layer -> getSceneNode());
}

REMesh* RamaEngine::createREMesh() {
    return new REMesh(defaultSceneNode->getSceneNode());
}

REMesh* RamaEngine::createREMesh(RESceneNode* layer) {
    return new REMesh(layer -> getSceneNode());
}

REAnimation* RamaEngine::createREAnimation() {
    return new REAnimation(defaultSceneNode->getSceneNode());
}

REAnimation* RamaEngine::createREAnimation(RESceneNode* layer) {
    return new REAnimation(layer -> getSceneNode());
}

void RamaEngine::registerLight(RELight* lightNode) {
    rootNode -> addChild(lightNode -> getLightNode());
    lights . push_back(lightNode);
}

void RamaEngine::registerCamera(RECamera* cameraNode) {
    rootNode -> addChild(cameraNode -> getCameraNode());
    cameras . push_back(cameraNode);
}

void RamaEngine::draw() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our tree
    rootNode -> draw();
}

TNode* RamaEngine::getRootNode() {
    return rootNode;
}

RESceneNode* RamaEngine::getDefaultLayer() {
    return defaultSceneNode;
}