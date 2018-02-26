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
		glm::mat4 m_position;
		glm::mat4 m_size;
		glm::mat4 m_rotation;

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

		inline glm::mat4& getTransformMatrice() { return m_transform; }
	};

} }