#include "texture.h"

Texture::Texture() :
textureID(0), w(0), h(0)
{}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

bool Texture::initialize(std::string filename)
{
	// TODO Put in code to load the image here.
	// TODO Put in code to record the size of the image here.
	return false;
}

void Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}