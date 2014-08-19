attribute vec4 position;
attribute vec4 vertColor;
attribute vec2 texCoord;

uniform vec4 mainColor;
uniform mat4 MVMatrix;
uniform mat3 NORMatrix;

varying vec4 snColor = mainColor;
varying vec2 texCo;

void main()
{
	//gl_FrontColor = gl_Color;
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_Position = ftransform();
	
	texCo = texCoord;
	gl_Position = MVMatrix * position;
}
