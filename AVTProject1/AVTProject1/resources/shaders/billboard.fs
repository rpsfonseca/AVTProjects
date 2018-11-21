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
	vec4 texel = texture( myTextureSampler, TexCoords );
	if(texel.a == 0.0)
	{
		discard;
	}
	else
	{
		color = texel;
		//colorOut = vec4(max(intensity*texel.rgb + spec, 0.1*texel.rgb), texel.a);
	}

	//color = vec4(1.0);
}