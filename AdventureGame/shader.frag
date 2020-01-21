uniform sampler2D texture;

void main()
{
    float px = 850.0;//centers light in the middle
    float py =  1050.0;
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float x = gl_FragCoord[0];//gets coordinates
    float y = gl_FragCoord[1];

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;//gets colour of the pixel
    float radius = sqrt(pow((x-px),2)+pow((y-py),2));//uses the light inverse square law to illuminate things
    if (gl_FragColor[3] != 0)
    {
        if (radius>100)//just changing brightness levels to make it darker
        {
            gl_FragColor[0] *= 50/radius;
            gl_FragColor[1] *= 50/radius;
            gl_FragColor[2] *= 50/radius;
        }
        else
        {
            if (60/radius >= 0.7)//max brightness
            {
                gl_FragColor[0] *= 0.7;
                gl_FragColor[1] *= 0.7;
                gl_FragColor[2] *= 0.7;
            }
            else
            {
                gl_FragColor[0] *= 60/radius;
                gl_FragColor[1] *= 60/radius;
                gl_FragColor[2] *= 60/radius;
            }
        }
    }
}
