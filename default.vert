#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// outputs a vec3 color to the fragment shader
out vec3 color;

out vec2 texCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
   gl_Position = proj * view * model * vec4(aPos,1.0);
   // assigns the color to the Vertex Data 
   color = aColor;
   texCoord = aTex;
}