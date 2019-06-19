#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
    Normal = normal;
	TexCoords = texCoords;
	gl_Position	= projection *  model	* vec4(position, 1.0f);
}