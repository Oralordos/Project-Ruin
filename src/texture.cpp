#include "texture.h"
#include "IL/ilut.h"

Texture::Texture() :
textureID(0), w(0), h(0)
{}

Texture::~Texture()
{
	destroy();
}

bool Texture::initialize(std::string filename)
{
	ILuint imageID = loadImage(filename);
	uploadToGL(imageID);
	destroyImage(imageID);
	return true;
}

void Texture::destroy()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
}

void Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

ILuint Texture::loadImage(std::string filename)
{
	ILuint imageName = ilGenImage();
	ilBindImage(imageName);
	ilLoadImage(filename.c_str());
	return imageName;
}

void Texture::uploadToGL(ILuint imageID)
{
	ilBindImage(imageID);
	textureID = ilutGLBindTexImage();
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
}

void Texture::destroyImage(ILuint imageID)
{
	ilDeleteImage(imageID);
}