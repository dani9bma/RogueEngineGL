#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "opengl/shader.h"
#include <GLFW/glfw3.h>

namespace Skel { namespace graphics {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

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
		void setupMesh();
	};
}}
#endif

