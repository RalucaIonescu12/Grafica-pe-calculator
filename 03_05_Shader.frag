
//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_05_Shader.frag |
// =======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330	//  Versiunea GLSL;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;
in vec2 tex_Coord;		//	Coordonata de texturare;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//  Variabile uniforme;
uniform sampler2D myTexture;
uniform int ok;

//	Variabile pentru culori;
vec4 red = vec4(1.0,0.0,0.0,1.0);
vec4 green= vec4(0.0,1.0,0.0,1.0);

void main(void)
  {
  //  out_Color=ex_Color;
  //  out_Color=mix(red,green,0.9);
  if(ok == 1)
	out_Color = mix(texture(myTexture, tex_Coord), ex_Color, 0.0);	//	Amestecarea texturii si a culorii;
  else out_Color=ex_Color;
  }