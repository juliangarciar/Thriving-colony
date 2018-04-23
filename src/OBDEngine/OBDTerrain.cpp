/*#include "OBDTerrain.h"

OBDTerrain::OBDTerrain(ResourceIMG *img){
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    terrain = new ParseTerrain(256, 256, 1); // ToDo
    terrain ->generateMeshFromBuffer(img->getResource(), img->getWidth(), img->getHeight(), img->getChannels());

    std::vector<f32> vbo;
    f32 max_y = 0.f;

    int w = terrain->getTerrainWidth();
    int h = terrain->getTerrainHeight();

    for (int x = 0; x < w; x++) {
            vbo.push_back(x);
            vbo.push_back(y);
            vbo.push_back(z);
            vbo.push_back(0);
            vbo.push_back(1);
            vbo.push_back(0);
            vbo.push_back(x/w);
            vbo.push_back(z/h);

            if (y > max_y) max_y = y; 
        }
    }

    ResourceMesh tempMesh;
    tempMesh.boundingBox.min = glm::vec3(0,0,0);
    tempMesh.boundingBox.max = glm::vec3(w, maxy, h);
    tempMesh.boundingBox.size = glm::vec3(w, maxy, h);
    tempMesh.boundingBox.center = glm::vec3(w/2, maxy/2, h/2);
    
    tempMesh.name = "terrain";
    tempMesh.vbo = vbo;
    tempMesh.indices = indices;

    ResourceMaterial material;


    //terrainNode = new TNode(new TMesh(m, mat), scaleNode);
}

OBDTerrain::OBDTerrain(OBDSceneNode* parent, ResourceIMG *img){
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    //terrainNode = new TNode(new TMesh(m, mat), scaleNode);

    parent->addChild(this);
}

OBDTerrain::~OBDTerrain() {
    delete rotationNode;
    rotationNode = nullptr;
}

void generateTerrain(i32 w, i32 h, i32 c, unsigned char *img){

    


    // ToDo: smoothing
    /*for (s32 run = 0; run < smoothFactor; ++run) {
        s32 yd = TerrainData.Size;
        for (s32 y = 1; y < TerrainData.Size - 1; ++y)
        {
            for (s32 x = 1; x < TerrainData.Size - 1; ++x)
            {
                mb->getVertexBuffer()[x + yd].Pos.Y =
                    (mb->getVertexBuffer()[x-1 + yd].Pos.Y + //left
                    mb->getVertexBuffer()[x+1 + yd].Pos.Y + //right
                    mb->getVertexBuffer()[x + yd - TerrainData.Size].Pos.Y + //above
                    mb->getVertexBuffer()[x + yd + TerrainData.Size].Pos.Y) * 0.25f; //below
            }
            yd += TerrainData.Size;
        }
    }*/


/*

	const f32 tdSize = 1.0f/(f32)(w-1);
    float fx=0.f;
    

    std::vector<us32> indices;
    //ToDo: indices
}

void OBDTerrain::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
    node_position += glm::vec3(tX, tY, tZ);
}

void OBDTerrain::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
    node_rotation += glm::vec3(rX, rY, rZ);
}

void OBDTerrain::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
    node_scale += glm::vec3(sX, sY, sZ);
}

void OBDTerrain::setPosition(glm::vec3 p) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    glm::vec3 o = node_position - p;
    t -> translate(o.x, o.y, o.z);
    node_position = p;
}

void OBDTerrain::setRotation(glm::vec3 r, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    glm::vec3 o = node_rotation - r;
    t -> rotate(o.x, o.y, o.z, angle);
    node_rotation = r;
}

void OBDTerrain::setScale(glm::vec3 s) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    glm::vec3 o = node_scale - s;
    t -> scale(o.x, o.y, o.z);
    node_scale = s;
}

void OBDTerrain::setActive(bool a) {
    terrainNode -> setActive(a);
}

bool OBDTerrain::getActive() {
    return terrainNode -> getActive();
}*/