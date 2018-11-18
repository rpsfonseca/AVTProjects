#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

in vec3 in_Position;
in vec3 VertexNormal;
layout(location = 2) in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main ()
{   
    TexCoords = texCoord;
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(in_Position.x, in_Position.y, 0.0, 1.0);
}