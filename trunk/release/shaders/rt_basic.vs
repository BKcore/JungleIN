#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform mat3 viewMatrix;
uniform mat4 shadowMatrix;
uniform mat4 shadowMatrixCascade;
uniform int cascadeShadow;
uniform vec3 lightDir;

out vec2 fTexcoord;
out vec4 fNormal;
out vec4 fShadowcoord;
out vec4 fShadowcoordCascade;
out vec4 fLightDir;


void main()
{
  vec4 fPosition = vec4(position, 1.0f);

  gl_Position = mvp * fPosition;

  fTexcoord = texcoord;
  fNormal = vec4(normalMatrix * normal, 1.0f);

  fShadowcoord = shadowMatrix * fPosition;
  fShadowcoordCascade = shadowMatrixCascade * fPosition;

  fLightDir = vec4(viewMatrix * lightDir, 1.0f);
  fPosition = gl_Position;
}
