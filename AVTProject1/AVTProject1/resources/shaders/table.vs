#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 in_Position;
in vec3 VertexNormal;    //por causa do gerador de geometria
in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main ()
{   
	FragPos = vec3(modelMatrix * vec4(in_Position, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;  
    TexCoords = texCoord;
    
	gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}