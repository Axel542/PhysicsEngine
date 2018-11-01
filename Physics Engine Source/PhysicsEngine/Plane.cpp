#include "Plane.h"
#include <iostream>


Plane::Plane() : Rigidbody(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
	m_elasticity = 1;
	m_velocity = glm::vec2(0, 0);
}

Plane::Plane(glm::vec2 normal, float distance)  :
	Rigidbody(ShapeType::PLANE)
	
{
	m_velocity = glm::vec2(0, 0);
	m_shapeID = ShapeType::PLANE;
	m_normal = normal;
	m_distanceToOrigin = distance;
}


Plane::~Plane()
{

}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{

}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	//easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	Gizmos::add2DLine(start, end, colour);

}

void Plane::resetPosition()
{
	m_normal = glm::vec2(0, 0);
}

void Plane::setNormal(glm::vec2 normal)
{
	m_normal = normal;
}

void Plane::setDistance(float distance)
{
	m_distanceToOrigin = distance;
}

void Plane::resolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float jTop = -(1 + actor2->getElasticity())
		* glm::dot(relativeVelocity, m_normal);

	float j = glm::dot(- (1 + actor2->getElasticity()) * 
		(relativeVelocity),	m_normal) /
		(1 / actor2->getMass());

	
	
	float newj = jTop / (1 / actor2->getMass());

	glm::vec2 force = m_normal *j;

	actor2->applyForce(force);
}
