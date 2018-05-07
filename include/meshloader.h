#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class MeshLoader {

    public:
        MeshLoader();
        ~MeshLoader();

        std::vector<Mesh*> loadMeshes(const std::string &fileName);

    private:
        std::vector<Mesh*> meshes;

        void readMeshTree(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);
        unsigned int loadTexture(const char* fileName);

};

#endif // MESHLOADER_H