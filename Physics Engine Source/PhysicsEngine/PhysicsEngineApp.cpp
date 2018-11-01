#define _USE_MATH_DEFINES
#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm\ext.hpp>
#include <Gizmos.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

using namespace glm;
using namespace std;


vec4 m_clearColour = vec4(1,1,1,1);

PhysicsEngineApp::PhysicsEngineApp() {

}

PhysicsEngineApp::~PhysicsEngineApp() {

}

bool PhysicsEngineApp::startup() {
	//Increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	bool filled = true;
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);


	m_physicsScene = new PhysicsScene();
	m_physicsScene->setTimeStep(0.001f);
	m_physicsScene->setGravity(glm::vec2(0, -4.8f));

	float radius = 1.0f;
	float speed = 30;
	vec2 startPos(-40, 0);
	float inclination = (float)3.14 / 4.f;  //45 degrees
	float radianInclination = 0.785398f;

	Sphere* sphere1 = new Sphere(vec2(23, 20), vec2(-40, 20), 8.0f, 4, vec4(1, 0, 0, 1));
	Sphere* sphere2 = new Sphere(vec2(45, 20), vec2(70, 30), 1.0f, 2, vec4(0, 1, 0, 1));
	Sphere* sphere3 = new Sphere(vec2(1, 20), vec2(5, 3), 7.0f, 4, vec4(1, 1, 1, 1));

	sphere1->setElasticity(0.8f);
	m_physicsScene->addActor(sphere1);
	m_physicsScene->addActor(sphere2);
	m_physicsScene->addActor(sphere3);
	sphere2->setKinematic(true);


	Plane* plane = new Plane(glm::vec2(0, 1), -40);
	Plane* plane1 = new Plane(glm::vec2(0, -1), -40);
	Plane* plane2 = new Plane(glm::vec2(1, 0), -70);
	Plane* plane3 = new Plane(glm::vec2(-1, 0), -70);


	m_physicsScene->addActor(plane);
	m_physicsScene->addActor(plane1);
	m_physicsScene->addActor(plane2);
	m_physicsScene->addActor(plane3);

	Box* box1 = new Box(vec2(-20, 30), vec2(0, 0), 2.0f, 7, 6, vec4(1, 0.5f, 1, 1));
	Box* box2 = new Box(vec2(-20, 10), vec2(0, 0), 2.0, 6, 6, vec4(1,1,1,1));
	Box* box3 = new Box(vec2(-15, -10), vec2(0, 0), 2.f, 3, 3, vec4(1, 1, 0.5f, 1));
	Box* box4 = new Box(vec2(5, -15), vec2(0, 0), 2.f, 5, 5, vec4(0.5f, 1, 1, 1));
	box1->setFilled(true);
	m_physicsScene->addActor(box1);
	m_physicsScene->addActor(box2);
	m_physicsScene->addActor(box3);
	m_physicsScene->addActor(box4);
	box1->setVelocity(vec2(73, 7));
	box2->setVelocity(vec2(16, 23));
	box3->setVelocity(vec2(20, 23));
	box4->setVelocity(vec2(30, -21));
	return true;
}

void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
	
	
}

void PhysicsEngineApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_EQUAL))
	{
		m_physicsScene->setGravity(glm::vec2(0, -4.8f));
	}
	if (input->isKeyDown(aie::INPUT_KEY_MINUS))
	{
		m_physicsScene->setGravity(glm::vec2(0, 4.8f));
	}

	if (input->isKeyDown(aie::INPUT_KEY_G))
	{
		if (gravityOn)
		{
			gravityOn = false;
		}
		else
		{
			gravityOn = true;
		}
	}

	if (gravityOn)
	{
		m_physicsScene->setGravity(glm::vec2(0, -9.6f));
	}
	else
	{
		m_physicsScene->setGravity(glm::vec2(0, 0));
	}
	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = (float)getWindowWidth() / getWindowHeight();
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//basic input instructions
//	m_2dRenderer->drawText(m_font, "Gravity On/Off = G", 0, 40);

	
	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsEngineApp::setupConinousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	vec4 colour = vec4(1, 0, 0, 1);

	while (t <= 5)
	{
		// calculate the x, y position of the projectile at time t
		float x = startPos.x + (speed* t);
		float y = startPos.y + (speed* t) + (0.5f * (gravity * (t*t)));

		aie::Gizmos::add2DCircle(vec2(x, y), radius, segments, colour);

		std::cout << "x: " << x;
		std::cout << "y: " << y;
		t += tStep;
	}
}
