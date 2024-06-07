#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Headers/TimeManager.h"
#include "Headers/Shader.h"
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
//#include "Headers/ThirdPersonCamera.h"
#include "Headers/FontTypeRendering.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Headers/Texture.h"
#include "Headers/Model.h"
#include "Headers/Terrain.h"
#include "Headers/AnimationUtils.h"
#include "Headers/Colisiones.h"
#include "Headers/ShadowBox.h"
#include <AL/alut.h>
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
int screenWidth;
int screenHeight;
GLFWwindow *window;

Shader shader;
Shader shaderSkybox;
Shader shaderMulLighting;
Shader shaderTerrain;
Shader shaderTexture;
Shader shaderDepth;
Shader shaderViewDepth;

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());
//std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

Sphere skyboxSphere(20, 20);
Box boxCesped;
Sphere esfera1(10, 10);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxIntro;

Box Pared1;
Box Pared2;
Box Pared3;
Box Pared4;
Box Pared5;
Box Pared6;
Box Pared7;
Box Pared8;
Box Pared9;
Box Pared10;
Box Pared11;
Box Pared12;
Box Pared13;
Box Pared14;
Box Pared15;
Box Pared16;

//Models complex instances.
Model modelTuboM;
Model modelTuboM2;
Model modelTuboM3;
Model modelTuboM4;
Model modelTuboM5;
Model modelTuboM6;
Model modelTuboM7;
Model modelTuboM8;
Model modelTuboM9;
Model modelTuboM10;

Model modelPilarH;
Model modelPilarH2;
Model modelPilarH3;
Model modelPilarH4;
Model modelPilarH5;
Model modelPilarH6;
Model modelPilarH7;
Model modelPilarH8;
Model modelPilarH9;
Model modelPilarH10;

Model modelPicoR;
Model modelPicoR2;
Model modelPicoR3;
Model modelPicoR4;
Model modelPicoR5;
Model modelPicoR6;
Model modelPicoR7;
Model modelPicoR8;
Model modelPicoR9;
Model modelPicoR10;

Model modelCactus;
Model modelCactus2;
Model modelCactus3;
Model modelCactus4;
Model modelCactus5;
Model modelCactus6;
Model modelCactus7;
Model modelCactus8;
Model modelCactus9;
Model modelCactus10;

//Lamps.
Model modelLamp1;
Model modelLamp2;
Model modelLampPost2;
//Modelos animados.
//Mayow.
Model mayowModelAnimate;

// Terrain model instance
Terrain terrain(-1, -1, 400, 7, "../Textures/HeightmapProyecto_.png");

GLuint textureCespedID, textureWallID, texturePraderaID, textureMontañasHeladasID, textureMontañaRocosaID, textureDesiertoID, textureHieloID, textureArenaID;
GLuint textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;
GLuint textureInit1ID, textureInit2ID, textureInit3ID, textureActivaID, textureScreenID, textureScreen2ID, textureScreen3ID;

bool iniciaPartida = false, presionarOpcion = false;
// Modelo para el render del texto.
FontTypeRendering::FontTypeRendering *modelText;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
std::string fileNames[6] = { "../Textures/Cielo/Dia_derecha.jpg",
		"../Textures/Cielo/Dia_izquierda.jpg",
		"../Textures/Cielo/Dia_arriba.jpg",
		"../Textures/Cielo/Dia_abajo.jpg",
		"../Textures/Cielo/Dia_atras.jpg",
		"../Textures/Cielo/Dia_frente.jpg",
		};

		
bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

//Model matrix definitions.
glm::mat4 modelMatrixTuboM = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM2 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM3 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM4 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM5 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM6 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM7 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM8 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM9 = glm::mat4(1.0f);
glm::mat4 modelMatrixTuboM10 = glm::mat4(1.0f);

glm::mat4 modelMatrixPilarH = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH2 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH3 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH4 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH5 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH6 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH7 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH8 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH9 = glm::mat4(1.0f);
glm::mat4 modelMatrixPilarH10 = glm::mat4(1.0f);

glm::mat4 modelMatrixPicoR = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR2 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR3 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR4 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR5 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR6 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR7 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR8 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR9 = glm::mat4(1.0f);
glm::mat4 modelMatrixPicoR10 = glm::mat4(1.0f);

glm::mat4 modelMatrixCactus = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus2 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus3 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus4 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus5 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus6 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus7 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus8 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus9 = glm::mat4(1.0f);
glm::mat4 modelMatrixCactus10 = glm::mat4(1.0f);

glm::mat4 modelMatrixMayow = glm::mat4(1.0f);

int animationMayowIndex = 0;
int modelSelected = 0;

//Lamps position.
std::vector<glm::vec3> lamp1Position = {
	glm::vec3(-7.03, 0, -19.14),
	glm::vec3(24.41, 0, -34.57),
	glm::vec3(-10.15, 0, -54.1)
};
std::vector<float> lamp1Orientation = {
	-17.0, -82.67, 23.70
};
std::vector<glm::vec3> lamp2Position = {
	glm::vec3(-36.52, 0, -23.24),
	glm::vec3(-52.73, 0, -3.90)
};
std::vector<float> lamp2Orientation = {
	21.37 + 90, -65.0 + 90
};

//Blending model unsorted.
std::map<std::string, glm::vec3> blendingUnsorted = {
};

double deltaTime;
double currTime, lastTime;

//Fly.
bool Fly_ = false;
float FlyG_ = 4.90;
double T_ = 0;
double Start_ = 0;

//Colliders.
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,	int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
//void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

//Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}
	screenWidth = width;
	screenHeight = height;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	//glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Init glew.
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Inicialización de los shaders.
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");

	//Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));
	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);
	esfera1.init();
	esfera1.setShader(&shaderMulLighting);
	boxIntro.init();
	boxIntro.setShader(&shaderTexture);
	boxIntro.setScale(glm::vec3(2.0, 2.0, 1.0));

	//Muros.
	Pared1.init();
	Pared1.setShader(&shaderMulLighting);
	Pared2.init();
	Pared2.setShader(&shaderMulLighting);
	Pared3.init();
	Pared3.setShader(&shaderMulLighting);
	Pared4.init();
	Pared4.setShader(&shaderMulLighting);
	Pared5.init();
	Pared5.setShader(&shaderMulLighting);
	Pared6.init();
	Pared6.setShader(&shaderMulLighting);
	Pared7.init();
	Pared7.setShader(&shaderMulLighting);
	Pared8.init();
	Pared8.setShader(&shaderMulLighting);
	Pared9.init();
	Pared9.setShader(&shaderMulLighting);
	Pared10.init();
	Pared10.setShader(&shaderMulLighting);
	Pared11.init();
	Pared11.setShader(&shaderMulLighting);
	Pared12.init();
	Pared12.setShader(&shaderMulLighting);
	Pared13.init();
	Pared13.setShader(&shaderMulLighting);
	Pared14.init();
	Pared14.setShader(&shaderMulLighting);
	Pared15.init();
	Pared15.setShader(&shaderMulLighting);
	Pared16.init();
	Pared16.setShader(&shaderMulLighting);

	modelTuboM.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM.setShader(&shaderMulLighting);
	modelTuboM2.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM2.setShader(&shaderMulLighting);
	modelTuboM3.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM3.setShader(&shaderMulLighting);
	modelTuboM4.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM4.setShader(&shaderMulLighting);
	modelTuboM5.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM5.setShader(&shaderMulLighting);
	modelTuboM6.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM6.setShader(&shaderMulLighting);
	modelTuboM7.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM7.setShader(&shaderMulLighting);
	modelTuboM8.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM8.setShader(&shaderMulLighting);
	modelTuboM9.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM9.setShader(&shaderMulLighting);
	modelTuboM10.loadModel("../models/Modelos Videojuego/TuboM.obj");
	modelTuboM10.setShader(&shaderMulLighting);
	
	modelPilarH.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH.setShader(&shaderMulLighting);
	modelPilarH2.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH2.setShader(&shaderMulLighting);
	modelPilarH3.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH3.setShader(&shaderMulLighting);
	modelPilarH4.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH4.setShader(&shaderMulLighting);
	modelPilarH5.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH5.setShader(&shaderMulLighting);
	modelPilarH6.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH6.setShader(&shaderMulLighting);
	modelPilarH7.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH7.setShader(&shaderMulLighting);
	modelPilarH8.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH8.setShader(&shaderMulLighting);
	modelPilarH9.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH9.setShader(&shaderMulLighting);
	modelPilarH10.loadModel("../models/Modelos Videojuego/PilarHielo.obj");
	modelPilarH10.setShader(&shaderMulLighting);

	modelPicoR.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR.setShader(&shaderMulLighting);
	modelPicoR2.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR2.setShader(&shaderMulLighting);
	modelPicoR3.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR3.setShader(&shaderMulLighting);
	modelPicoR4.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR4.setShader(&shaderMulLighting);
	modelPicoR5.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR5.setShader(&shaderMulLighting);
	modelPicoR6.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR6.setShader(&shaderMulLighting);
	modelPicoR7.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR7.setShader(&shaderMulLighting);
	modelPicoR8.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR8.setShader(&shaderMulLighting);
	modelPicoR9.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR9.setShader(&shaderMulLighting);
	modelPicoR10.loadModel("../models/Modelos Videojuego/PicoRock.obj");
	modelPicoR10.setShader(&shaderMulLighting);

	modelCactus.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus.setShader(&shaderMulLighting);
	modelCactus2.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus2.setShader(&shaderMulLighting);
	modelCactus3.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus3.setShader(&shaderMulLighting);
	modelCactus4.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus4.setShader(&shaderMulLighting);
	modelCactus5.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus5.setShader(&shaderMulLighting);
	modelCactus6.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus6.setShader(&shaderMulLighting);
	modelCactus7.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus7.setShader(&shaderMulLighting);
	modelCactus8.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus8.setShader(&shaderMulLighting);
	modelCactus9.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus9.setShader(&shaderMulLighting);
	modelCactus10.loadModel("../models/Modelos Videojuego/Cactus.obj");
	modelCactus10.setShader(&shaderMulLighting);

	//Lamps models.
	modelLamp1.loadModel("../models/Street-Lamp-Black/objLamp.obj");
	modelLamp1.setShader(&shaderMulLighting);
	modelLamp2.loadModel("../models/Street_Light/Lamp.obj");
	modelLamp2.setShader(&shaderMulLighting);
	modelLampPost2.loadModel("../models/Street_Light/LampPost.obj");
	modelLampPost2.setShader(&shaderMulLighting);

	//Mayow.
	mayowModelAnimate.loadModel("../models/Modelos Videojuego/Bird_.fbx");
	mayowModelAnimate.setShader(&shaderMulLighting);

	//Terreno.
	terrain.init();
	terrain.setShader(&shaderTerrain);

	//Se inicializa el model de render text.
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
	modelText->Initialize();

	camera->setPosition(glm::vec3(0.0, 5.0, 100.0));
	//camera->setDistanceFromTarget(distanceFromTarget);
	//camera->setSensitivity(1.0);
	
	//Carga de texturas para el skybox.
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	//Tipo de textura CUBE MAP.
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//Set texture wrapping to GL_REPEAT (default wrapping method).
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//Set texture wrapping to GL_REPEAT (default wrapping method).
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		skyboxTexture.loadImage(true);
		if (skyboxTexture.getData()) {
			glTexImage2D(types[i], 0, skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, skyboxTexture.getWidth(), skyboxTexture.getHeight(), 0,
			skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, skyboxTexture.getData());
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage();
	}

	//Definiendo la textura a utilizar.
	Texture textureCesped("../Textures/BlendmapBlack_.png");
	//Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria).
	textureCesped.loadImage();
	//Creando la textura con id 1.
	glGenTextures(1, &textureCespedID);
	//Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	//Set the texture wrapping parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//Set texture wrapping to GL_REPEAT (default wrapping method).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//Set texture filtering parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Verifica si se pudo abrir la textura.
	if (textureCesped.getData()) {
		//Transferis los datos de la imagen a memoria
		//Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		//Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		//a los datos.
		std::cout << "Numero de canales :=> " << textureCesped.getChannels() << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, textureCesped.getWidth(), textureCesped.getHeight(), 0,
		textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureCesped.getData());
		//Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos).
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	//Libera la memoria de la textura.
	textureCesped.freeImage();

	// Defininiendo texturas del mapa de mezclas
	// Definiendo la textura
	Texture textureR("../Textures/BlendmapRed_.png");
	textureR.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainRID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureR.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, textureR.getWidth(), textureR.getHeight(), 0,
		textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureR.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureR.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureG("../Textures/BlendmapGreen_.png");
	textureG.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainGID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureG.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, textureG.getWidth(), textureG.getHeight(), 0,
		textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureG.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureG.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureB("../Textures/BlendmapBlue_.png");
	textureB.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureB.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, textureB.getWidth(), textureB.getHeight(), 0,
		textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureB.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureB.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureBlendMap("../Textures/BlendmapProyecto_.png");
	textureBlendMap.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBlendMapID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureBlendMap.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, textureBlendMap.getWidth(), textureBlendMap.getHeight(), 0,
		textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureBlendMap.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureBlendMap.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro1("../Textures/Inicio.png");
	textureIntro1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro1.getWidth(), textureIntro1.getHeight(), 0,
		textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro1.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro2("../Textures/Game over.png");
	textureIntro2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro2.getWidth(), textureIntro2.getHeight(), 0,
		textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro2.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro3("../Textures/Fin.png");
	textureIntro3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit3ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit3ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro3.getWidth(), textureIntro3.getHeight(), 0,
		textureIntro3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro3.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen("../Textures/3vidas.png");
	textureScreen.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen.getWidth(), textureScreen.getHeight(), 0,
		textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen2("../Textures/2vidas.png");
	textureScreen2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen2.getWidth(), textureScreen2.getHeight(), 0,
		textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen2.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen3("../Textures/1vida.png");
	textureScreen3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen3ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen3ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen3.getWidth(), textureScreen3.getHeight(), 0,
		textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen3.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureHielo("../Textures/Hielo.png");
	textureHielo.loadImage(); // Cargar la textura
	glGenTextures(1, &textureHieloID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureHieloID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureHielo.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureHielo.getChannels() == 3 ? GL_RGB : GL_RGBA, textureHielo.getWidth(), textureHielo.getHeight(), 0,
		textureHielo.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureHielo.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureHielo.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureArena("../Textures/Arena.png");
	textureArena.loadImage(); // Cargar la textura
	glGenTextures(1, &textureArenaID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureArenaID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureArena.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureArena.getChannels() == 3 ? GL_RGB : GL_RGBA, textureArena.getWidth(), textureArena.getHeight(), 0,
		textureArena.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureArena.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureArena.freeImage(); // Liberamos memoria

	//Carga de textura de las paredes
	//Pared pradera
	Texture texturePradera("../Textures/Pradera2.png"); 
    texturePradera.loadImage();
    glGenTextures(1, &texturePraderaID);
    glBindTexture(GL_TEXTURE_2D, texturePraderaID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (texturePradera.getData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, texturePradera.getChannels() == 3 ? GL_RGB : GL_RGBA, texturePradera.getWidth(), texturePradera.getHeight(), 0,
        texturePradera.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, texturePradera.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Fallo la carga de textura" << std::endl;
    }
    texturePradera.freeImage();
	
	//Pared Montaña Helada
	Texture textureMontañasHeladas("../Textures/Heladas1.png"); 
    textureMontañasHeladas.loadImage();
    glGenTextures(1, &textureMontañasHeladasID);
    glBindTexture(GL_TEXTURE_2D, textureMontañasHeladasID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureMontañasHeladas.getData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, textureMontañasHeladas.getChannels() == 3 ? GL_RGB : GL_RGBA, textureMontañasHeladas.getWidth(), textureMontañasHeladas.getHeight(), 0,
        textureMontañasHeladas.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureMontañasHeladas.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Fallo la carga de textura" << std::endl;
    }
    textureMontañasHeladas.freeImage();

	//Pared Montaña Rocosa
	Texture textureMontañaRocosa("../Textures/Rocosa.png"); 
    textureMontañaRocosa.loadImage();
    glGenTextures(1, &textureMontañaRocosaID);
    glBindTexture(GL_TEXTURE_2D, textureMontañaRocosaID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureMontañaRocosa.getData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, textureMontañaRocosa.getChannels() == 3 ? GL_RGB : GL_RGBA, textureMontañaRocosa.getWidth(), textureMontañaRocosa.getHeight(), 0,
        textureMontañaRocosa.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureMontañaRocosa.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Fallo la carga de textura" << std::endl;
    }
    textureMontañaRocosa.freeImage();

	//Pared Desierto
	Texture textureDesierto("../Textures/Desierto.png"); 
    textureDesierto.loadImage();
    glGenTextures(1, &textureDesiertoID);
    glBindTexture(GL_TEXTURE_2D, textureDesiertoID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureDesierto.getData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, textureDesierto.getChannels() == 3 ? GL_RGB : GL_RGBA, textureDesierto.getWidth(), textureDesierto.getHeight(), 0,
        textureDesierto.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureDesierto.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Fallo la carga de textura" << std::endl;
    }
    textureDesierto.freeImage();
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	skyboxSphere.destroy();
	boxCesped.destroy();
	esfera1.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();
	boxIntro.destroy();
	Pared1.destroy();
	Pared2.destroy();
	Pared3.destroy();
	Pared4.destroy();
	Pared5.destroy();
	Pared6.destroy();
	Pared7.destroy();
	Pared8.destroy();
	Pared9.destroy();
	Pared10.destroy();
	Pared11.destroy();
	Pared12.destroy();
	Pared13.destroy();
	Pared14.destroy();
	Pared15.destroy();
	Pared16.destroy();

	modelTuboM.destroy();
	modelTuboM2.destroy();
	modelTuboM3.destroy();
	modelTuboM4.destroy();
	modelTuboM5.destroy();
	modelTuboM6.destroy();
	modelTuboM7.destroy();
	modelTuboM8.destroy();
	modelTuboM9.destroy();
	modelTuboM10.destroy();

	modelPilarH.destroy();
	modelPilarH2.destroy();
	modelPilarH3.destroy();
	modelPilarH4.destroy();
	modelPilarH5.destroy();
	modelPilarH6.destroy();
	modelPilarH7.destroy();
	modelPilarH8.destroy();
	modelPilarH9.destroy();
	modelPilarH10.destroy();
	
	modelPicoR.destroy();
	modelPicoR2.destroy();
	modelPicoR3.destroy();
	modelPicoR4.destroy();
	modelPicoR5.destroy();
	modelPicoR6.destroy();
	modelPicoR7.destroy();
	modelPicoR8.destroy();
	modelPicoR9.destroy();
	modelPicoR10.destroy();
	
	modelCactus.destroy();
	modelCactus2.destroy();
	modelCactus3.destroy();
	modelCactus4.destroy();
	modelCactus5.destroy();
	modelCactus6.destroy();
	modelCactus7.destroy();
	modelCactus8.destroy();
	modelCactus9.destroy();
	modelCactus10.destroy();
	
	modelLamp1.destroy();
	modelLamp2.destroy();
	modelLampPost2.destroy();
	mayowModelAnimate.destroy();
	
	terrain.destroy();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureInit1ID);
	glDeleteTextures(1, &textureInit2ID);
	glDeleteTextures(1, &textureInit3ID);
	glDeleteTextures(1, &textureScreenID);
	glDeleteTextures(1, &textureScreen2ID);
	glDeleteTextures(1, &textureScreen3ID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

/*void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}
*/
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	if(!iniciaPartida){
		bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
		if(textureActivaID == textureInit1ID && presionarEnter){
			iniciaPartida = true;
			textureActivaID = textureScreenID;
		}
		else if(!presionarOpcion && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
			presionarOpcion = true;
			if(textureActivaID == textureInit1ID)
				textureActivaID = textureInit2ID;
			else if(textureActivaID == textureInit2ID)
				textureActivaID = textureInit1ID;
		}
		else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
			presionarOpcion = false;
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime*5.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime*5.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime*5.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime*5.0f);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
	offsetX = 0;
	offsetY = 0;
	
	//Controles de mayow.
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, 0.02f*5.0f, glm::vec3(0, 1, 0));
		animationMayowIndex = 0;
	} else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, -0.02f*5.0f, glm::vec3(0, 1, 0));
		animationMayowIndex = 0;
	}
	if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, 0.02*8.0f));
		animationMayowIndex = 0;
	}
	else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, -0.02*8.0f));
		animationMayowIndex = 0;
	}
	
	bool StatFly_ = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
	if(!Fly_ && StatFly_){
		Fly_ = true;
		Start_ = currTime;
		T_ = 0;
	}
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;

	modelMatrixTuboM = glm::translate(modelMatrixTuboM, glm::vec3(0.0, 0.0, 80.0));
	modelMatrixTuboM2 = glm::translate(modelMatrixTuboM2, glm::vec3(0.0, 20.0, 80.0));
	modelMatrixTuboM2 = glm::rotate(modelMatrixTuboM2, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixTuboM3 = glm::translate(modelMatrixTuboM3, glm::vec3(0.0, 0.0, 60.0));
	modelMatrixTuboM4 = glm::translate(modelMatrixTuboM4, glm::vec3(0.0, 20.0, 60.0));
	modelMatrixTuboM4 = glm::rotate(modelMatrixTuboM4, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixTuboM5 = glm::translate(modelMatrixTuboM5, glm::vec3(0.0, 0.0, 40.0));
	modelMatrixTuboM6 = glm::translate(modelMatrixTuboM6, glm::vec3(0.0, 20.0, 40.0));
	modelMatrixTuboM6 = glm::rotate(modelMatrixTuboM6, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixTuboM7 = glm::translate(modelMatrixTuboM7, glm::vec3(0.0, 0.0, 20.0));
	modelMatrixTuboM8 = glm::translate(modelMatrixTuboM8, glm::vec3(0.0, 20.0, 20.0));
	modelMatrixTuboM8 = glm::rotate(modelMatrixTuboM8, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixTuboM9 = glm::translate(modelMatrixTuboM9, glm::vec3(0.0, 0.0, 0.0));
	modelMatrixTuboM10 = glm::translate(modelMatrixTuboM10, glm::vec3(0.0, 20.0, 0.0));
	modelMatrixTuboM10 = glm::rotate(modelMatrixTuboM10, glm::radians(180.0f), glm::vec3(0, 0, 1));
	
	modelMatrixPilarH = glm::translate(modelMatrixPilarH, glm::vec3(0.0, 0.0, -20.0));
	modelMatrixPilarH2 = glm::translate(modelMatrixPilarH2, glm::vec3(0.0, 20.0, -20.0));
	modelMatrixPilarH2 = glm::rotate(modelMatrixPilarH2, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPilarH3 = glm::translate(modelMatrixPilarH3, glm::vec3(0.0, 0.0, -40.0));
	modelMatrixPilarH4 = glm::translate(modelMatrixPilarH4, glm::vec3(0.0, 20.0, -40.0));
	modelMatrixPilarH4 = glm::rotate(modelMatrixPilarH4, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPilarH5 = glm::translate(modelMatrixPilarH5, glm::vec3(0.0, 0.0, -60.0));
	modelMatrixPilarH6 = glm::translate(modelMatrixPilarH6, glm::vec3(0.0, 20.0, -60.0));
	modelMatrixPilarH6 = glm::rotate(modelMatrixPilarH6, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPilarH7 = glm::translate(modelMatrixPilarH7, glm::vec3(0.0, 0.0, -80.0));
	modelMatrixPilarH8 = glm::translate(modelMatrixPilarH8, glm::vec3(0.0, 20.0, -80.0));
	modelMatrixPilarH8 = glm::rotate(modelMatrixPilarH8, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPilarH9 = glm::translate(modelMatrixPilarH9, glm::vec3(0.0, 0.0, -100.0));
	modelMatrixPilarH10 = glm::translate(modelMatrixPilarH10, glm::vec3(0.0, 20.0, -100.0));
	modelMatrixPilarH10 = glm::rotate(modelMatrixPilarH10, glm::radians(180.0f), glm::vec3(0, 0, 1));

	modelMatrixPicoR = glm::translate(modelMatrixPicoR, glm::vec3(0.0, 0.0, -120.0));
	modelMatrixPicoR2 = glm::translate(modelMatrixPicoR2, glm::vec3(0.0, 20.0, -120.0));
	modelMatrixPicoR2 = glm::rotate(modelMatrixPicoR2, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPicoR3 = glm::translate(modelMatrixPicoR3, glm::vec3(0.0, 0.0, -140.0));
	modelMatrixPicoR4 = glm::translate(modelMatrixPicoR4, glm::vec3(0.0, 20.0, -140.0));
	modelMatrixPicoR4 = glm::rotate(modelMatrixPicoR4, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPicoR5 = glm::translate(modelMatrixPicoR5, glm::vec3(0.0, 0.0, -160.0));
	modelMatrixPicoR6 = glm::translate(modelMatrixPicoR6, glm::vec3(0.0, 20.0, -160.0));
	modelMatrixPicoR6 = glm::rotate(modelMatrixPicoR6, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPicoR7 = glm::translate(modelMatrixPicoR7, glm::vec3(0.0, 0.0, -180.0));
	modelMatrixPicoR8 = glm::translate(modelMatrixPicoR8, glm::vec3(0.0, 20.0, -180.0));
	modelMatrixPicoR8 = glm::rotate(modelMatrixPicoR8, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixPicoR9 = glm::translate(modelMatrixPicoR9, glm::vec3(0.0, 0.0, -200.0));
	modelMatrixPicoR10 = glm::translate(modelMatrixPicoR10, glm::vec3(0.0, 20.0, -200.0));
	modelMatrixPicoR10 = glm::rotate(modelMatrixPicoR10, glm::radians(180.0f), glm::vec3(0, 0, 1));

	modelMatrixCactus = glm::translate(modelMatrixCactus, glm::vec3(0.0, 0.0, -220.0));
	modelMatrixCactus2 = glm::translate(modelMatrixCactus2, glm::vec3(0.0, 20.0, -220.0));
	modelMatrixCactus2 = glm::rotate(modelMatrixCactus2, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixCactus2 = glm::rotate(modelMatrixCactus2, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus3 = glm::translate(modelMatrixCactus3, glm::vec3(0.0, 0.0, -240.0));
	modelMatrixCactus3 = glm::rotate(modelMatrixCactus3, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus4 = glm::translate(modelMatrixCactus4, glm::vec3(0.0, 20.0, -240.0));
	modelMatrixCactus4 = glm::rotate(modelMatrixCactus4, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixCactus4 = glm::rotate(modelMatrixCactus4, glm::radians(45.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus5 = glm::translate(modelMatrixCactus5, glm::vec3(0.0, 0.0, -260.0));
	modelMatrixCactus5 = glm::rotate(modelMatrixCactus5, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus6 = glm::translate(modelMatrixCactus6, glm::vec3(0.0, 20.0, -260.0));
	modelMatrixCactus6 = glm::rotate(modelMatrixCactus6, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixCactus7 = glm::translate(modelMatrixCactus7, glm::vec3(0.0, 0.0, -280.0));
	modelMatrixCactus7 = glm::rotate(modelMatrixCactus7, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus8 = glm::translate(modelMatrixCactus8, glm::vec3(0.0, 20.0, -280.0));
	modelMatrixCactus8 = glm::rotate(modelMatrixCactus8, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixCactus8 = glm::rotate(modelMatrixCactus8, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus9 = glm::translate(modelMatrixCactus9, glm::vec3(0.0, 0.0, -300.0));
	modelMatrixCactus9 = glm::rotate(modelMatrixCactus9, glm::radians(135.0f), glm::vec3(0, 1, 0));
	modelMatrixCactus10 = glm::translate(modelMatrixCactus10, glm::vec3(0.0, 20.0, -300.0));
	modelMatrixCactus10 = glm::rotate(modelMatrixCactus10, glm::radians(180.0f), glm::vec3(0, 0, 1));
	modelMatrixCactus10 = glm::rotate(modelMatrixCactus10, glm::radians(90.0f), glm::vec3(0, 1, 0));

	modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0f, 0.05f, 100.0f));
	
	lastTime = TimeManager::Instance().GetTime();
	textureActivaID = textureInit1ID;

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		
		std::map<std::string, bool> collisionDetection;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();
		if(modelSelected == 0){
			axis = glm::axis(glm::quat_cast(modelMatrixMayow));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
			target = modelMatrixMayow[3];
		}	
		/*
		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		glm::mat4 view = camera->getViewMatrix();
		*/

		//Settea la matriz de vista y projection al shader con solo color.
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));
		//Settea la matriz de vista y projection al shader con skybox.
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		//Settea la matriz de vista y projection al shader con multiples luces.
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		//Settea la matriz de vista y projection al shader con multiples luces.
		shaderTerrain.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));

		//Neblina.
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));

		//Propiedades Luz direccional.
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));

		//Propiedades spotLights.
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderTerrain.setInt("spotLightCount", 1);
		glm::vec3 spotPosition = glm::vec3(modelMatrixMayow * glm::vec4(0.0, 0.2, 1.75, 1.0));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.07);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.07);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));

		//Propiedades pointLights.
		shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Position.size());
		for(int i = 0; i < lamp1Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.0, 10.35, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}
		for(int i = 0; i < lamp2Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.75, 5.0, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
		}

		//Render de imagen de frente.
		if(!iniciaPartida){
			shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
			shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureActivaID);
			shaderTexture.setInt("outTexture", 0);
			boxIntro.render();
			glfwSwapBuffers(window);
			continue;
		}

		//Terrain Cesped.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureCespedID);
		shaderTerrain.setInt("backgroundTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
		shaderTerrain.setInt("rTexture", 1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
		shaderTerrain.setInt("gTexture", 2);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
		shaderTerrain.setInt("bTexture", 3);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
		shaderTerrain.setInt("blendMapTexture", 4);
		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(80, 80)));
		terrain.setPosition(glm::vec3(100, 0, 100));
		terrain.render();
		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
		glBindTexture(GL_TEXTURE_2D, 0);

		//Custom objects obj.
		//Paredes.
		glActiveTexture(GL_TEXTURE0);
       	 	glBindTexture(GL_TEXTURE_2D, texturePraderaID);
        	shaderMulLighting.setInt("texture1", 0);
        	//Pared1.
		Pared1.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared1.setPosition(glm::vec3(-20.0f, 10.0f, 75.0f));
		Pared1.render();
		//Pared2.
		Pared2.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared2.setPosition(glm::vec3(-20.0f, 10.0f, 25.0f));
		Pared2.render();
		//Pared3.
		Pared3.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared3.setPosition(glm::vec3(20.0f, 10.0f, 75.0f));
		Pared3.render();
		//Pared4.
		Pared4.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared4.setPosition(glm::vec3(20.0f, 10.0f, 25.0f));
		Pared4.render();

		glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, textureMontañasHeladasID);
        	shaderMulLighting.setInt("texture1", 0);
		//Pared5.
		Pared5.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared5.setPosition(glm::vec3(-20.0f, 10.0f, -25.0f));
		Pared5.render();
		//Pared6.
		Pared6.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared6.setPosition(glm::vec3(-20.0f, 10.0f, -75.0f));
		Pared6.render();
		//Pared7.
		Pared7.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared7.setPosition(glm::vec3(20.0f, 10.0f, -25.0f));
		Pared7.render();
		//Pared8.
		Pared8.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared8.setPosition(glm::vec3(20.0f, 10.0f, -75.0f));
		Pared8.render();

		glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, textureMontañaRocosaID);
        	shaderMulLighting.setInt("texture1", 0);
		//Pared9.
		Pared9.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared9.setPosition(glm::vec3(-20.0f, 10.0f, -125.0f));
		Pared9.render();
		//Pared10.
		Pared10.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared10.setPosition(glm::vec3(-20.0f, 10.0f, -175.0f));
		Pared10.render();
		//Pared11.
		Pared11.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared11.setPosition(glm::vec3(20.0f, 10.0f, -125.0f));
		Pared11.render();
		//Pared12.
		Pared12.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared12.setPosition(glm::vec3(20.0f, 10.0f, -175.0f));
		Pared12.render();

		glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, textureDesiertoID);
        	shaderMulLighting.setInt("texture1", 0);
		//Pared13.
		Pared13.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared13.setPosition(glm::vec3(-20.0f, 10.0f, -225.0f));
		Pared13.render();
		//Pared14.
		Pared14.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared14.setPosition(glm::vec3(-20.0f, 10.0f, -275.0f));
		Pared14.render();
		//Pared15.
		Pared15.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared15.setPosition(glm::vec3(20.0f, 10.0f, -225.0f));
		Pared15.render();
		//Pared16.
		Pared16.setScale(glm::vec3(0.2, 20.0, 50.0));
		Pared16.setPosition(glm::vec3(20.0f, 10.0f, -275.0f));
		Pared16.render();
		
		//Obstaculos Tubos.
		//Tubo1.
		modelTuboM.setScale(glm::vec3(0.7f, 0.45f, 0.7f));
		modelTuboM.render(modelMatrixTuboM);
		glActiveTexture(GL_TEXTURE0);
		//Tubo2 arriba.
		modelTuboM.setScale(glm::vec3(0.7f, 0.60f, 0.7f));
		modelTuboM.render(modelMatrixTuboM2);
		glActiveTexture(GL_TEXTURE0);
		//Tubo3.
		modelTuboM.setScale(glm::vec3(0.7f, 0.65f, 0.7f));
		modelTuboM.render(modelMatrixTuboM3);
		glActiveTexture(GL_TEXTURE0);
		//Tubo4 arriba.
		modelTuboM.setScale(glm::vec3(0.7f, 0.40f, 0.7f));
		modelTuboM.render(modelMatrixTuboM4);
		glActiveTexture(GL_TEXTURE0);
		//Tubo5.
		modelTuboM.setScale(glm::vec3(0.7f, 0.35f, 0.7f));
		modelTuboM.render(modelMatrixTuboM5);
		glActiveTexture(GL_TEXTURE0);
		//Tubo6 arriba.
		modelTuboM.setScale(glm::vec3(0.7f, 0.70f, 0.7f));
		modelTuboM.render(modelMatrixTuboM6);
		glActiveTexture(GL_TEXTURE0);
		//Tubo7.
		modelTuboM.setScale(glm::vec3(0.7f, 0.65f, 0.7f));
		modelTuboM.render(modelMatrixTuboM7);
		glActiveTexture(GL_TEXTURE0);
		//Tubo8 arriba.
		modelTuboM.setScale(glm::vec3(0.7f, 0.35f, 0.7f));
		modelTuboM.render(modelMatrixTuboM8);
		glActiveTexture(GL_TEXTURE0);
		//Tubo9.
		modelTuboM.setScale(glm::vec3(0.7f, 0.45f, 0.7f));
		modelTuboM.render(modelMatrixTuboM9);
		glActiveTexture(GL_TEXTURE0);
		//Tubo10 arriba.
		modelTuboM.setScale(glm::vec3(0.7f, 0.60f, 0.7f));
		modelTuboM.render(modelMatrixTuboM10);
		glActiveTexture(GL_TEXTURE0);
		
		//Obstaculos Pilares de hielo.
		//Pilar 1.
		modelPilarH.setScale(glm::vec3(0.7f, 1.0f, 0.7f));
		modelPilarH.render(modelMatrixPilarH);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 2 arriba.
		modelPilarH2.setScale(glm::vec3(0.7f, 1.5f, 0.7f));
		modelPilarH2.render(modelMatrixPilarH2);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 3.
		modelPilarH3.setScale(glm::vec3(0.7f, 2.0f, 0.7f));
		modelPilarH3.render(modelMatrixPilarH3);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 4 arriba.
		modelPilarH4.setScale(glm::vec3(0.7f, 0.5f, 0.7f));
		modelPilarH4.render(modelMatrixPilarH4);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 5.
		modelPilarH5.setScale(glm::vec3(0.7f, 0.5f, 0.7f));
		modelPilarH5.render(modelMatrixPilarH5);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 6 arriba.
		modelPilarH6.setScale(glm::vec3(0.7f, 2.0f, 0.7f));
		modelPilarH6.render(modelMatrixPilarH6);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 7.
		modelPilarH7.setScale(glm::vec3(0.7f, 1.5f, 0.7f));
		modelPilarH7.render(modelMatrixPilarH7);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 8 arriba.
		modelPilarH8.setScale(glm::vec3(0.7f, 1.0f, 0.7f));
		modelPilarH8.render(modelMatrixPilarH8);
		glActiveTexture(GL_TEXTURE0);
		//Pilar9.
		modelPilarH9.setScale(glm::vec3(0.7f, 0.5f, 0.7f));
		modelPilarH9.render(modelMatrixPilarH9);
		glActiveTexture(GL_TEXTURE0);
		//Pilar 10 arriba.
		modelPilarH10.setScale(glm::vec3(0.7f, 2.0f, 0.7f));
		modelPilarH10.render(modelMatrixPilarH10);
		glActiveTexture(GL_TEXTURE0);

		//Obstaculos picos de roca.
		//Pico 1.
		modelPicoR.setScale(glm::vec3(0.7f, 0.6f, 0.7f));
		modelPicoR.render(modelMatrixPicoR);
		glActiveTexture(GL_TEXTURE0);
		//Pico 2 arriba.
		modelPicoR2.setScale(glm::vec3(0.7f, 1.0f, 0.7f));
		modelPicoR2.render(modelMatrixPicoR2);
		glActiveTexture(GL_TEXTURE0);
		//Pico 3.
		modelPicoR3.setScale(glm::vec3(0.7f, 1.0f, 0.5f));
		modelPicoR3.render(modelMatrixPicoR3);
		glActiveTexture(GL_TEXTURE0);
		//Pico 4 arriba.
		modelPicoR4.setScale(glm::vec3(0.7f, 0.6f, 0.7f));
		modelPicoR4.render(modelMatrixPicoR4);
		glActiveTexture(GL_TEXTURE0);
		//Pico 5.
		modelPicoR5.setScale(glm::vec3(0.7f, 0.2f, 0.7f));
		modelPicoR5.render(modelMatrixPicoR5);
		glActiveTexture(GL_TEXTURE0);
		//Pico 6 arriba.
		modelPicoR6.setScale(glm::vec3(0.7f, 1.4f, 0.7f));
		modelPicoR6.render(modelMatrixPicoR6);
		glActiveTexture(GL_TEXTURE0);
		//Pico 7.
		modelPicoR7.setScale(glm::vec3(0.7f, 1.5f, 0.7f));
		modelPicoR7.render(modelMatrixPicoR7);
		glActiveTexture(GL_TEXTURE0);
		//Pico 8 arriba.
		modelPicoR8.setScale(glm::vec3(0.7f, 0.1f, 0.7f));
		modelPicoR8.render(modelMatrixPicoR8);
		glActiveTexture(GL_TEXTURE0);
		//Pico 9.
		modelPicoR9.setScale(glm::vec3(0.7f, 0.7f, 0.7f));
		modelPicoR9.render(modelMatrixPicoR9);
		glActiveTexture(GL_TEXTURE0);
		//Pico 10 arriba.
		modelPicoR10.setScale(glm::vec3(0.7f, 1.1f, 0.7f));
		modelPicoR10.render(modelMatrixPicoR10);
		glActiveTexture(GL_TEXTURE0);

		//Obstaculos cactus.
		//Cactus 1.
		modelCactus.setScale(glm::vec3(1.2f, 1.5, 1.2f));
		modelCactus.render(modelMatrixCactus);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 2 arriba.
		modelCactus2.setScale(glm::vec3(1.2f, 1.1f, 1.2f));
		modelCactus2.render(modelMatrixCactus2);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 3.
		modelCactus3.setScale(glm::vec3(1.2f, 2.0f, 1.2f));
		modelCactus3.render(modelMatrixCactus3);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 4 arriba.
		modelCactus4.setScale(glm::vec3(1.2f, 0.6f, 1.2f));
		modelCactus4.render(modelMatrixCactus4);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 5.
		modelCactus5.setScale(glm::vec3(1.2f, 0.6f, 1.2f));
		modelCactus5.render(modelMatrixCactus5);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 6 arriba.
		modelCactus6.setScale(glm::vec3(1.2f, 2.0f, 1.2f));
		modelCactus6.render(modelMatrixCactus6);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 7.
		modelCactus7.setScale(glm::vec3(1.2f, 1.5f, 1.2f));
		modelCactus7.render(modelMatrixCactus7);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 8 arriba.
		modelCactus8.setScale(glm::vec3(1.2f, 1.0f, 1.2f));
		modelCactus8.render(modelMatrixCactus8);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 9.
		modelCactus9.setScale(glm::vec3(1.2f, 1.5f, 1.2f));
		modelCactus9.render(modelMatrixCactus9);
		glActiveTexture(GL_TEXTURE0);
		//Cactus 10 arriba.
		modelCactus10.setScale(glm::vec3(1.2f, 1.2f, 1.2f));
		modelCactus10.render(modelMatrixCactus10);
		glActiveTexture(GL_TEXTURE0);
		
		//Render lamp.
		for(int i = 0; i < lamp1Position.size(); i++){
			lamp1Position[i].y = terrain.getHeightTerrain(lamp1Position[i].x, lamp1Position[i].z);
			modelLamp1.setPosition(lamp1Position[i]);
			modelLamp1.setScale(glm::vec3(0.5));
			modelLamp1.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
			modelLamp1.render();
		}
		for(int i = 0; i < lamp2Position.size(); i++){
			lamp2Position[i].y = terrain.getHeightTerrain(lamp2Position[i].x, lamp2Position[i].z);
			modelLamp2.setPosition(lamp2Position[i]);
			modelLamp2.setScale(glm::vec3(0.5));
			modelLamp2.setOrientation(glm::vec3(0, lamp2Orientation[i], 0));
			modelLamp2.render();
			modelLampPost2.setPosition(lamp2Position[i]);
			modelLampPost2.setScale(glm::vec3(0.5));
			modelLampPost2.setOrientation(glm::vec3(0, lamp2Orientation[i], 0));
			modelLampPost2.render();
		}

		
		//Objetos animados por huesos.
		glm::vec3 ejey = glm::normalize(terrain.getNormalTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]));
		glm::vec3 ejex = glm::vec3(modelMatrixMayow[0]);
		glm::vec3 ejez = glm::normalize(glm::cross(ejex, ejey));
		ejex = glm::normalize(glm::cross(ejey, ejez));
		modelMatrixMayow[0] = glm::vec4(ejex, 0.0);
		modelMatrixMayow[1] = glm::vec4(ejey, 0.0);
		modelMatrixMayow[2] = glm::vec4(ejez, 0.0);
		modelMatrixMayow[3][1] = -FlyG_ * T_ * T_ + 3.5 * T_ + terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
		T_ = currTime - Start_;
		if(modelMatrixMayow[3][1] < terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2])){
			Fly_ = false;
			modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
		}
		glm::mat4 modelMatrixMayowBody = glm::mat4(modelMatrixMayow);
		modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(0.021f));
		mayowModelAnimate.setAnimationIndex(animationMayowIndex);
		mayowModelAnimate.render(modelMatrixMayowBody);
		animationMayowIndex = 0;


		//Skybox.
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		//Deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro.
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);

		//Colliders.
		//Lamps1 colliders.
		for (int i = 0; i < lamp1Position.size(); i++){
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp1Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp1Orientation[i]),
					glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp1-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(0.5, 0.5, 0.5));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, modelLamp1.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLamp1.getObb().e * glm::vec3(0.5, 0.5, 0.5);
			std::get<0>(collidersOBB.find("lamp1-" + std::to_string(i))->second) = lampCollider;
		}

		//Lamps2 colliders.
		for (int i = 0; i < lamp2Position.size(); i++){
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp2Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp2Orientation[i]),
					glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp2-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			//Set the orientation of collider before doing the scale.
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(1.0, 1.0, 1.0));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, modelLampPost2.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLampPost2.getObb().e * glm::vec3(1.0, 1.0, 1.0);
			std::get<0>(collidersOBB.find("lamp2-" + std::to_string(i))->second) = lampCollider;
		}

		//Collider de mayow.
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		//Set the orientation of collider before doing the scale.
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.021, 0.021, 0.021));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
				glm::vec3(mayowModelAnimate.getObb().c.x,
						mayowModelAnimate.getObb().c.y,
						mayowModelAnimate.getObb().c.z));
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.021, 0.021, 0.021) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);

		/*//Render de colliders.
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}
		*/
		std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
		std::map<std::string, glm::vec3>::iterator itblend;
		for(itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++){
			float distanceFromView = glm::length(camera->getPosition() - itblend->second);
			blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
		}

		//Render de las transparencias.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);

		//Render de imagen de frente.
		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureActivaID);
		shaderTexture.setInt("outTexture", 0);
		glEnable(GL_BLEND);
		boxIntro.render();
		glDisable(GL_BLEND);
		modelText->render("Texto en OpenGL", -1, 0);

		//Prueba de colisiones.
		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt && testSphereSphereIntersection(
					std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay collision entre " << it->first <<
						" y el modelo " << jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator it =
			collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isColision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt && 
					testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay colision entre " << it->first << " y el modelo" <<
						jt->first << std::endl;
					isColision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isColision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::cout << "Hay colision del " << it->first << " y el modelo" <<
						jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, true);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		std::map<std::string, bool>::iterator itCollision;
		for (itCollision = collisionDetection.begin(); 
			itCollision != collisionDetection.end(); itCollision++) {
			std::map<std::string, std::tuple<AbstractModel::SBB, 
				glm::mat4, glm::mat4>>::iterator sbbBuscado = 
				collidersSBB.find(itCollision->first);
			std::map<std::string, std::tuple<AbstractModel::OBB,
				glm::mat4, glm::mat4>>::iterator obbBuscado =
				collidersOBB.find(itCollision->first);
			if (sbbBuscado != collidersSBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersSBB, itCollision->first);
			}
			if (obbBuscado != collidersOBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersOBB, itCollision->first);
				else {
					if (itCollision->first.compare("mayow") == 0)
						modelMatrixMayow = std::get<1>(obbBuscado->second);
					
				}
			}
		}
		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
