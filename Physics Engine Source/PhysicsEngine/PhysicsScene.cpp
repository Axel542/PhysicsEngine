#include "PhysicsScene.h"
#include "PhysicsEngineApp.h"
#include <algorithm>
#include <cassert>

using namespace std;

//function pointer array for doing our collisions
typedef bool(*collisionFnc)(PhysicsObject*,PhysicsObject*);

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0,-9.8f))
{

}


PhysicsScene::~PhysicsScene()
{
	for (auto& actor : m_actors)
	{
		delete actor;
	}

}


static collisionFnc collisionFunctionArray[] =
{
	nullptr,	
	PhysicsScene::plane2Sphere, 
	PhysicsScene::plane2AABB,
	PhysicsScene::sphere2Plane,
	PhysicsScene::sphere2Sphere,
	PhysicsScene::sphere2AABB,
	PhysicsScene::aabb2Plane,
	PhysicsScene::aabb2Sphere,
	PhysicsScene::aabb2AABB,

};

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

	//update physics at a fixed time step

	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
		checkForCollision();
		////check for collisions (ideally you'd want to have some sort of
		////scene management in place.
		//for (auto pActor : m_actors) {
		//	for (auto pOther : m_actors) {
		//		if (pActor == pOther)
		//		{
		//			continue;
		//		}
		//		if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
		//			std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
		//		{
		//			continue;
		//		}

		//		Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
		////		if (pRigid != nullptr)
		//	//	{

		//		checkForCollision();

		//			//if (pRigid->checkCollision(pOther) == true)
		//			//{
		//			//	/*pRigid->applyForceToActor(dynamic_cast<Rigidbody*>(pOther),
		//			//		pRigid->getVelocity() * pRigid->getMass());*/
		//			//	pRigid->setVelocity(glm::vec2(0, 0));
		//			//	pOther->setVelocity(glm::vec2(0, 0));
		//			//	dirty.push_back(pRigid);
		//			//	dirty.push_back(pOther);
		//			//}
		//		}
		//	//}
		//}
		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		cout << count << " : ";
		pActor->debug();
		count++;
	}
}

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//need to check for collisions against all obvjects all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeId();
			int shapeId2 = object2->getShapeId();

			//using function pointers
			int functionIdx = (shapeId1 * ShapeType::SHAPE_COUNT) + shapeId2;
			collisionFnc collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				//did a collision occur
				bool wasCollision = collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2Sphere(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are succesful then test a collision
	if (sphere != nullptr && plane != nullptr)
	{
	/*	glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(
			sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();
	
		//if we are behind plane then we flip the normal
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() + sphereToPlane;
		if (intersection > 0)
		{
			sphere->setVelocity(glm::vec2(0, 0));

			return true;
		}
		*/

		//the distance between the spheres closest point and the plane
		float distanceBetween = glm::dot(sphere->getPosition(), plane->getNormal())
						- plane->getDistance() - sphere->getRadius();

		if (distanceBetween < 0)
		{
			plane->resolveCollision(sphere);
			return true;
		}
	}



	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject * obj1,PhysicsObject * obj2)
{
	//try to cast objects to sphere and plane
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{

	/*	glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(
			sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();

		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0) {
			
			sphere->setVelocity(glm::vec2(0, 0));

			return true;
		}
		*/

		float distanceBetween = glm::dot(sphere->getPosition(), plane->getNormal())
										- plane->getDistance() - sphere->getRadius();

		if (distanceBetween < 0)
		{
			plane->resolveCollision(sphere);

			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject * obj1, PhysicsObject * obj2)
{
	//try to cast objects to sphere and sphere
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
//	if we are successful then test for collision

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if (distance < (sphere1->getRadius() + sphere2->getRadius()))
		{
		

			sphere1->resolveCollision(sphere2);
		//	sphere2->setVelocity(glm::vec2(0, 0));

			return true;
		}
	}
	return false;
}

bool PhysicsScene::aabb2AABB(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	bool collided = false;

	if (box1 != nullptr && box2 != nullptr)
	{
		//the distance between the two lanes
		float distanceBetween = glm::length(box2->getPosition() - box1->getPosition());

		//the min x of box 1
		float box1MinX = box1->getPosition().x - box1->getExtenseX();
		//the min x of box 2
		float box2MinX = box2->getPosition().x - box2->getExtenseX();
		//the min y of box 1
		float box1MinY = box1->getPosition().y - box1->getExtenseY();
		//the min y of box 2
		float box2MinY = box2->getPosition().y - box2->getExtenseY();
		//the Max x of box 1
		float box1MaxX = box1->getPosition().x + box1->getExtenseX();
		//the max x of box 2
		float box2MaxX = box2->getPosition().x + box2->getExtenseX();
		//the max y of box 1
		float box1MaxY = box1->getPosition().y + box2->getExtenseY();
		//the max y ofbox 2
		float box2MaxY = box2->getPosition().y + box2->getExtenseY();

		glm::vec2 aMin = box1->getPosition() - box1->getExtense();
		glm::vec2 aMax = box1->getPosition() + box1->getExtense();

		glm::vec2 bMin = box2->getPosition() - box2->getExtense();
		glm::vec2 bMax = box2->getPosition() + box2->getExtense();

		bool overX = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
		bool overY = ((bMin.y <= aMax.x) && (aMin.y <= bMax.y));

		
		if ((box1MinX < box2MaxX && box1MaxX > box2MinX && box1MinY < box2MaxY && box1MaxY > box2MinY))

		{
			float xSeperationBox1Box2 = box1MinX - box2MaxX;
			float xSeperationBox2Box1 = box1MaxX - box2MinX;
			float ySeperationBox1Box2 = box1MinY - box2MaxY;
			float ySeperationBox2Box1 = box1MaxY - box2MinY;

			float overlapX = std::fabsf(xSeperationBox1Box2) < std::fabsf(xSeperationBox2Box1) ? xSeperationBox1Box2 : xSeperationBox2Box1;
			float overlapY = std::fabsf(ySeperationBox1Box2) < std::fabsf(ySeperationBox2Box1) ? ySeperationBox1Box2 : ySeperationBox2Box1;
			glm::vec2 overlap = std::fabsf(overlapX) < std::fabsf(overlapY) ? glm::vec2(overlapX, 0) : glm::vec2(0, overlapY);
			glm::vec2 normal =	glm::normalize(overlap);
			
			/*box1->setVelocity(glm::vec2(0, 0));
			box2->setVelocity(glm::vec2(0, 0))*/;
			box1->resolveCollisionBox(box2, normal);
			
			return true;
		}
		else
		{
			return false;
		}
	}

	
}

bool PhysicsScene::aabb2Sphere(PhysicsObject * obj1, PhysicsObject * obj2)
{
	
	return sphere2AABB(obj1, obj2);
}

bool PhysicsScene::plane2AABB(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		//the distance between the spheres closest point and the plane
		float distanceBetween = glm::dot(box->getPosition(), 
									plane->getNormal());
		float d = (distanceBetween - plane->getDistance() - glm::length(box->getExtense() * plane->getNormal()));

		if (d < 0)
		{
			plane->resolveCollision(box);
			return true;
		}

	}
	
	return false;
}

