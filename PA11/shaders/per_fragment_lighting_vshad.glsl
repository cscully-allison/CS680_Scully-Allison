#version 330
          
          layout (location = 0) in vec4 position;
          layout (location = 1) in vec3 normal;
          layout (location = 2) in vec2 texture; 
          layout (location = 3) in vec3 Ka;
          layout (location = 4) in vec3 Ks;

          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix; 
          uniform mat4 modelMatrix;
          
          uniform vec3 diffuse;
          uniform vec3 scalar;
          uniform vec3 spec;
          uniform vec3 spot;
          uniform vec3 height;
          uniform vec3 eyePos;

          out VS_OUT{
            vec3 N;  //normal
            vec3 L;  //light source
            vec3 V;  //view
            vec3 L2;  //2nd light source

            // material properties
            vec3 Ka;
            vec2 texture;
            vec3 Ks;

            vec3 diffuse;
            vec3 scalar;
            vec3 spot;
            vec3 spec;  //scalar
            vec3 light_color;            

            // spotlight
            vec3 spotlightPos;
            vec3 spotLightDir;

          } vs_out;

          
          void main(void) 
          { 
            //light positions
            
            vec3 light_pos = vec3(500.0, 100.0, 100.0);
            vec3 light_pos2 = vec3(-500.0, 100.0, -150.0);
            vs_out.spotlightPos = spot;
            vs_out.spotLightDir = vec3(0.0,-1.0,0.0);

            //vec3 light_pos = spot - vec3(10.0, 0.0, 10.0);
            //vec3 light_pos2 = spot;


            if(true){
                vs_out.light_color = vec3(1.0,1.0,1.0);
            }

            //view space coordinate
            vec4 p = modelMatrix * position;


            // Calculate normal in view space
            vs_out.N = mat3(modelMatrix) * normal;

            //Caluclate light vector
            vs_out.L = light_pos - p.xyz;

            //Caluclate 2nd light vector
            vs_out.L2 = light_pos2 - p.xyz;

            vs_out.spotlightPos = spot - p.xyz;
            vs_out.spotLightDir = normalize(-spot.xyz);

            //calculate view vector
            vs_out.V = eyePos;

            //get gl_Position
            gl_Position = projectionMatrix * viewMatrix * p;

            // pass other values to the fragment shader
            vs_out.Ks = Ks;
            vs_out.Ka = Ka;
            vs_out.texture = texture;

            vs_out.diffuse = diffuse; 
            vs_out.scalar = scalar;
            vs_out.spec = spec;
            vs_out.spot = spot;
          } 
