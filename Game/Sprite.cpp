#include "Sprite.h"
#include "Character.h"
#include "Game.h"


Sprite::Sprite(Character* c, int draw)
{
	drawOrder = draw;
	owner = c;
	c->GetGame()->AddSprite(this);
}


Sprite::~Sprite()
{
}
void Sprite::SetTexture(SDL_Texture* text)
{ 
	texture = text;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void Sprite::DrawTexture(SDL_Renderer* renderer)
{
	if (texture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(width);
		r.h = static_cast<int>(height);
		r.x = static_cast<int>(owner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(owner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer,
			texture,
			nullptr,
			&r,
			-Math::ToDegrees(owner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}
