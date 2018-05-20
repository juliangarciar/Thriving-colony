#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;
uniform mat4 VP; // View-Projection matrix (the position is in BillboardPos; the orientation depends on the camera)
uniform vec3 position; // Position of the center of the billboard, in world units (probably meters)
uniform vec2 size; // Size of the billboard, in world units (probably meters)

void main(){
	vec3 vertexPosition_worldspace =
    position
    + CameraRight_worldspace * vertexPosition_modelspace.x * size.x
    + CameraUp_worldspace * vertexPosition_modelspace.y * size.y;
	
	gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);

	UV = vertexPosition_modelspace.xy + vec2(0.5, 0.5);
}