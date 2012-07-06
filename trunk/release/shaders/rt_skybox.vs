#version 400

layout (location = 0) in vec3 position;

uniform mat4 mvp;

out vec3 pos;


void main()
{
  gl_Position = mvp * vec4(position, 1.0f);

  pos = position;
}
