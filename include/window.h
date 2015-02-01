#ifndef WINDOW_H_
#define WINDOW_H_

#include "SDL.h"
#include "units.h"

class Window
{
public:
	Window();
	~Window();
	bool initialize(const char *title, units::Pixel width, units::Pixel height, bool fullscreen);
	void swapBuffer();
private:
	SDL_Window *window;
	SDL_GLContext glContext;
};

#endif // WINDOW_H_
