#pragma once
#include "SDL.h"

/// <summary>
/// Used to manage the texture loading
/// </summary>
class TextureManager
{
public:
	/// <summary>
	/// Load a texture
	/// </summary>
	/// <param name="fileName">Name of the file</param>
	/// <returns></returns>
	static SDL_Texture* LoadTexture(const char* fileName);

	/// <summary>
	/// Draw the texture
	/// </summary>
	/// <param name="tex">: Texture to draw</param>
	/// <param name="src">: Source rect</param>
	/// <param name="dest">: Dest Rect</param>
	/// <param name="flip">: Is it flipped?</param>
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};