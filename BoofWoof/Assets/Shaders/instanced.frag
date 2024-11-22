
#version 450 core
out vec4 fragColor;

layout(location = 0) in float visibility;

void main()
{
      if(visibility < 0.5f){
            fragColor = vec4(1.0, 0.0, 0.0, 0.0); // Solid color with full opacity
      }else{ 
            fragColor = vec4(1.0, 1.0, 0.0, 1.0); // Solid color with full opacity
      }  
}

/*layout(location = 0) in vec3 vertColor;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 FragPos;
layout(location = 3) in vec2 TexCoords;


uniform sampler2D texture;

out vec4 fragColor;

void main()
{

    
        //vec3 lightVector = lightPos - FragPos;
        //float N_dot_L = max( dot( normalize(vertNormal), normalize(lightVector)), 0.0f );
        fragColor = vec4(vertColor, 1.0f);

}*/
