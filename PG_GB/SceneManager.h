#pragma once

#include "Shader.h"
#include "Sprite.h" 

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	//GLFW callbacks - PRECISAM SER EST�TICAS
	//Para isso, as vari�veis que modificamos dentro deles
	//tamb�m precisam ser e est�o no in�cio do SceneManager.cpp
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);

	static void resize(GLFWwindow* window, int width, int height);

	//M�todos pricipais
	void initialize(GLuint width, GLuint height);
	void run();
	void finish();

	//M�todos chamados no run (ciclo)
	void update();
	void render();

	//M�todos para configura��o e carregamento dos elementos da cena
	void initializeGraphics();
	void addShader(string vFilename, string fFilename);
	void setupScene();
	void setupCamera2D();
	unsigned int loadTexture(string filename); 

	// M�todos dos stickers
	void addSticker(int qualStickerAdicionar);
	void removeSticker();
	void moveSticker(int qualStickerMover);

private:
	GLFWwindow *window;

	vector <Shader*> shaders;

	glm::vec4 ortho2D;
	glm::mat4 projection;

	// Nossos objetos (sprites) da cena
	vector <Sprite*> objects;
};