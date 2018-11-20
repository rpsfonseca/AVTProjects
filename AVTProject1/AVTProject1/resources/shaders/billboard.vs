#version 330 core

// Input vertex data, different for all executions of this shader.
//layout(location = 0) in vec3 squareVertices;

in vec3 in_Position;
in vec3 VertexNormal;    //por causa do gerador de geometria
in vec2 texCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;



void main()
{

	FragPos = vec3(viewMatrix * modelMatrix * vec4(in_Position, 1.0));
	Normal = mat3(transpose(inverse(modelMatrix))) * VertexNormal;
    TexCoords = texCoord;

	// Output position of the vertex
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);



	// Or, if BillboardSize is in percentage of the screen size (1,1 for fullscreen) :
	//vertexPosition_worldspace = particleCenter_wordspace;
	//gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition_worldspace, 1.0f); // Get the screen-space position of the particle's center
	//gl_Position /= gl_Position.w; // Here we have to do the perspective division ourselves.
	//gl_Position.xy += in_Position.xy * vec2(0.2, 0.05); // Move the vertex in directly screen space. No need for CameraUp/Right_worlspace here.
	
	// Or, if BillboardSize is in pixels : 
	// Same thing, just use (ScreenSizeInPixels / BillboardSizeInPixels) instead of BillboardSizeInScreenPercentage.


	// UV of the vertex. No special space for this one.
	//UV = in_Position.xy + vec2(0.5, 0.5);

}
