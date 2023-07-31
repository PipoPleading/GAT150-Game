#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"


class SpaceGame : public kiko::Game
{
public:

	enum class eState 
	{
		Title,
		StartGame,
		MusicStart,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
		

	};


public:

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	//number of seconds something occurs
	float m_spawnTime = 3;
	float m_random = 0;
	bool m_music = true;
	float m_stateTimer = 0;

	std::shared_ptr<kiko::Font> m_font;
	std::shared_ptr<kiko::Font> m_titleFont;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_titleText;
	std::unique_ptr<kiko::Text> m_timerText;
	std::unique_ptr<kiko::Text> m_livesText;
	std::unique_ptr<kiko::Text> m_gameoverText;
	std::unique_ptr<kiko::Text> m_shootText;

};