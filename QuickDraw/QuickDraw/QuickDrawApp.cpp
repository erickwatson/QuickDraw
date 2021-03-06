#include "QuickDrawApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace std;
// draw a message image saying "Ready"  or "Draw"
aie::Texture* message = nullptr;

QuickDrawApp::QuickDrawApp() {

}

QuickDrawApp::~QuickDrawApp() {

}

// Title Textures. Includes Ready states, Win/Lose states and Gun
void QuickDrawApp::TitleTextures()
{
	m_Border = new aie::Texture("../images/Quickdraw_Border.png");
	//m_Game_Menu = new aie::Texture("../images/Quickdraw_Game_Menu.png");
	m_Instructions = new aie::Texture("../images/Quickdraw_Game_Instructions.png");
	m_Title = new aie::Texture("../images/Quickdraw_Title.png");
	m_Flash = new aie::Texture("../images/Quickdraw_Flash.png");
	m_Game_SquareUp = new aie::Texture("../images/Quickdraw_Game_Square_Up.png");
	m_Game_Ready = new aie::Texture("../images/Quickdraw_Game_Ready.png");
	m_Game_Draw = new aie::Texture("../images/Quickdraw_Game_Draw.png");
	m_Game_Win = new aie::Texture("../images/Quickdraw_Game_Win.png");
	m_Game_Lose = new aie::Texture("../images/Quickdraw_Game_Lose.png");
	m_Game_Enter_Instruction = new aie::Texture("../images/Quickdraw_Game_Enter_Instruction.png");
	m_Game_Menu_Selection = new aie::Texture("../images/Quickdraw_Menu_Selection.png");
}

// Character Textures. Includes Player, Enemy and Hats
void QuickDrawApp::CharacterTextures()
{
	// Player First State
	m_Player_Gun = new aie::Texture("../images/Quickdraw_Player_Gun.png");
	m_Player = new aie::Texture("../images/Quickdraw_Player.png");
	m_Player_Hat = new aie::Texture("../images/Quickdraw_Player_Hat.png");
	m_Player_Hat_Dead = new aie::Texture("../images/Quickdraw_Player_Hat_Dead.png");

	// Enemy First State
	m_Enemy_Body = new aie::Texture("../images/Quickdraw_Enemy_Body.png");
	m_Enemy_Shadow = new aie::Texture("../images/Quickdraw_Enemy_Shadow.png");
	m_Enemy_Shadow_Hat = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Hat.png");

	// Hats
	m_Enemy_Hat = new aie::Texture("../images/Quickdraw_Enemy_Hat.png");
	m_Enemy_Hat_Dead = new aie::Texture("../images/Quickdraw_Enemy_Hat_Dead.png");
	m_Enemy_Shadow_Hat_Dead = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Hat_Dead.png");
}


