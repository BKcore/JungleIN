#version 400

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 shadowMatrix;
uniform vec3 lightDir;

out vec3 fPosition;
out vec3 fNormal;
out vec4 fShadowcoord;
out vec3 fLightDir;

out vec3 fTangent;
out vec3 fBinormal;

void computeTangentSpace(vec3 normal)
{
	vec3 tangent; 
	vec3 binormal; 
	
	vec3 c1 = cross(normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(normal, vec3(0.0, 1.0, 0.0)); 
	
	if(length(c1)>length(c2))
	{
		tangent = c1;	
	}
	else
	{
		tangent = c2;	
	}
	
	fTangent = normalize(tangent);
	
	binormal = cross(normal, tangent); 
	fBinormal = normalize(binormal);
}

void main()
{
  gl_Position = mvp * vec4(position, 1.0f);

  fPosition = position;
  fShadowcoord = shadowMatrix * vec4(position, 1.0f);
  fLightDir = vec3(mv * vec4(lightDir, 1.0f));

  vec3 normal = vec3(mv * vec4(normalize(normal), 1.0f));
  fNormal = normal;
  computeTangentSpace(normal);
}
