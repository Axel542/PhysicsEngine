#include "Box.h"
#include <Gizmos.h>
#include <glm\glm.hpp>

Box::Box() :
	Rigidbody(BOX, DEFAULT_POSITION, DEFAULT_VELOCITY, 0,
				DEFAULT_MASS)
{
	m_extenseX = 1;
	m_extenseY = 1;
}

Box::Box(glm::vec2 position, glm::vec2 velocity,
	float mass, const float extenseX,
	const float extenseY, const glm::vec4 RGBAValues) :
	Rigidbody(BOX, position, velocity, 0.0f, mass)
	, m_extenseX(extenseX)
	, m_extenseY(extenseY)
	, m_colour(RGBAValues)
{
	m_extenseX = extenseX;
	m_extenseY = extenseY;
}

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 extenseX, glm::vec2 extenseY,
	glm::vec4 RGBAValues) :
	Rigidbody(BOX, position, velocity, 0.0f, mass)
	, m_extenseX()
	, m_extenseY()
	, m_colour(RGBAValues)
{
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	if (isFilled)
	{
		Gizmos::add2DAABBFilled(m_position, getExtense(), m_colour);
	}
	else
	{
		Gizmos::add2DAABB(m_position, getExtense(), m_colour);
	}

}

//sets the extense of the box.
void Box::setExtense(glm::vec2 extense)
{
	m_extenseX = extense.x;
	m_extenseY = extense.y;
}

//sets colour of box.
void Box::setColour(glm::vec4 RGBAValues)
{
	m_colour = RGBAValues;
}

//Identical to resolve collision but with the
//ability to plug the normal into the constructor.
void Box::resolveCollisionBox(Rigidbody * actor2, glm::vec2 a_normal)
{
	glm::vec2 normal = a_normal;
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;


	float j = glm::dot(-(1 + m_elasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;


	applyForceToActor(actor2, force);
}
