#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image {
	public:
		// Constructor
		Image();

		// Destructor
		~Image();

		void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

		void UpdateSize(const int xSize, const int ySize);

		void setPixel(const int x, const int y, const double red, const double green, const double blue);

		void Display();

	private:
		Uint32 ConvertColor(const double red, const double green, const double blue);

		void InitTexture();
		std::vector<std::vector<double>> matrixRedChannel;
		std::vector<std::vector<double>> matrixGreenChannel;
		std::vector<std::vector<double>> matrixBlueChannel;

		int xSize;
		int ySize;

		SDL_Renderer* pRenderer;
		SDL_Texture* pTexture;
};

#endif
