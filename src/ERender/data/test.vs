#version 140

uniform mat4 projectionMatrix;
uniform float time;

in vec3 position;
in vec3 normal;

out vec3 t_normal;

void main(void)
{
    // перевод вершинных координат в однородные
    vec4 res = vec4(position, 1.0 );
    res.x += 2.0 * sin(time+res.y);
    res.y += 2.0 * sin(time+res.z);
    res.z += 2.0 * sin(time+res.x);


    gl_Position = projectionMatrix * res;

}