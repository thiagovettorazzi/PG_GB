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
	
	//GLFW callbacks - PRECISAM SER ESTÁTICAS
	//Para isso, as variáveis que modificamos dentro deles
	//também precisam ser e estão no início do SceneManager.cpp
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);

	static void resize(GLFWwindow* window, int width, int height);

	//Métodos pricipais
	void initialize(GLuint width, GLuint height);
	void run();
	void finish();

	//Métodos chamados no run (ciclo)
	void update();
	void render();

	//Métodos para configuração e carregamento dos elementos da cena
	void initializeGraphics();
	void addShader(string vFilename, string fFilename);
	void setupScene();
	void setupCamera2D();
	unsigned int loadTexture(string filename); 

	// Métodos dos stickers
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