#shader name
FlatColor
#shader vertex
#version 330 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec3 normal;
layout ( location = 2 ) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main( )
{
    gl_Position = projection * view * model * vec4(position, 1.0);
}

#shader fragment
#version 330 core

out vec4 color;

uniform vec3 flatColor;

void main( )
{
    color = vec4(flatColor, 1.0f);
}