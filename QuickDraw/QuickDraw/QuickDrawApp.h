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
	//BackGround
	aie::Texture*		m_BG;

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

	//Player
	aie::Texture*		m_Player_Gun;
	aie::Texture*		m_Player;
	aie::Texture*		m_Player_Hat;
	aie::Texture*		m_Player_Hat_Dead;

	//Titles
	aie::Texture*		m_Border;
	aie::Texture*		m_Title;
	aie::Texture*		m_Flash;
	aie::Texture*		m_Game_Ready;
	aie::Texture*		m_Game_Draw;
	aie::Texture*		m_Game_Win;
	aie::Texture*		m_Game_Lose;
	aie::Font*			m_font;
	aie::Font*			m_font_rope;
	
	//sound::sound*		m_Sound_BG;
	//sound::sound*		m_Sound_Gunshot_Player_Left;
	//sound::sound*		m_Sound_Gunshot_Enemy_Right;
	
	float m_cameraX, m_cameraY;
	//float m_timer;

	string m_playerName;
	float m_reactionTime = 0;
	float m_timer = 0; // Required to be Float to track fractions of a second
	const unsigned int timerMin = 2;
	const unsigned int timerMax = 6;

	//int m_gameState; // Game States: Starting (Enter Name), Counting Down, "Fire" (Counting reaction time), Game Over (Win or Lose)

	enum CharacterState
	{
		Idle,
		Shooting,
		Dead,
	};

	CharacterState m_playerState;
	CharacterState m_enemyState;

	float m_drawTimer;
	float m_waitTimer;
	float m_deathTimer;

	enum GameState
	{
		Draw,
		Ready,
		Win,
		Lose,
		Restart,
	};

	GameState m_gameState;
};