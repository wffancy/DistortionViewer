#version 120    //only support this version and before

uniform sampler2D rttTexture;
uniform float scale;
uniform float fovy;
uniform float aspectRatio;

vec2 Equidistance_Fisheye(vec2 pos);
vec2 Orthogonal_projection(vec2 pos);
vec2 FOVModel(vec2 pos);
vec2 TransformModel(vec2 pos);

void main()
{
    /*scale*/
    vec2 v2 = gl_TexCoord[0].xy;
    vec2 mid = v2 - vec2(0.5,0.5);
    mid *= scale;
	mid.x *= aspectRatio;
    v2 = mid + vec2(0.5,0.5);

    vec2 coord = Equidistance_Fisheye(v2);
//    vec2 coord = Orthogonal_projection(v2);
//    vec2 coord = FOVModel(v2);
//    vec2 coord = TransformModel(v2);

	mid = coord - vec2(0.5,0.5);
	mid.x /= aspectRatio;
	coord = mid + vec2(0.5,0.5);

    gl_FragColor = texture2D(rttTexture, coord);
}

vec2 Equidistance_Fisheye(vec2 pos)
{
    float FOV = radians(fovy);
    float f = 0.5/tan(FOV/2);
    vec2 center = vec2(0.5,0.5);
    vec2 dpos = pos - center;
    float theta = atan(dpos.y, dpos.x);
    float r = length(dpos);

    float ru = f * tan(r/f);
    float xu = ru * cos(theta);
    float yu = ru * sin(theta);

    return vec2(xu,yu) + center;
}

vec2 Orthogonal_projection(vec2 pos)
{
    float FOV = radians(fovy);
    float f = 0.5/tan(FOV/2);
    vec2 center = vec2(0.5,0.5);
    vec2 dpos = pos - center;
    float theta = atan(dpos.y, dpos.x);
    float r = length(dpos);

    float mid_prim = clamp(r/f,-1.0,1.0);   //arcsin的定义域为[-1,1]
    float ru = f * tan(asin(mid_prim));
    float xu = ru * cos(theta);
    float yu = ru * sin(theta);

    return vec2(xu,yu) + center;
}

vec2 FOVModel(vec2 pos)
{
    float FOV = radians(fovy);
    vec2 center = vec2(0.5,0.5);
    vec2 dpos = pos - center;
    float theta = atan(dpos.y, dpos.x);
    float r = length(dpos);

    float ru = tan(r*FOV)/(2.0 * tan(FOV/2.0));
    float xu = ru * cos(theta);
    float yu = ru * sin(theta);

    return vec2(xu,yu) + center;
}

vec2 TransformModel(vec2 pos)
{
    float s = 0.3;
    float namda = 10.0;
    
    vec2 center = vec2(0.5,0.5);
    vec2 dpos = pos - center;
    float theta = atan(dpos.y, dpos.x);
    float r = length(dpos);

    float temp = exp(r/s)-1.0;
    float ru = temp/namda;
    float xu = ru * cos(theta);
    float yu = ru * sin(theta);

    return vec2(xu,yu) + center;
}
