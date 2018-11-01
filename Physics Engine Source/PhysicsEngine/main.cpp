#include "PhysicsEngineApp.h"
#include <imgui.h>
#include <stdio.h>
#include <imgui_glfw3.h>
#include <Application.h>


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d %s\n", error, description);
}

int main() {

	// allocation
	auto app = new PhysicsEngineApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}