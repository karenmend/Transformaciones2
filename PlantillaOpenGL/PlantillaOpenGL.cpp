// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
/*#include <conio.h>*/

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0;
enum Direccion {Izquierda, Derecha, Arriba, Abajo};

Direccion direccionXTriangulo = Direccion::Izquierda;
Direccion direccionYTriangulo = Direccion::Arriba;

void dibujarTriangulo() {


	//Utilizar Matriz entidad
	glPushMatrix();
	//transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);

	glRotatef(angulo, 0.0f, 0.0f, 1.0f);

	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0);
	glVertex3f(0.4f, -0.4f, 0);
	glVertex3f(0.f, 0.4f, 0);
	glEnd();
	
	//Soltar la matrix
	glPopMatrix();




}
void dibujar() {
	dibujarTriangulo();
}

void actualizar() {

	if (angulo >= 360) {
		angulo = 0;
	}

	angulo += 0.1;
	if (direccionXTriangulo == Direccion::Izquierda)
	{
		if (posicionXTriangulo > -0.6f) {
			posicionXTriangulo -= 0.0001f;
		}
		else
		{
			direccionXTriangulo = Direccion::Derecha;
		}
	}
	if (direccionXTriangulo == Direccion::Derecha) {
		if (posicionXTriangulo < 0.6f) {
			posicionXTriangulo += 0.0001f;
		}
		else {
			direccionXTriangulo = Direccion::Izquierda;
		}
	}

	if (direccionYTriangulo == Direccion::Arriba) {
		if (posicionYTriangulo < 0.6f)
		{
			posicionYTriangulo += 0.001f;
		}
		else
		{
			direccionYTriangulo = Direccion::Abajo;
		}
	}
	if (direccionYTriangulo == Direccion::Abajo) {
		if (posicionYTriangulo > -0.6f)
		{
			posicionYTriangulo -= 0.001f;
		}
		else
		{
			direccionYTriangulo = Direccion::Arriba;
		}
	}
}
int main()
{
	/*Crear un contexto 

	°Un contexto es una ventana de un sistema operativo
	°OpenGL no gestiona el iso de ventanas*/

	//Declaramos un apuntador de ventana.

	GLFWwindow *window;
	// Si no se pudo iniciar glfw terminamos ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window =
		glfwCreateWindow(1024, 728, "Ventana", NULL, NULL);
	if (!window) {
		glfwTerminate();
			exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, activamos funciones modernas(trabajar con GPU/CPU)
	glewExperimental = true;
	GLenum  errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Ciclo de dibujo(draw loop)
	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar Buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();


		
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

