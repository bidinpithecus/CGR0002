#include "Image.hpp"
#include <iostream>

Image::Image() {
	xSize = 0;
	ySize = 0;
	pTexture = NULL;
}

Image::~Image() {
	if (pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
	}
}

void Image::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer) {
	matrixRedChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	matrixGreenChannel.resize(xSize, std::vector<double>(ySize, 0.0));
	matrixBlueChannel.resize(xSize, std::vector<double>(ySize, 0.0));

	this->xSize = xSize;
	this->ySize = ySize;
	this->pRenderer = pRenderer;

	InitTexture();
}

void Image::UpdateSize(const int xSize, const int ySize) {
	this->xSize = xSize;
	this->ySize = ySize;

	matrixRedChannel.resize(this->xSize, std::vector<double>(this->ySize, 0.0));
	matrixGreenChannel.resize(this->xSize, std::vector<double>(this->ySize, 0.0));
	matrixBlueChannel.resize(this->xSize, std::vector<double>(this->ySize, 0.0));
}

void Image::setPixel(const int x, const int y, const double red, const double green, const double blue) {
	matrixRedChannel.at(x).at(y) = red;
	matrixGreenChannel.at(x).at(y) = green;
	matrixBlueChannel.at(x).at(y) = blue;
}

void Image::Display() {
	Uint32* tempPixels = new Uint32[xSize * ySize];

	memset(tempPixels, 0, xSize * ySize * sizeof(Uint32));

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			tempPixels[(y * xSize) + x] = ConvertColor(matrixRedChannel.at(x).at(y), matrixGreenChannel.at(x).at(y), matrixBlueChannel.at(x).at(y));
		}
	}

	SDL_UpdateTexture(pTexture, NULL, tempPixels, xSize * sizeof(Uint32));

	delete[] tempPixels;

	SDL_Rect srcRect;
	SDL_Rect bounds;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = xSize;
	srcRect.h = ySize;

	bounds = srcRect;

	SDL_RenderCopy(pRenderer, pTexture, &srcRect, &bounds);
}

void Image::InitTexture() {
	Uint32 rMask;
	Uint32 gMask;
	Uint32 bMask;
	Uint32 aMask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rMask = 0xff000000;
		gMask = 0x00ff0000;
		bMask = 0x0000ff00;
		aMask = 0x000000ff;
	#else
		aMask = 0x000000ff;
		bMask = 0x0000ff00;
		gMask = 0x00ff0000;
		rMask = 0xff000000;
	#endif

	if (pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
	}

	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, xSize, ySize, 32, rMask, gMask, bMask, aMask);
	pTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(const double red, const double green, const double blue) {
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
	#endif

	return pixelColor;
}
