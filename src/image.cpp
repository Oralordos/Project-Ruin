#include "image.h"
#include "texture.h"

Image::Image():
tex(NULL), texLeft(0.0f), texRight(0.0f), texTop(0.0f), texBottom(0.0f)
{}

bool Image::initialize(Texture *tex, units::Pixel x, units::Pixel y, units::Pixel w, units::Pixel h)
{
	this->tex = tex;
	units::Pixel texWidth = tex->getWidth();
	units::Pixel texHeight = tex->getHeight();
	units::Scalar sx = static_cast<units::Scalar>(x);
	units::Scalar sy = static_cast<units::Scalar>(y);
	texLeft = sx / texWidth;
	texRight = (sx + w) / texWidth;
	texTop = sy / texHeight;
	texBottom = (sy + h) / texHeight;
	return true;
}

void Image::render(units::Game x, units::Game y, units::Game w, units::Game h)
{
	// TODO Put the image into a drawing queue for batch drawing.
}