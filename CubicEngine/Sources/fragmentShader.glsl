#version 330 core

out vec3 color;

void main() {
	int r = 255;
	int g = 255;
	int b = 255;
	color = vec3(r/255,g/255,b/255);
}