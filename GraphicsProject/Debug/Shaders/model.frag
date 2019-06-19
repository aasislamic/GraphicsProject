#version 430

in vec2 TexCoords;
in vec3 Normal;

out vec4 finalColor;
uniform vec3 color;

void main() {

  vec3 lightDir =	vec3(-1.0f, 1.0f, -1.0f);
  vec3 l = normalize(lightDir);
  vec3 n = normalize(Normal);
  vec3 diffuse = max(dot(n, l), 0.1f) * color;
  diffuse = pow(diffuse, vec3(1.0f/2.2f));
  finalColor = vec4(diffuse, 1.0f);
}