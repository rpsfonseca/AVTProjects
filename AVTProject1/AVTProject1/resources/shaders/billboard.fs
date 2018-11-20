#version 330 core

// Interpolated values from the vertex shaders

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, TexCoords );
	//color = vec4(1.0);
}