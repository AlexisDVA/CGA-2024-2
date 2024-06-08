#define _USE_MATH_DEFINES
#include <set>
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
#include "Headers/ThirdPersonCamera.h"
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

//std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());
std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 20.0;

Sphere skyboxSphere(20, 20);
Box boxCesped;
Sphere esfera1(10, 10);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxIntro;

Box ParedHU;
Box ParedHD;
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
//Bird
Model birdModelAnimate;

// Terrain model instance
Terrain terrain(-1, -1, 400, 8, "../Textures/HeightmapProyecto_.png");

GLuint textureCespedID, textureWallID, texturePraderaID, textureMontañasHeladasID, textureMontañaRocosaID, textureDesiertoID, textureHieloID, textureArenaID, textureTransparenciaID;
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

glm::mat4 modelMatrixBird = glm::mat4(1.0f);
int animationBirdIndex = 0;
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

//Animacion de Bird.
float birdSpeed = 0.35f;//Velocidad inicial del bird.
bool isSpacePressed = false;
float birdGravity = 0.30f;
float birdJumpSpeed = 0.30f;

//Contador de colisiones.
int colisiones = 0;
std::set<std::string> colisionesActuales;

//Colliders.
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

//Sound.
#define NUM_BUFFERS 3
#define NUM_SOURCES 3
#define NUM_ENVIRONMENTS 1
//Listener.
ALfloat listenerPos[] = {0.0, 0.0, 4.0};
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
//Source 0.
ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
//Buffers.
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
//Configs.
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = {true};

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

	ParedHU.init();
	ParedHU.setShader(&shaderMulLighting);
	ParedHD.init();
	ParedHD.setShader(&shaderMulLighting);
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

	//Bird.
	birdModelAnimate.loadModel("../models/Modelos Videojuego/Bird_.fbx");
	birdModelAnimate.setShader(&shaderMulLighting);

	//Terreno.
	terrain.init();
	terrain.setShader(&shaderTerrain);

	//Se inicializa el model de render text.
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
	modelText->Initialize();

	camera->setPosition(glm::vec3(0.0, 3.0, 4.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0);
	
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

	//Pared Transparente
	Texture textureTransparencia("../Textures/Transparencia.png"); 
    textureTransparencia.loadImage();
    glGenTextures(1, &textureTransparenciaID);
    glBindTexture(GL_TEXTURE_2D, textureTransparenciaID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureTransparencia.getData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, textureTransparencia.getChannels() == 3 ? GL_RGB : GL_RGBA, textureTransparencia.getWidth(), textureTransparencia.getHeight(), 0,
        textureTransparencia.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureTransparencia.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Fallo la carga de textura" << std::endl;
    }
    textureTransparencia.freeImage();
	
   //Sound.
	//OpenAL init.
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError();
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../sounds/SongProyecto_2.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}
	alGetError();
	alGenSources(NUM_SOURCES, source);
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 3.0f);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 2000);
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

	ParedHU.destroy();
	ParedHD.destroy();
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
	birdModelAnimate.destroy();
	
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

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

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

	if (!iniciaPartida) {
        bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
        if (textureActivaID == textureInit1ID && presionarEnter) {
            iniciaPartida = true;
            textureActivaID = textureScreenID; // Cambiar a la textura de 3 vidas
            colisiones = 0; // Resetear el contador de colisiones
        }
    } else {
        // Solo permitir cerrar el juego con ESC cuando se muestra "Game over"
        if (textureActivaID == textureInit2ID && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            return false;
        }
    }

	// Controlar la tecla SPACE para el salto
    isSpacePressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

	//Camara en 1ra persona
	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
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
	*/

	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);

	offsetX = 0;
	offsetY = 0;
	
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

	modelMatrixBird = glm::translate(modelMatrixBird, glm::vec3(0.0f, 6.5f, 95.0f));
	modelMatrixBird = glm::rotate(modelMatrixBird, glm::radians(180.0f), glm::vec3(0, 1, 0));
	
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

		if (iniciaPartida) {
			// Actualizar la posición y velocidad del bird
			glm::vec3 birdPosition = glm::vec3(modelMatrixBird[3]);
			// Aumentar la velocidad en ciertos puntos
			if (birdPosition.z <= 0.0f && birdPosition.z > -100.0f) {
				birdSpeed = 0.4f;
			} else if (birdPosition.z <= -100.0f && birdPosition.z > -200.0f) {
				birdSpeed = 0.45f;
			} else if (birdPosition.z <= -200.0f) {
				birdSpeed = 0.5f;
			}

			// Avance automático hacia adelante
			modelMatrixBird = glm::translate(modelMatrixBird, glm::vec3(0.0f, 0.0f, birdSpeed));
			
			// Movimiento hacia arriba si se presiona SPACE
            if (isSpacePressed) {
                modelMatrixBird = glm::translate(modelMatrixBird, glm::vec3(0.0f, birdJumpSpeed, 0.0f));
            } else {
                // Movimiento descendente constante (gravedad)
                modelMatrixBird = glm::translate(modelMatrixBird, glm::vec3(0.0f, -birdGravity, 0.0f));
            }
			
			// Condición para mostrar la pantalla "Final"
			if (birdPosition.z <= -300.0f) {
				iniciaPartida = false; // Detener el movimiento del bird
				textureActivaID = textureInit3ID; // Cambiar a la textura de "Final"
			}
		}

		std::map<std::string, bool> collisionDetection;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		//glm::mat4 view = camera->getViewMatrix();
		
		if(modelSelected == 0){
			axis = glm::axis(glm::quat_cast(modelMatrixBird));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixBird));
			target = modelMatrixBird[3];
		}	
		
		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 0)
			angleTarget -= glm::radians(15.0f);//90.0f
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		glm::mat4 view = camera->getViewMatrix();

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
		glm::vec3 spotPosition = glm::vec3(modelMatrixBird * glm::vec4(0.0, 10.0, 1.75, 1.0));
		//glm::vec3 spotPosition = glm::vec3(modelMatrixMayow * glm::vec4(0.0, 0.2, 1.75, 1.0));
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
		
		/*glActiveTexture(GL_TEXTURE0);
       	 	glBindTexture(GL_TEXTURE_2D, textureTransparenciaID);
        	shaderMulLighting.setInt("texture1", 0);
		//Pared Arriba.
		ParedHU.setScale(glm::vec3(40.0, 0.01, 400.0));
		ParedHU.setPosition(glm::vec3(0.0f, 23.0f, -100.0f));
		ParedHU.render();
		//ParedAbajo.
		ParedHD.setScale(glm::vec3(40.0, 0.01, 400.0));
		ParedHD.setPosition(glm::vec3(0.0f, -3.0f, -100.0f));
		ParedHD.render();
		*/
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
		modelPicoR10.setScale(glm::vec3(0.7f, 0.9f, 0.7f));
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
		
		//Objetos animados por huesos.
		glm::mat4 modelMatrixBirdBody = glm::mat4(modelMatrixBird);
		modelMatrixBirdBody = glm::scale(modelMatrixBirdBody, glm::vec3(0.02f));
		birdModelAnimate.setAnimationIndex(animationBirdIndex);
		birdModelAnimate.render(modelMatrixBirdBody);
		animationBirdIndex = 0;

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

		//*************************************************************************** */
		//*************************Colliders.**********************************
		//******************************************************************** */
		
		/*//Pared arriba
		glm::mat4 modelMatrixColliderParedHU = glm::mat4(modelMatrixColliderParedHU);
		AbstractModel::OBB ParedHUCollider;
		// Set the orientation of collider before doing the scale
		ParedHUCollider.u = glm::quat_cast(modelMatrixColliderParedHU);
		modelMatrixColliderParedHU = glm::scale(modelMatrixColliderParedHU, glm::vec3(40.0f, 0.01f, 400.0f));
		modelMatrixColliderParedHU = glm::translate(
				modelMatrixColliderParedHU, ParedHU.getObb().c);
		ParedHUCollider.c = glm::vec3(modelMatrixColliderParedHU[3]);
		ParedHUCollider.e = ParedHU.getObb().e * glm::vec3(40.0f, 0.01f, 400.0f);
		addOrUpdateColliders(collidersOBB, "ParedHU", ParedHUCollider, modelMatrixColliderParedHU);
		*/
		//-----------------------Colliders de Tubos-------------------------------------
		//Tubo1
		glm::mat4 modelMatrixColliderTuboM = glm::mat4(modelMatrixTuboM);
		AbstractModel::OBB TuboMCollider;
		// Set the orientation of collider before doing the scale
		TuboMCollider.u = glm::quat_cast(modelMatrixTuboM);
		modelMatrixColliderTuboM = glm::scale(modelMatrixColliderTuboM,
				glm::vec3(0.7f, 0.45f, 0.7f));
		modelMatrixColliderTuboM = glm::translate(
				modelMatrixColliderTuboM, modelTuboM.getObb().c);
		TuboMCollider.c = glm::vec3(modelMatrixColliderTuboM[3]);
		TuboMCollider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.45f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM", TuboMCollider, modelMatrixTuboM);
		
		// Tubo 2
		glm::mat4 modelMatrixColliderTuboM2 = glm::mat4(modelMatrixTuboM2);
		AbstractModel::OBB TuboM2Collider;
		// Set the orientation of collider before doing the scale
		TuboM2Collider.u = glm::quat_cast(modelMatrixTuboM2);
		modelMatrixColliderTuboM2 = glm::scale(modelMatrixColliderTuboM2, glm::vec3(0.7f, 0.60f, 0.7f));
		modelMatrixColliderTuboM2 = glm::translate(modelMatrixColliderTuboM2, modelTuboM.getObb().c);
		TuboM2Collider.c = glm::vec3(modelMatrixColliderTuboM2[3]);
		TuboM2Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.60f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM2", TuboM2Collider, modelMatrixTuboM2);

		// Tubo 3
		glm::mat4 modelMatrixColliderTuboM3 = glm::mat4(modelMatrixTuboM3);
		AbstractModel::OBB TuboM3Collider;
		// Set the orientation of collider before doing the scale
		TuboM3Collider.u = glm::quat_cast(modelMatrixTuboM3);
		modelMatrixColliderTuboM3 = glm::scale(modelMatrixColliderTuboM3, glm::vec3(0.7f, 0.65f, 0.7f));
		modelMatrixColliderTuboM3 = glm::translate(modelMatrixColliderTuboM3, modelTuboM.getObb().c);
		TuboM3Collider.c = glm::vec3(modelMatrixColliderTuboM3[3]);
		TuboM3Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.65f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM3", TuboM3Collider, modelMatrixTuboM3);

		// Tubo 4
		glm::mat4 modelMatrixColliderTuboM4 = glm::mat4(modelMatrixTuboM4);
		AbstractModel::OBB TuboM4Collider;
		// Set the orientation of collider before doing the scale
		TuboM4Collider.u = glm::quat_cast(modelMatrixTuboM4);
		modelMatrixColliderTuboM4 = glm::scale(modelMatrixColliderTuboM4, glm::vec3(0.7f, 0.40f, 0.7f));
		modelMatrixColliderTuboM4 = glm::translate(modelMatrixColliderTuboM4, modelTuboM.getObb().c);
		TuboM4Collider.c = glm::vec3(modelMatrixColliderTuboM4[3]);
		TuboM4Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.40f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM4", TuboM4Collider, modelMatrixTuboM4);

		// Tubo 5
		glm::mat4 modelMatrixColliderTuboM5 = glm::mat4(modelMatrixTuboM5);
		AbstractModel::OBB TuboM5Collider;
		// Set the orientation of collider before doing the scale
		TuboM5Collider.u = glm::quat_cast(modelMatrixTuboM5);
		modelMatrixColliderTuboM5 = glm::scale(modelMatrixColliderTuboM5, glm::vec3(0.7f, 0.35f, 0.7f));
		modelMatrixColliderTuboM5 = glm::translate(modelMatrixColliderTuboM5, modelTuboM.getObb().c);
		TuboM5Collider.c = glm::vec3(modelMatrixColliderTuboM5[3]);
		TuboM5Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.35f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM5", TuboM5Collider, modelMatrixTuboM5);

		// Tubo 6
		glm::mat4 modelMatrixColliderTuboM6 = glm::mat4(modelMatrixTuboM6);
		AbstractModel::OBB TuboM6Collider;
		// Set the orientation of collider before doing the scale
		TuboM6Collider.u = glm::quat_cast(modelMatrixTuboM6);
		modelMatrixColliderTuboM6 = glm::scale(modelMatrixColliderTuboM6, glm::vec3(0.7f, 0.70f, 0.7f));
		modelMatrixColliderTuboM6 = glm::translate(modelMatrixColliderTuboM6, modelTuboM.getObb().c);
		TuboM6Collider.c = glm::vec3(modelMatrixColliderTuboM6[3]);
		TuboM6Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.70f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM6", TuboM6Collider, modelMatrixTuboM6);

		// Tubo 7
		glm::mat4 modelMatrixColliderTuboM7 = glm::mat4(modelMatrixTuboM7);
		AbstractModel::OBB TuboM7Collider;
		// Set the orientation of collider before doing the scale
		TuboM7Collider.u = glm::quat_cast(modelMatrixTuboM7);
		modelMatrixColliderTuboM7 = glm::scale(modelMatrixColliderTuboM7, glm::vec3(0.7f, 0.65f, 0.7f));
		modelMatrixColliderTuboM7 = glm::translate(modelMatrixColliderTuboM7, modelTuboM.getObb().c);
		TuboM7Collider.c = glm::vec3(modelMatrixColliderTuboM7[3]);
		TuboM7Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.65f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM7", TuboM7Collider, modelMatrixTuboM7);

		// Tubo 8
		glm::mat4 modelMatrixColliderTuboM8 = glm::mat4(modelMatrixTuboM8);
		AbstractModel::OBB TuboM8Collider;
		// Set the orientation of collider before doing the scale
		TuboM8Collider.u = glm::quat_cast(modelMatrixTuboM8);
		modelMatrixColliderTuboM8 = glm::scale(modelMatrixColliderTuboM8, glm::vec3(0.7f, 0.35f, 0.7f));
		modelMatrixColliderTuboM8 = glm::translate(modelMatrixColliderTuboM8, modelTuboM.getObb().c);
		TuboM8Collider.c = glm::vec3(modelMatrixColliderTuboM8[3]);
		TuboM8Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.35f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM8", TuboM8Collider, modelMatrixTuboM8);

		// Tubo 9
		glm::mat4 modelMatrixColliderTuboM9 = glm::mat4(modelMatrixTuboM9);
		AbstractModel::OBB TuboM9Collider;
		// Set the orientation of collider before doing the scale
		TuboM9Collider.u = glm::quat_cast(modelMatrixTuboM9);
		modelMatrixColliderTuboM9 = glm::scale(modelMatrixColliderTuboM9, glm::vec3(0.7f, 0.45f, 0.7f));
		modelMatrixColliderTuboM9 = glm::translate(modelMatrixColliderTuboM9, modelTuboM.getObb().c);
		TuboM9Collider.c = glm::vec3(modelMatrixColliderTuboM9[3]);
		TuboM9Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.45f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM9", TuboM9Collider, modelMatrixTuboM9);

		// Tubo 10
		glm::mat4 modelMatrixColliderTuboM10 = glm::mat4(modelMatrixTuboM10);
		AbstractModel::OBB TuboM10Collider;
		// Set the orientation of collider before doing the scale
		TuboM10Collider.u = glm::quat_cast(modelMatrixTuboM10);
		modelMatrixColliderTuboM10 = glm::scale(modelMatrixColliderTuboM10, glm::vec3(0.7f, 0.60f, 0.7f));
		modelMatrixColliderTuboM10 = glm::translate(modelMatrixColliderTuboM10, modelTuboM.getObb().c);
		TuboM10Collider.c = glm::vec3(modelMatrixColliderTuboM10[3]);
		TuboM10Collider.e = modelTuboM.getObb().e * glm::vec3(0.7f, 0.60f, 0.7f);
		addOrUpdateColliders(collidersOBB, "TuboM10", TuboM10Collider, modelMatrixTuboM10);

		//-------------Colliders Pilares de hielo----------------------------------
		// Pilar 1
		glm::mat4 modelMatrixColliderPilarH = glm::mat4(modelMatrixPilarH);
		AbstractModel::OBB PilarHCollider;
		// Set the orientation of collider before doing the scale
		PilarHCollider.u = glm::quat_cast(modelMatrixPilarH);
		modelMatrixColliderPilarH = glm::scale(modelMatrixColliderPilarH, glm::vec3(0.7f, 1.0f, 0.7f));
		modelMatrixColliderPilarH = glm::translate(modelMatrixColliderPilarH, modelPilarH.getObb().c);
		PilarHCollider.c = glm::vec3(modelMatrixColliderPilarH[3]);
		PilarHCollider.e = modelPilarH.getObb().e * glm::vec3(0.7f, 1.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH", PilarHCollider, modelMatrixPilarH);

		// Pilar 2
		glm::mat4 modelMatrixColliderPilarH2 = glm::mat4(modelMatrixPilarH2);
		AbstractModel::OBB PilarH2Collider;
		// Set the orientation of collider before doing the scale
		PilarH2Collider.u = glm::quat_cast(modelMatrixPilarH2);
		modelMatrixColliderPilarH2 = glm::scale(modelMatrixColliderPilarH2, glm::vec3(0.7f, 1.5f, 0.7f));
		modelMatrixColliderPilarH2 = glm::translate(modelMatrixColliderPilarH2, modelPilarH2.getObb().c);
		PilarH2Collider.c = glm::vec3(modelMatrixColliderPilarH2[3]);
		PilarH2Collider.e = modelPilarH2.getObb().e * glm::vec3(0.7f, 1.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH2", PilarH2Collider, modelMatrixPilarH2);

		// Pilar 3
		glm::mat4 modelMatrixColliderPilarH3 = glm::mat4(modelMatrixPilarH3);
		AbstractModel::OBB PilarH3Collider;
		// Set the orientation of collider before doing the scale
		PilarH3Collider.u = glm::quat_cast(modelMatrixPilarH3);
		modelMatrixColliderPilarH3 = glm::scale(modelMatrixColliderPilarH3, glm::vec3(0.7f, 2.0f, 0.7f));
		modelMatrixColliderPilarH3 = glm::translate(modelMatrixColliderPilarH3, modelPilarH3.getObb().c);
		PilarH3Collider.c = glm::vec3(modelMatrixColliderPilarH3[3]);
		PilarH3Collider.e = modelPilarH3.getObb().e * glm::vec3(0.7f, 2.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH3", PilarH3Collider, modelMatrixPilarH3);

		// Pilar 4
		glm::mat4 modelMatrixColliderPilarH4 = glm::mat4(modelMatrixPilarH4);
		AbstractModel::OBB PilarH4Collider;
		// Set the orientation of collider before doing the scale
		PilarH4Collider.u = glm::quat_cast(modelMatrixPilarH4);
		modelMatrixColliderPilarH4 = glm::scale(modelMatrixColliderPilarH4, glm::vec3(0.7f, 0.5f, 0.7f));
		modelMatrixColliderPilarH4 = glm::translate(modelMatrixColliderPilarH4, modelPilarH4.getObb().c);
		PilarH4Collider.c = glm::vec3(modelMatrixColliderPilarH4[3]);
		PilarH4Collider.e = modelPilarH4.getObb().e * glm::vec3(0.7f, 0.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH4", PilarH4Collider, modelMatrixPilarH4);

		// Pilar 5
		glm::mat4 modelMatrixColliderPilarH5 = glm::mat4(modelMatrixPilarH5);
		AbstractModel::OBB PilarH5Collider;
		// Set the orientation of collider before doing the scale
		PilarH5Collider.u = glm::quat_cast(modelMatrixPilarH5);
		modelMatrixColliderPilarH5 = glm::scale(modelMatrixColliderPilarH5, glm::vec3(0.7f, 0.5f, 0.7f));
		modelMatrixColliderPilarH5 = glm::translate(modelMatrixColliderPilarH5, modelPilarH5.getObb().c);
		PilarH5Collider.c = glm::vec3(modelMatrixColliderPilarH5[3]);
		PilarH5Collider.e = modelPilarH5.getObb().e * glm::vec3(0.7f, 0.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH5", PilarH5Collider, modelMatrixPilarH5);

		// Pilar 6
		glm::mat4 modelMatrixColliderPilarH6 = glm::mat4(modelMatrixPilarH6);
		AbstractModel::OBB PilarH6Collider;
		// Set the orientation of collider before doing the scale
		PilarH6Collider.u = glm::quat_cast(modelMatrixPilarH6);
		modelMatrixColliderPilarH6 = glm::scale(modelMatrixColliderPilarH6, glm::vec3(0.7f, 2.0f, 0.7f));
		modelMatrixColliderPilarH6 = glm::translate(modelMatrixColliderPilarH6, modelPilarH6.getObb().c);
		PilarH6Collider.c = glm::vec3(modelMatrixColliderPilarH6[3]);
		PilarH6Collider.e = modelPilarH6.getObb().e * glm::vec3(0.7f, 2.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH6", PilarH6Collider, modelMatrixPilarH6);

		// Pilar 7
		glm::mat4 modelMatrixColliderPilarH7 = glm::mat4(modelMatrixPilarH7);
		AbstractModel::OBB PilarH7Collider;
		// Set the orientation of collider before doing the scale
		PilarH7Collider.u = glm::quat_cast(modelMatrixPilarH7);
		modelMatrixColliderPilarH7 = glm::scale(modelMatrixColliderPilarH7, glm::vec3(0.7f, 1.5f, 0.7f));
		modelMatrixColliderPilarH7 = glm::translate(modelMatrixColliderPilarH7, modelPilarH7.getObb().c);
		PilarH7Collider.c = glm::vec3(modelMatrixColliderPilarH7[3]);
		PilarH7Collider.e = modelPilarH7.getObb().e * glm::vec3(0.7f, 1.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH7", PilarH7Collider, modelMatrixPilarH7);

		// Pilar 8
		glm::mat4 modelMatrixColliderPilarH8 = glm::mat4(modelMatrixPilarH8);
		AbstractModel::OBB PilarH8Collider;
		// Set the orientation of collider before doing the scale
		PilarH8Collider.u = glm::quat_cast(modelMatrixPilarH8);
		modelMatrixColliderPilarH8 = glm::scale(modelMatrixColliderPilarH8, glm::vec3(0.7f, 1.0f, 0.7f));
		modelMatrixColliderPilarH8 = glm::translate(modelMatrixColliderPilarH8, modelPilarH8.getObb().c);
		PilarH8Collider.c = glm::vec3(modelMatrixColliderPilarH8[3]);
		PilarH8Collider.e = modelPilarH8.getObb().e * glm::vec3(0.7f, 1.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH8", PilarH8Collider, modelMatrixPilarH8);

		// Pilar 9
		glm::mat4 modelMatrixColliderPilarH9 = glm::mat4(modelMatrixPilarH9);
		AbstractModel::OBB PilarH9Collider;
		// Set the orientation of collider before doing the scale
		PilarH9Collider.u = glm::quat_cast(modelMatrixPilarH9);
		modelMatrixColliderPilarH9 = glm::scale(modelMatrixColliderPilarH9, glm::vec3(0.7f, 0.5f, 0.7f));
		modelMatrixColliderPilarH9 = glm::translate(modelMatrixColliderPilarH9, modelPilarH9.getObb().c);
		PilarH9Collider.c = glm::vec3(modelMatrixColliderPilarH9[3]);
		PilarH9Collider.e = modelPilarH9.getObb().e * glm::vec3(0.7f, 0.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH9", PilarH9Collider, modelMatrixPilarH9);

		// Pilar 10
		glm::mat4 modelMatrixColliderPilarH10 = glm::mat4(modelMatrixPilarH10);
		AbstractModel::OBB PilarH10Collider;
		// Set the orientation of collider before doing the scale
		PilarH10Collider.u = glm::quat_cast(modelMatrixPilarH10);
		modelMatrixColliderPilarH10 = glm::scale(modelMatrixColliderPilarH10, glm::vec3(0.7f, 2.0f, 0.7f));
		modelMatrixColliderPilarH10 = glm::translate(modelMatrixColliderPilarH10, modelPilarH10.getObb().c);
		PilarH10Collider.c = glm::vec3(modelMatrixColliderPilarH10[3]);
		PilarH10Collider.e = modelPilarH10.getObb().e * glm::vec3(0.7f, 2.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PilarH10", PilarH10Collider, modelMatrixPilarH10);

		//------------------Colliders Picos de Roca--------------------
		// Pico 1
		glm::mat4 modelMatrixColliderPicoR = glm::mat4(modelMatrixPicoR);
		AbstractModel::OBB PicoRCollider;
		// Set the orientation of collider before doing the scale
		PicoRCollider.u = glm::quat_cast(modelMatrixPicoR);
		modelMatrixColliderPicoR = glm::scale(modelMatrixColliderPicoR, glm::vec3(0.7f, 0.6f, 0.7f));
		modelMatrixColliderPicoR = glm::translate(modelMatrixColliderPicoR, modelPicoR.getObb().c);
		PicoRCollider.c = glm::vec3(modelMatrixColliderPicoR[3]);
		PicoRCollider.e = modelPicoR.getObb().e * glm::vec3(0.7f, 0.6f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR", PicoRCollider, modelMatrixPicoR);

		// Pico 2
		glm::mat4 modelMatrixColliderPicoR2 = glm::mat4(modelMatrixPicoR2);
		AbstractModel::OBB PicoR2Collider;
		// Set the orientation of collider before doing the scale
		PicoR2Collider.u = glm::quat_cast(modelMatrixPicoR2);
		modelMatrixColliderPicoR2 = glm::scale(modelMatrixColliderPicoR2, glm::vec3(0.7f, 1.0f, 0.7f));
		modelMatrixColliderPicoR2 = glm::translate(modelMatrixColliderPicoR2, modelPicoR2.getObb().c);
		PicoR2Collider.c = glm::vec3(modelMatrixColliderPicoR2[3]);
		PicoR2Collider.e = modelPicoR2.getObb().e * glm::vec3(0.7f, 1.0f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR2", PicoR2Collider, modelMatrixPicoR2);

		// Pico 3
		glm::mat4 modelMatrixColliderPicoR3 = glm::mat4(modelMatrixPicoR3);
		AbstractModel::OBB PicoR3Collider;
		// Set the orientation of collider before doing the scale
		PicoR3Collider.u = glm::quat_cast(modelMatrixPicoR3);
		modelMatrixColliderPicoR3 = glm::scale(modelMatrixColliderPicoR3, glm::vec3(0.7f, 1.0f, 0.5f));
		modelMatrixColliderPicoR3 = glm::translate(modelMatrixColliderPicoR3, modelPicoR3.getObb().c);
		PicoR3Collider.c = glm::vec3(modelMatrixColliderPicoR3[3]);
		PicoR3Collider.e = modelPicoR3.getObb().e * glm::vec3(0.7f, 1.0f, 0.5f);
		addOrUpdateColliders(collidersOBB, "PicoR3", PicoR3Collider, modelMatrixPicoR3);

		// Pico 4
		glm::mat4 modelMatrixColliderPicoR4 = glm::mat4(modelMatrixPicoR4);
		AbstractModel::OBB PicoR4Collider;
		// Set the orientation of collider before doing the scale
		PicoR4Collider.u = glm::quat_cast(modelMatrixPicoR4);
		modelMatrixColliderPicoR4 = glm::scale(modelMatrixColliderPicoR4, glm::vec3(0.7f, 0.6f, 0.7f));
		modelMatrixColliderPicoR4 = glm::translate(modelMatrixColliderPicoR4, modelPicoR4.getObb().c);
		PicoR4Collider.c = glm::vec3(modelMatrixColliderPicoR4[3]);
		PicoR4Collider.e = modelPicoR4.getObb().e * glm::vec3(0.7f, 0.6f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR4", PicoR4Collider, modelMatrixPicoR4);

		// Pico 5
		glm::mat4 modelMatrixColliderPicoR5 = glm::mat4(modelMatrixPicoR5);
		AbstractModel::OBB PicoR5Collider;
		// Set the orientation of collider before doing the scale
		PicoR5Collider.u = glm::quat_cast(modelMatrixPicoR5);
		modelMatrixColliderPicoR5 = glm::scale(modelMatrixColliderPicoR5, glm::vec3(0.7f, 0.2f, 0.7f));
		modelMatrixColliderPicoR5 = glm::translate(modelMatrixColliderPicoR5, modelPicoR5.getObb().c);
		PicoR5Collider.c = glm::vec3(modelMatrixColliderPicoR5[3]);
		PicoR5Collider.e = modelPicoR5.getObb().e * glm::vec3(0.7f, 0.2f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR5", PicoR5Collider, modelMatrixPicoR5);

		// Pico 6
		glm::mat4 modelMatrixColliderPicoR6 = glm::mat4(modelMatrixPicoR6);
		AbstractModel::OBB PicoR6Collider;
		// Set the orientation of collider before doing the scale
		PicoR6Collider.u = glm::quat_cast(modelMatrixPicoR6);
		modelMatrixColliderPicoR6 = glm::scale(modelMatrixColliderPicoR6, glm::vec3(0.7f, 1.4f, 0.7f));
		modelMatrixColliderPicoR6 = glm::translate(modelMatrixColliderPicoR6, modelPicoR6.getObb().c);
		PicoR6Collider.c = glm::vec3(modelMatrixColliderPicoR6[3]);
		PicoR6Collider.e = modelPicoR6.getObb().e * glm::vec3(0.7f, 1.4f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR6", PicoR6Collider, modelMatrixPicoR6);

		// Pico 7
		glm::mat4 modelMatrixColliderPicoR7 = glm::mat4(modelMatrixPicoR7);
		AbstractModel::OBB PicoR7Collider;
		// Set the orientation of collider before doing the scale
		PicoR7Collider.u = glm::quat_cast(modelMatrixPicoR7);
		modelMatrixColliderPicoR7 = glm::scale(modelMatrixColliderPicoR7, glm::vec3(0.7f, 1.5f, 0.7f));
		modelMatrixColliderPicoR7 = glm::translate(modelMatrixColliderPicoR7, modelPicoR7.getObb().c);
		PicoR7Collider.c = glm::vec3(modelMatrixColliderPicoR7[3]);
		PicoR7Collider.e = modelPicoR7.getObb().e * glm::vec3(0.7f, 1.5f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR7", PicoR7Collider, modelMatrixPicoR7);

		// Pico 8
		glm::mat4 modelMatrixColliderPicoR8 = glm::mat4(modelMatrixPicoR8);
		AbstractModel::OBB PicoR8Collider;
		// Set the orientation of collider before doing the scale
		PicoR8Collider.u = glm::quat_cast(modelMatrixPicoR8);
		modelMatrixColliderPicoR8 = glm::scale(modelMatrixColliderPicoR8, glm::vec3(0.7f, 0.1f, 0.7f));
		modelMatrixColliderPicoR8 = glm::translate(modelMatrixColliderPicoR8, modelPicoR8.getObb().c);
		PicoR8Collider.c = glm::vec3(modelMatrixColliderPicoR8[3]);
		PicoR8Collider.e = modelPicoR8.getObb().e * glm::vec3(0.7f, 0.1f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR8", PicoR8Collider, modelMatrixPicoR8);

		// Pico 9
		glm::mat4 modelMatrixColliderPicoR9 = glm::mat4(modelMatrixPicoR9);
		AbstractModel::OBB PicoR9Collider;
		// Set the orientation of collider before doing the scale
		PicoR9Collider.u = glm::quat_cast(modelMatrixPicoR9);
		modelMatrixColliderPicoR9 = glm::scale(modelMatrixColliderPicoR9, glm::vec3(0.7f, 0.7f, 0.7f));
		modelMatrixColliderPicoR9 = glm::translate(modelMatrixColliderPicoR9, modelPicoR9.getObb().c);
		PicoR9Collider.c = glm::vec3(modelMatrixColliderPicoR9[3]);
		PicoR9Collider.e = modelPicoR9.getObb().e * glm::vec3(0.7f, 0.7f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR9", PicoR9Collider, modelMatrixPicoR9);

		// Pico 10
		glm::mat4 modelMatrixColliderPicoR10 = glm::mat4(modelMatrixPicoR10);
		AbstractModel::OBB PicoR10Collider;
		// Set the orientation of collider before doing the scale
		PicoR10Collider.u = glm::quat_cast(modelMatrixPicoR10);
		modelMatrixColliderPicoR10 = glm::scale(modelMatrixColliderPicoR10, glm::vec3(0.7f, 0.9f, 0.7f));
		modelMatrixColliderPicoR10 = glm::translate(modelMatrixColliderPicoR10, modelPicoR10.getObb().c);
		PicoR10Collider.c = glm::vec3(modelMatrixColliderPicoR10[3]);
		PicoR10Collider.e = modelPicoR10.getObb().e * glm::vec3(0.7f, 0.9f, 0.7f);
		addOrUpdateColliders(collidersOBB, "PicoR10", PicoR10Collider, modelMatrixPicoR10);

		//----------------Colliders Cactus------------------------
		// Cactus 1
		glm::mat4 modelMatrixColliderCactus = glm::mat4(modelMatrixCactus);
		AbstractModel::OBB CactusCollider;
		// Set the orientation of collider before doing the scale
		CactusCollider.u = glm::quat_cast(modelMatrixCactus);
		modelMatrixColliderCactus = glm::scale(modelMatrixColliderCactus, glm::vec3(1.2f, 1.5f, 1.2f));
		modelMatrixColliderCactus = glm::translate(modelMatrixColliderCactus, modelCactus.getObb().c);
		CactusCollider.c = glm::vec3(modelMatrixColliderCactus[3]);
		CactusCollider.e = modelCactus.getObb().e * glm::vec3(1.2f, 1.5f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus", CactusCollider, modelMatrixCactus);

		// Cactus 2
		glm::mat4 modelMatrixColliderCactus2 = glm::mat4(modelMatrixCactus2);
		AbstractModel::OBB Cactus2Collider;
		// Set the orientation of collider before doing the scale
		Cactus2Collider.u = glm::quat_cast(modelMatrixCactus2);
		modelMatrixColliderCactus2 = glm::scale(modelMatrixColliderCactus2, glm::vec3(1.2f, 1.1f, 1.2f));
		modelMatrixColliderCactus2 = glm::translate(modelMatrixColliderCactus2, modelCactus2.getObb().c);
		Cactus2Collider.c = glm::vec3(modelMatrixColliderCactus2[3]);
		Cactus2Collider.e = modelCactus2.getObb().e * glm::vec3(1.2f, 1.1f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus2", Cactus2Collider, modelMatrixCactus2);

		// Cactus 3
		glm::mat4 modelMatrixColliderCactus3 = glm::mat4(modelMatrixCactus3);
		AbstractModel::OBB Cactus3Collider;
		// Set the orientation of collider before doing the scale
		Cactus3Collider.u = glm::quat_cast(modelMatrixCactus3);
		modelMatrixColliderCactus3 = glm::scale(modelMatrixColliderCactus3, glm::vec3(1.2f, 2.0f, 1.2f));
		modelMatrixColliderCactus3 = glm::translate(modelMatrixColliderCactus3, modelCactus3.getObb().c);
		Cactus3Collider.c = glm::vec3(modelMatrixColliderCactus3[3]);
		Cactus3Collider.e = modelCactus3.getObb().e * glm::vec3(1.2f, 2.0f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus3", Cactus3Collider, modelMatrixCactus3);

		// Cactus 4
		glm::mat4 modelMatrixColliderCactus4 = glm::mat4(modelMatrixCactus4);
		AbstractModel::OBB Cactus4Collider;
		// Set the orientation of collider before doing the scale
		Cactus4Collider.u = glm::quat_cast(modelMatrixCactus4);
		modelMatrixColliderCactus4 = glm::scale(modelMatrixColliderCactus4, glm::vec3(1.2f, 0.6f, 1.2f));
		modelMatrixColliderCactus4 = glm::translate(modelMatrixColliderCactus4, modelCactus4.getObb().c);
		Cactus4Collider.c = glm::vec3(modelMatrixColliderCactus4[3]);
		Cactus4Collider.e = modelCactus4.getObb().e * glm::vec3(1.2f, 0.6f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus4", Cactus4Collider, modelMatrixCactus4);

		// Cactus 5
		glm::mat4 modelMatrixColliderCactus5 = glm::mat4(modelMatrixCactus5);
		AbstractModel::OBB Cactus5Collider;
		// Set the orientation of collider before doing the scale
		Cactus5Collider.u = glm::quat_cast(modelMatrixCactus5);
		modelMatrixColliderCactus5 = glm::scale(modelMatrixColliderCactus5, glm::vec3(1.2f, 0.6f, 1.2f));
		modelMatrixColliderCactus5 = glm::translate(modelMatrixColliderCactus5, modelCactus5.getObb().c);
		Cactus5Collider.c = glm::vec3(modelMatrixColliderCactus5[3]);
		Cactus5Collider.e = modelCactus5.getObb().e * glm::vec3(1.2f, 0.6f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus5", Cactus5Collider, modelMatrixCactus5);

		// Cactus 6
		glm::mat4 modelMatrixColliderCactus6 = glm::mat4(modelMatrixCactus6);
		AbstractModel::OBB Cactus6Collider;
		// Set the orientation of collider before doing the scale
		Cactus6Collider.u = glm::quat_cast(modelMatrixCactus6);
		modelMatrixColliderCactus6 = glm::scale(modelMatrixColliderCactus6, glm::vec3(1.2f, 2.0f, 1.2f));
		modelMatrixColliderCactus6 = glm::translate(modelMatrixColliderCactus6, modelCactus6.getObb().c);
		Cactus6Collider.c = glm::vec3(modelMatrixColliderCactus6[3]);
		Cactus6Collider.e = modelCactus6.getObb().e * glm::vec3(1.2f, 2.0f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus6", Cactus6Collider, modelMatrixCactus6);

		// Cactus 7
		glm::mat4 modelMatrixColliderCactus7 = glm::mat4(modelMatrixCactus7);
		AbstractModel::OBB Cactus7Collider;
		// Set the orientation of collider before doing the scale
		Cactus7Collider.u = glm::quat_cast(modelMatrixCactus7);
		modelMatrixColliderCactus7 = glm::scale(modelMatrixColliderCactus7, glm::vec3(1.2f, 1.5f, 1.2f));
		modelMatrixColliderCactus7 = glm::translate(modelMatrixColliderCactus7, modelCactus7.getObb().c);
		Cactus7Collider.c = glm::vec3(modelMatrixColliderCactus7[3]);
		Cactus7Collider.e = modelCactus7.getObb().e * glm::vec3(1.2f, 1.5f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus7", Cactus7Collider, modelMatrixCactus7);

		// Cactus 8
		glm::mat4 modelMatrixColliderCactus8 = glm::mat4(modelMatrixCactus8);
		AbstractModel::OBB Cactus8Collider;
		// Set the orientation of collider before doing the scale
		Cactus8Collider.u = glm::quat_cast(modelMatrixCactus8);
		modelMatrixColliderCactus8 = glm::scale(modelMatrixColliderCactus8, glm::vec3(1.2f, 1.0f, 1.2f));
		modelMatrixColliderCactus8 = glm::translate(modelMatrixColliderCactus8, modelCactus8.getObb().c);
		Cactus8Collider.c = glm::vec3(modelMatrixColliderCactus8[3]);
		Cactus8Collider.e = modelCactus8.getObb().e * glm::vec3(1.2f, 1.0f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus8", Cactus8Collider, modelMatrixCactus8);

		// Cactus 9
		glm::mat4 modelMatrixColliderCactus9 = glm::mat4(modelMatrixCactus9);
		AbstractModel::OBB Cactus9Collider;
		// Set the orientation of collider before doing the scale
		Cactus9Collider.u = glm::quat_cast(modelMatrixCactus9);
		modelMatrixColliderCactus9 = glm::scale(modelMatrixColliderCactus9, glm::vec3(1.2f, 1.5f, 1.2f));
		modelMatrixColliderCactus9 = glm::translate(modelMatrixColliderCactus9, modelCactus9.getObb().c);
		Cactus9Collider.c = glm::vec3(modelMatrixColliderCactus9[3]);
		Cactus9Collider.e = modelCactus9.getObb().e * glm::vec3(1.2f, 1.5f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus9", Cactus9Collider, modelMatrixCactus9);

		// Cactus 10
		glm::mat4 modelMatrixColliderCactus10 = glm::mat4(modelMatrixCactus10);
		AbstractModel::OBB Cactus10Collider;
		// Set the orientation of collider before doing the scale
		Cactus10Collider.u = glm::quat_cast(modelMatrixCactus10);
		modelMatrixColliderCactus10 = glm::scale(modelMatrixColliderCactus10, glm::vec3(1.2f, 1.2f, 1.2f));
		modelMatrixColliderCactus10 = glm::translate(modelMatrixColliderCactus10, modelCactus10.getObb().c);
		Cactus10Collider.c = glm::vec3(modelMatrixColliderCactus10[3]);
		Cactus10Collider.e = modelCactus10.getObb().e * glm::vec3(1.2f, 1.2f, 1.2f);
		addOrUpdateColliders(collidersOBB, "Cactus10", Cactus10Collider, modelMatrixCactus10);

		//------------------Collider de Bird.------------------------------
		AbstractModel::OBB birdCollider;
		glm::mat4 modelmatrixColliderBird = glm::mat4(modelMatrixBird);
		modelmatrixColliderBird = glm::rotate(modelmatrixColliderBird,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		//Set the orientation of collider before doing the scale.
		birdCollider.u = glm::quat_cast(modelmatrixColliderBird);
		modelmatrixColliderBird = glm::scale(modelmatrixColliderBird, glm::vec3(0.03f, 0.03f, 0.03f));
		modelmatrixColliderBird = glm::translate(modelmatrixColliderBird,
				glm::vec3(birdModelAnimate.getObb().c.x,
						birdModelAnimate.getObb().c.y,
						birdModelAnimate.getObb().c.z));
		birdCollider.e = birdModelAnimate.getObb().e * glm::vec3(0.03f, 0.03f, 0.03f) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		birdCollider.c = glm::vec3(modelmatrixColliderBird[3]);
		addOrUpdateColliders(collidersOBB, "bird", birdCollider, modelMatrixBird);

		
		//****************************************** */
		//************Render de colliders.
		//*************************************** */
		/*for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
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
		//modelText->render("Texto en OpenGL", -1, 0);

		// Prueba de colisiones.
		for (auto it = collidersOBB.begin(); it != collidersOBB.end(); it++) {
			for (auto jt = collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt && testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;

					if (colisionesActuales.find(colisionID) == colisionesActuales.end() && colisionesActuales.find(colisionIDInversa) == colisionesActuales.end()) {
						std::cout << "Nueva colisión entre " << it->first << " y " << jt->first << std::endl;
						colisiones++;
						colisionesActuales.insert(colisionID);
						colisionesActuales.insert(colisionIDInversa);
					}
				} else {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;
					colisionesActuales.erase(colisionID);
					colisionesActuales.erase(colisionIDInversa);
				}
			}
		}

		for (auto it = collidersSBB.begin(); it != collidersSBB.end(); it++) {
			for (auto jt = collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt && testSphereSphereIntersection(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;

					if (colisionesActuales.find(colisionID) == colisionesActuales.end() && colisionesActuales.find(colisionIDInversa) == colisionesActuales.end()) {
						std::cout << "Nueva colisión entre " << it->first << " y " << jt->first << std::endl;
						colisiones++;
						colisionesActuales.insert(colisionID);
						colisionesActuales.insert(colisionIDInversa);
					}
				} else {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;
					colisionesActuales.erase(colisionID);
					colisionesActuales.erase(colisionIDInversa);
				}
			}
		}

		for (auto it = collidersSBB.begin(); it != collidersSBB.end(); it++) {
			for (auto jt = collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second), std::get<0>(jt->second))) {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;

					if (colisionesActuales.find(colisionID) == colisionesActuales.end() && colisionesActuales.find(colisionIDInversa) == colisionesActuales.end()) {
						std::cout << "Nueva colisión entre " << it->first << " y " << jt->first << std::endl;
						colisiones++;
						colisionesActuales.insert(colisionID);
						colisionesActuales.insert(colisionIDInversa);
					}
				} else {
					std::string colisionID = it->first + "-" + jt->first;
					std::string colisionIDInversa = jt->first + "-" + it->first;
					colisionesActuales.erase(colisionID);
					colisionesActuales.erase(colisionIDInversa);
				}
			}
		}

		// Cambiar la textura según el número de colisiones
		if (colisiones == 1) {
			textureActivaID = textureScreen2ID; // 2 vidas
		} else if (colisiones == 2) {
			textureActivaID = textureScreen3ID; // 1 vida
		} else if (colisiones >= 3) {
			textureActivaID = textureInit2ID; // Game over
			iniciaPartida = false; // Detener el movimiento del bird
		}

		// Render de la imagen de fondo
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(view));
		shaderTexture.setMatrix4("model", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureActivaID);
		shaderTexture.setInt("outTexture", 0);
		boxIntro.render();
		glDisable(GL_BLEND);

		glfwSwapBuffers(window);

		//Sound.
		//Listener for the third person camera.
		listenerPos[0] = modelMatrixBird[3].x;
		listenerPos[1] = modelMatrixBird[3].y;
		listenerPos[2] = modelMatrixBird[3].z;
		alListenerfv(AL_POSITION, listenerPos);
		glm::vec3 upModel = glm::normalize(modelMatrixBird[1]);
  		glm::vec3 frontModel = glm::normalize(modelMatrixBird[2]);
		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;
		alListenerfv(AL_ORIENTATION, listenerOri);
		for(unsigned int i = 0; i < sourcesPlay.size(); i++){
			if(sourcesPlay[i]){
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
		
	}
}

int main(int argc, char **argv) {
	init(1024, 768, "Proyecto final: Sky Hopper.", false);
	applicationLoop();
	destroy();
	return 1;
}
