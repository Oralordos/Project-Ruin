#include <cstdlib>
#include <string>
#include "RuinConfig.h"
#include "GL/glew.h"
#include "IL/il.h"
#include "IL/ilut.h"
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_opengl.h"
#include "window.h"
#include "texture.h"
#include "image.h"

const std::string titleString = "Project Ruin " + std::to_string(Ruin_VERSION_MAJOR) + "." + std::to_string(Ruin_VERSION_MINOR);

void initDevIL()
{
	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

int main(int argc, char* args[])
{
	initDevIL();
	Window *window = new Window();
	if (!window->initialize(titleString.c_str(), 640, 480, false))
	{
		return EXIT_FAILURE;
	}
	glewInit();
	if (!GLEW_VERSION_3_3)
	{
		return EXIT_FAILURE;
	}
	Texture tex;
	if (!tex.initialize("test.png"))
	{
		return EXIT_FAILURE;
	}
	Image image;
	if (!image.initialize(&tex, 0, 0, tex.getWidth(), tex.getHeight()))
	{
		return EXIT_FAILURE;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	bool running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		window->swapBuffer();
	}
	tex.destroy();
	delete window;
	SDL_Quit();
	return EXIT_SUCCESS;
}
