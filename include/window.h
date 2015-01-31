#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL.h"

class Window
{
public:
	Window();
	~Window();
	bool initialize(const char *title, int width, int height, bool fullscreen);
	void swapBuffer();
private:
	SDL_Window *window;
	SDL_GLContext glContext;
};

#endif // WINDOW_H_
