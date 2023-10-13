#version 330 core                                    
  in vec4 color;                                       
  in vec2 texCoords;                                     
  out vec4 outColor;                                   
  uniform sampler2D ourTexture;                          
  void main(){                                           
      outColor = texture(ourTexture, texCoords) * color;
      }