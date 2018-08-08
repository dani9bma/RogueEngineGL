#include "DirectionalLight.h"

namespace Skel
{
	DirectionalLight::DirectionalLight(Shader* shader, Camera* camera)
		: m_shader(shader), m_camera(camera)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::update()
	{
		m_shader->enable();
		m_shader->setUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		m_shader->setUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		m_shader->setUniform3f("lightPos", m_direction);
		m_shader->setUniform3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		m_shader->setUniform1i("material.diffuse", 0);
		m_shader->setUniform1i("material.specular", 1);
		m_shader->setUniform1f("material.shininess", 32.0f);
		m_shader->setUniform3f("light.direction", m_direction);
		//m_shader->setUniform1f("light.constant", 1.0f);
		//m_shader->setUniform1f("light.linear", 0.09f);
		//m_shader->setUniform1f("light.quadratic", 0.0002f);
		m_shader->setUniform3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_shader->setUniform3f("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f)); // darken the light a bit to fit the scene
		m_shader->setUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_shader->setUniform3f("viewPos", m_camera->getPosition());
		m_shader->disable();
	}

	void DirectionalLight::setLightDirection(glm::vec3 direction)
	{
		m_direction = direction;
	}

	void DirectionalLight::setIntensity(float value)
	{
		m_intensity = glm::vec3(value, value, value);
	}
}