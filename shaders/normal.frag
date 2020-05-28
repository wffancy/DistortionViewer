#version 120    //only support this version and before

uniform sampler2D rttTexture;

void main()
{
	vec2 v2 = gl_TexCoord[0].xy;
	gl_FragColor = texture2D(rttTexture, v2);
}
