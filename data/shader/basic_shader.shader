#shader vertex 
#version 450 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texturecord;

out vec4 fragmentcolor;
out vec2 textureuv;

void main()
{
	gl_Position = position;
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

