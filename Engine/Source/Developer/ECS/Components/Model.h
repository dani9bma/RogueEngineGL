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


#include "../../Graphics/shader.h"
#include "mesh.h"
#include "../../Graphics/stb_image.h"
#include "../../Utils/Log.h"

namespace Skel
{
	class SKEL_API Model
	{
	public:
		EAVector<Mesh> meshes;
		SKString directory;
		EAVector<TextureMesh> textures_loaded;
		bool gammaCorrection;

		Model(SKString path)
		{
			loadModel(path);
		}
		~Model();
		void Draw(Shader* shader);
	private:
		void loadModel(SKString path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		EAVector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, SKString typeName);
	};
}