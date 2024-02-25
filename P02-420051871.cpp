//Práctica 2 semestre 2024-1: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//shaders nuevos se crearían acá
static const char* vShaderRojo = "shaders/ShaderRojo.vert";
static const char* fShaderRojo = "shaders/shader.frag";

static const char* vShaderVerde = "shaders/ShaderVerde.vert";
static const char* fShaderVerde = "shaders/shader.frag";

static const char* vShaderCafe = "shaders/ShaderCafe.vert";
static const char* fShaderCafe = "shaders/shader.frag";

static const char* vShaderAzul = "shaders/ShaderAzul.vert";
static const char* fShaderAzul = "shaders/shader.frag";

static const char* vShaderVerdeOscuro = "shaders/ShaderVerdeOsc.vert";
static const char* fShaderVerdeOscuro = "shaders/shader.frag";



float angulo = 0.0f;
//color café: 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {

		// lETRA J
		-0.65f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.65f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  //ABD
		-0.55f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.55f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.55f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.65f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.65f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.55f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.55f, -0.58f, 0.0f, 0.0f, 1.0f, 0.0f,
		
		-0.55f, -0.58f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.65f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,  //FBG
		-0.62f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f,
		 
		-0.65f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.62f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f, //BGH
		-0.7f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f,

		-0.65f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.7f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f,      //BHJ
		-0.8f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f,

		-0.65f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.8f, -0.62f,0.0f,	    0.0f,1.0f, 0.0f,		
		-0.8f, -0.5f,0.0f,	    0.0f,1.0f, 0.0f,
	
		//LETRA U

		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,		//LNM
		-0.4f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		-0.4f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  //LMO
		-0.4f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.4f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, //NMP
		-0.4f, -0.6f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.4f, -0.6f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, 0.0f, 1.0f, 1.0f, 0.0f, //PRQ
		-0.2f, -0.4f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.4f, -0.6f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.2f, -0.4f, 0.0f, 1.0f, 1.0f, 0.0f, //PQS
		-0.2f, -0.6f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.2f, -0.6f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, //STU
		-0.2f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.2f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, //TUW
		-0.2f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.2f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, //WVT
		-0.1f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		//LERTRA G
		0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.005f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //AZB
		0.1f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, //ABC
		0.5f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.005f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, //ZBE
		-0.005f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 
		-0.005f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //BEF
		0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.005f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //EFG
		0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,//HGI
		0.4f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.1f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.5f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //KJL
		0.5f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //JLM
		0.5f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.4f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.4f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

		// LETRA F
		
		0.6f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.6f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.7f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.6f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.7f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.7f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.9f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.9f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, sizeof(vertices_letras) / sizeof(vertices_letras[0]));
	meshColorList.push_back(letras);

	// Triangulo rojo
	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	// Triangulo azul
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	// Triangulo verde
	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	//Cuadrado verde 
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	//Cuadrado rojo
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	//Cuadrado café
	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);

}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //Shader para  índices:  cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderRojo, fShaderRojo);  //Shader  rojo
	shaderList.push_back(*shaderRojo);

	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderVerde, fShaderVerde);  //Shader  verde
	shaderList.push_back(*shaderVerde);

	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderCafe, fShaderCafe);  //Shader  cafe
	shaderList.push_back(*shaderCafe);

	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderAzul, fShaderAzul);  //Shader  azul
	shaderList.push_back(*shaderAzul);

	Shader* shaderVerdeOscuro = new Shader();
	shaderVerdeOscuro->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro);  //Shader verde oscuro
	shaderList.push_back(*shaderVerdeOscuro);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); 
	CrearCubo();
	CrearLetrasyFiguras(); 
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	

	glm::mat4 model(1.0); 

	glm::mat4 figuras(1.0);

	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//Letras 

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(-0.2f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		
		// Casa
		
		//Estructura casa
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		angulo += 0.01;
		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.0f, -0.7f, -4.0f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		figuras = glm::scale(figuras, glm::vec3(1.5f, 2.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		
		//Ventana y puerta
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.25f, -0.2f, -3.0f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		figuras = glm::scale(figuras, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(-0.25f, -0.2f, -3.0f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		figuras = glm::scale(figuras, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.0f, -1.25f, -3.0f));
		figuras = glm::scale(figuras, glm::vec3(0.35f, 0.45f, 0.3f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Techo
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.0f, 0.5f, -1.95f));
		figuras = glm::scale(figuras, glm::vec3(1.09f, 0.7f, 0.5f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Troncos
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(-0.80f, -0.9f, -2.1f));
		figuras = glm::scale(figuras, glm::vec3(0.2f, 0.3f, 0.18f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.80f, -0.9f, -2.1f));
		figuras = glm::scale(figuras, glm::vec3(0.2f, 0.3f, 0.18f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puntas arbol
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(0.77f, -0.52f, -2.0f));
		figuras = glm::scale(figuras, glm::vec3(0.5f, 0.5f, 0.5f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		figuras = glm::mat4(1.0);
		figuras = glm::translate(figuras, glm::vec3(-0.77f, -0.52f, -2.0f));
		figuras = glm::scale(figuras, glm::vec3(0.5f, 0.5f, 0.5f));
		//figuras = glm::rotate(figuras, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(figuras));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		
		
		
		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/