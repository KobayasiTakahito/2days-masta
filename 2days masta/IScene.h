#pragma once
#include"Card.h"

enum class Phase
{
	TITLE,
	TUTORIAL,
	PRE,
	GAMES,
	ENDGAME
};

enum class GamePhase {
	DROW,
	SELECT,
	PLAY,
	WLF,

};
enum class TutolialPhase {
	CARD,
	TIME,
	SOUSA,
	BATOL,
	WL,
};

class IScene
{
public:
	IScene();
	~IScene();
	void Initialize();
	void Run();
	void GameRun();
	bool TutoRun();
	void Draw();
	bool Time();
	void TutoDraw();
private:
	Card* card_ = nullptr;
	Phase phase_ = Phase::TITLE;
	GamePhase gamePhase_ = GamePhase::DROW;
	TutolialPhase tPhase_ = TutolialPhase::CARD;
	int textureHandle_;
	int title_;
	int moji_;
	int Win_;
	int Lose_;
	
};

