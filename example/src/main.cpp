#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include <AL/al.h>
#include <cstdio>
#include "se_helpers.hpp"
#include <test.hpp>
#include <engine.hpp>
#include <sound.hpp>
#include <listener.hpp>
#include <source.hpp>

int main(int argc, char **argv)
{
	SoundEngine::Engine se = SoundEngine::Engine();
	SoundEngine::Listener listener = SoundEngine::Listener();
	listener.update(
		0.0, 2.0, 0.0,
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
	//se.play("iwas");

	SoundEngine::Sound sound01 = SoundEngine::Sound("assets/01 Lich is Unbreakable (Expedition 1).ogg");
	SoundEngine::Sound sound02 = SoundEngine::Sound("assets/30 Golden Win (piano).ogg");

	SoundEngine::Source source01 = SoundEngine::Source();
	source01.set_position(10.0, 1.0, 0.0);
	source01.set_buffer(sound01);
	source01.play();

	SoundEngine::Source source02 = SoundEngine::Source();
	source02.set_buffer(sound02);
	source02.set_position(0.0, 1.0, 0.0);
	source02.play();

	// while(1);
	// /*
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { .position = {.x = 0} };
	camera.position = (Vector3){ 0.0f, 2.0f, 0.0f };	// Camera position
	camera.target = (Vector3){ 1.0f, 0.0f, 0.0f };		// Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };			// Camera up vector (rotation towards target)
	camera.fovy = 60.0f;										// Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;						// Camera projection type

	int cameraMode = CAMERA_FIRST_PERSON;

	DisableCursor();

	SetTargetFPS(60);

	// int failure = initialize(argc, argv);
	// if(failure) {
	// 	return 1;
	// }

	while (!WindowShouldClose()) {
		Vector3 oldCameraPos = camera.position;
		UpdateCamera(&camera, cameraMode);
		Vector3 cameraVelocity = Vector3Subtract(camera.position, oldCameraPos);
		Vector3 lookAt = Vector3Subtract(camera.target, camera.position);
		// update_listener(
		// 	camera.position.x, camera.position.y, camera.position.z,
		// 	cameraVelocity.x, cameraVelocity.y, cameraVelocity.z,
		// 	lookAt.x, lookAt.y, lookAt.z, camera.up.x, camera.up.y, camera.up.z
		// );
		listener.update(    
			camera.position.x, camera.position.y, camera.position.z,
			cameraVelocity.x, cameraVelocity.y, cameraVelocity.z,
			lookAt.x, lookAt.y, lookAt.z, camera.up.x, camera.up.y, camera.up.z
		);

		BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode3D(camera);
				// Draw ground
				DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY);
				DrawCube((Vector3){0.0, 1.0, 0.0}, 0.5f, 0.5f, 0.5f, PURPLE);
				DrawCube((Vector3){10.0, 1.0, 0.0}, 0.5f, 0.5f, 0.5f, PURPLE);
			EndMode3D();

			DrawText("WASD to move,\nMouse for turning.", 50, 50, 20, BLACK);
			DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
			DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", lookAt.x, lookAt.y, lookAt.z), 610, 75, 10, BLACK);
			DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);
		EndDrawing();
	}

	// deinitialize();
	CloseWindow();
	//*/

	return 0;
}