#pragma once
#include "PhysicsObject.h"
#include <glm\vec2.hpp>
#include <vector>
#include <list>
#include "Rigidbody.h"
#include <iostream>
#include "Plane.h"

class PhysicsScene
{
private:
	struct CollisionData
	{
		bool wasCollision;
		glm::vec2  normal;
		float     overlap;
		glm::vec2 contactpoint;
	};
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void debugScene();

	void checkForCollision();

	static bool plane2Sphere(PhysicsObject*,PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*,PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*,PhysicsObject*);
	static bool aabb2AABB(PhysicsObject*, PhysicsObject*);
	static bool aabb2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2AABB(PhysicsObject*, PhysicsObject*);
	static bool aabb2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2AABB(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
	
	
};

