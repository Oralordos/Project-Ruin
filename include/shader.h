#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include "SDL_opengl.h"

class Shader
{
public:
	Shader();
	~Shader();
	void destroy();
	GLuint loadShader(std::string filename, GLenum shaderType) const;
	bool compileProgram(GLuint vertexShaderID, GLuint fragmentShaderID, GLuint geometryShaderID = 0);
	bool loadProgram(std::string vertexFilename, std::string fragmentFilename, std::string geometryFilename = "");
	bool bindProgram() const;
	void unbindProgram() const;
protected:
	std::string getShaderLog(GLuint shaderID) const;
	std::string getProgramLog() const;
	inline GLuint getProgramID() const;
private:
	GLuint shaderProgramID;
};

inline GLuint Shader::getProgramID() const
{
	return shaderProgramID;
}

#endif // SHADER_H_