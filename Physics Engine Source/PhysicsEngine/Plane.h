#pragma once
#include "PhysicsObject.h"
#include <Gizmos.h>
#include "Rigidbody.h"
using namespace aie;

//Child of rigidbody.
class Plane : public Rigidbody
{
public:
	//Constructors and destructors.
	Plane();
	Plane(glm::vec2 normal, float distance);
	~Plane();

	//Fixed Update override default fixedUpdate in rigidbody class.
	void fixedUpdate(glm::vec2 gravity, float timeStep) override;
    void debug() override {}
	
	//Virtual gizmo function to draw the gizmo.
	virtual void makeGizmo();

	//Resets the position to the origin.
	void resetPosition();

	//Getter and setter for the planes normal.
	glm::vec2 getNormal() const { return m_normal; }
	void setNormal(glm::vec2 normal);

	//Getter and setter for distance.
	float getDistance()  const{ return m_distanceToOrigin; }
	void setDistance(float distance);

	//Collision response after a collision is detected.
	void resolveCollision(Rigidbody* actor2);

protected:
	//Protected variables.
	glm::vec2 m_normal; //Plane's normal.
	float m_distanceToOrigin; //Distance of plane from the origin.
};

