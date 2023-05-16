#pragma once
#include"Card.h"

class IScene
{
public:
	~IScene();
	void Initialize();
	void Run();
	void GameRun();
	void Draw();
private:
	Card* card_ = nullptr;
	Phase phase_;
	GamePhase gamePhase_;
};

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