#include "RamaEngine.h"

#include "Graphics/TRoot.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceGLSL.h"

RamaEngine::RamaEngine() {
    rootNode = new TNode();

    // Create default layer
    clSceneNode = new RESceneNode(rootNode);
    defaultSceneNode = new RESceneNode(rootNode);

    // Resource Manager
    REManager = new ResourceManager();
}

RamaEngine::~RamaEngine() {
    delete rootNode;

    // defaultSceneNode
    // REManager

    //ToDo: recorrer vaciando
    cameras . clear();
    lights . clear();
    
	glDeleteProgram(programID);
}

void RamaEngine::Init() {
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
}

void RamaEngine::End(){
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
}

RELight* RamaEngine::createLight() {
    RELight* lightNode = new RELight(clSceneNode->getSceneNode());
    lights . push_back(lightNode);
    return lightNode;
}

RECamera* RamaEngine::createCamera() {
    RECamera* cameraNode = new RECamera(clSceneNode->getSceneNode());
    cameras . push_back(cameraNode);
    return cameraNode;
}

RESceneNode* RamaEngine::createSceneNode() {
    return new RESceneNode(defaultSceneNode);
}

RESceneNode* RamaEngine::createSceneNode(RESceneNode* layer) {
    return new RESceneNode(layer);
}

REMesh* RamaEngine::createMesh(std::string mesh) {
    return new REMesh(defaultSceneNode, (ResourceOBJ*)REManager->getResource(mesh, true));
}

REMesh* RamaEngine::createMesh(RESceneNode* layer, std::string mesh) {
    return new REMesh(layer, (ResourceOBJ*)REManager->getResource(mesh, true));
}

REAnimation* RamaEngine::createAnimation(std::string anim) {
    //ToDo
    return new REAnimation(defaultSceneNode);
}

REAnimation* RamaEngine::createAnimation(RESceneNode* layer, std::string anim) {
    //ToDo
    return new REAnimation(layer);
}

REShaderProgram *RamaEngine::createShaderProgram(std::string programName, std::string vs, std::string fs){
	ResourceGLSL *s1 = (ResourceGLSL*)REManager->getResource(vs, true);
	ResourceGLSL *s2 = (ResourceGLSL*)REManager->getResource(fs, true);
	REShaderProgram *p = new REShaderProgram(s1, s2);
    shaderPrograms . insert(std::pair<std::string, REShaderProgram*>(programName, p));
    return p;
}

void RamaEngine::registerLight(RELight* lightNode) {
    clSceneNode -> getSceneNode() -> addChild(lightNode -> getLightNode());
    lights . push_back(lightNode);
}

void RamaEngine::registerCamera(RECamera* cameraNode) {
    clSceneNode -> getSceneNode() -> addChild(cameraNode -> getCameraNode());
    cameras . push_back(cameraNode);
}

void RamaEngine::registerShaderProgram(std::string programName, REShaderProgram *r){
    shaderPrograms . insert(std::pair<std::string, REShaderProgram*>(programName, r));
}

void RamaEngine::setCurrentShaderProgram(std::string programName){
    std::map<std::string, REShaderProgram*>::iterator it;
    it = shaderPrograms.find(programName);
    if (it != shaderPrograms.end()){
        currentProgram = it->second;
        rootNode -> setEntity(currentProgram->getRootEntity());
    }
}

void RamaEngine::draw() {
    glUseProgram(currentProgram->getShaderProgram());

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