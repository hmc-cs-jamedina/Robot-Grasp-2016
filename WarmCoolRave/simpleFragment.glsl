//#version 330
/*#version 130
 
//layout(location = 0, index = 0) out vec4 fragColor;

varying vec4 vertex;
 
void main()
{
 gl_FragColor =  vec4( 0.0, 0.0, 1.0, 1.0 );
}
*/



/* !!GLSL */

varying vec4 eposition;
varying vec3 normal;
varying vec3 diffuseColor;
varying vec3 specularColor;
varying vec3 emissiveColor;
varying vec3 ambientColor;
varying float shininess;

void main()
  {
  const vec3 lightColor = vec3(1, 1, 1);
    const vec3 globalAmbient = vec3(0.2, 0.2, 0.2);

  // Position in eye space
    vec3 P = vec3(eposition);

  // Normalize normal in eye space
    vec3 N = normalize(normal);

  // Compute the emissive term
    vec3 emissive = emissiveColor;

  // Compute the ambient term
    vec3 ambient = ambientColor * globalAmbient;

  // Compute the diffuse term
  // Normalized vector toward the light source FROM WHERE BRO
    vec3 L = normalize(vec3(gl_LightSource[0].position) - P);
    //float diffuseLight = max(dot(N, L), 0);
    //vec3 diffuse = diffuseColor * lightColor * diffuseLight;	
    float NL = max(dot(N, L), 0);

//wermc00l
    float coolScalar = 0.7;
    float warmScalar = 0.2;
    vec3 Kcool = vec3(0, 0, 0.8) + coolScalar * diffuseColor.xyz;
    vec3 Kwarm = (vec3(0.9, 0.5, 0) + warmScalar * diffuseColor.xyz);

    float it = ((1.0 + 1.5* NL) / 2.0);
    vec3 color = (1.0-(0.8*it)) * Kcool + it * Kwarm;


  // Compute the specular term
/*
    vec3 V = normalize(-P);      // Normalized vector toward the viewpoint
    vec3 H = normalize(L + V);   // Normalized vector that is halfway between V and L
    float specularLight = pow(max(dot(N, H),0), shininess);
 //   if(diffuseLight <= 0){
 //   specularLight = 0;}
    vec3 specular = specularColor * lightColor * specularLight; */


  // Define the final vertex color
    gl_FragColor.xyz = color; //specular; //emissive + ambient + diffuse + specular;
    gl_FragColor.w = 1.0;
  }



