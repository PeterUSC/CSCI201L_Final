

#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include <fstream>
#include "Math.h"
#include "Character.h"
#include "Sprite.h"
#include "Person.h"
#include "Player.h"
#include "Brick.h"
#include "Enemy.h"
#include "Collision.h"
#include <iostream>

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
	std::vector<Character*> copy = characters;
	for (auto character : copy)
	{
		character->ProcessInput(state);
	}
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
	//SDL_Log("to characters size %i", characters.size());
	std::vector<Character*> toDelete;
	for (auto character : characters)
	{
		if (!character->isAlive())
		{
			toDelete.emplace_back(character);
		}
	}
	//SDL_Log("to delete size %i", toDelete.size());
	for (auto dead : toDelete)
	{
		delete dead;
	}
	
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	for (auto sprite : sprites)
	{
		sprite->DrawTexture(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Game::RemoveCharacter(Character* removee)
{
	auto charIter = std::find(characters.begin(), characters.end(), removee);
	if (charIter != characters.end())
	{
		characters.erase(charIter);
	}
}

void Game::RemoveSprite(Sprite* removee)
{
	auto spriteIter = std::find(sprites.begin(), sprites.end(), removee);
	sprites.erase(spriteIter);

}
void Game::LoadData()
{
	LoadTexture("Assets/sky.png");
	LoadTexture("Assets/rocks_1.png");
	LoadTexture("Assets/rocks_2.png");
	LoadTexture("Assets/sky.png");
	LoadTexture("Assets/Idle.png");
	LoadTexture("Assets/Bullet.png");
	LoadTexture("Assets/BlockA.png");
	LoadTexture("Assets/Run1.png");

	int size = 17;
	for (int i = 0; i < size; i++)
	{
		Vector2 middle = Vector2(i * 1024 / 2, 768 / 2);
		Character* layer1 = new Character(this);
		layer1->SetPosition(middle);
		Sprite* bgSprite = new Sprite(layer1, 9);
		bgSprite->SetParralax(0.75);
		layer1->SetSprite(bgSprite);
		bgSprite->SetTexture(GetTexture("Assets/rocks_2.png"));


		Character* layer2 = new Character(this);
		layer2->SetPosition(middle);
		Sprite* lay2Sprite = new Sprite(layer2, 8);
		lay2Sprite->SetParralax(0.50);
		layer2->SetSprite(lay2Sprite);
		lay2Sprite->SetTexture(GetTexture("Assets/rocks_1.png"));

		Character* layer3 = new Character(this);
		layer3->SetPosition(middle);
		Sprite* lay3Sprite = new Sprite(layer3, 7);
		lay3Sprite->SetParralax(0.25);
		layer3->SetSprite(lay3Sprite);
		lay3Sprite->SetTexture(GetTexture("Assets/sky.png"));
	}


	
	
	player = new Player(this);
	player->SetStart(Vector2(20,20));

	Enemy* zombie = new Enemy(this);
	zombie->SetPosition(Vector2(800, 600));
	
	Brick* newBrick = new Brick(this);
	newBrick->SetPosition(Vector2(700, 600));
}

void Game::LoadLevel(std::string fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open())
    {
		SDL_Log("Failed tp load level: %s", fileName);
    }
    
    size_t row = 0;
    std::string line;
    while(!file.eof())
    {
        std::getline(file, line);
        for(size_t col = 0; col < line.size(); col++)
        {
            //if not empty space
			if (line[col] != '.')
			{
				//if start position
				if (line[col] == 'S')
				{
					Vector2 pos;
					pos.x = 32.0f + 64.0f * col;
					pos.y = 16.0f + 32.0f * row;
					player = new Player(this);
					player->SetStart(pos);
				}

				//if finish positon
				else if (line[col] == 'F')
				{
					Vector2 pos;
					pos.x = 32.0f + 64.0f * col;
					pos.y = 16.0f + 32.0f * row;
					Character* finish = new Character(this);
					finish->SetPosition(pos);
					Collision* finishColl = new Collision(finish);
					finish->SetCollision(finishColl);
				}

				//if enemy positon
				else if (line[col] == 'E')
                {
                   Vector2 pos;
                   pos.x = 32.0f + 64.0f * col;
                   pos.y = 16.0f + 32.0f * row;
                   Enemy* enemy = new Enemy(this);
				   enemy->SetPosition(pos);
                 }
                             
                //if barrier location
                else
                {
                    Vector2 pos;
                    pos.x = 32.0f + 64.0f * col;
                    pos.y = 16.0f + 32.0f * row;
                    Brick* b = new Brick(this);
                    b->SetPosition(pos);
                }
            }
        }
        
        row++;
    }
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






