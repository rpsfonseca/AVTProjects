#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 in_Position;
//in vec4 VertexColor;
in vec3 VertexNormal;
in vec2 texCoord;

//out vec4 Color;
out vec3 Normal;
out vec3 Position;
out vec3 world_normal;
out vec4 viewSpace;

/*uniform sharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};*/

void main(void)
{
	//Color = in_Position;

	world_normal = normalize(mat3(modelMatrix) * VertexNormal);
	viewSpace = viewMatrix * modelMatrix * vec4(in_Position,1);
	
	Position = vec3(modelMatrix * vec4(in_Position,1.0));
	Normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;

	gl_Position = projectionMatrix * viewMatrix * vec4(Position,1.0);
}