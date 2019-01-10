#include "Game.h"
#include "Player.h"
#include "Scene/Camera.h"
#include "Scene/Skybox.h"
#include "Scene/StaticModel.h"
#include "Scene/PointLight.h"
#include "Scene/SpotLight.h"
#include "Scene/DirectionalLight.h"
#include "Scene/CameraController.h"

ST_NS_BEGIN

Camera *cam;
Player *player;

Game::Game(string title, int width, int height, bool fullscreen, bool resizable):
	Window(title, width, height, fullscreen, resizable), _scene(width, height)
{
	_scene.setClearColor(Color(0.4, 0.4, 0.5));
	_scene.setAmbientColor(Color(0.2, 0.2, 0.2));
//	_scene.setAmbientColor(Color::WHITE);

	Skybox *sb = new Skybox("Assets/Textures/Skyboxes/cottoncandy_", ".tga");
//	Skybox *sb = new Skybox("Assets/Textures/Skyboxes/a_", ".png");
	_scene.addChild(sb);

	createRoom();
	createLights();

	StaticModel *box = new StaticModel("Assets/Models/cube.obj");
	box->getMeshes()[0].setMaterial(Material("Assets/Materials/Bricks.xml"));
	box->getTransform().setScale(vec3(5.0));
	box->getTransform().setPosition(vec3(0.0, 5.0, -200.0));
	box->getTransform().rotateLocalY(radians(60.0));
	_scene.addChild(box);

//	player = new Player("Assets/Models/cube.obj");
//	player->setName("Player");
////	player->getModel().getMeshes()[0].getMaterial()->setDiffuseTexture(Texture::load("Assets/Textures/container2.png"));
////	player->getModel().getMeshes()[0].getMaterial()->setSpecularTexture(Texture::load("Assets/Textures/container2_specular.png"));
//	player->getTransform().setPosition(vec3(100, 200, -50));
//	_scene.addChild(player);

	cam = new Camera(60, width/(float)height, 0.01, 10000);
	cam->setName("Main Camera");
	cam->getTransform().setPosition(vec3(0.0, 90.0, -30.0));
	cam->getTransform().rotateLocalX(radians(20.f));
	cam->addComponent(new CameraController());
	_scene.addChild(cam);
	_scene.setMainCamera(cam);
}

void Game::createRoom()
{
	// TODO: make material immutable
	Material wallMat("Assets/Materials/Bricks.xml");
//	wallMat->setSpecularIntensity(0.8);
	wallMat.setBumpTexture(Texture::load("Assets/Textures/Farmhouse_Texture_Bump_Map.jpg"));

	vec3 scale = vec3(250.0, 1.0, 250.0);

	Node *room = new Node();
	_scene.addChild(room);

	// Ground
	StaticModel *ground = new StaticModel("Assets/Models/cube_tiled.obj");
	ground->getMeshes()[0].setMaterial(wallMat);
	ground->getTransform().setScale(scale);
	room->addChild(ground);

	// Walls
	for (int i = 2; i < 6 && 0; i++)
	{
		StaticModel *wall = new StaticModel("Assets/Models/cube_tiled.obj");
		wall->getMeshes()[0].setMaterial(wallMat);
		wall->getTransform().setScale(scale);
		if ((i%4)/2)
		{
			wall->getTransform().rotateLocalX(radians(90.0));
			wall->getTransform().move(vec3(0.0, -100.0, 250*(i%2? 1: -1)));
		}
		else
		{
			wall->getTransform().rotateLocalZ(radians(90.0));
			wall->getTransform().move(vec3(250*(i%2? 1: -1), -100.0, 0.0));
		}
		room->addChild(wall);
	}

	// House
	StaticModel *house = new StaticModel("Assets/Models/Farmhouse.obj");
	house->setName(string("Farm House"));

	Material houseMat = house->getMeshes()[0].getMaterial();
	houseMat.setSpecularIntensity(0.3);
	houseMat.setBumpTexture(Texture::load("Assets/Textures/Farmhouse_Texture_Bump_Map.jpg"));
	house->getMeshes()[0].setMaterial(houseMat);

//	house->getTransform().setPosition(vec3(40.0 * i + 40.0, 1.0, 0.0));
//	house->getTransform().rotateLocalY(radians(i/10.0 * 120.0 - 60));
	house->getTransform().setScale(vec3(3.0));
	room->addChild(house);
}

float getRand(float min, float max)
{
	float range = max-min;
	return (rand()/(float)INT_MAX * range + min);
}

void Game::createLights()
{
	DirectionalLight *light = new DirectionalLight(Color(0.5, 0.5, 0.5));
//	light->getTransform().setPosition(vec3(50, 50, 0));
	light->getTransform().rotateLocalY(radians(20.0));
//	light->getTransform().rotateLocalZ(radians(-50.0));
	light->getTransform().rotateLocalX(radians(50.0));
	_scene.addChild(light);

//	return;

//	srand(2);
	srand(5);

	for (int i = 0; i < 3; i++)
	{
		Node *l = new Node();
//		l->getTransform().setPosition(vec3(getRand(-240, 240), getRand(10, 40), getRand(-240, 240)));
		l->getTransform().setPosition(vec3(getRand(-100, 100), getRand(10, 40), getRand(-100, 100)));

		Color c = Color::fromHSL(getRand(0.05, 0.85), 0.8, 0.3);
		PointLight *light = new PointLight(getRand(150, 250), c);
		l->addChild(light);

		Material mat(Color::BLACK, 1.0, c);

		StaticModel *lightSource = new StaticModel("Assets/Models/cube.obj");
		lightSource->getMeshes()[0].setMaterial(mat);
		lightSource->getTransform().setScale(vec3(4.0));
		l->addChild(lightSource);

		_scene.addChild(l);
	}

//	PointLight *flight = new PointLight(100, Color(1.0, 1.0, 1.0));
//	SpotLight *flight = new SpotLight(200, 0.98, Color(1.0, 1.0, 1.0));
//	cam->addChild(flight);
//	_scene.addChild(spotLight);
}

void Game::render(float deltaTime)
{
	static float time = 0;
	time += deltaTime;

	static float second = 0;
	static int frames = 0;

	second += deltaTime;
	frames++;

	if (second >= 1.0)
	{
		cout<<"FPS: "<<(frames/second)<<endl;
		second -= 1;
		frames = 0;
	}

	_scene.update(deltaTime);
	_scene.render();
}

void Game::resized(int width, int height)
{
	_scene.resized(width, height);
}

bool Game::keyDown(SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
	{
		quit();
		return true;
	}
	else if (key == SDLK_f)
	{
		_scene.getRenderManager().setFXAA(!_scene.getRenderManager().getFXAA());
	}
	else if (key == SDLK_m)
	{
		_scene.getRenderManager().setMSAA(_scene.getRenderManager().getMSAA()? 0: 8);
	}
	return false;
}



ST_NS_END
