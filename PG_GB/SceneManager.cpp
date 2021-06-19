#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
int filtroEscolhido = 0;
string foto;

// Controle ds stickers que estarão na tela
vector <Sprite*> stickers;
static vector <string> caminhoStrickes = { "../stickers/1.png", "../stickers/2.png", "../stickers/3.png", "../stickers/4.png", "../stickers/5.png" };

bool adicionarSticker = false;
int qualStickerAdicionar = 0;

bool removerSticker = false;

// Movimentação dos Stickers
int qualStickerMover;
bool moverSticker = false;

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

void SceneManager::initialize(GLuint w, GLuint h){
	width = w;
	height = h;
	initializeGraphics();
}

void SceneManager::initializeGraphics() {
	glfwInit();

	window = glfwCreateWindow(width, height, "Editor de imagens", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glfwSetKeyCallback(window, key_callback);

	glfwSetMouseButtonCallback(window, mouse_callback);

	glfwSetWindowSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Build and compile our shader program
	addShader("../shaders/Filtro.vs", "../shaders/Filtro0.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro1.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro2.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro3.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro4.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro5.frag");
	addShader("../shaders/Filtro.vs", "../shaders/Filtro6.frag");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez
}

void SceneManager::addShader(string vFilename, string fFilename) {
	Shader* shader = new Shader(vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	// Clique no botão esquerdo
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Área dos filtros
		if (488 < ypos && ypos < 588) {
			if (12 < xpos && xpos < 112) // Filtro 1
				filtroEscolhido = 0;
			else if (124 < xpos && xpos < 224) // Filtro 2
				filtroEscolhido = 1;
			else if (236 < xpos && xpos < 336) // Filtro 3
				filtroEscolhido = 2;
			else if (348 < xpos && xpos < 448) // Filtro 4
				filtroEscolhido = 3;
			else if (460 < xpos && xpos < 560) // Filtro 5
				filtroEscolhido = 4;
			else if (572 < xpos && xpos < 672) // Filtro 6
				filtroEscolhido = 5;
			else if (684 < xpos && xpos < 784) // Filtro 7
				filtroEscolhido = 6;
		}

		// Área dos stickers
		else if (12 < ypos && ypos < 84) {
			if (82 < xpos && xpos < 142) { // Sticker 1
				adicionarSticker = true;
				qualStickerAdicionar = 0;
			}
			else if (224 < xpos && xpos < 284) { // Sticker 2
				adicionarSticker = true;
				qualStickerAdicionar = 1;
			}
			else if (366 < xpos && xpos < 426) { // Sticker 3
				adicionarSticker = true;
				qualStickerAdicionar = 2;
			}
			else if (508 < xpos && xpos < 568) { // Sticker 4
				adicionarSticker = true;
				qualStickerAdicionar = 3;
			}
			else if (650 < xpos && xpos < 710) { // Sticker 5
				adicionarSticker = true;
				qualStickerAdicionar = 4;
			}
		}

		// Mover sticker na tela
		else {
			double stickerX, stickerY, posicaoVerificacaoY;

			for (int i = stickers.size() - 1; i >= 0; i--) {
				stickerX = stickers[i]->getPosition().x;
				stickerY = stickers[i]->getPosition().y;

				posicaoVerificacaoY = 600.0f - ypos;

				if (posicaoVerificacaoY > stickerY - 30 && stickerY + 30 > posicaoVerificacaoY) {
					if (xpos > stickerX - 30 && stickerX + 30 > xpos) {
						qualStickerMover = i;
						moverSticker = true;

						// Parar de executar o for, para excluir apenas um sticker
						i = -1;
					}
				}
			}
		}
	}

	// Soltar clique no botão esquerdo
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		moverSticker = false;
	}

	// Clique no botão direito
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		moverSticker = false;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (100 < ypos && ypos < 460) {
			if (220 < xpos && xpos < 580) {
				removerSticker = true;
			}
		}
	}

	// Soltar clique no botão direito
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		moverSticker = false;
	}
}

