uniform sampler2D texture1;
//uniform vec2 size;

void main()
{
    vec2 v2 = gl_TexCoord[0].xy;

    //inverse_equirectangular
    float pai = 4.0 * atan(1.0);
    
    float fai_ = (1.0 - v2.x) * pai;
    float tita_ = (1.0 - v2.y) * pai;
    
    float x = sin(tita_) * cos(fai_);
    float y = cos(tita_);
    float z = sin(tita_) * sin(fai_);
    
    float tita = acos(z);
    float fai;
    if(y>=0.0)
    {
        if(x==0.0 && y==0.0)
        {
            fai = 0.0;
        }
        else
        {
            fai = acos(x/sqrt(x*x + y*y));
        }
    }
    else
    {
        fai = 2.0*pai - acos(x/sqrt(x*x + y*y));
    }
    
    float alfa = pai;
    float r = (tita * 2.0)/ alfa;
    
    float x_final,y_final;
    
    x_final = r * cos(fai) / 2.0 + 0.5;
    y_final = r * sin(fai) / 2.0 + 0.5;

    vec2 coord = vec2(x_final ,y_final);
    
    gl_FragColor = texture2D(texture1, coord);

}
