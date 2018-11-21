#version 330
precision highp float;
uniform sampler2D texture0;
in vec2 TexCoords;
uniform vec4 tint;
out vec4 FragColor;

void main() {
	FragColor = texture(texture0, TexCoords) * tint;
    //FragColor = vec4(1.0, 0.5, 1.0, 1.0);
}
