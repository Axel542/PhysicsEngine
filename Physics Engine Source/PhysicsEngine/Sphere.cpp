#include "Sphere.h"


Sphere::Sphere()
{

}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) :
	Rigidbody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

//Sphere::Sphere(glm::vec2 position, float inclination, float speed, int segments, float radius, glm::vec4 colour) :
//	Rigidbody(SPHERE, position, velocity, 0, mass)
//{
//
//}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);

}

void Sphere::setPosition(glm::vec2 newPos)
{
	m_position = newPos;
}

void Sphere::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}
