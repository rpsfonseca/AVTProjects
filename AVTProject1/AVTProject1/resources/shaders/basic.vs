#version 330 core

in vec4 in_Position;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec4 VertexColor;
in vec3 VertexNormal;

out vec4 Color;
out vec3 Normal;
out vec3 Position;

/*uniform sharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};*/

void main(void)
{
	Color = in_Position;
	Normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
	//gl_Position = modelMatrix * in_Position;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
	Position = vec3(gl_Position);
}