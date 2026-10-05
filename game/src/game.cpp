#include "game.h"

using namespace utils;

#pragma region gameFunctions

float x1{-400};
float y1{};
float r{};
float g{};
float b{};
int colorValue{};
int moveValue{};
float pi{ 3.1415f };

// Load textures and initialize other resources here.
void Start()
{

}

// Draw your game objects here.
void Draw()
{
	ClearBackground(); // Clear the background with a default color

	// draw pokeball
	SetColor(r, g, b, 1.f);
	FillArc( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, g_WindowWidth / 4, g_WindowHeight / 3, pi, pi * 2.f); //red arc

	SetColor(1, 1, 1, 1.f);
	FillArc( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, g_WindowWidth / 4, g_WindowHeight / 3, 0.f, pi); //white arc

	SetColor(0.f, 0.f, 0.f, 1.f); // middle part of the ball with the button
	FillRect( (x1 + g_WindowWidth) / 4, (y1 + g_WindowHeight) / 2.1f, g_WindowWidth / 2.f, 25.f);
	FillEllipse( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, 25.f, 25.f);
	SetColor(1.f, 1.f, 1.f, 1.f);
	FillEllipse( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, 15.f, 15.f);
	SetColor(0.f, 0.f, 0.f, 1.f);
	DrawEllipse( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, 10.f, 10.f, 1.f);
	DrawEllipse( (x1 + g_WindowWidth) / 2, (y1 + g_WindowHeight) / 2, g_WindowWidth / 4, g_WindowHeight / 3, 1.f); //black outline
}

// Handle gameplay, movement and collisions here.
void Update(float elapsedSec)
{
	++r;

	moveValue = (moveValue + 1) % 200;
	x1 = ((moveValue-100) / 199.f) * 20;
}

// Delete textures and free other resources here.
void End()
{
}

#pragma endregion gameFunctions

#pragma region inputHandling

// Called once when a key is pressed.
void OnKeyDownEvent(SDL_Keycode key)
{
}

// Called once when a key is released.
void OnKeyUpEvent(SDL_Keycode key)
{
}

// Called whenever the mouse moves.
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

// Called once when a mouse button is pressed.
void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

// Called once when a mouse button is released.
void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

#pragma endregion inputHandling

#pragma region myFunctionDefinitions

#pragma endregion