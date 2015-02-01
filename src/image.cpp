#include "image.h"

Image::Image():
tex(NULL), texLeft(0.0f), texRight(0.0f), texTop(0.0f), texBottom(0.0f)
{}

Image::~Image()
{
	tex = NULL;
	// TODO Inform the data repository that we are done with the texture.
}

bool Image::initialize(std::string filname, units::Pixel x, units::Pixel y, units::Pixel w, units::Pixel h)
{
	// TODO Put in code to get the image from the data repository here.
	units::Pixel texWidth = 0;
	units::Pixel texHeight = 0;
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