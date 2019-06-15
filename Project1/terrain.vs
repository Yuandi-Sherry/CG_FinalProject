#version 330 core
uniform mat4 projection;
uniform mat4 modelview;
uniform vec3 lightPosition;

// Transformation matrix from camera view to light view.
uniform mat4 lightOffsetMVP;

// Texture 0. Defined by glActiveTexture and passed by glUniform1i.
uniform sampler2D heightMapTex;

// First input buffer. Defined here, retrieved in C++ by glGetAttribLocation.
layout(location = 0) in vec2 position;

//for animate the wave
uniform float time;

// Position (world coordinates) after heightmap displacement.
// Add suffix for coordinate system.
out vec3 displaced;
//light direction
out vec3 light_dir;
//view direction
out vec3 view_dir;
// ShadowCoord is the position of the vertex as seen from the last camera (the light)
out vec4 ShadowCoord;
//
out vec3 displaced_mv;


void main() {

    // World (triangle grid) coordinates are (-1,-1) x (1,1).
    // Texture (height map) coordinates are (0,0) x (1,1).
    vec2 UV = (position + 1.0) / 2.0;
    float height = texture(heightMapTex, UV).r;

	// Generate wave using sin function
	if(height <= 0.01f)
	{
		height = sin(-6.28*position.x - 6.28*position.y+time*0.07) * 0.008; 
	}

	displaced = vec3(position.xy, height);
	
    // Vertex in camera space then projection/clip space.
    // gl_Position is the position of the vertex as seen from the current camera
    vec4 position_mv = modelview * vec4(displaced.xyz,  1.0);
    gl_Position = projection * position_mv;

    //vertex position in camera coordinate
    displaced_mv = vec3(gl_Position);

    //compute the light direction

    view_dir = vec3(position_mv);
	light_dir = normalize(lightPosition - view_dir);

    // ShadowCoord is the position of the vertex as seen from the last camera (the light)
    ShadowCoord = lightOffsetMVP * vec4(displaced,1);

}
