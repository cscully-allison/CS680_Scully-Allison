#version 330
          
          layout (location = 0) in vec3 v_position; 
          layout (location = 1) in vec2 v_texture; 
          
          smooth out vec2 texture; 
          
          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix; 
          uniform mat4 modelMatrix;
          
          void main(void) 
          { 
            vec4 v = vec4(v_position, 1.0); 
            gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v; 
            texture = v_texture; 
          } 

