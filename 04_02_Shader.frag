//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_02_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;
in vec2 ex_TextureCoord;
//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;
uniform sampler2D textureSampler; 
void main(void)
  {
    out_Color = texture(textureSampler, ex_TextureCoord) * ex_Color;
  }