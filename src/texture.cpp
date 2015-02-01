#include "texture.h"
#include "IL/il.h"
#include "IL/ilut.h"

Texture::Texture() :
textureID(0), w(0), h(0)
{}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

bool Texture::initialize(std::string filename)
{
	ILuint imageName = ilGenImage();
	ilBindImage(imageName);
	ilLoadImage(filename.c_str());
	textureID = ilutGLBindTexImage();
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
	ilDeleteImage(imageName);
	return false;
}

void Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}