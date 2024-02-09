#include "Display.h"

#include <iostream>
#include <GL/glew.h>

Display::Display(const int width, const int height, const std::string& title)
	: width(width), height(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SetColorAttributes();
	SetBufferAttributes();

	window = SDL_CreateWindow(
		title.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		this->width, 
		this->height, 
		SDL_WINDOW_OPENGL);

	// draw the display using the GPU instead of the CPU
	glContext = SDL_GL_CreateContext(window);

	const GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!\n";
	}

	isClosed = false;

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Display::SetColorAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
}

void Display::SetBufferAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
}

void Display::Update()
{
	SDL_GL_SwapWindow(window);

	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}

void Display::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed() const
{
	return isClosed;
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
