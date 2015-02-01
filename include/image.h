#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "SDL_opengl.h"
#include "texture.h"
#include "units.h"

class Image
{
public:
	Image();
	~Image();
	bool initialize(std::string filename, units::Pixel x, units::Pixel y, units::Pixel w, units::Pixel h);
	void render(units::Game x, units::Game y, units::Game w, units::Game h);
private:
	Texture *tex;
	units::Scalar texLeft;
	units::Scalar texRight;
	units::Scalar texTop;
	units::Scalar texBottom;
};

#endif // IMAGE_H_