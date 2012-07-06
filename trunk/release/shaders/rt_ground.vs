#version 400

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform mat3 viewMatrix;
uniform mat4 shadowMatrix;
uniform mat4 shadowMatrixCascade;
uniform int cascadeShadow;
uniform vec3 lightDir;

out vec4 fPosition;
out vec4 fNormal;
out vec4 fShadowcoord;
out vec4 fShadowcoordCascade;
out vec4 fLightDir;

void main()
{
  fPosition = vec4(position, 1.0f);

  gl_Position = mvp * fPosition;

  fShadowcoord = shadowMatrix * fPosition;
  if(cascadeShadow == 1) fShadowcoordCascade = shadowMatrixCascade * fPosition;

  fLightDir = vec4(viewMatrix * lightDir, 1.0f);

  fNormal = vec4(normalMatrix * normal, 1.0f);
}
