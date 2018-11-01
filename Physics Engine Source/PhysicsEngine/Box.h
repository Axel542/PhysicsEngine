#pragma once
#include "Rigidbody.h"
#include "PhysicsObject.h"
#include <Gizmos.h>

using namespace aie;
//Child of Rigidbody.
class Box : public Rigidbody
{
public:
	//Constructors and Destructors.
	Box();
	Box(glm::vec2 position, glm::vec2 velocity,
		float mass,const float extenseX,
		const float extenseY,
		const glm::vec4 RGBAValues);
	Box(glm::vec2 position, glm::vec2 velocity,
		float mass, glm::vec2 extenseX, glm::vec2 extenseY,
		glm::vec4 RGBAValues);
	~Box();

	//Makes the shape using the gizmos.
	void makeGizmo( );
	//virtual bool checkCollision(PhysicsObject* other) override;

	//Gets the x and y extenses.
	const float getExtenseX() const { return m_extenseX; }
	const float getExtenseY() const { return m_extenseY; }

	//Sets and gets both extenses
	void setExtense(glm::vec2 extense);
	const glm::vec2 getExtense() const { return{ m_extenseX, m_extenseY }; }
	//Sets and gets colour
	void setColour(glm::vec4 RGBAValues);
	const glm::vec4 getColour() const { return m_colour; }
	
	//Sets and checks whether the shape is filled.
	bool getFilled() { return isFilled; }
	void setFilled(bool filled) { isFilled = filled; }
	
	//Sets where the box can rotate or not.
	void setOOBB(bool oobb) { isOOBB = oobb; }

	//Resolves the collisions slightly differently.
	//then the basic function.
	void resolveCollisionBox(Rigidbody* actor2, glm::vec2 normal);

protected:
	//Protected variables.

	glm::vec4 m_colour = { 0,1,0,1 }; //Boxes colour
	float m_extenseX = 1.0f; // X extense
	float m_extenseY = 1.0f; // Y extense
	glm::vec2 DEFAULT_POSITION = { 0,0 }; //Default position variable
	glm::vec2 DEFAULT_VELOCITY = { 0,0 }; //Default velocity.
	float DEFAULT_MASS = 1.0f; // Default mass.
	bool isFilled = false; //Checks if the box is filled.
	bool isOOBB = false; //Checks if the box is able to rotate.
};

