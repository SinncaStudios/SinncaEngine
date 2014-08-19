uniform sampler2D tex;

varying vec4 snColor;
varying vec2 texCo;

void main()
{
	//gl_FragColor = gl_Color * texture2D(tex, gl_TexCoord[0].xy);
	gl_FragColor = snColor * texture2D(tex, texCo);
}