bool QuickDrawApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../fonts/consolas.ttf", 80);
	m_font_rope = new aie::Font("../fonts/Rope_MF.ttf", 80);
	
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

	// Characters
	CharacterTextures();

	// Draw
	m_Enemy_Body_Draw = new aie::Texture("../images/Quickdraw_Enemy_Body_Draw.png");
	m_Enemy_Shadow_Draw = new aie::Texture("../images/Quickdraw_Enemy_Shadow_Draw.png");
	
	// Extra stuff
	m_Building_Left = new aie::Texture("../images/Quickdraw_Building_Left.png");
	
	// Titles
	TitleTextures();

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
	
	// Input example
	aie::Input* input = aie::Input::getInstance();
	
	switch (m_gameState)
	{
		case Restart:
		{
			m_flashState = Off;
			m_drawTimer = 0;
			m_drawTimer2 = 0;
			m_waitTimer = -1;
			m_bgState = BGState::Off;
			m_playerState = CharacterState::Null;
			m_enemyState = CharacterState::Null;
			m_Selection = Play;
			m_gameState = Menu1;
			break;
		}



		case Menu1:
		case Menu2:
		case Menu3:
		{
		
			// Trying to make a menu
			if (input->wasKeyPressed(aie::INPUT_KEY_F1))
			{
				m_gameState = Instructions;
			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			{
				// move on to the next item
				currentMenuItem = (currentMenuItem + 1) % menuItems;
				m_gameState = menu[currentMenuItem].state;
			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = menu[currentMenuItem].nextState;

			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			{
				// move on to the previous item
				currentMenuItem = (menuItems + currentMenuItem - 1) % menuItems;
				m_gameState = menu[currentMenuItem].state;
			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_F3))
			{
				m_gameState = SquareUp2;

			}
			break;
		}

		case Instructions:
		{
			m_Selection = GameState::Clear;
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Menu1;
				m_Selection = GameState::Play;
			}
			break;
		}
		case SquareUp:
		{
			m_Selection = GameState::Clear;
			m_readyState = GameState::SquareUp;
			m_bgState = BGState::On;
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;

			if ((m_waitTimer < 0) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				m_waitTimer = rand() % 4 + 1;
				m_enemyShoot = (rand() % 1000 * 0.05) / 1000 + 0.23;
				// Between: 0.21 - 0.25
				cout << "enemyshoot: " << m_enemyShoot << endl;
				cout << "Wait time: " << m_waitTimer << endl;
				m_gameState = Ready;

			}
			/*if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				m_gameState = Ready;

			}*/
			break;
			break;
		}
		case SquareUp2:
		{
			m_Selection = GameState::Clear;
			m_readyState = GameState::SquareUp;
			m_bgState = BGState::On;
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;

			if ((m_waitTimer < 0) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				m_waitTimer = rand() % 4 + 1;
				//m_enemyShoot = (rand() % 1000 * 0.05) / 1000 + 0.23;
				// Between: 0.21 - 0.25
				//cout << "enemyshoot: " << m_enemyShoot << endl;
				cout << "Wait time: " << m_waitTimer << endl;
				m_gameState = Ready2;

			}
						
			break;
		}
		case Ready:
		{
			int i;
			m_readyState = Ready;

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


			break;
		}
		case Ready2:
		{
			int i;
			m_readyState = Ready;

			if (m_waitTimer > 0)
			{
				if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_CONTROL))
				{
					m_gameState = Win2;
				}
				else if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT_CONTROL))
				{
					m_gameState = Win1;
				}
				m_waitTimer -= deltaTime;


				if (m_waitTimer <= 0)
				{
					m_gameState = Draw2;
				}

				break;

			}


			break;
		}
		case Draw:
		{
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;
			m_readyState = GameState::Clear;
			m_drawTimer += deltaTime;



			if ((m_drawTimer < m_enemyShoot) && input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			{
				// Checking if player drew first
				// Change states to win/lose accordingly
				m_flashState = On;
				cout << "Reaction time: " << m_drawTimer << endl;

				m_enemyState = Dead;
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
		case Draw2:
		{
			m_playerState = CharacterState::Idle;
			m_enemyState = CharacterState::Idle;
			m_readyState = GameState::Clear;
			m_drawTimer += deltaTime;
			m_drawTimer2 += deltaTime;



			if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_CONTROL))
			{
				// Checking if player drew first
				// Change states to win/lose accordingly
				m_flashState = On;
				cout << "Player 1 reaction: " << m_drawTimer << endl;
				m_gameState = Win1;

				//break;
			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT_CONTROL))
			{
				// Checking if player drew first
				// Change states to win/lose accordingly
				m_flashState = On;
				cout << "Player 2 reaction: " << m_drawTimer2 << endl;
				m_gameState = Win2;

				//break;
			}

			//else if (m_drawTimer > m_enemyShoot)
			//{
			//	m_flashState = On;

			//	m_gameState = Lose;

			//	break;
			//}

			break;
		}
		case Win:
		{
			m_flashState = Off;
			

			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;

			}
			break;
		}
		case Win1:
		{
			m_flashState = Off;
			m_playerState = Dead;
			m_drawTimer2 += deltaTime;
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;

			}

	
			else if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT_CONTROL))
			{
				//m_drawTimer += deltaTime;
				cout << "Player 2 reaction: " << m_drawTimer2 << endl;
				m_gameState = Win;
				break;

			}
			
			break;
		}
		case Win2:
		{
			m_flashState = Off;
			m_enemyState = Dead;
			m_drawTimer += deltaTime;

			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			{
				m_gameState = Restart;
			}
			else if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_CONTROL))
			{
				cout << "Player 1 reaction: " << m_drawTimer << endl;
				m_gameState = Win;
			}
			break;
		}
		case Lose :
		{
			m_readyState = GameState::Clear;
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
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE) && input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
		quit();
}

