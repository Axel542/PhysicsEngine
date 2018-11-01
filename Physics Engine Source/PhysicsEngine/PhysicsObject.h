#pragma once
#include <glm\glm.hpp>

//Enum containing all shape types.
enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX ,
	SHAPE_COUNT

};

//Base physics object class.
class PhysicsObject
{
protected:
	//Constructors.
	PhysicsObject();
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	//Virtual functions for the physics objects children to override.
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
	virtual void setVelocity(glm::vec2 velocity);

	//returns the objects shape id.
	ShapeType getShapeId() { return m_shapeID; }

protected:
	//What type of the shape am I?
	ShapeType m_shapeID;
};

