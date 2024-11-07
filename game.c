#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#define MAX_COLUMNS 5

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1200;
	const int screenHeight = 750;

	const double character_rotation = 90;

	bool left_was_clicked = false;
	bool obj_should_move = false;
	double obj_move_base = 1.0f; //2.0f
	double obj_move = obj_move_base;
	float aimag = 1.5f;

	InitWindow(screenWidth, screenHeight, "Title - Subtitle");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position = (Vector3) { 0.0f, 2.0f, 4.0f };    // Camera position
	camera.target = (Vector3) { 0.0f, 2.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	Vector3 player_coords = (Vector3) { camera.target.x + 0.5f, camera.target.y + 0.5f, camera.target.z + 0.5f };

	int cameraMode = CAMERA_FIRST_PERSON;

	// Generates some random columns
	float heights[MAX_COLUMNS] = { 0 };
	Vector3 positions[MAX_COLUMNS] = { 0 };
	Color colors[MAX_COLUMNS] = { 0 };

	for (int i = 0; i < MAX_COLUMNS; i++)
	{
		heights[i] = (float)GetRandomValue(1, 12);
		positions[i] = (Vector3) { (float)GetRandomValue(-15, 15), heights[i] / 2.0f, (float)GetRandomValue(-15, 15) };
		colors[i] = (Color) { GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
	}

	DisableCursor();                    // Limit cursor to relative movement inside the window

	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// Switch camera mode
		if (IsKeyPressed(KEY_ONE))
		{
			cameraMode = CAMERA_FREE;
			camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_TWO))
		{
			cameraMode = CAMERA_FIRST_PERSON;
			camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_THREE))
		{
			cameraMode = CAMERA_THIRD_PERSON;
			camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_FOUR))
		{
			cameraMode = CAMERA_ORBITAL;
			camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_EIGHT)) {
			DisableCursor();
		}

		if (IsKeyPressed(KEY_NINE)) {
			EnableCursor();
		}

		// Switch camera projection
		if (IsKeyPressed(KEY_P))
		{
			if (camera.projection == CAMERA_PERSPECTIVE)
			{
				// Create isometric view
				cameraMode = CAMERA_THIRD_PERSON;
				// Note: The target distance is related to the render distance in the orthographic projection
				camera.position = (Vector3) { 0.0f, 2.0f, -100.0f };
				camera.target = (Vector3) { 0.0f, 2.0f, 0.0f };
				camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
				camera.projection = CAMERA_ORTHOGRAPHIC;
				camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
				CameraYaw(&camera, -135 * DEG2RAD, true);
				CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
			}
			else if (camera.projection == CAMERA_ORTHOGRAPHIC)
			{
				// Reset to default view
				cameraMode = CAMERA_THIRD_PERSON;
				camera.position = (Vector3) { 0.0f, 2.0f, 10.0f };
				camera.target = (Vector3) { 0.0f, 2.0f, 0.0f };
				camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
				camera.projection = CAMERA_PERSPECTIVE;
				camera.fovy = 60.0f;
			}
		}

		///////////////////////////////////
		///////// new
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			left_was_clicked = true;
		}
		/////////////////////////////

		UpdateCamera(&camera, cameraMode);

			
		// DRAW
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawPlane((Vector3) { 0.0f, 0.0f, 0.0f }, (Vector2) { 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
		DrawCube((Vector3) { -16.0f, 2.5f, 0.0f }, 1.0f, 12.0f, 32.0f, DARKGRAY);     // LEFT WALL
		DrawCube((Vector3) { 16.0f, 2.5f, 0.0f }, 1.0f, 12.0f, 32.0f, DARKGRAY);      // RIGHT WALL
		DrawCube((Vector3) { 0.0f, 2.5f, 16.0f }, 32.0f, 12.0f, 1.0f, DARKGRAY);      // BACK WALL

		// Draw some cubes around
		for (int i = 0; i < MAX_COLUMNS; i++)
		{
			DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
			DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
		}

		// PLAYER CUBE
		if (cameraMode == CAMERA_THIRD_PERSON)
		{
			player_coords = (Vector3) { camera.target.x, camera.target.y, camera.target.z };
			Model model = LoadModel("lowpolycat/cat.obj"); 

			//(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
			DrawModelEx(model, player_coords, (Vector3) { 0.0f, 1.0f, 0.0f }, 0.0f, (Vector3) { 0.003f, 0.003f, 0.003f }, BLACK);
		}
		else { //FIRST-PERSON VIEW
			player_coords = (Vector3) { camera.position.x, camera.position.y, camera.position.z };

			// for a first-person camera, the camera.target is always in front of the camera, 
			// and the horizontal rotation is represented by the angle between the camera's 
			// forward vector and the world's forward vector (typically the negative Z-axis)
			Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
			// angle between the camera's forward vector and the world's forward vector in the XZ plane
			// convert the angle from radians to degrees using RAD2DEG (a constant provided by raylib)
			float rotationAngle = atan2f(forward.x, forward.z) * RAD2DEG; 

			Model model = LoadModel("lowpolycat/cat.obj");
			DrawModelEx(model, player_coords, (Vector3) { 0.0f, 1.0f, 0.0f }, rotationAngle + character_rotation, (Vector3) { 0.003f, 0.003f, 0.003f }, BLACK);
		}


		//////////////////////////////////////////
		/////////new
		if (obj_should_move) {
			obj_move += 1.0f;

			if (obj_move >= 50.0f) {
				obj_should_move = false;
				obj_move = obj_move_base;
			}
		}

		if (left_was_clicked) {
			Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
			Vector3 objectPosition = Vector3Add(camera.position, Vector3Scale(forward, obj_move));

			DrawCube(objectPosition, 0.1f, 0.1f, 0.1f, BROWN);
			left_was_clicked = false;
			obj_should_move = true;
		}

		///////////////////////////////////////

		EndMode3D();

		// Draw info boxes
		DrawRectangle(5, 5, 440, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(5, 5, 440, 100, BLUE);

		DrawText("Camera controls:", 15, 15, 20, BLACK);
		DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 16, BLACK);
		DrawText("- Look around: arrow keys or mouse", 15, 45, 16, BLACK);
		DrawText("- Camera mode keys: 1, 2, 3, 4", 15, 60, 16, BLACK);
		DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 16, BLACK);
		DrawText("- Camera projection key: P", 15, 90, 16, BLACK);

		DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(600, 5, 195, 100, BLUE);

		DrawText("Camera status:", 610, 15, 10, BLACK);
		DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
			(cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
			(cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
			(cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
		DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
			(camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
		DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
		DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
		DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);


		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
