#shader vertex 
#version 450 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 fragmentcolor;

void main()
{
	gl_Position = position;
	fragmentcolor = color;
} 

#shader fragment 
#version 450 core 

layout(location = 0) out vec4 out_color;

in vec4 fragmentcolor;

void main()
{
	out_color = fragmentcolor;
}