bool PhysicsScene::aabb2Plane(PhysicsObject *obj1, PhysicsObject *obj2)
{

	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		//the distance between the spheres closest point and the plane
		float distanceBetween = glm::dot(box->getPosition(),
			plane->getNormal());
		float d = (distanceBetween - plane->getDistance() - glm::length(box->getExtense() * plane->getNormal()));

		if (d < 0)
		{
			plane->resolveCollision(box);
			return true;
		}

	}


	return false;
}

bool PhysicsScene::sphere2AABB(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Box* box = dynamic_cast<Box*>(obj2);
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);

	if (box != nullptr && sphere != nullptr)
	{
		//collision by offset
		glm::vec2 offset = (sphere->getPosition() - box->getPosition());

		if (std::fabsf(offset.x) > box->getExtenseX())
		{
			offset.x = offset.x < 0 ? box->getExtenseX() * -1 : box->getExtenseX();
		}
		if (std::fabsf(offset.y > box->getExtenseY()))
		{
			offset.y = offset.y < 0 ? box->getExtenseY() * -1 : box->getExtenseY();
		}
		glm::vec2 closestPointOnBox = box->getPosition() + offset;
		glm::vec2 actualOffset = sphere->getPosition() - closestPointOnBox;

		//Min max by radius.
//-=-=-=-=-=-=-=-=-=-=-=--=-=-=-==-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		glm::vec2 aMin = box->getPosition() - box->getExtense();
		glm::vec2 aMax = box->getPosition() + box->getExtense();

		glm::vec2 a = glm::clamp(sphere->getPosition(), aMin, aMax);

		glm::vec2 v = a - sphere->getPosition();
		float vDot = glm::dot(v, v);
		glm::vec2 normal = glm::normalize(actualOffset);

		//if (glm::length(actualOffset) < sphere->getRadius())
		//{	
		//	
		//	float overlap = sphere->getRadius() - glm::length(actualOffset);
		//	//box->seperateObjects(box, sphere, normal, overlap);
		//	box->resolveCollisionBox(sphere, normal);
		//		return true;
		//}

		if (vDot < (sphere->getRadius() * sphere->getRadius()))
		{
			box->resolveCollision(sphere);
			return true;


		}
		
	}
	return false;
}

 void PhysicsScene::addActor(PhysicsObject* actor)
{
	 assert(actor != nullptr);
	 assert(std::find(std::begin(m_actors), std::end(m_actors), actor) == m_actors.end());
	 m_actors.push_back(actor);
}

 void PhysicsScene::removeActor(PhysicsObject* actor)
 {
	 std::remove(std::begin(m_actors), std::end(m_actors), actor);
 }