void SceneManager::addSticker(int qualStickerAdicionar) {
	int texID = loadTexture(caminhoStrickes[qualStickerAdicionar]);

	Sprite* sticker = new Sprite;
	sticker->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	sticker->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	sticker->setShader(shaders[0]);
	sticker->setTexture(texID);
	stickers.push_back(sticker);

	adicionarSticker = false;
}

void SceneManager::removeSticker() {
	if (stickers.size() > 0)
		stickers.pop_back();
	removerSticker = false;
}

void SceneManager::moveSticker(int qualStickerMover) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float novaPosicaoY = 600.0f - ypos;

	stickers[qualStickerMover]->setTranslation(glm::vec3(xpos, novaPosicaoY, 0.0));
}

void SceneManager::resize(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;
	resized = true;

	glViewport(0, 0, width, height);
}

string mudarFoto() {
	ifstream txtfile;
	string linha;
	int cont = 0;

	if (!txtfile.is_open())
		txtfile.open("../foto/foto.txt");

	while (!txtfile.eof()) {
		getline(txtfile, linha);
		break;
	}

	txtfile.close();
	return linha;
}

void SceneManager::update() {
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Atualiza a foto com o shader escolhido
	objects[7]->setShader(shaders[filtroEscolhido]);
	
	// Adicionar um sticker na tela
	if (adicionarSticker)
		addSticker(qualStickerAdicionar);

	// Remover um sticker na tela
	if (removerSticker)
		removeSticker();

	// Mover o sticker
	if (moverSticker)
		moveSticker(qualStickerMover);

	// Mudar foto
	string novaFoto = mudarFoto();
	
	if (foto != novaFoto) {
		unsigned int texNovaID = loadTexture(novaFoto);
		for (int i = 0; i < 8; i++) {
			objects[i]->setTexture(texNovaID);
		}
		foto = novaFoto;
	}
}

void SceneManager::render() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (resized) {
		setupCamera2D();
		resized = false;
	}

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
		objects[i]->draw();
	}

	for (int j = 0; j < stickers.size(); j++) {
		stickers[j]->update();
		stickers[j]->draw();
	}
}

void SceneManager::run() {
	// GAME LOOP
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		update();
		
		render();

		glfwSwapBuffers(window);
	}
}

void SceneManager::finish() {
	glfwTerminate();
}

void SceneManager::setupScene() {
	// Textura
	foto = mudarFoto();
	unsigned int texID = loadTexture(foto);

	// Adicionando os botões de escolha dos filtros
	Sprite* obj;
	static vector <int> posicaoHorizontalFiltros = { 62, 174, 286, 398, 510, 622, 734 };
	int i;

	for (i = 0; i < shaders.size(); i++) {
		obj = new Sprite;
		obj->setPosition(glm::vec3(posicaoHorizontalFiltros[i], 62.0f, 0.0));
		obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
		obj->setShader(shaders[i]);
		objects.push_back(obj);

		// Carregamento das texturas
		objects[i]->setTexture(texID);
	}

	// Adicionando a foto principal
	obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 320.0f, 0.0));
	obj->setDimension(glm::vec3(360.0f, 360.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);

	// Carregamento das texturas
	objects[i]->setTexture(texID);


	// Adicionando os stickers
	static vector <int> posicaoHorizontalStickers = { 112, 254, 396, 538, 680 };

	for (int j = 0; j < 5; j++) {
		texID = loadTexture(caminhoStrickes[j]);

		obj = new Sprite;
		obj->setPosition(glm::vec3(posicaoHorizontalStickers[j], 548.0f, 0.0));
		obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
		obj->setShader(shaders[0]);
		obj->setTexture(texID);

		objects.push_back(obj);
	}

	// Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f;
	ortho2D[1] = 800.0f;
	ortho2D[2] = 0.0f;
	ortho2D[3] = 600.0f;

	// Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SceneManager::setupCamera2D() {
	float zNear = -1.0, zFar = 1.0;

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	for (int i = 0; i < shaders.size(); i++) {
		shaders[i]->Use();
		GLint projLoc = glGetUniformLocation(shaders[i]->ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

unsigned int SceneManager::loadTexture(string filename) {
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);

	return texture;
}
