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
	aie::Texture*		m_BG;
	aie::Texture*		m_Enemy;
	aie::Texture*		m_Building_Left;
	aie::Texture*		m_Player_Gun;
	aie::Texture*		m_Player;
	aie::Texture*		m_Player_Hat;
	aie::Texture*		m_Border;
	aie::Texture*		m_Title;
	aie::Font*			m_font;
	aie::Font*			m_font_rope;
	
	float m_cameraX, m_cameraY;
	//float m_timer;

	string m_playerName;
	float m_reactionTime = 0;
	float m_timer = 0; // Required to be Float to track fractions of a second
	const unsigned int timerMin = 2;
	const unsigned int timerMax = 6;

	int m_gameState; // Game States: Starting (Enter Name), Counting Down, "Fire" (Counting reaction time), Game Over (Win or Lose)
};