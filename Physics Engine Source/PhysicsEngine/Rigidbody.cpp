#include "Rigidbody.h"

//Constructor 1.
Rigidbody::Rigidbody()
{
	m_isKinematic = false;
}

//Constructor 2.
Rigidbody::Rigidbody(ShapeType shapeID)
{
	m_shapeID = shapeID;
	m_isKinematic = false;
}

//Constructor 3.
Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_shapeID = shapeID;
	m_mass = mass;
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_isKinematic = false;
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position)
{
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float angularVelocity, float moment)
{
	m_shapeID = shapeID;
	m_mass = mass;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_angularVelocity = angularVelocity;
	m_moment = moment;
}

Rigidbody::~Rigidbody()
{
	delete this;
}

//Applies force to one object.
void Rigidbody::applyForce(glm::vec2 force)
{
	//a = f / m
	glm::vec2 acceleration = force / m_mass;
	
	//adds to velocity based on acceleration variable.
	m_velocity += acceleration;
}

//Applies forces to two objects.
//Used in collision response.
void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
	//Applies force to the 2nd actor.
	actor2->applyForce(force);

	if (!this->isKinematic())
	{
		//Applies force to this rigidbody actor.
		applyForce(-force);
	}
	
}

//Resolve collisions (basic)
void Rigidbody::resolveCollision(Rigidbody * actor2)
{
		//Normal is the normalized distance between
		//the two rigidbodies positions.
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;


	//Grabs the elasticity
	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	
	if (!m_isKinematic)
	{
		//General formula for collision response can be used for most types.
		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
			glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

		//force is the normal times the outcome of the formula.
		glm::vec2 force = normal * j;

		//Applies force to both objects.
		applyForceToActor(actor2, force);
	}
	else if (m_isKinematic)
	{
		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
			glm::dot(normal, normal *(1/m_mass));

		glm::vec2 force = normal * j;

		actor2->applyForce(force * 0.1f);
	}
}

//Seperates objects after collision occurs to prevent objects
//clipping inside eachother. (not working)
void Rigidbody::seperateObjects(Rigidbody * rb1, Rigidbody * rb2, glm::vec2 normal, float overlap)
{
	float obj1MoveRatio = 0;
	float obj2MoveRatio = 0;

	if (rb1 && rb2)
	{
		float totalMass = rb1->getMass() + rb2->getMass();
		obj1MoveRatio = 1 - (rb1->getMass() / totalMass);
		obj2MoveRatio = 1 - (rb2->getMass() / totalMass);

	}
	else if (rb1)
	{
		obj1MoveRatio = 1.0f;
	}
	else if (rb2)
	{
		obj2MoveRatio = 1.0f;
	}

	if (rb1)
	{
		rb1->setPosition(rb1->getPosition() +
			(obj1MoveRatio * overlap * normal));
	}
	if (rb2)
	{
		rb2->setPosition(rb2->getPosition() -
			(obj2MoveRatio * overlap * normal));
	}
}

//Set's the mass of the rigidbody.
void Rigidbody::setMass(float a_mass)
{
	m_mass = a_mass;
}

//sets the velocity of the rigidbody.
void Rigidbody::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}

//fixed update where physics are calculated on a fixed timestep.
void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (m_isKinematic)
	{
		return;
	}

	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if (length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_velocity = glm::vec2(0, 0);
	}

	if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}

}

//empty debug function.
void Rigidbody::debug()
{
}
