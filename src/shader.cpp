#include <GL\glew.h>
#include <fstream>
#include <iterator>
#include <cassert>
#include "shader.h"

Shader::Shader() :
shaderProgramID(0)
{}

Shader::~Shader()
{
	destroy();
}

void Shader::destroy()
{
	if (shaderProgramID != 0)
	{
		glDeleteProgram(shaderProgramID);
	}
}

GLuint Shader::loadShader(std::string filename, GLenum shaderType) const
{
	assert(shaderType == GL_FRAGMENT_SHADER || shaderType == GL_GEOMETRY_SHADER || shaderType == GL_VERTEX_SHADER);
	std::ifstream sourceFile(filename);
	if (sourceFile)
	{
		std::string shaderString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
		sourceFile.close();
		GLuint shaderID = glCreateShader(shaderType);
		if (shaderID == 0)
		{
			// TODO Add error checking for unable to create shader.
			return 0;
		}
		else
		{
			const GLchar *shaderSource = shaderString.c_str();
			glShaderSource(shaderID, 1, &shaderSource, NULL);
			glCompileShader(shaderID);
			GLint shaderCompiled = GL_FALSE;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
			if (shaderCompiled == GL_TRUE)
			{
				return shaderID;
			}
			else
			{
				std::string shaderLog = getShaderLog(shaderID);
				// TODO Print the shader log.
				glDeleteShader(shaderID);
				return 0;
			}
		}
	}
	else
	{
		// TODO Add error message for unable to find file.
		return 0;
	}
}

std::string Shader::getShaderLog(GLuint shaderID) const
{
	if (glIsShader(shaderID))
	{
		int maxLength = 0;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		char* charLog = new char[maxLength];

		glGetShaderInfoLog(shaderID, maxLength, NULL, charLog);
		std::string log(charLog);
		delete[] charLog;
		return log;
	}
	else
	{
		std::string log(std::to_string(shaderID));
		log += " is not a valid shader ID";
		return log;
	}
}

bool Shader::compileProgram(GLuint vertexShaderID, GLuint fragmentShaderID, GLuint geometryShaderID)
{
	assert(glIsShader(vertexShaderID));
	assert(glIsShader(fragmentShaderID));
	shaderProgramID = glCreateProgram();
	if (shaderProgramID == 0)
	{
		return false;
	}
	else
	{
		glAttachShader(shaderProgramID, vertexShaderID);
		glDeleteShader(vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glDeleteShader(fragmentShaderID);
		if (geometryShaderID != 0)
		{
			glAttachShader(shaderProgramID, geometryShaderID);
			glDeleteShader(geometryShaderID);
		}
		glLinkProgram(shaderProgramID);
		GLint programLinked = GL_FALSE;
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &programLinked);
		if (programLinked == GL_TRUE)
		{
			return true;
		}
		else
		{
			std::string programLog = getProgramLog();
			// TODO Print the program log
			glDeleteProgram(shaderProgramID);
			shaderProgramID = 0;
			return false;
		}
	}
}

bool Shader::loadProgram(std::string vertexFilename, std::string fragmentFilename, std::string geometryFilename)
{
	GLuint vertexShaderID = loadShader(vertexFilename, GL_VERTEX_SHADER);
	if (vertexShaderID != 0)
	{
		GLuint fragmentShaderID = loadShader(fragmentFilename, GL_FRAGMENT_SHADER);
		if (fragmentShaderID == 0)
		{
			glDeleteShader(vertexShaderID);
		}
		else
		{
			GLuint geometryShaderID = 0;
			bool success = true;
			if (!geometryFilename.empty())
			{
				geometryShaderID = loadShader(geometryFilename, GL_GEOMETRY_SHADER);
				if (geometryShaderID == 0)
				{
					glDeleteShader(vertexShaderID);
					glDeleteShader(fragmentShaderID);
					success = false;
				}
			}
			if (success)
			{
				return compileProgram(vertexShaderID, fragmentShaderID, geometryShaderID);
			}
		}
	}
	return false;
}

std::string Shader::getProgramLog() const
{
	if (glIsProgram(shaderProgramID))
	{
		int maxLength = 0;

		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		char* charLog = new char[maxLength];

		glGetProgramInfoLog(shaderProgramID, maxLength, NULL, charLog);
		std::string log(charLog);
		delete[] charLog;
		return log;
	}
	else
	{
		std::string log(std::to_string(shaderProgramID));
		log += " is not a valid shader program ID";
		return log;
	}
}

bool Shader::bindProgram() const
{
	assert(shaderProgramID != 0);
	glUseProgram(shaderProgramID);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::string log = getProgramLog();
		// TODO Print the program log
		return false;
	}
	return true;
}

void Shader::unbindProgram() const
{
	glUseProgram(0);
}