#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <string>
#include <Texture.h>

using namespace std;

class QuickDrawApp : public aie::Application {
public:

	QuickDrawApp();
	virtual ~QuickDrawApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;

	// Textures
	//BackGrounds
	aie::Texture*		m_BG_Dark;
	aie::Texture*		m_BG_Sunset;

	//Enemy
	aie::Texture*		m_Enemy_Body;
	aie::Texture*		m_Enemy_Body_Draw;
	aie::Texture*		m_Enemy_Hat;
	aie::Texture*		m_Enemy_Hat_Dead;
	aie::Texture*		m_Enemy_Shadow;
	aie::Texture*		m_Enemy_Shadow_Draw;
	aie::Texture*		m_Enemy_Shadow_Hat;
	aie::Texture*		m_Enemy_Shadow_Hat_Dead;

	//Extras
	aie::Texture*		m_Building_Left;
	aie::Texture*		m_Game_Menu_Selection;

	//Player
	aie::Texture*		m_Player_Gun;
	aie::Texture*		m_Player;
	aie::Texture*		m_Player_Hat;
	aie::Texture*		m_Player_Hat_Dead;

	//Titles
	aie::Texture*		m_Border;
	aie::Texture*		m_Title;
	//aie::Texture*		m_Game_Menu;
	aie::Texture*		m_Instructions;
	aie::Texture*		m_Flash;
	aie::Texture*		m_Game_SquareUp;
	aie::Texture*		m_Game_Ready;
	aie::Texture*		m_Game_Draw;
	aie::Texture*		m_Game_Win;
	aie::Texture*		m_Game_Lose;
	aie::Texture*		m_Game_Enter_Instruction;

	//Fonts
	aie::Font*			m_font;
	aie::Font*			m_font_rope;
	
	//sound::sound*		m_Sound_BG;
	//sound::sound*		m_Sound_Gunshot_Player_Left;
	//sound::sound*		m_Sound_Gunshot_Enemy_Right;


	void TitleTextures();

	void CharacterTextures();
	
	float m_cameraX, m_cameraY;
	//float m_timer;

	string m_playerName;
	float m_reactionTime = 0;
	float m_timer = 0; // Required to be Float to track fractions of a second
	const unsigned int timerMin = 2;
	const unsigned int timerMax = 6;

	float m_enemyShoot;

	//int m_gameState; // Game States: Starting (Enter Name), Counting Down, "Fire" (Counting reaction time), Game Over (Win or Lose)

	enum CharacterState
	{
		Null,
		Idle,
		Shooting,
		Dead,
	};

	CharacterState m_playerState;
	CharacterState m_enemyState;

	float m_drawTimer;
	float m_drawTimer2;
	float m_waitTimer;
	float m_deathTimer;

	enum BGState
	{
		On,
		Off,
	};
	BGState m_bgState;
	BGState m_flashState;
	BGState m_enterToMenu;

	enum GameState
	{
		Clear,
		Menu1,
		Menu2,
		Menu3,
		Menu4,
		Play,
		Play2,
		Instructions,
		Exit,
		Draw,
		Draw2,
		SquareUp,
		SquareUp2,
		Ready,
		Ready2,
		Win,
		Win1,
		Win2,
		Lose,
		Jumped,
		Restart,
	};
	GameState m_Selection;
	GameState m_gameState;
	GameState m_readyState;

	//Hi-Score

	void TitleGraphics();
	void DrawBackground();
	void FlashState();
	void ReadyState();
	void PlayerState();
	void EnemyState();
	void GunPosition();


	struct MenuItem 
	{
		string text;
		float yPos;
		GameState state; // this is the state we're in when we're showing this menu item
		GameState nextState; // this is the state we go to when we press enter
	};

	const int menuItems = 3;

	MenuItem menu[3] = {
		{ "Play", 350, GameState::Menu1, GameState::SquareUp },
		{ "Instructions", 280, GameState::Menu2, GameState::Instructions },
		{ "Exit", 210, GameState::Menu3, GameState::Exit },
	};

	int currentMenuItem = 0;
};