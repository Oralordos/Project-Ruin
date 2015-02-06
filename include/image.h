#ifndef IMAGE_H_
#define IMAGE_H_

#include "units.h"

class Texture;

class Image
{
public:
	Image();
	bool initialize(Texture *texture, units::Pixel x, units::Pixel y, units::Pixel w, units::Pixel h);
	void render(units::Game x, units::Game y, units::Game w, units::Game h);
private:
	Texture *tex;
	units::Scalar texLeft;
	units::Scalar texRight;
	units::Scalar texTop;
	units::Scalar texBottom;
};

#endif // IMAGE_H_