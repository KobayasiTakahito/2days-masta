#include "IScene.h"
#include <Novice.h>
#include"Card.h"
IScene::IScene() {
	textureHandle_ = Novice::LoadTexture("./Resources./back.png");
	title_ = Novice::LoadTexture("./Resources./title.png");
	moji_ = Novice::LoadTexture("./Resources./moji.png");
	Win_ = Novice::LoadTexture("./Resources./win.png");
	Lose_ = Novice::LoadTexture("./Resources./Lose.png");
	carasu_ = Novice::LoadTexture("./Resources./pokemon.png");
	explanation_[0] = Novice::LoadTexture("./Resources./explanation1.png");
	explanation_[1] = Novice::LoadTexture("./Resources./explanation2.png");
	explanation_[2] = Novice::LoadTexture("./Resources./explanation3.png");
	card_ = new Card;
}

IScene::~IScene() {
	delete card_;
}

void IScene::Initialize() {
	card_->Initialize();
	phase_ = Phase::TITLE;
	gamePhase_ = GamePhase::DROW;
	tPhase_ = TutolialPhase::CARD;
	texnumber_ = 0;
	
}
bool IScene::Time() {
	static int t = 18;
	t--;
	if (t == 0) {
		t = 18;
		return true;
	}
	return false;

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
			IScene::Initialize();
			phase_ = Phase::TUTORIAL;
		}
		if (keys[DIK_S] && preKeys[DIK_S] == 0) {
			IScene::Initialize();
			phase_ = Phase::PRE;
		}
		break;
	case Phase::TUTORIAL:
		IScene::TutoRun();
		//IScene::GameRun();
		break;
	case Phase::PRE:
		IScene::GameRun();
		break;
	case Phase::GAMES:

		break;
	case Phase::ENDGAME:
		
		

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && IScene::Time()) {
				phase_ = Phase::TITLE;
			}
			
		
		
		break;
	
	}

}
//チュートリアル
bool IScene::TutoRun() {
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	switch (tPhase_)
	{
	case TutolialPhase::CARD:
		card_->Shuffile();
		card_->Distibute();
		tPhase_ = TutolialPhase::TIME;

		break;
	case TutolialPhase::TIME:
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			if (IScene::Time()) {
				texnumber_ += 1;
			}

		}
		if (texnumber_ == 2 && keys[DIK_W] && preKeys[DIK_W] == 0) {
			tPhase_ = TutolialPhase::SOUSA;
		}
		else if (texnumber_ == 2 && keys[DIK_S] && preKeys[DIK_S] == 0){
			texnumber_ = 0;
	}
		break;
	case TutolialPhase::SOUSA:
		if (IScene::Time()) {
			if (card_->Select()) {
				tPhase_ = TutolialPhase::BATOL;
			}
		}
		break;
	case TutolialPhase::BATOL:
		card_->TutolialCpu();
		if (card_->Calculation()) {
			tPhase_ = TutolialPhase::WL;
		}
		else {
			tPhase_ = TutolialPhase::SOUSA;
		}

		break;
	case TutolialPhase::WL:
		phase_ = Phase::ENDGAME;
		break;
	
	}
	return false;
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
		phase_ = Phase::ENDGAME;
		
		
		break;

	}
}

void IScene::TutoDraw() {
	Novice::DrawSprite(860, 350, explanation_[texnumber_], 0.6f, 0.6f, 0.0f, WHITE);
	Novice::DrawSprite(1100, 400, carasu_, 0.8f, 0.8f, 0.0f, WHITE);
	switch (tPhase_)
	{
	case TutolialPhase::CARD:
		
		break;
	case TutolialPhase::TIME:

		break;
	case TutolialPhase::SOUSA:

		break;
	case TutolialPhase::BATOL:

		break;
	case TutolialPhase::WL:

		break;

	}



}

void IScene::Draw() {
	Novice::DrawSprite(0, 0, textureHandle_, 2.0f, 1.8f, 0.0f, WHITE);
	switch (phase_)
	{
	case Phase::TITLE:
		Novice::DrawSprite(380, 200, title_, 1.2f, 1.2f, 0.0f, WHITE);
		Novice::DrawSprite(420, 400, moji_, 1.0f, 1.0f, 0.0f, WHITE);
		break;
	case Phase::TUTORIAL:
		card_->Draw();
		IScene::TutoDraw();
		break;
	case Phase::PRE:
		card_->Draw();
		break;
	case Phase::GAMES:
		card_->Draw();
		break;
	case Phase::ENDGAME:
		if (card_->WinLose()) {
			Novice::DrawSprite(380, 200, Win_, 1.2f, 1.2f, 0.0f, WHITE);
		}
		else {
			Novice::DrawSprite(380, 200, Lose_, 1.2f, 1.2f, 0.0f, WHITE);
		}
		break;

	}
}