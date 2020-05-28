#version 120    //only support this version and before

uniform sampler2D rttTexture;
uniform float factor[5];
uniform float scale;
uniform float aspectRatio;

void main()
{
    /*scale*/
    vec2 v2 = gl_TexCoord[0].xy;
    vec2 mid = v2 - vec2(0.5,0.5);
    mid *= scale;
	mid.x *= aspectRatio;
    v2 = mid + vec2(0.5,0.5);
    
    //Polynomial Models
    vec2 center = vec2(0.5,0.5);
    vec2 temp = v2 - center;
    float r2 = length(temp) * length(temp);
    vec2 coord = (v2 - center) * (factor[0] + factor[2]*r2 + factor[4]*r2*r2) + center;
    
	mid = coord - vec2(0.5,0.5);
	mid.x /= aspectRatio;
	coord = mid + vec2(0.5,0.5);
    gl_FragColor = texture2D(rttTexture, coord);
}
