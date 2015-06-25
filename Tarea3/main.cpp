#include <GL/glew.h>
#include "offReader.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp> 

#include <iostream>
 
using namespace std;

GLuint indexes[32];
GLuint VBOid[64];

GLuint BBoxIndices[] = { 0, 1, 1, 5, 5, 4, 4, 0
, 3, 2, 2, 6, 6, 7, 7, 3
, 1, 2, 5, 6, 4, 7, 0, 3

};

enum RenderingMode
{
	Immediate, VertexArray, DisplayList, VBO

};

std::vector<offReader> offObjects;
bool IOtest = false;
bool Orthogonal = false;
RenderingMode Mode = Immediate;

void initDisplaylists(int i){
	indexes[i] = glGenLists(1);
	glNewList(indexes[i], GL_COMPILE);
	glBegin(GL_TRIANGLES);
	glCullFace(GL_BACK);

	glColor3f(1.0f, 0.5f, 0.5f);
	for (int i = 0; i < offObjects[0].mesh.Faces.size(); i++){

		for (int z = 0; z < offObjects[0].mesh.Faces[i].Faces.size(); z++){
			glNormal3f(offObjects[0].mesh.Faces[i].Faces[z].tNormal[0],
				offObjects[0].mesh.Faces[i].Faces[z].tNormal[1],
				offObjects[0].mesh.Faces[i].Faces[z].tNormal[2]);

			for (int x = 0; x < 3; x++){
				glVertex3f(offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[0],
					offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[1],
					offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[2]);
			}
		}
	}

	glEnd();

	glBegin(GL_LINES);
	glCullFace(GL_BACK);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.f, 1.f);
	for (int i = 0; i < offObjects[0].mesh.Faces.size(); i++){

		for (int z = 0; z < offObjects[0].mesh.Faces[i].Faces.size(); z++){
			glVertex3f(offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[0], offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[1], offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[2]);
			glVertex3f(
				offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[0] + offObjects[0].mesh.Faces[i].Faces[z].tNormal[0] * 0.05f,
				offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[1] + offObjects[0].mesh.Faces[i].Faces[z].tNormal[1] * 0.05f,
				offObjects[0].mesh.Faces[i].Faces[z].tNormalVector[2] + offObjects[0].mesh.Faces[i].Faces[z].tNormal[2] * 0.05f);
			//glVertex3f(offObjects[0].mesh.Faces[i].Faces[z].tNormal[0], offObjects[0].mesh.Faces[i].Faces[z].tNormal[0], offObjects[0].mesh.Faces[i].Faces[z].tNormal[2]);

		}
	}
	glEnd();
	glEndList();


}

void LoadModel(std::string path){
	if (offObjects.size() < 32) {
		offObjects.push_back(offReader(path));
		
	
	}
	else{
		std::cout << "Ya existen 32 objetos" << std::endl;
	
	}



};



