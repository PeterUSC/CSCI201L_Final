

#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include <fstream>
#include "Math.h"
#include "Character.h"
#include "Sprite.h"

Game::Game()
:window(nullptr)
,renderer(nullptr)
,isRunning(true)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	window = SDL_CreateWindow("Game", 100, 100, 1024, 768, 0);
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	LoadData();

	ticksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	//player->ProcessInput(state);
}

void Game::Shutdown()
{
	IMG_Quit();
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	ticksCount = SDL_GetTicks();

	std::vector<Character*> copy = characters;
	// Update all characters
	for (auto character : copy)
	{
		character->Update(deltaTime);
	}
	
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	for (auto sprite : sprites)
	{
		SDL_Log("sprite %i",sprites.size());
		sprite->DrawTexture(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Game::LoadData()
{
	LoadTexture("Assets/Background.png");
	LoadTexture("Assets/Idle.png");

	Character* background = new Character(this);
	Vector2 middle = Vector2(1024/2, 768/2);
	background->SetPosition(middle);
	Sprite* bgSprite = new Sprite(background,9);
	background->SetSprite(bgSprite);
	bgSprite->SetTexture(GetTexture("Assets/Background.png"));

	
	
	player = new Character(this);
	player->SetPosition(Vector2(20,20));
	
	Sprite* playerSprite = new Sprite(player,10);
	player->SetSprite(playerSprite);
	playerSprite->SetTexture(GetTexture("Assets/Idle.png"));
	
}

void Game::LoadTexture(const char* fileName)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName);
		return;
	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if (!text)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName);
		return;
	}
	textures.emplace(fileName, text);
}

void Game::AddSprite(Sprite* sprite)
{
	sprites.emplace_back(sprite);
	std::sort(sprites.begin(), sprites.end(), [](Sprite* a, Sprite* b) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	});
}


SDL_Texture* Game::GetTexture(const char* fileName)
{
	SDL_Texture* tex = nullptr;
	auto iter = textures.find(fileName);
	if (iter != textures.end())
	{
		tex = iter->second;
	}
	return tex;
}






