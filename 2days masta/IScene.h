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

class IScene
{
public:
	IScene();
	~IScene();
	void Initialize();
	void Run();
	void GameRun();
	void Draw();
private:
	Card* card_ = nullptr;
	Phase phase_ = Phase::TITLE;
	GamePhase gamePhase_ = GamePhase::DROW;
	int textureHandle_;
	int title_;
	int moji_;
};

