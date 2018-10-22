#version 330 core

in vec4 in_Position;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

/*uniform sharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};*/

out vec4 color;

void main(void)
{
	color = in_Position;
	//gl_Position = modelMatrix * in_Position;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
}