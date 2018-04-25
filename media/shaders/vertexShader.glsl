#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

// Output vertex data
out vec3 vertexPosition_out;
out vec3 vertexNormal_out;
out vec2 vertexUV_out;

out vec3 normalizedVertexPosition_out;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MV;

void main(){
	vertexPosition_out = vec3(MV * vec4(vertexPosition, 1));
	vertexNormal_out = normalize(vertexNormal * vertexNormal); //ToDo: revisar
	normalizedVertexPosition_out = normalize(-vertexPosition_out);
	
	// UV of the vertex. No special space for this one.
	vertexUV_out = vertexUV;

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition, 1);
}