int main(){
	
	//std::vector<objReader> objObjects;

	offObjects.push_back(offReader("C:\\Users\\Jazmina Liz\\Desktop\\m1495.off"));
	offObjects.push_back(offReader("C:\\Users\\Jazmina Liz\\Desktop\\m1800.off"));
	int it=0;


	if (IOtest){
	for (int i = 0; i < offObjects[0].mesh.Faces.size();i++){
	
		for (int z = 0; z < offObjects[0].mesh.Faces[i].Faces.size(); z++){
			for (int x = 0; x < 3; x++){
				std::cout << offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[0] << " " <<
					offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[1] << " " <<
					offObjects[0].mesh.Faces[i].Faces[z].tVertices[x].Vertex[2] << "	" << it++ <<std::endl;
			}
		
		
		}
	
	}
	}
	
	
	
	
	GLFWwindow* window;
	//glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	//glfwSetKeyCallback(window, key_callback);
	initDisplaylists(0);
	glewInit();
	/*
	offObjects[0].mesh.DisplacementVector[0] = -0.5;
	offObjects[0].mesh.DisplacementVector[1] = -0.5;
	offObjects[0].mesh.DisplacementVector[2] = -0.5;
	offObjects[0].mesh.RotationMatrix[0] = 0.1f;
	offObjects[0].mesh.RotationMatrix[1] = 0.2f;
	offObjects[0].mesh.RotationMatrix[2] = 0.55f;
	offObjects[0].mesh.RotationMatrix[3] = 0.3f;
	*/
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (Orthogonal) { glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); }
		else{ glFrustum(-ratio, ratio, -1.f, 1.f, -1.f, 1.f); }
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);    // use default light diffuse and position
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		glEnable(GL_LINE_SMOOTH);
		

		switch (Mode){
		case Immediate:
			
			for (int objs = 0; objs < offObjects.size(); objs++){
			glPushMatrix();
			glTranslatef(offObjects[objs].mesh.DisplacementVector[0], offObjects[objs].mesh.DisplacementVector[1], offObjects[objs].mesh.DisplacementVector[2]);
			glMultMatrixf(glm::value_ptr(glm::mat4_cast(offObjects[objs].mesh.RotationMatrix)));
			glColor3f(1.0f, 0.5f, 0.5f);
			for (int i = 0; i < offObjects[objs].mesh.Faces.size(); i++){
				glBegin(GL_TRIANGLES);
				glCullFace(GL_BACK);
				
				for (int z = 0; z < offObjects[objs].mesh.Faces[i].Faces.size(); z++){
					glNormal3f(offObjects[objs].mesh.Faces[i].Faces[z].tNormal[0],
						offObjects[objs].mesh.Faces[i].Faces[z].tNormal[1],
						offObjects[objs].mesh.Faces[i].Faces[z].tNormal[2]);

					for (int x = 0; x < 3; x++){
						glVertex3f(offObjects[objs].mesh.Faces[i].Faces[z].tVertices[x].Vertex[0],
							offObjects[objs].mesh.Faces[i].Faces[z].tVertices[x].Vertex[1],
							offObjects[objs].mesh.Faces[i].Faces[z].tVertices[x].Vertex[2]);
					}
				}
			}

			glEnd();

			glBegin(GL_LINES);
			glCullFace(GL_BACK);
			glDisable(GL_LIGHTING);
			glColor3f(1.0f, 1.f, 1.f);
			for (int i = 0; i < offObjects[objs].mesh.Faces.size(); i++){

				for (int z = 0; z < offObjects[objs].mesh.Faces[i].Faces.size(); z++){
					glVertex3f(offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[0], offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[1], offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[2]);
					glVertex3f(
						offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[0] + offObjects[objs].mesh.Faces[i].Faces[z].tNormal[0] * 0.05f,
						offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[1] + offObjects[objs].mesh.Faces[i].Faces[z].tNormal[1] * 0.05f,
						offObjects[objs].mesh.Faces[i].Faces[z].tNormalVector[2] + offObjects[objs].mesh.Faces[i].Faces[z].tNormal[2] * 0.05f);
					//glVertex3f(offObjects[0].mesh.Faces[i].Faces[z].tNormal[0], offObjects[0].mesh.Faces[i].Faces[z].tNormal[0], offObjects[0].mesh.Faces[i].Faces[z].tNormal[2]);

				}
			}
			glEnd();
			glPopMatrix();
			}


			break;
		case VertexArray: 
			glEnableClientState(GL_VERTEX_ARRAY);
			for (int i = 0; i < offObjects.size(); i++){
				
				glVertexPointer(3, GL_FLOAT, 0, &offObjects[0].fVertexData[0]);
				glDrawElements(GL_TRIANGLES, offObjects[0].indexData.size(), GL_UNSIGNED_SHORT, &offObjects[0].indexData[0]);
				if (DrawBBox){}
				if (DrawNormals){}

			
			}
			glDisableClientState(GL_VERTEX_ARRAY);
			break;
		case DisplayList:
			glCallList(indexes[0]);

			break;
		case VBO: 
			glGenBuffersARB(1, &VBOid[0]);
			glGenBuffers(1, &VBOid[1]);

			glBindBuffer(GL_ARRAY_BUFFER_ARB,VBOid[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBOid[1]);
			
			
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, offObjects[0].fVertexData.size() *3 *sizeof(GLfloat), &offObjects[0].fVertexData[0], GL_STATIC_DRAW_ARB);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, offObjects[0].indexData.size() * sizeof(GLshort), &offObjects[0].indexData[0], GL_STATIC_DRAW_ARB);
			
			glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glDrawElements(GL_TRIANGLES, offObjects[0].indexData.size(), GL_UNSIGNED_SHORT, 0);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
			
			
			break;

		}






		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	
	
	exit(0);



}