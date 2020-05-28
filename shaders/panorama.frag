#version 120    //only support this version and before

uniform sampler2D rttTexture;
uniform float scale;
uniform float fovy;
uniform float aspectRatio;

vec2 CylinderInBack(vec2 pos);
vec2 CylinderInFront(vec2 pos);
vec2 Sphere(vec2 pos);

void main()
{
    /*scale*/
    vec2 v2 = gl_TexCoord[0].xy;
    vec2 mid = v2 - vec2(0.5,0.5);
    mid *= scale;
    v2 = mid + vec2(0.5,0.5);
    
	vec2 coord = CylinderInBack(v2);
//	  vec2 coord = Sphere(v2);

    gl_FragColor = texture2D(rttTexture, coord);
}

vec2 CylinderInBack(vec2 pos)
{
    float FOV_Y = radians(fovy);
    float x = pos.x;
    float y = pos.y;
    float f = 0.5/tan(FOV_Y/2.0);   //undistorted plane as unit
	float FOV_X = atan( aspectRatio*0.5 / f ) * 2.0;
    float r = f / cos(FOV_X/2);
    float x_mid1,x_mid2,y_mid2;
    
	x *= r * FOV_X;
    x_mid1 = x>=FOV_X*r*0.5 ? tan(abs(FOV_X/2.0-x/r))*f : -tan(abs(FOV_X/2.0-x/r))*f;
    x_mid2 = f/cos(abs(FOV_X/2-x/r));
    y_mid2 = y>=0.5 ? x_mid2*abs(y-0.5)/r : -x_mid2*abs(y-0.5)/r;
	x_mid1 /= r * FOV_X;
    return vec2(x_mid1,y_mid2) + vec2(0.5,0.5);
}

vec2 Sphere(vec2 pos)   //lose some pixels
{
    float FOV_Y = radians(fovy);
    float x = pos.x;
    float y = pos.y;
    float f = 0.5/tan(FOV_Y/2.0);	//undistorted plane as unit
    float R = sqrt(f*f+0.25+0.25);
    float tita = x/R - 1.0/(2*R);
    float pai =acos(-1.0);
    float fai = -y/R + pai/2.0 + 1.0/(2*R);

    float x_prim = sin(tita)*f/cos(tita);
    float y_prim = cos(fai)*f/(cos(tita)*sin(fai));

    return vec2(x_prim,y_prim) + vec2(0.5,0.5);
}
