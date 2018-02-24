#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


#include "opengl/shader.h"
#include "mesh.h"
#include "opengl/stb_image.h"

namespace Skel { namespace graphics {

	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

	class Model
	{
	public:
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<TextureMesh> textures_loaded;
		bool gammaCorrection;

		Model(const char* path)
		{
			loadModel(path);
		}
		~Model();
		void Draw(Shader* shader);
	private:
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}}


