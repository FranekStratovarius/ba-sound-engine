#include "music_box.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include <AL/al.h>
#include <cstdio>
#include <engine.hpp>
#include <sound.hpp>
#include <listener.hpp>
#include <source.hpp>
#include <string>

int main(int argc, char **argv) {
	SoundEngine::Engine se = SoundEngine::Engine();
	SoundEngine::Listener listener = SoundEngine::Listener();
	listener.update(
		0.0, 2.0, 0.0,
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);

	// SoundEngine::Sound sound01 = SoundEngine::Sound("assets/01 Lich is Unbreakable (Expedition 1).ogg");
	// SoundEngine::Sound sound02 = SoundEngine::Sound("assets/30 Golden Win (piano).ogg");

	// SoundEngine::Source source01 = SoundEngine::Source();
	// source01.setPosition(10.0, 1.0, 0.0);
	// source01.setBuffer(&sound01);
	// source01.play();

	// SoundEngine::Source source02 = SoundEngine::Source();
	// source02.set_buffer(sound02);
	// source02.set_position(0.0, 1.0, 0.0);
	// source02.play();

	SoundEngine::MusicBox musicBox = SoundEngine::MusicBox();
	musicBox.setPosition(0.0, 1.0, 0.0);

	std::vector<WorldVariable> variables = musicBox.getWorldVariables();
	for (WorldVariable variable : variables) {
		printf("[%s] %f\n", variable.name, variable.value);
	}
	unsigned int selected = 0;

	// while(1) {
	// 	usleep(100 * 1000);
	// 	musicBox.update(GetFrameTime());
	// }
	//*
	const int screenWidth = 800;
	const int screenHeight = 450;
	// const int screenWidth = GetScreenWidth();
	// const int screenHeight = GetScreenHeight();

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { .position = {.x = 0} };
	camera.position = { 0.0f, 2.0f, 0.0f };	// Camera position
	camera.target = { 1.0f, 0.0f, 0.0f };		// Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };			// Camera up vector (rotation towards target)
	camera.fovy = 60.0f;										// Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;						// Camera projection type

	int cameraMode = CAMERA_FIRST_PERSON;

	DisableCursor();
	// ToggleFullscreen();

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		musicBox.update();
		Vector3 oldCameraPos = camera.position;
		UpdateCamera(&camera, cameraMode);
		Vector3 cameraVelocity = Vector3Subtract(camera.position, oldCameraPos);
		Vector3 lookAt = Vector3Subtract(camera.target, camera.position);
		listener.update(    
			camera.position.x, camera.position.y, camera.position.z,
			cameraVelocity.x, cameraVelocity.y, cameraVelocity.z,
			lookAt.x, lookAt.y, lookAt.z, camera.up.x, camera.up.y, camera.up.z
		);
		// update variables with input
		if (IsKeyPressed(KEY_J)) {
			selected = (selected + 1) % variables.size();
		}
		if (IsKeyPressed(KEY_U)) {
			int size = (int)variables.size();
			selected = ((selected - 1) + size) % size;
		}
		if (IsKeyPressed(KEY_H)) {
			variables[selected].value = variables[selected].value - 1;
			musicBox.setWorldVariable(variables[selected]);
		}
		if (IsKeyPressed(KEY_K)) {
			variables[selected].value = variables[selected].value + 1;
			musicBox.setWorldVariable(variables[selected]);
		}

		if (IsKeyPressed(KEY_R)) {
			printf("stop to debug");
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode3D(camera);
				// Draw ground
				DrawPlane({ 0.0f, 0.0f, 0.0f }, { 32.0f, 32.0f }, LIGHTGRAY);
				DrawCube({0.0, 1.0, 0.0}, 0.5f, 0.5f, 0.5f, PURPLE);
				DrawCube({10.0, 1.0, 0.0}, 0.5f, 0.5f, 0.5f, PURPLE);
			EndMode3D();

			DrawText("WASD to move,\nMouse for turning,\nUHJK for music control.", 50, 50, 20, BLACK);
			DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
			DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", lookAt.x, lookAt.y, lookAt.z), 610, 75, 10, BLACK);
			DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);

			// variables ui
			std::string output = "";
			for (unsigned int i = 0; i < variables.size(); i++) {
				if (i == selected) {
					output += "[";
				}
				output += variables[i].name;
				output += " <"; 
				output += std::to_string(variables[i].value);
				output += ">";
				if (i == selected) {
					output += "]";
				}
				output += "\n";
			}
			DrawText(output.c_str(), 10, 200, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();
	// */

	return 0;
}