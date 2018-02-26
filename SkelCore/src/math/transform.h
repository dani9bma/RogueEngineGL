/*
 * @module Maths
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphics/opengl/shader.h"

namespace Skel { namespace maths {

	class Transform
	{
	private:
		glm::mat4 m_transform;

		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec3 m_rotation;
		float m_angle;

		graphics::Shader* m_shader;
	public:
		Transform();
		Transform(graphics::Shader* shader);
		/*
		* angle in degrees
		*/
		glm::mat4 setRotation(float angle, bool x = true, bool y = true, bool z = true);
		glm::mat4 setPosition(float x, float y, float z);
		glm::mat4 setSize(float x, float y, float z);
		glm::mat4 setTransform(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle);

		inline glm::mat4& getTransformMatrice() { return m_transform; }
	};

} }