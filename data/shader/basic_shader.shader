#shader vertex 
#version 450 core 

// Shader program assign vec4.w as 
// 1.0f if the value coming from inside
// of type vec3 

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texturecord;

out vec4 fragmentcolor;
out vec2 textureuv;

uniform mat4 transformation;

void main()
{
	gl_Position = transformation * position;
	fragmentcolor = color;
	textureuv = texturecord;
} 

#shader fragment 
#version 450 core 

layout(location = 0) out vec4 out_color;

in vec4 fragmentcolor;
in vec2 textureuv;

uniform sampler2D texture1;

void main()
{
	out_color = texture(texture1, textureuv);
}

