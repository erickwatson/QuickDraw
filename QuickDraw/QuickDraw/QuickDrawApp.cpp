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
	m_BG_Dark = new aie::Texture("../images/Quickdraw_BG_Dark.png");
	m_BG_Sunset = new aie::Texture("../images/Quickdraw_BG_Sunset.png");

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
	m_Game_Menu_Selection = new aie::Texture("../images/Quickdraw_Menu_Selection.png");

	// Player First State
	m_Player_Gun = new aie::Texture("../images/Quickdraw_Player_Gun.png");
	m_Player = new aie::Texture("../images/Quickdraw_Player.png");
	m_Player_Hat = new aie::Texture("../images/Quickdraw_Player_Hat.png");
	m_Player_Hat_Dead = new aie::Texture("../images/Quickdraw_Player_Hat_Dead.png");

	//Titles
	m_Border = new aie::Texture("../images/Quickdraw_Border.png");
	m_Game_Menu = new aie::Texture("../images/Quickdraw_Game_Menu.png");
	m_Instructions = new aie::Texture("../images/Quickdraw_Game_Instructions.png");
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
			m_bgState = BGState::Off;
			m_playerState = CharacterState::Null;
			m_enemyState = CharacterState::Null;
			m_Selection = Play;
			m_gameState = Menu1;
			break;
		}
		case Menu1:
		{
		
			// Trying to make a menu
			if (input->wasKeyPressed(aie::INPUT_KEY_F1))
			{
				m_gameState = Instructions;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			{
				m_Selection = Instructions;
				m_gameState = Menu2;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Ready;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			{
				m_Selection = Exit;
				m_gameState = Menu3;

			}
			break;
		}
		case Menu2:
		{

			// Trying to make a menu
			if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			{
				m_Selection = Exit;
				m_gameState = Menu3;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Instructions;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			{
				m_gameState = Menu1;
				m_Selection = Play;

			}
			break;
		}
		case Menu3:
		{

			// Trying to make a menu
			if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			{
				m_Selection = Play;
				m_gameState = Menu1;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Exit;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			{
				m_gameState = Menu2;
				m_Selection = Instructions;

			}
			break;
		}
		case Play:
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Ready;

			}
			break;
		}
		case Instructions:
		{
			m_Selection = GameState::Clear;
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Menu1;
				m_Selection = Play;
			}
			break;
		}
		case Ready:
		{
			int i;
			m_Selection = GameState::Clear;
			m_bgState = BGState::On;
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;



			if (m_waitTimer > 0)
			{
				if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
				{
					m_gameState = Lose;
				}
				m_waitTimer -= deltaTime;


				if (m_waitTimer <= 0)
				{
					m_gameState = Draw;
				}
				// Trying to check if player prematurely pressed Space
				/*else if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
				{

					m_gameState = Lose;

					break;
				}*/
				break;

			}
			if ((m_waitTimer < 0) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				m_waitTimer = rand() % 4 + 1;
				m_enemyShoot = (rand() % 1000 * 0.05) / 1000 + 0.23;
				// Between: 0.21 - 0.25
				cout << "enemyshoot: " << m_enemyShoot << endl;
				cout << "Wait time: " << m_waitTimer << endl;

			}

			break;
		}
		case Draw:
		{
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;
			m_drawTimer += deltaTime;



			if ((m_drawTimer < m_enemyShoot) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				// Checking if player drew first
				// Change states to win/lose accordingly
				m_flashState = On;
				cout << "Reaction time: " << m_drawTimer << endl;
				m_gameState = Win;

				break;
			}

			else if (m_drawTimer > m_enemyShoot)
			{
				m_flashState = On;
				
				m_gameState = Lose;

				break;
			}

			break;
		}
		case Win:
		{
			m_flashState = Off;
			m_enemyState = Dead;
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;

			}
			break;
		}
		case Lose :
		{
			m_flashState = Off;
			if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				//m_drawTimer += deltaTime;
				cout << "Reaction time: " << m_drawTimer << endl;
				break;
			}

			m_playerState = Dead;
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;
				
			}
			break;
		}
		case Exit:
		{
			quit();
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
	


	switch (m_bgState)
	{
	case On:
		m_2dRenderer->drawSprite(m_Building_Left, 400, 300, 0, 0, 0, 11);
		m_2dRenderer->drawSprite(m_BG_Sunset, 400, 300, 0, 0, 0, 20);
		break;
	case Off:

		break;
	}

	switch (m_flashState)
	{
	case On:
		m_2dRenderer->drawSprite(m_Flash, 400, 300, 0, 0, 0, 3);
		break;
	case Off:
		break;
	}

	switch (m_Selection)
	{
	case Clear:
		break;
	case Play:
		m_2dRenderer->drawSprite(m_Game_Menu_Selection, 200, 350, 0, 0, 0, 5);
		break;
	case Instructions:
		m_2dRenderer->drawSprite(m_Game_Menu_Selection, 200, 290, 0, 0, 0, 5);
		break;
	case Exit:
		m_2dRenderer->drawSprite(m_Game_Menu_Selection, 200, 210, 0, 0, 0, 5);
		break;
	}

	//Titles
	switch (m_gameState) {
	case Menu1:
	case Menu2:
	case Menu3:
		m_2dRenderer->drawSprite(m_Game_Menu, 400, 300, 0, 0, 0, 5);
		
		break;
	case Play:

	case Instructions:
		m_2dRenderer->drawSprite(m_Instructions, 400, 300, 0, 0, 0, 5);
		break;
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
	case Exit:
		break;
	}

	//Player
	
	switch (m_playerState) {
	case Null:
		break;
	case Dead:
		m_2dRenderer->drawSprite(m_Player, 400, 300, 0, 0, 0, 9);
		m_2dRenderer->drawSprite(m_Player_Hat_Dead, 400, 300, 0, 0, 0, 7);
		m_2dRenderer->drawSprite(m_Player_Gun, 400, 300, 0, 0, 0, 10);
		break;
	case Idle:
		m_2dRenderer->drawSprite(m_Player, 400, 300, 0, 0, 0, 9);
		m_2dRenderer->drawSprite(m_Player_Hat, 400, 300, 0, 0, 0, 8);
		break;
	case Shooting:
		m_2dRenderer->drawSprite(m_Player, 400, 300, 0, 0, 0, 9);
		m_2dRenderer->drawSprite(m_Player_Hat, 400, 300, 0, 0, 0, 8);
		m_2dRenderer->drawSprite(m_Player_Gun, 400, 300, 0, 0, 0, 10);
		break;
	}

	//Extra
	
	
	//Enemy
	switch (m_enemyState) {
	case Null:
		break;
	case Dead:
		m_2dRenderer->drawSprite(m_Enemy_Hat_Dead, 400, 300, 0, 0, 0, 12);
		m_2dRenderer->drawSprite(m_Enemy_Body_Draw, 400, 300, 0, 0, 0, 14);
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Hat_Dead, 400, 300, 0, 0, 0, 16);
		m_2dRenderer->drawSprite(m_Enemy_Shadow_Draw, 400, 300, 0, 0, 0, 6);
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
	m_2dRenderer->drawSprite(m_BG_Dark, 400, 300, 0, 0, 0,					21);

	// draw your stuff here! m_font;
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Testing Consolas Font", 0, 0, 11);
	m_2dRenderer->drawText(m_font_rope, "Testing Rope MF Font", 0, 0, 12);
	// done drawing sprites
	m_2dRenderer->end();
}