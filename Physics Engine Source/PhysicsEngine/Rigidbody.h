#pragma once
#include "PhysicsObject.h"
#include <glm\glm.hpp>


//Child of PhysicsObject.
class Rigidbody : public PhysicsObject
{
public:
	//Standard class constructors and destructors.
	Rigidbody();
	Rigidbody(ShapeType shapeID);
	Rigidbody(ShapeType shapeID, glm::vec2 position,
			glm::vec2 velocity, float rotation, float mass);
	Rigidbody(ShapeType shapeID, glm::vec2 position);
	Rigidbody(ShapeType shapeID, glm::vec2 position,
			glm::vec2 velocity, float rotation, float mass,
			float angularVelocity, float moment);
	~Rigidbody();

	//Fixed update (used in most physics calculations as physics
	//calculations will not be effected by how much fps the game
	//is running at).
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();

	//Applies force to the rigidbody object.
	void applyForce(glm::vec2 force);

	//Applies force to two actors.
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

	//Collision response function.
	void resolveCollision(Rigidbody* actor2);

	//Function to seperate objects after a collision is dected.
	void seperateObjects(Rigidbody* rb1, Rigidbody* rb2, glm::vec2 normal, float overlap);
	
	//Getter and setters for position.
	glm::vec2 getPosition() { return m_position; }
	void setPosition(glm::vec2 position) { m_position = position; }
	
	//Getter and setter for rotation.
	float getRotation() { return m_rotation; }
	float setRotation(float a_rotation) { m_rotation = a_rotation; }

	//Getter and setter for mass.
	float getMass() { return (m_isKinematic) ? 1.0f : m_mass; }
	void setMass(float a_mass);

	//Getter and setter for velocity.
	void setVelocity(glm::vec2 velocity);
	glm::vec2 getVelocity() { return m_velocity; }


	//Getter and setter for the elasticity of the rigid body.
	void setElasticity(float elasticity) { m_elasticity = elasticity; }
	float getElasticity() { return m_elasticity; }


	//Kinematic functions sets kinematic and checks whether the rigidbody object is kinematic.
	void setKinematic(bool state) { m_isKinematic = state; }
	bool isKinematic() { return m_isKinematic; }

	//Getter and setters for linear drag.
	float getLinearDrag() { return m_linearDrag; }
	void setLinearDrag(float a_linearDrag) { m_linearDrag = a_linearDrag; }

	//Getters and setters for angular drag
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float a_angularDrag) { m_angularDrag = a_angularDrag; }

protected:
	//Protected variables.
	glm::vec2 m_position; //objects position
	glm::vec2 m_velocity; // objects velocity
	bool m_isKinematic; // is the object kinematic or not?
	float m_elasticity = 1; //elasticity variable
	float m_mass; // whats the objects mass?
	float m_rotation; // 2D so we only need a single float to represent our rotation
	float m_angularVelocity; //
	float m_moment; // The moment of inertia (the rotational equivalent of mass).
	float m_linearDrag = 0.2f;
	float m_angularDrag = 0.2f;

	float MIN_LINEAR_THRESHOLD = m_linearDrag;
	float MIN_ROTATION_THRESHOLD = m_angularDrag;
};

