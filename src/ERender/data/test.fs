#version 140

uniform vec2 resolution;
uniform float time;

in vec3 t_normal;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor  = vec4(1.0);
}