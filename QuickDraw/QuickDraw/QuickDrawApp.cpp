#include "QuickDrawApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace std;

QuickDrawApp::QuickDrawApp() {

}

QuickDrawApp::~QuickDrawApp() {

}

bool QuickDrawApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 80);
	m_font_rope = new aie::Font("./font/Rope_MF.ttf", 80);
	//
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_playerState = Idle;
	m_enemyState = Idle;

	// Load in Textures

	// Background
	m_BG = new aie::Texture("../images/Quickdraw_BG.jpg");

	// Enemy First State
	m_Enemy_Body = new aie::Texture("../images/Quickdraw_Enemy_Body.png");
	m_Enemy_Shadow = new aie::Texture("../images/Quickdraw_Enemy_Shadow.png");
	m_Enemy_Shadow_Hat = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Hat.png");

	// Hats
	m_Enemy_Hat = new aie::Texture("../images/Quickdraw_Enemy_Hat.png");
	m_Enemy_Hat_Dead = new aie::Texture("../images/Quickdraw_Enemy_Hat_Dead.png");
	m_Enemy_Shadow_Hat_Dead = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Hat_Dead.png");

	// Draw
	m_Enemy_Body_Draw = new aie::Texture("../images/Quickdraw_Enemy_Body_Draw.png");
	m_Enemy_Shadow_Draw = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Draw.png");
	
	// Extra stuff
	m_Building_Left = new aie::Texture("../images/Quickdraw_Building_Left.png");

	// Player First State
	m_Player_Gun = new aie::Texture("../images/Quickdraw_Player_Gun.png");
	m_Player = new aie::Texture("../images/Quickdraw_Player.png");
	m_Player_Hat = new aie::Texture("../images/Quickdraw_Player_Hat.png");
	m_Player_Hat_Dead = new aie::Texture("../images/Quickdraw_Player_Hat_Dead.png");

	//Titles
	m_Border = new aie::Texture("../images/Quickdraw_Border.png");
	m_Title = new aie::Texture("../images/Quickdraw_Title.png");
	m_Flash = new aie::Texture("../images/Quickdraw_Flash.png");
	m_Game_Ready = new aie::Texture("../images/Quickdraw_Game_Ready.png");
	m_Game_Draw = new aie::Texture("../images/Quickdraw_Game_Draw.png");
	m_Game_Win = new aie::Texture("../images/Quickdraw_Game_Win.png");
	m_Game_Lose = new aie::Texture("../images/Quickdraw_Game_Lose.png");

	// Load in sounds
	//m_Sound_BG = new sound??("../sounds/Quickdraw_Sound_BG.wav");
	//m_Sound_Gunshot_Player_Left = new sound??("../sounds/Quickdraw_Sound_Gunshot_Player_Left.wav");
	//m_Sound_Gunshot_Enemy_Right = new sound??("../sounds/Quickdraw_Sound_Gunshot_Enemy_Right.wav");

	m_gameState = Restart;
	srand((unsigned int)time(NULL));
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
	
	switch (m_gameState)
	{
		case Restart:
		{
			m_drawTimer = 0;
			m_waitTimer = -1;
			m_gameState = Ready;
			break;
		}
		case Ready:
		{
			int i;
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;

			if ((m_waitTimer < 0) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				m_waitTimer = rand() % 4 + 1;
				cout << "Wait time: " << m_waitTimer << endl;

			}

			if (m_waitTimer > 0)
			{
				m_waitTimer -= deltaTime;

				if (m_waitTimer <= 0)
				{
					m_gameState = Draw;
				}
			}


			break;
		}
		case Draw:
		{
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;
			m_drawTimer += deltaTime;



			if ((m_drawTimer < 1) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				// Checking if player drew first
				// Change states to win/lose accordingly
				cout << "Reaction time: " << m_drawTimer << endl;
				m_gameState = Win;

				break;
			}
			else if (m_drawTimer > 1)
			{
				m_gameState = Lose;

				break;
			}

			break;
		}
		case Win:
		case Lose :
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;
				
			}
			break;
		}

	}

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
	m_2dRenderer->drawSprite(m_Title, 400, 300, 0, 0, 0,				1);
	m_2dRenderer->drawSprite(m_Border, 400, 300, 0, 0, 0,				2);
	//m_2dRenderer->drawSprite(m_Flash, 400, 300, 0, 0, 0,				3);

	//Titles
	switch (m_gameState) {
	case Ready:
		m_2dRenderer->drawSprite(m_Game_Ready, 400, 300, 0, 0, 0, 5);
		break;
	case Draw:
		m_2dRenderer->drawSprite(m_Game_Draw, 400, 300, 0, 0, 0, 5);
		break;
	case Win:
		m_2dRenderer->drawSprite(m_Game_Win, 400, 300, 0, 0, 0, 6);
		break;
	case Lose:
		m_2dRenderer->drawSprite(m_Game_Lose, 400, 300, 0, 0, 0, 7);
		break;
	}

	//Player
	m_2dRenderer->drawSprite(m_Player, 400, 300, 0, 0, 0,				9);
	switch (m_playerState) {
	case Dead:
		m_2dRenderer->drawSprite(m_Player_Hat_Dead, 400, 300, 0, 0, 0, 7);
		break;
	case Idle:
		m_2dRenderer->drawSprite(m_Player_Hat, 400, 300, 0, 0, 0, 8);
		break;
	case Shooting:
		m_2dRenderer->drawSprite(m_Player_Hat, 400, 300, 0, 0, 0, 8);
		m_2dRenderer->drawSprite(m_Player_Gun, 400, 300, 0, 0, 0, 10);
		break;
	}

	//Extra
	m_2dRenderer->drawSprite(m_Building_Left, 400, 300, 0, 0, 0,		11);
	
	//Enemy
	switch (m_playerState) {
	case Dead:
		m_2dRenderer->drawSprite(m_Enemy_Hat_Dead, 400, 300, 0, 0, 0, 12);
		m_2dRenderer->drawSprite(m_Enemy_Body_Draw, 400, 300, 0, 0, 0, 14);
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Hat_Dead, 400, 300, 0, 0, 0, 16);
		break;
	case Idle:
		m_2dRenderer->drawSprite(m_Enemy_Hat, 400, 300, 0, 0, 0, 13);
		m_2dRenderer->drawSprite(m_Enemy_Body, 400, 300, 0, 0, 0, 15);
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Hat, 400, 300, 0, 0, 0, 17);
		m_2dRenderer->drawSprite(m_Enemy_Shadow, 400, 300, 0, 0, 0, 19);
		break;
	case Shooting:		
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Hat, 400, 300, 0, 0, 0, 17);
		m_2dRenderer->drawSprite(m_Enemy_Body_Draw, 400, 300, 0, 0, 0, 14);
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Draw, 400, 300, 0, 0, 0, 18);
		break;

	}

	//Background
	m_2dRenderer->drawSprite(m_BG, 400, 300, 0, 0, 0,					20);

	// draw your stuff here! m_font;
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Testing Consolas Font", 0, 0, 11);
	m_2dRenderer->drawText(m_font_rope, "Testing Rope MF Font", 0, 0, 12);
	// done drawing sprites
	m_2dRenderer->end();
}