#include "OBDEngine.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceGLSL.h"

TCache TEntity::cache = TCache();

OBDEngine::OBDEngine() {
    rootNode = new TNode();

    // Create default layers
    clSceneNode = new OBDSceneNode(rootNode);
    defaultSceneNode = new OBDSceneNode(rootNode);

    // Resource Manager
    OBDManager = new ResourceManager();
}

OBDEngine::~OBDEngine() {
    //ToDo: revisar destructor
    cameras.clear();
    lights.clear();

    delete rootNode;
}

void OBDEngine::Init(i32 sW, i32 sH) {
    windowWidth = sW;
    windowHeight = sH;

	// Viewport
	viewport = glm::vec4(0.0f, 0.0f, windowWidth, windowHeight);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Enable textures
	glEnable(GL_TEXTURE_2D);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

    //Backface culling
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT, GL_FILL);
	
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	//Gen VAO
    GLuint VAO = TEntity::cache.getID(OBDEnums::OpenGLIDs::VAO_BUFFER);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void OBDEngine::End(){
    GLuint VAO = TEntity::cache.getID(OBDEnums::OpenGLIDs::VAO_BUFFER);
	glDeleteVertexArrays(1, &VAO);
}

void OBDEngine::draw() {
    glUseProgram(currentProgram->getShaderProgram());

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw our tree
    rootNode -> draw();

    // Clear light cache
    TEntity::cache.getLights()->clear();
}

OBDLight* OBDEngine::createLight(OBDColor color, f32 intensity, f32 ambient, f32 attenuation) {
    OBDLight* lightNode = new OBDLight(clSceneNode, color, intensity, ambient, attenuation);
    lights.push_back(lightNode);
    return lightNode;
}

OBDCamera* OBDEngine::createCamera(f32 far, f32 fov) {
    OBDCamera* cameraNode = new OBDCamera(clSceneNode, windowWidth, windowHeight, far, fov);
    cameras.push_back(cameraNode);
    return cameraNode;
}

OBDSceneNode* OBDEngine::createSceneNode() {
    return new OBDSceneNode(defaultSceneNode);
}

OBDSceneNode* OBDEngine::createSceneNode(OBDSceneNode* layer) {
    return new OBDSceneNode(layer);
}

OBDObject* OBDEngine::createObject(u32 id, std::string mesh, bool autoload) {
    ResourceOBJ *obj = (ResourceOBJ*)OBDManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)OBDManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDObject *tempObject = new OBDObject(defaultSceneNode, id, obj, mtl);
	if (autoload) {
		for (std::map<std::string, OBDMaterial*>::iterator it = tempObject->getMaterials().begin(); it != tempObject->getMaterials().end(); ++it){
			it->second->loadTextures(mtl, OBDManager, true);
		}
	}
    return tempObject;
}

OBDObject* OBDEngine::createObject(OBDSceneNode* layer, u32 id, std::string mesh, bool autoload) {
    ResourceOBJ *obj = (ResourceOBJ*)OBDManager->getResource(mesh, true);
    ResourceMTL *mtl = (ResourceMTL*)OBDManager->getResource(obj->getDefaultMaterialPath(), true);
    OBDObject *tempObject = new OBDObject(layer, id, obj, mtl);
	if (autoload) {
		for (std::map<std::string, OBDMaterial*>::iterator it = tempObject->getMaterials().begin(); it != tempObject->getMaterials().end(); ++it){
			it->second->loadTextures(mtl, OBDManager, true);
		}
	}
    return tempObject;
}

OBDShaderProgram *OBDEngine::createShaderProgram(std::string programName, std::string vs, std::string fs){
	ResourceGLSL *s1 = (ResourceGLSL*)OBDManager->getResource(vs, true);
	ResourceGLSL *s2 = (ResourceGLSL*)OBDManager->getResource(fs, true);
	OBDShaderProgram *p = new OBDShaderProgram(s1, s2);
    shaderPrograms.insert(std::pair<std::string, OBDShaderProgram*>(programName, p));
    return p;
}

