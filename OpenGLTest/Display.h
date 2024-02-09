#pragma once

#include <string>
#include "SDL.h"
#undef main

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();
	
	void SetColorAttributes();
	void SetBufferAttributes();
	
	void Update();
	void Clear(float red, float green, float blue, float alpha);

	bool IsClosed() const;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
protected:

private:
	Display(const Display& other) = default;
	// Display& operator=(const Display& other) {}

	SDL_Window* window;
	SDL_GLContext glContext;

	int width;
	int height;

	bool isClosed = false;
};

