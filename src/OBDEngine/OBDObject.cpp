OBDMesh::OBDMesh(ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    std::map<std::string, ResourceMesh> submeshes = obj->getResource();
    std::map<std::string, ResourceMaterial> submats = mtl->getResource();

    for (std::map<std::string, ResourceMesh>::iterator it = submeshes.begin(); it != submeshes.end(); ++it) {
        std::map<std::string, ResourceMaterial>::iterator it2;
        it2 = submats.find(it->second.defaultMaterialName);
        if (it2 == submats.end()){
            std::cout << "No existe material " << it->second.defaultMaterialName << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        TMesh *tempMesh = new TMesh(it->second, it2->second);

        meshes.insert(std::pair<std::string, TMesh*>(it->second.name, tempMesh));
    }

    //ToDo: un nodo para cada submesh
    meshNode = new TNode(meshes.begin()->second, scaleNode);
}

OBDMesh::OBDMesh(OBDSceneNode* parent, ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    parent->addChild(this);

    std::map<std::string, ResourceMesh> submeshes = obj->getResource();
    std::map<std::string, ResourceMaterial> submats = mtl->getResource();

    for (std::map<std::string, ResourceMesh>::iterator it = submeshes.begin(); it != submeshes.end(); ++it) {
        std::map<std::string, ResourceMaterial>::iterator it2;
        it2 = submats.find(it->second.defaultMaterialName);
        if (it2 == submats.end()){
            std::cout << "No existe material " << it->second.defaultMaterialName << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        TMesh *tempMesh = new TMesh(it->second, it2->second);

        meshes.insert(std::pair<std::string, TMesh*>(it->second.name, tempMesh));
    }

    //ToDo: un nodo para cada submesh
    meshNode = new TNode(meshes.begin()->second, scaleNode);
}


u32 OBDMesh::getMeshAmount(){
    return meshes.size();
}

TMesh *OBDMesh::getShape(std::string meshName){
    return meshes[meshName];
}

std::map<std::string, TMesh*> OBDMesh::getMeshes(){
    return meshes;
}
