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
	//
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

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

	// draw your stuff here!
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}