#include "Game.h"
#include "glm/glm.hpp"
#include "ECS.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Game::Game() {}

Game::~Game() {}

void Game::Initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return;
	}

	displayID = SDL_GetPrimaryDisplay();
	mode = SDL_GetCurrentDisplayMode(displayID);
	if (!mode)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't get display: %s", SDL_GetError()); 
	}
	windowWidth = mode->w;
	windowHeight = mode->h;
	SDL_Log("Display mode: %dx%d @ %.2fHz", mode->w, mode->h, mode->refresh_rate);
	
	window = SDL_CreateWindow("Pikuma", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
		return;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void Game::Run()
{

	Setup();

	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();

		uint32_t frameEnd = SDL_GetTicks();
		int frameDuration = frameEnd - frameStart;
		if (frameDuration < MILLISECS_PER_FRAME) 
		{
			SDL_Delay(MILLISECS_PER_FRAME - frameDuration);
		}
	}
}

void Game::ProcessInput()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}
	
void Game::Setup()
{
	
}

void Game::Update()
{
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevioseFrame);
	double deltaTime = (SDL_GetTicks() - millisecsPrevioseFrame) / 1000.0f;

	millisecsPrevioseFrame = SDL_GetTicks();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	
	SDL_Surface* surface = IMG_Load("./assets/sprites/characters/player.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
	
	SDL_FRect srcRect = { 0, 0, 48, 48 };
	SDL_FRect dstRect = { playerPosition.x, playerPosition.y, 48, 48 };
	SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);

	SDL_RenderPresent(renderer);

}

void Game::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}