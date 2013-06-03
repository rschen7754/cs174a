//#version 120

attribute   vec4 vPosition;
attribute   vec3 vNormal;
//attribute   vec2 vTexCoords;

//// output values that will be interpretated per-fragment


uniform mat4 ModelView;
//  uniform mat4 View;
uniform vec4 LightPosition;
uniform mat4 Projection;
uniform mat4 Transformation;

varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

// Collin's Code:
uniform vec4 fcolor;
varying vec4 color;

void main()
{
    //    vec4 N = vec4(vNormal, 0.0f);
    //    fN =  (ModelView * N).xyz; //not correct, should be inverse(transpose(ModelView)); only for version 150 or higher.
    //    fE = -(ModelView * vPosition).xyz;
    //    fL =  (LightPosition).xyz;
    //    //fL = (View * LightPosition).xyz;
    //
    //    if( LightPosition.w != 0.0 )
    //    {
    //        fL = LightPosition.xyz - vPosition.xyz;
    //    }
    //
    //    gl_Position = Projection * ModelView * vPosition;
    //    gl_TexCoord[0].xy = vTexCoords;


//    fN = (ModelView*Transformation*vec4(vNormal,0)).xyz;
//    fE =-(ModelView*Transformation*vPosition).xyz;
//    fL = (ModelView*(LightPosition-Transformation*vPosition)).xyz;
//
//    vec3 N,V,L,H;
//    N = normalize(fN);
//    V = normalize(fE);
//    L = normalize(fL);
//    H = normalize(L + V);
//
//    vec4 ambient = 0.2*fcolor;
//    vec4 diffuse = max(dot(L,N),0.0)*0.5*fcolor;
//    vec4 specular = pow(max(dot(N,H),0.0),20.0)*0.5*vec4(1.0,1.0,1.0,1.0);
//    if(dot(L,N) < 0.0){
//    specular = vec4(0.0,0.0,0.0,1.0);
//    }

   // color = ambient + diffuse + specular;

    // Collin's Code:
    gl_Position =  Projection*ModelView*vPosition;;
    color = fcolor;
}
