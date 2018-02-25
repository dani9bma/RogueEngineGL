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

#include "opengl/vertex_array.h"
#include "opengl/vertex_buffer.h"
#include "opengl/index_buffer.h"
#include "opengl/shader.h"
#include "opengl/texture.h"

#include <GLFW/glfw3.h>

namespace Skel { namespace graphics {

	struct TextureMesh {
		unsigned int id;
		std::string type;
		aiString path;
	};

	class Mesh
	{
	public:
		/*Mesh Data*/
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<TextureMesh> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureMesh> texture);
		~Mesh();
		void Draw(Shader* shader);
	private:
		unsigned int VAO, VBO, EBO;
		VertexArray m_vao = VertexArray();
		VertexBuffer m_vbo;
		void setupMesh();
	};
}}

