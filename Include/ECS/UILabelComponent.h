#pragma once
#include "ECS\ECS.h"
#include "AssetManager.h"
#include "Game.h"
#include "Vector2D.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(Vec2i position, const std::string& text, const std::string& font, SDL_Color& color) :
		labelText(text), labelFont(font), textColor(color)
	{
		this->position = { position.x, position.y };
		SetLabelText(labelText, labelFont);
	};
	~UILabel() {};

	void SetLabelText(const std::string& text, const std::string& font)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

	}

	void Draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
		SDL_DestroyTexture(this->labelTexture);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
};