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
    //Back face culling
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT, GL_FILL);

    // Create vertexArray
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

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
    registerCamera(rec);
    return rec;
}

RECamera* RamaEngine::createRECamera(RESceneNode* layer) {
    RECamera* rec = new RECamera(layer -> getSceneNode());
    registerCamera(rec);
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

void RamaEngine::registerCamera(RECamera* rec) {
    cameras . push_back(rec);
}

void RamaEngine::registerLight(TNode* lightNode) {
    lights . push_back(lightNode);
}

void RamaEngine::registerSceneNode(TNode* sceneNode) {
    sceneNodes . push_back(sceneNode);
}