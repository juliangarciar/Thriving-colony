#include "OBDEngine.h"

#include "Graphics/TRoot.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceGLSL.h"

OBDEngine::OBDEngine() {
    rootNode = new TNode();

    // Create default layer
    clSceneNode = new OBDESceneNode(rootNode);
    defaultSceneNode = new OBDESceneNode(rootNode);

    // Resource Manager
    REManager = new ResourceManager();

    // Cache
    matrixCache = TMatrixCache::Instance();
}

OBDEngine::~OBDEngine() {
    //ToDo: recorrer vaciando
    cameras . clear();
    lights . clear();

    // delete defaultSceneNode
    // delete REManager

    delete rootNode;
}

void OBDEngine::Init() {
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

void OBDEngine::End(){
	glDeleteVertexArrays(1, &vertexArrayID);
}

OBDELight* OBDEngine::createLight(OBDEColor color, u32 intensity) {
    OBDELight* lightNode = new OBDELight(clSceneNode->getSceneNode(), color, intensity);
    lights . push_back(lightNode);
    return lightNode;
}

OBDECamera* OBDEngine::createCamera() {
    OBDECamera* cameraNode = new OBDECamera(clSceneNode->getSceneNode());
    cameras . push_back(cameraNode);
    return cameraNode;
}

OBDESceneNode* OBDEngine::createSceneNode() {
    return new OBDESceneNode(defaultSceneNode);
}

OBDESceneNode* OBDEngine::createSceneNode(OBDESceneNode* layer) {
    return new OBDESceneNode(layer);
}

OBDEMesh* OBDEngine::createMesh(std::string mesh) {
    ResourceOBJ *obj = (ResourceOBJ*)REManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)REManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDEMesh *tempMesh = new OBDEMesh(defaultSceneNode, obj, mtl);
    //ToDo: texture AutoLoad
    return tempMesh;
}

OBDEMesh* OBDEngine::createMesh(OBDESceneNode* layer, std::string mesh) {
    ResourceOBJ *obj = (ResourceOBJ*)REManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)REManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDEMesh *tempMesh = new OBDEMesh(layer, obj, mtl);
    //ToDo: texture AutoLoad
    return tempMesh;
}

OBDEAnimation* OBDEngine::createAnimation(std::string anim) {
    //ToDo
    return new OBDEAnimation(defaultSceneNode);
}

OBDEAnimation* OBDEngine::createAnimation(OBDESceneNode* layer, std::string anim) {
    //ToDo
    return new OBDEAnimation(layer);
}

OBDEShaderProgram *OBDEngine::createShaderProgram(std::string programName, std::string vs, std::string fs){
	ResourceGLSL *s1 = (ResourceGLSL*)REManager->getResource(vs, true);
	ResourceGLSL *s2 = (ResourceGLSL*)REManager->getResource(fs, true);
	OBDEShaderProgram *p = new OBDEShaderProgram(s1, s2);
    shaderPrograms . insert(std::pair<std::string, OBDEShaderProgram*>(programName, p));
    return p;
}

void OBDEngine::registerLight(OBDELight* lightNode) {
    clSceneNode -> getSceneNode() -> addChild(lightNode -> getLightNode());
    lights . push_back(lightNode);
}

void OBDEngine::registerCamera(OBDECamera* cameraNode) {
    clSceneNode -> getSceneNode() -> addChild(cameraNode -> getCameraNode());
    cameras . push_back(cameraNode);
}

void OBDEngine::registerShaderProgram(std::string programName, OBDEShaderProgram *r){
    shaderPrograms . insert(std::pair<std::string, OBDEShaderProgram*>(programName, r));
}

void OBDEngine::setCurrentShaderProgram(std::string programName){
    std::map<std::string, OBDEShaderProgram*>::iterator it;
    it = shaderPrograms.find(programName);
    if (it != shaderPrograms.end()){
        currentProgram = it->second;
        rootNode -> setEntity(currentProgram->getRootEntity());
    }
}

void OBDEngine::draw() {
    glUseProgram(currentProgram->getShaderProgram());

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our tree
    rootNode -> draw();
}

TNode* OBDEngine::getRootNode() {
    return rootNode;
}

OBDESceneNode* OBDEngine::getDefaultLayer() {
    return defaultSceneNode;
}