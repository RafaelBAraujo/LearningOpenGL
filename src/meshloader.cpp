#include "meshloader.h"

#include <iostream>

#include "texture.h"

MeshLoader::MeshLoader() {}

MeshLoader::~MeshLoader() {

	for(int i = 0; i < this->meshes.size(); i++) {
		delete this->meshes[i];
	}

}

void MeshLoader::readMeshTree(aiNode* node, const aiScene* scene) {

	for(int i=0;i<node->mNumMeshes;i++) {
		aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}
	
	//recursion
	for(int i=0;i<node->mNumChildren;i++)
		readMeshTree(node->mChildren[i], scene);

}

void MeshLoader::processMesh(aiMesh* mesh, const aiScene* scene) {

	std::vector<Vertex> data;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

	aiColor4D col;
	aiMaterial* mat=scene->mMaterials[mesh->mMaterialIndex];
	aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);

	for(int i = 0; i < mesh->mNumVertices; i++) {

		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoord;
		glm::vec3 color;

		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;

		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		if(mesh->mTextureCoords[0]) {
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
			texCoord.x = texCoord.y = 0.0;

		if(mesh->mColors[0]) {

			color.r = mesh->mColors[0][i].r;
			color.g = mesh->mColors[0][i].g;
			color.b = mesh->mColors[0][i].b;

		}
		else 
			color = glm::vec3(1.0, 1.0, 1.0);
		

		Vertex vertex(pos, texCoord, normal, color);
		data.push_back(vertex);

	}

	for(int i = 0; i < mesh->mNumFaces; i++) {

		aiFace face = mesh->mFaces[i];
		for(int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}

	//std::cout << "textureCount(): " << mat->GetTextureCount(aiTextureType_DIFFUSE) << '\n';
	// texture data idk what it is
	for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++)
	{
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
		
		std::string fileName(str.C_Str());
		textures.push_back(new Texture("./res/obj/Americana/textures/" + fileName));
		
	}
	// ---------------------------

	aiColor4D ambient;
	if(AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &ambient)) {
		// ambient.r ambient.g ambient.b ambient.a ...
	}

	aiColor4D diffuse;
	if(AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
		// ambient.r ambient.g ambient.b ambient.a ...
	}

	aiColor4D specular;
	if(AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &specular)) {
		// ambient.r ambient.g ambient.b ambient.a ...
	}

	float s;
	if(AI_SUCCESS == aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &s)) {
		// 4 * Ns - shininess - talvez eu deva dividir por 4. provavelmente.
	}

	

	this->meshes.push_back(new Mesh(data, indices, textures));

}

unsigned int MeshLoader::loadTexture(const char* fileName) {}

std::vector<Mesh*> MeshLoader::loadMeshes(const std::string &fileName) {

    Assimp::Importer importer;
	const aiScene* scene=importer.ReadFile(fileName.c_str(), aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if(scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "The file wasn't successfuly opened " << fileName << std::endl;
		return this->meshes; 
	}

	readMeshTree(scene->mRootNode, scene);

	return this->meshes;

}