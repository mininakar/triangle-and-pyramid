#include <stdio.h>#include <iostream>
#include <GL/glew.h> /
#include <GL/freeglut.h> /
#include <glm/glm.hpp>	
#include "Pipeline.h"

//#include "math_3d.h"
///#include "pipeline.h"

GLuint VBO; //объект буфера вершины, VBO
GLuint IBO; // объект Index Index, Element Buff Element, Ebo или Obder Buffer, IBO

GLuint gWorldLocation;

float Scale = 0.0f;
GLint success; 
GLchar InfoLog[1024];

constexpr auto WINDOW_WIDTH = 1980;
constexpr auto WINDOW_HEIGHT = 1250;


// шейдер
static const char* vert = R"(
	#version 330 core
	layout (location = 0) in vec3 Pos;
	out vec4 vertexColor;
	uniform mat4 gWorld;
	void main()
	{
		gl_Position = gWorld * vec4(4 * Pos.x, 4 * Pos.y, Pos.z, 1.0);
		vertexColor = vec4(clamp(Pos, 0.0, 1.0), 1.0);
	})";

static const char* frag = R"(
	#version 330 core
	out vec4 FragColor;
	in vec4 vertexColor;
	void main()
	{
		FragColor = vertexColor;
	})";


void RenderSceneCB() //фцнкция для рисования
{
	glClear(GL_COLOR_BUFFER_BIT); //отчистка

	Scale += 0.1f;

	Pipeline p;

	p.Scale(0.1f, 0.1f, 0.1f);
	p.WorldPos(0.0f, 0.0f, 3.0f);
	p.Rotate(0, Scale, 0);

	glm::vec3 CameraPos(0.0f, 0.0f, -3.0f);
	glm::vec3 CameraTarget(0.0f, 0.0f, 2.0f);
	glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
	p.SetCamera(CameraPos, CameraTarget, CameraUp);
	p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);

	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (GLfloat*)p.GetTrans());

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

	
	glutPostRedisplay();

	glutSwapBuffers(); 
}

//функция для проверки ошибок 
void error(GLuint program, GLint success, GLenum ShaderType)
{
	if (!success)
	{
		if (ShaderType == 0)
		{
			glGetProgramInfoLog(program, sizeof(InfoLog), nullptr, InfoLog);
			std::cerr << "Error compiling shader type " << static_cast<int>(ShaderType) << InfoLog << "\n";
		}
		else
		{
			glGetShaderInfoLog(program, sizeof(InfoLog), nullptr, InfoLog);
			std::cerr << "Error linking shader program " << InfoLog << "\n";
		}
	}
}

// добавляем шейдер
void addshader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType)
{
	GLuint shader = glCreateShader(ShaderType);

	const GLchar* ShaderSource[1];
	ShaderSource[0] = ShaderText;
	glShaderSource(shader, 1, ShaderSource, nullptr);
	glCompileShader(shader);


	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	error(shader, success, ShaderType);

	glAttachShader(ShaderProgram, shader);
}

//cоздаем шейдер
void createshaders(const char* ShaderText_v, const char* ShaderText_f)
{
	GLuint ShaderProgram = glCreateProgram();

	addshader(ShaderProgram, ShaderText_v, GL_VERTEX_SHADER);
	addshader(ShaderProgram, ShaderText_f, GL_FRAGMENT_SHADER);


	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	error(ShaderProgram, success, 0);

	glUseProgram(ShaderProgram);

	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}





int main(int argc, char** argv)
{
	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowSize(1024, 768); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Pyramid"); 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	glutDisplayFunc(RenderSceneCB); 
	glutIdleFunc(RenderSceneCB);


	glm::vec3 Vertices[4];
	Vertices[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
	Vertices[1] = glm::vec3(0.0f, -1.0f, 5.0f);
	Vertices[2] = glm::vec3(1.0f, -1.0f, -1.0f);
	Vertices[3] = glm::vec3(0.0f, 1.0f, 1.0f);

	unsigned int Indices[] = {
		0, 2, 3,
		1, 3, 2,
		2, 6, 0,
		0, 2, 1 };

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


	createshaders(vert, frag);

	glutMainLoop(); 

	return 0;
}