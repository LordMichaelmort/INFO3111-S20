#version 420

in vec4 colour;

void main()
{
    //gl_FragColor = vec4(colour, 1.0);
	gl_FragColor = colour;
}
