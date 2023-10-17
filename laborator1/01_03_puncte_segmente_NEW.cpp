//
// =================================================
// | Grafica pe calculator                         |
// =================================================
// | Laboratorul I - 01_03_puncte_segmente_OLD.cpp |
// =================================================
//
//	Program ce desenaza mai multe segmente de dreapta si puncte individuale, folosindu-se tehnicile OLD OpenGL;
//
//
//	Biblioteci
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>  
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
GLuint
VaoId,
VboId,
ColorBufferId,
VertexShaderId,
FragmentShaderId,
ProgramId;
const GLchar* VertexShader =
{
	  "#version 400\n"\

	  "layout(location=0) in vec4 in_Position;\n"\
	  "layout(location=1) in vec4 in_Color;\n"\
	  "out vec4 ex_Color;\n"\

	  "void main(void)\n"\
	  "{\n"\
	  "  gl_Position = in_Position;\n"\
	  "  ex_Color = in_Color;\n"\
	  "}\n"
};

//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
const GLchar* FragmentShader =
{
	  "#version 400\n"\

	  "in vec4 ex_Color;\n"\
	  "out vec4 fragColor;\n"\

	  "void main(void)\n"\
	  "{\n"\
	  "  fragColor = ex_Color;\n"\
	  "}\n"
};
void CreateShaders(void)
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);
}
void CreateVBO(void)
{
    //  Coordonatele varfurilor;
    GLfloat Vertices[] = {
    -0.8f, -0.3f, 0.0f, 1.0f,
	 -0.3f, 0.4f, 0.0f, 1.0f,
	 0.0f, 0.6f, 0.0f, 1.0f,
	 -0.3f, 0.2f, 0.0f, 1.0f,
	 0.0f, 0.4f, 0.0f, 1.0f,
	 0.2f, 0.5f, 0.0f, 1.0f,
	 0.1f, 0.8f, 0.0f, 1.0f,

	 //puncte
	  -0.5f, 0.4f, 0.0f, 1.0f,
	 -0.8f, 0.1f, 0.0f, 1.0f,
	 -0.8f, -0.7f, 0.0f, 1.0f,
	 -0.5f, -0.5f, 0.0f, 1.0f,
       //
    };

    //  Culorile in spectrul RGB ca atribute ale varfurilor;
    GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		//puncte
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
    //  Transmiterea datelor prin buffere;0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };



    //  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
    glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
    glBindVertexArray(VaoId);

    //  Se creeaza un buffer pentru VARFURI;
    glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
    glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
    //  Se asociaza atributul (0 = coordonate) pentru shader;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //  Se creeaza un buffer pentru CULOARE;
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    //  Se asociaza atributul (1 =  culoare) pentru shader;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare
void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);		//  Culoarea de fond a ecranului;
	CreateVBO();
    //glMatrixMode(GL_PROJECTION);			//	Se precizeaza ca este vorba de o reprezentare 2D, realizata prin proiectie ortogonala;
	//gluOrtho2D(0.0, 1200.0, 0.0, 700.0);	//  Sunt indicate coordonatele extreme ale ferestrei de vizualizare;
	CreateShaders();
}

//  Functia de desenarea a graficii pe ecran;
//	Comentati/decomentati linii de cod pentru afisari diferite;
void RenderFunction(void)  
{
	glClear(GL_COLOR_BUFFER_BIT);	//  Se curata ecranul de vizualizare pentru a fi desenat noul continut;
	
	//	Toate primitivelele definite vor avea specificatiile de mai jos (culoare, dimensiune) pana la o noua schimbare a acestora;

	glPointSize(2.5);				//  Se seteaza dimensiunea punctelor;
	//glColor3f(0.0, 0.0, 1.0);		//  Culoarea punctelor: albastru;

	//	Desenare puncte in 2D, coordonate valori intregi (2i);
	//  Functia glBegin(arg) primeste un argument care specifica tipul primitivei desenate - puncte;
	//  Finalizarea desenarii primitivei este marcata de glEnd;

	//glBegin (GL_POINTS);
	//	glVertex2i(20, 20);
	//	glVertex2i(21, 21);
	//	glVertex2i(22, 22);
	//	glVertex2i(23, 23);
	//	glVertex2i(24, 24);
	//	glVertex2i(27, 27);
	//	glVertex2i(100, 100);
	//glEnd();
		   
	//glColor3d(0.0, 0.05, 0.05);		//	Se schimba culoarea si dimensiunea punctului;
	//glPointSize(6.0);

	//	Desenare puncte;

	/*glBegin(GL_POINTS);
		glVertex2i(100, 400);
		glColor3f(1.0, 0.0, 0.5);
		glVertex2i(300, 500);
	glEnd();*/

	//glColor3f(1.0, 0.0, 0.0);		//  Se schimba culoarea si dimensiunea punctului;
	//glLineWidth (2.0);
	//glEnable (GL_LINE_STIPPLE);	//	Liniile devin punctate;
	//glLineStipple (1, 0x1EED);

	//	Se deseneaza o linie franta;

 /*   glBegin(GL_LINE_STRIP); 
		glVertex2i(0,100);
		glVertex2i(400, 500);
		glVertex2i(600, 600);
    glEnd();*/
	
	//glDisable (GL_LINE_STIPPLE);
	//glColor3f (0.5, 0.0, 1.0);  
	//glLineWidth (6.0);
	
	//	Se deseneaza o reuniune de segmente;

	//glBegin (GL_LINES); 
 //      glVertex2i(400,400);		//	Segmentul 1;
	//   glVertex2i(600, 500);
	//   glVertex2i(700, 520);	//	Segmentul 2;
	//   glVertex2i(655, 690);
 //   glEnd();
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 1, 2);
	glDrawArrays(GL_LINES, 3, 2);
	glDrawArrays(GL_LINES, 5, 2);

	glPointSize(7.0);
	glDrawArrays(GL_POINTS, 7, 2);
	glPointSize(8.0);
	glDrawArrays(GL_POINTS, 9, 1);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 10, 1);
	
    glFlush();    //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru varfuri, culori;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}
//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char** argv)
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);				//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowPosition(100, 100);							//  Pozitia initiala a ferestrei;
	glutInitWindowSize(600, 350);								//  Dimensiunea ferestrei;
	glutCreateWindow ("Puncte & Segmente - OpenGL <<vechi>>");	//	Creeaza fereastra de vizualizare, indicand numele acesteia;
	glewInit();
	Initialize();									//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);				//  Desenarea scenei in fereastra; 
	glutCloseFunc(Cleanup);
	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra de vizualizare pana cand utilizatorul o inchide;

	glutMainLoop ();

	return 0;
}