void QuickDrawApp::DrawBackground()
{
	switch (m_bgState)
	{
	case On:
		m_2dRenderer->drawSprite(m_Building_Left, 400, 300, 0, 0, 0, 11);
		m_2dRenderer->drawSprite(m_BG_Sunset, 400, 300, 0, 0, 0, 20);
		break;
	case Off:

		break;
	}
}

// Flash state
// Turns on and off the white screenflash that simulates gunfire
void QuickDrawApp::FlashState()
{
	switch (m_flashState)
	{
	case On:
		m_2dRenderer->drawSprite(m_Flash, 400, 300, 0, 0, 0, 3);
		break;
	case Off:
		break;
	}	
}

// Gun Position
// Draw the selection gun on the main menu
void QuickDrawApp::GunPosition()
{
	float gunYPosition = -1;

	if (m_gameState >= Menu1 && m_gameState <= Menu3)
		m_2dRenderer->drawSprite(m_Game_Menu_Selection, 200, menu[currentMenuItem].yPos, 0, 0, 0, 5);
}

// Titles
// Contains the different menu graphics and where they're rendered.
void QuickDrawApp::TitleGraphics()
{
	switch (m_gameState) {
	case Menu1:
	case Menu2:
	case Menu3:
		//m_2dRenderer->drawSprite(m_Game_Menu, 400, 300, 0, 0, 0, 5);
		m_2dRenderer->setRenderColour(1, 1, 0, 1);
		for (int i = 0; i < 3; i++)
			m_2dRenderer->drawText(m_font_rope, menu[i].text.c_str(), 400, menu[i].yPos, 1);
		m_2dRenderer->setRenderColour(1, 1, 1, 1);
		break;

	case Instructions:
		m_2dRenderer->drawSprite(m_Game_Enter_Instruction, 400, 300, 0, 0, 0, 6);
		m_2dRenderer->drawSprite(m_Instructions, 400, 300, 0, 0, 0, 5);
		break;
	case Draw:
		m_2dRenderer->drawSprite(m_Game_Draw, 400, 300, 0, 0, 0, 5);
		break;
	case Win:

		m_2dRenderer->drawSprite(m_Game_Enter_Instruction, 400, 300, 0, 0, 0, 6);
		m_2dRenderer->drawSprite(m_Game_Win, 400, 300, 0, 0, 0, 6);
		break;
	case Lose:
		m_2dRenderer->drawSprite(m_Game_Enter_Instruction, 400, 300, 0, 0, 0, 6);
		m_2dRenderer->drawSprite(m_Game_Lose, 400, 300, 0, 0, 0, 7);
		break;
	case Exit:
		break;
	}
}

// Ready? Draw!
// Draws the preparation messages before each round
void QuickDrawApp::ReadyState()
{
	switch (m_readyState)
	{
	case SquareUp:	message = m_Game_SquareUp;	break;
	case Ready: message = m_Game_Ready;	break;
	}
	if (message != nullptr)
		m_2dRenderer->drawSprite(message, 400, 300, 0, 0, 0, 5);
}

// Player
// Draws the state of the Player at different stages of the game
void QuickDrawApp::PlayerState()
{
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
}

// Enemy
// Draws the state of the Enemy at different stages of the game
void QuickDrawApp::EnemyState()
{
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
}


void QuickDrawApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->drawSprite(m_Title, 400, 300, 0, 0, 0,				1);
	m_2dRenderer->drawSprite(m_Border, 400, 300, 0, 0, 0,				2);

	DrawBackground();

	FlashState();

	GunPosition();
		
	ReadyState();

	TitleGraphics();

	PlayerState();

	EnemyState();

	//Background
	m_2dRenderer->drawSprite(m_BG_Dark, 400, 300, 0, 0, 0,					21);

	// draw your stuff here! m_font;
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	// output some text, uses the last used colour
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawText(m_font, "Testing Consolas Font", 400, 400, 1);
	
	// done drawing sprites
	m_2dRenderer->end();
}