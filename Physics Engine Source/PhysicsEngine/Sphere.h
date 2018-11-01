#pragma once
#include "Rigidbody.h"
#include <Gizmos.h>

//Child of rigidbody.
class Sphere : public Rigidbody
{
public:
	//Constructors and Deconstructor
	Sphere();
	Sphere(glm::vec2 position, glm::vec2 velocity,
		float mass, float radius, glm::vec4 colour);
	//Sphere(glm::vec2 position, float inclination, float speed, 
	//			int segments, float radius, glm::vec4 colour);

	~Sphere();

	//Draws the object.
	virtual void makeGizmo();
//	virtual bool checkCollision(PhysicsObject* pOther);

	//gets radius.
	float getRadius() { return m_radius; }
	//gets colour
	glm::vec4 getColour() { return m_colour; }

	//sets position.
	void setPosition(glm::vec2 position);
	
	//set velocity.
	void setVelocity(glm::vec2 velocity);

protected:
	//Protected variables.

	float m_radius; // Radius of the sphere.
	glm::vec4 m_colour; // Colour of the sphere.
};

