#version 330 core

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec2 vertexUV;

out VertexData
{
	vec2 uv;
} vertexOut;

void main()
{
	gl_Position.xy = vertexPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	vertexOut.uv = vertexUV;
}
