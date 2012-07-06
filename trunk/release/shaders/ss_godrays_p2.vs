#version 400

in vec2 position;

//uniform sampler2D ssTex;

out vec2 uv;

void main()
{
  gl_Position = vec4(position, 0.0f, 1.0f);

  uv = position * 0.5 + 0.5;
}
