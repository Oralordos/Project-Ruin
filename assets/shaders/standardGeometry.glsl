#version 330 core

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in VertexData
{
	vec2 uv;
} vertexIn[];

out VertexData
{
	vec2 uv;
} vertexOut;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	vertexOut.uv = vertexIn[0].uv;
	EmitVertex();
	
	gl_Position = vec4(gl_in[1].gl_Position.x, gl_in[0].gl_Position.yzw);
	vertexOut.uv = vec2(vertexIn[1].uv.x, vertexIn[0].uv.y);
	EmitVertex();
	
	gl_Position = vec4(gl_in[0].gl_Position.x, gl_in[1].gl_Position.y, gl_in[0].gl_Position.zw);
	vertexOut.uv = vec2(vertexIn[0].uv.x, vertexIn[1].uv.y);
	EmitVertex();
	
	gl_Position = gl_in[1].gl_Position;
	vertexOut.uv = vertexIn[1].uv;
	EmitVertex();
}
