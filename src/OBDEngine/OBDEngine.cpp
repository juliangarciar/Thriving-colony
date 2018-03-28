#include "OBDEngine.h"

#include <GL/glew.h>

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceGLSL.h"

TCache TEntity::cache = TCache();

OBDEngine::OBDEngine() {
    rootNode = new TNode();

    // Create default layer
    clSceneNode = new OBDSceneNode(rootNode);
    defaultSceneNode = new OBDSceneNode(rootNode);

    // Resource Manager
    OBDManager = new ResourceManager();
}

OBDEngine::~OBDEngine() {
    //ToDo: recorrer vaciando
    cameras . clear();
    lights . clear();

    // delete defaultSceneNode
    // delete OBDManager

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

    // Enable textures
	glEnable(GL_TEXTURE_2D);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
    //Back face culling
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    GLuint VAO = TEntity::cache.getID(OBDEnums::OpenGLIDs::VAO_BUFFER);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void OBDEngine::End(){
    GLuint VAO = TEntity::cache.getID(OBDEnums::OpenGLIDs::VAO_BUFFER);
	glDeleteVertexArrays(1, &VAO);
}

OBDLight* OBDEngine::createLight(OBDColor color, u32 intensity) {
    OBDLight* lightNode = new OBDLight(clSceneNode->getSceneNode(), color, intensity);
    lights . push_back(lightNode);
    return lightNode;
}

OBDCamera* OBDEngine::createCamera() {
    OBDCamera* cameraNode = new OBDCamera(clSceneNode->getSceneNode());
    cameras . push_back(cameraNode);
    return cameraNode;
}

OBDSceneNode* OBDEngine::createSceneNode() {
    return new OBDSceneNode(defaultSceneNode);
}

OBDSceneNode* OBDEngine::createSceneNode(OBDSceneNode* layer) {
    return new OBDSceneNode(layer);
}

OBDMesh* OBDEngine::createMesh(std::string mesh) {
    ResourceOBJ *obj = (ResourceOBJ*)OBDManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)OBDManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDMesh *tempMesh = new OBDMesh(defaultSceneNode, obj, mtl);
    //ToDo: texture AutoLoad
    return tempMesh;
}

OBDMesh* OBDEngine::createMesh(OBDSceneNode* layer, std::string mesh) {
    ResourceOBJ *obj = (ResourceOBJ*)OBDManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)OBDManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDMesh *tempMesh = new OBDMesh(layer, obj, mtl);
    //ToDo: texture AutoLoad
    return tempMesh;
}

OBDAnimation* OBDEngine::createAnimation(std::string anim) {
    //ToDo
    return new OBDAnimation(defaultSceneNode);
}

OBDAnimation* OBDEngine::createAnimation(OBDSceneNode* layer, std::string anim) {
    //ToDo
    return new OBDAnimation(layer);
}

OBDShaderProgram *OBDEngine::createShaderProgram(std::string programName, std::string vs, std::string fs){
	ResourceGLSL *s1 = (ResourceGLSL*)OBDManager->getResource(vs, true);
	ResourceGLSL *s2 = (ResourceGLSL*)OBDManager->getResource(fs, true);
	OBDShaderProgram *p = new OBDShaderProgram(s1, s2);
    shaderPrograms . insert(std::pair<std::string, OBDShaderProgram*>(programName, p));
    return p;
}

void OBDEngine::registerLight(OBDLight* lightNode) {
    clSceneNode -> getSceneNode() -> addChild(lightNode -> getLightNode());
    lights . push_back(lightNode);
}

void OBDEngine::registerCamera(OBDCamera* cameraNode) {
    clSceneNode -> getSceneNode() -> addChild(cameraNode -> getCameraNode());
    cameras . push_back(cameraNode);
}

void OBDEngine::registerShaderProgram(std::string programName, OBDShaderProgram *r){
    shaderPrograms . insert(std::pair<std::string, OBDShaderProgram*>(programName, r));
}

void OBDEngine::setCurrentShaderProgram(std::string programName){
    std::map<std::string, OBDShaderProgram*>::iterator it;
    it = shaderPrograms.find(programName);
    if (it != shaderPrograms.end()){
        currentProgram = it->second;
        TEntity::cache.setAllIDs(currentProgram -> getParamIDs());
        TEntity::cache.setID(OBDEnums::OpenGLIDs::CURRENT_PROGRAM_ID, currentProgram -> getShaderProgram());
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

OBDSceneNode* OBDEngine::getDefaultLayer() {
    return defaultSceneNode;
}