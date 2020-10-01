#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleScene::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	if (SDL_GetTicks() >= TIME_TRIAL)
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

void ModuleScene::CreateBox(int degrees, vec3 angle, vec3 offset, vec3 size, Color color) {

	Cube cube;
	cube.size = size;
	cube.SetPos(offset.x, offset.y, offset.z);
	cube.color = color;
	cube.SetRotation(degrees, angle);
	cube.Render();
}

void ModuleScene::RenderBox(int degrees, vec3 angle, vec3 offset, vec3 size, Color color) {

	Cube cube;
	cube.size = size;
	cube.SetPos(offset.x, offset.y, offset.z);
	cube.color = color;
	cube.SetRotation(degrees, angle);
	cube.Render();
}
