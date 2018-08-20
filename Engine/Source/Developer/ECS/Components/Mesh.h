#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../Graphics/VertexArray.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/shader.h"
#include "../../Graphics/texture.h"

#include "EASTL/vector.h"

#include <GLFW/glfw3.h>

namespace Skel
{
	struct TextureMesh {
		unsigned int id;
		std::string type;
		aiString path;
	};

	class SKEL_API Mesh
	{
	public:
		/*Mesh Data*/
		EAVector<Vertices> vertices;
		EAVector<unsigned int> indices;
		EAVector<TextureMesh> textures;

		Mesh(EAVector<Vertices> vertices, EAVector<unsigned int> indices, EAVector<TextureMesh> texture);
		~Mesh();
		void Draw(Shader* shader);
	private:
		unsigned int VAO, VBO;
		VertexArray m_vao = VertexArray();
		VertexBuffer m_vbo;
		void setupMesh();
	};

}