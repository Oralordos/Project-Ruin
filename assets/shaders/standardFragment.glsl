#version 330 core

in VertexData
{
	vec2 uv;
} vertexIn;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, vertexIn.uv).rgb;
}