OBDTerrain *OBDEngine::createTerrain(std::string heightMap, f32 y_offset, f32 y_scale, i32 step){
	return new OBDTerrain(defaultSceneNode, heightMap, y_offset, y_scale, step);
}

OBDTerrain *OBDEngine::createTerrain(OBDSceneNode* layer, std::string heightMap, f32 y_offset, f32 y_scale, i32 step){
	return new OBDTerrain(layer, heightMap, y_offset, y_scale, step);
}

OBDTexture *OBDEngine::createTexture(OBDEnums::TextureTypes t, std::string fs){
	ResourceIMG *s = (ResourceIMG*)OBDManager->getResource(fs, true);
	return new OBDTexture(t, s);
}

OBDMaterial *OBDEngine::createMaterial(){
	return new OBDMaterial();
}

OBDMaterial *OBDEngine::createMaterial(std::string path, std::string name){
	ResourceMTL *s = (ResourceMTL*)OBDManager->getResource(path, true);
	return new OBDMaterial(s, name);
}

void OBDEngine::registerLight(OBDLight* lightNode) {
    lights.push_back(lightNode);
}

void OBDEngine::registerCamera(OBDCamera* cameraNode) {
    cameras.push_back(cameraNode);
}

void OBDEngine::registerShaderProgram(std::string programName, OBDShaderProgram *r){
    shaderPrograms.insert(std::pair<std::string, OBDShaderProgram*>(programName, r));
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

void OBDEngine::setWindowSize(i32 w, i32 h){
	windowWidth = w;
	windowHeight = h;
	viewport = glm::vec4(0.0f, 0.0f, windowWidth, windowHeight);
}

void OBDEngine::setClearColor(OBDColor c) {
	glClearColor(c.r, c.g, c.b, c.a);
}

glm::vec3 OBDEngine::getWorldCoordinatesFromScreen(glm::vec3 screen){
    screen.y = windowHeight - screen.y; //Invert y
    return glm::unProject(screen, *TEntity::cache.getViewMatrix(), *TEntity::cache.getProjectionMatrix(), viewport);
}
 
glm::vec3 OBDEngine::getScreenCoordinatesFromWorld(glm::vec3 world){
    return glm::project(world, *TEntity::cache.getViewMatrix(), *TEntity::cache.getProjectionMatrix(), viewport);
}

OBDLine OBDEngine::getRaycastFromScreenCoordinates(glm::vec2 screen){
    OBDLine l;
    l.start = getWorldCoordinatesFromScreen(glm::vec3(screen.x, screen.y, 0));
    l.end = getWorldCoordinatesFromScreen(glm::vec3(screen.x, screen.y, 1));
    return l;
}

TNode* OBDEngine::getRootNode() {
    return rootNode;
}

OBDSceneNode* OBDEngine::getDefaultLayer() {
    return defaultSceneNode;
}

ResourceManager *OBDEngine::getResourceManager(){
	return OBDManager;
}

//////SANDBOX//////

OBDAnimation* OBDEngine::createAnimation(std::string anim) {
    //ToDo: hacer animaciones
    return new OBDAnimation(defaultSceneNode);
}

OBDAnimation* OBDEngine::createAnimation(OBDSceneNode* layer, std::string anim) {
    //ToDo: hacer animaciones
    return new OBDAnimation(layer);
}

OBDBillboard* OBDEngine::createBillboard(OBDSceneNode* layer, glm::vec3 pos) {
    OBDBillboard* billboard = new OBDBillboard(layer, pos, currentProgram -> getShaderProgram());
    return billboard;
}

OBDTile* OBDEngine::createTile(ResourceIMG* _texture, glm::vec2 _position){
    OBDTile* tmp = new OBDTile(defaultSceneNode, _texture, _position);
    return tmp;
}

OBDSkybox* OBDEngine::createSkybox(TTexture* texture) {
    OBDSkybox* skybox = new OBDSkybox(texture);
    defaultSceneNode -> addChild(skybox);
    return skybox;
}

/////////////////