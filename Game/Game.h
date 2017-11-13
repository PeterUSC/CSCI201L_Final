#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SDL/SDL_mixer.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void LoadTexture(const char* fileName);
	void AddCharacter(class Character* newChar) { characters.push_back(newChar); }
	SDL_Texture* GetTexture(const char* fileName);
	void AddSprite(class Sprite* sprite);
	class Player* GetPlayer() { return player; }

	void RemoveCharacter(class Character* removee);
	void RemoveSprite(class Sprite* removee);

	std::vector<class Brick*> bricks;
	std::vector<class Enemy*> enemies;
	void LoadLevel(std::string fileName);
	Vector2 GetCamPos() { return camPos; }
	void SetCamPos(Vector2 newPos) { camPos = newPos; }
	//void LoadSound(const std::string& filename);
	//Mix_Chunk* GetSound(const std::string& filename);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();

	Vector2 camPos;
	

	
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;
	class Player* player;

	std::vector<class Sprite*> sprites;
	std::unordered_map<const char*, SDL_Texture*> textures;
	std::vector<class Character*> characters; 
};
