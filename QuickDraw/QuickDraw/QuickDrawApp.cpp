#include "QuickDrawApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

QuickDrawApp::QuickDrawApp() {

}

QuickDrawApp::~QuickDrawApp() {

}

bool QuickDrawApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_font_rope = new aie::Font("./font/Rope_MF.ttf", 32);
	//
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	m_BG = new aie::Texture("../images/Quickdraw_BG.jpg");
	m_Enemy = new aie::Texture("../images/Quickdraw_Enemy.png");
	m_Building_Left = new aie::Texture("../images/Quickdraw_Building_Left.png");
	m_Player_Gun = new aie::Texture("../images/Quickdraw_Player_Gun.png");
	m_Player = new aie::Texture("../images/Quickdraw_Player.png");
	m_Player_Hat = new aie::Texture("../images/Quickdraw_Player_Hat.png");
	m_Border = new aie::Texture("../images/Quickdraw_Border.png");
	m_Title = new aie::Texture("../images/Quickdraw_Title.png");


	return true;
}

void QuickDrawApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void QuickDrawApp::update(float deltaTime) {

	m_timer += deltaTime;
	
	// input example
	aie::Input* input = aie::Input::getInstance();
	
	// DRAW!
	//if (input->isKeyDown(aie::INPUT_KEY_SPACE))

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void QuickDrawApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->drawSprite(m_Title, 400, 300, 0, 0, 0, 0);
	m_2dRenderer->drawSprite(m_Border, 400, 300, 0, 0, 0, 1);
	m_2dRenderer->drawSprite(m_Player_Hat, 400, 300, 0, 0, 0, 2);
	m_2dRenderer->drawSprite(m_Player, 400, 300, 0, 0, 0, 3);
	m_2dRenderer->drawSprite(m_Player_Gun, 400, 300, 0, 0, 0, 4);
	m_2dRenderer->drawSprite(m_Building_Left, 400, 300, 0, 0, 0, 5);
	m_2dRenderer->drawSprite(m_Enemy, 400, 300, 0, 0, 0, 6);
	m_2dRenderer->drawSprite(m_BG, 400, 300, 0, 0, 0, 7);
	// draw your stuff here! m_font;
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}