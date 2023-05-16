#include "IScene.h"
#include <Novice.h>
#include"Card.h"

IScene::~IScene() {
	delete card_;
}

void IScene::Initialize() {
	card_ = new Card;
	card_->Initialize();
	phase_ = Phase::TITLE;
	gamePhase_ = GamePhase::DROW;
}

void IScene::Run() {
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	switch (phase_)
	{
	case Phase::TITLE:
		if (keys[DIK_W] && preKeys[DIK_W] == 0) {
			card_->Initialize();
			phase_ = Phase::TUTORIAL;
		}
		if (keys[DIK_S] && preKeys[DIK_S] == 0) {
			card_->Initialize();
			phase_ = Phase::PRE;
		}
		break;
	case Phase::TUTORIAL:
		IScene::GameRun();
		break;
	case Phase::PRE:
		IScene::GameRun();
		break;
	case Phase::GAMES:

		break;
	case Phase::ENDGAME:

		break;
	
	}

}

void IScene::GameRun() {
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	switch (gamePhase_)
	{
	case GamePhase::DROW:
		card_->Shuffile();
		card_->Distibute();
		gamePhase_ = GamePhase::SELECT;
		break;

	case GamePhase::SELECT:
		if (card_->Select()) {
			gamePhase_ = GamePhase::PLAY;
		}
		break;

	case GamePhase::PLAY:
		if (phase_ == Phase::TUTORIAL) {
			card_->TutolialCpu();
		}
		if (phase_ == Phase::PRE) {
			card_->Cpu();
		}

		if (card_->Calculation()) {
			gamePhase_ = GamePhase::WLF;
		}
		else{
			gamePhase_ = GamePhase::SELECT;
		}
		break;
	case GamePhase::WLF:
		//Novice::ScreenPrintf(10, 10, "aaaaaaa");
		break;

	}
}

void IScene::Draw() {
	switch (phase_)
	{
	case Phase::TITLE:
		
		break;
	case Phase::TUTORIAL:
		card_->Draw();
		break;
	case Phase::PRE:
		card_->Draw();
		break;
	case Phase::GAMES:
		card_->Draw();
		break;
	case Phase::ENDGAME:

		break;

	}
}