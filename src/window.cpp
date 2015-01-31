#include "window.h"
#include "SDL_opengl.h"

bool hasInitSDL = false;
bool initializeSDL();

Window::Window() :
window(NULL), glContext(NULL)
{}

Window::~Window()
{
	if (glContext != NULL)
	{
		SDL_GL_DeleteContext(glContext);
	}
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
}

bool Window::initialize(const char *title, int width, int height, bool fullscreen)
{
	if (!hasInitSDL)
	{
		if (!initializeSDL())
		{
			return false;
		}
	}
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	if (window == NULL)
	{
		return false;
	}
	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL)
	{
		return false;
	}
	return true;
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		return false;
	}
	SDL_DisableScreenSaver();
	if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1) != 0)
	{
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) != 0)
	{
		return false;
	}
	hasInitSDL = true;
	return true;
}
