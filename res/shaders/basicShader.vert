#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 color;

varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec3 v_color;

uniform mat4 transform;
uniform mat4 view;

void main() {
    
    gl_Position = view * transform * vec4(position, 1.0);
    v_texCoord = texCoord;
    v_color = color;
    v_normal = (view * transform * vec4(normal, 0.0)).xyz;

}