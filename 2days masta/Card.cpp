#include "Card.h"
#include <stdlib.h>
#include<Novice.h>
#include<time.h>


void Card::Initialize() {
	
	//手持ち
	for (int i = 0; i < 5; i++) {
		handAlive_[i] = false;
		enemyHandAlive[i] = false;
		hand_[i] = 0;
		enemyHand_[i] = 0;
	}
	//ナンバー
	for (int i = 0; i < 10; i++) {
		number_[i] = i + 1;
	}
	//テクスチャ
	textureHandle_[0] = Novice::LoadTexture("./Resources./card1.png");
	textureHandle_[1] = Novice::LoadTexture("./Resources./card2.png");
	textureHandle_[2] = Novice::LoadTexture("./Resources./card3.png");
	textureHandle_[3] = Novice::LoadTexture("./Resources./card4.png");
	textureHandle_[4] = Novice::LoadTexture("./Resources./card5.png");
	textureHandle_[5] = Novice::LoadTexture("./Resources./card6.png");
	textureHandle_[6] = Novice::LoadTexture("./Resources./card7.png");
	textureHandle_[7] = Novice::LoadTexture("./Resources./card8.png");
	textureHandle_[8] = Novice::LoadTexture("./Resources./card9.png");
	textureHandle_[9] = Novice::LoadTexture("./Resources./card10.png");

	numberCard[0] = Novice::LoadTexture("./Resources./num0.png");
	numberCard[1] = Novice::LoadTexture("./Resources./num1.png");
	numberCard[2] = Novice::LoadTexture("./Resources./num2.png");
	numberCard[3] = Novice::LoadTexture("./Resources./num3.png");
	numberCard[4] = Novice::LoadTexture("./Resources./num4.png");
	numberCard[5] = Novice::LoadTexture("./Resources./num5.png");
	numberCard[6] = Novice::LoadTexture("./Resources./num6.png");
	numberCard[7] = Novice::LoadTexture("./Resources./num7.png");
	numberCard[8] = Novice::LoadTexture("./Resources./num8.png");
	numberCard[9] = Novice::LoadTexture("./Resources./num9.png");
	dark_ = Novice::LoadTexture("./Resources./dark.png");
	//
	select_ = 0;
	time_ = 12;
	end_ = handNum;
	breakTime_ = 0;
	enemytime_ = 0;
	//フラグの初期化
	winF_ = false;
	loseF_ = false;
}
//シャッフル
void Card::Shuffile() {
	srand(static_cast<int>(time(nullptr)));

	int i, j;
	int tmp;
	i = 10;
	while (i > 0)
	{
		i--;
		j = rand() % (i + 1);
		tmp = number_[j];
		number_[j] = number_[i];
		number_[i] = tmp;


	}

}
//配る
void Card::Distibute() {
	int top = 0;
	for (int i = 0; i < 5; i++) {
		hand_[i] = number_[top];
		handAlive_[i] = true;
		top++;
	}
	for (int i = 0; i < 5; i++) {
		enemyHand_[i] = number_[top];
		enemyHandAlive[i] = true;
		top++;
	}
}
//選択
bool Card::Select() {
	static char keys[256] = { 0 };
	static char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	//右にセレクト
	if (keys[DIK_D] && preKeys[DIK_D] == 0) {
		select_ += 1;
		if (select_ >= 5) {
			select_ = 0;
		}
	}
	//左にセレクト
	if (keys[DIK_A] && preKeys[DIK_A] == 0) {
		select_ -= 1;
		if (select_ < 0) {
			select_ = 4;
		}
	}
	if (hand_[select_] > 0) {
		//決定
		
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && handAlive_[select_]) {
				breakTime_ = hand_[select_];
				handAlive_[select_] = false;
				return true;
			}
		
	}
	return false;
}

void Card::TutolialCpu() {
	int top = 0;
	while (enemyHandAlive[top] == false) {
		top++;
		
	}
	enemytime_ = enemyHand_[top];
	enemyHandAlive[top] = false;
	
}
void Card::Cpu() {
	srand(static_cast<int>(time(nullptr)));
	int j;
	for (int i = 0;i<5;i++)
	{
		j = rand() % 5;
		if (enemyHandAlive[j]) {
			enemytime_ = enemyHand_[j];
			enemyHandAlive[j] = false;
			break;
		}
	}
}
//計算
bool Card::Calculation() {
	//午後
	if (time_ >= 12) {
		if (breakTime_ > enemytime_) {
			time_ += (breakTime_ - enemytime_);
		}
		else if (breakTime_ < enemytime_) {
			time_ -= (enemytime_ - breakTime_);
		}
	}
	//午前
	else if (time_ < 12) {
		if (breakTime_ > enemytime_) {
			time_ -= (breakTime_ - enemytime_);
		}
		else if (breakTime_ < enemytime_) {
			time_ += (enemytime_ - breakTime_);
		}
	}
	if (time_ >= 24) {
		winF_ = true;
		return true;
	}
	else if (time_ <= 0) {
		loseF_ = true;
		return true;
	}
	for (int i = 0; i < 5; i++) {

		if (handAlive_[i] == false) {
			end_ += 1;
		}
		else {  
			end_ = 0;
			break; 
		}
	}
		if (end_ == 5) {
			if (time_ <= 12) {
				loseF_ = true;
				return true;
			}
			else if (time_ > 12) {
				winF_ = true;
				return true;
			}
		}
	
	return false;
}
//描画

void Card::NumDraw() {
	int num = time_;
	int eachNumber[2] = {};
	if (num < 0) {
		num = 0;
	}
	Novice::DrawSprite(550, 350, numberCard[num/10], 1.0f, 1.0f, 0.0f, WHITE);
	eachNumber[1] = num / 10;
	num = num % 10;
	Novice::DrawSprite(600, 350, numberCard[num], 1.0f, 1.0f, 0.0f, WHITE);
	eachNumber[0] = num / 1;
	num = num % 1;
}

void Card::Draw() {
	Card::NumDraw();
	for (int i = 0; i < 5; i++) {


		for (int j = 0; j < 10; j++) {

			if (hand_[i] == j + 1) {
				if (hand_[select_] == j + 1) {
					Novice::DrawSprite(300 + 130 * i, 450, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (handAlive_[i] == 0) { Novice::DrawSprite(300 + 130 * i, 450, dark_, 0.5f, 0.5f, 0.0f, WHITE); }
				}
				else {
					Novice::DrawSprite(300 + 130 * i, 470, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (handAlive_[i] == 0) {
						Novice::DrawSprite(300 + 130 * i, 470, dark_, 0.5f, 0.5f, 0.0f, WHITE);
					}
				}


			}
			if (enemyHand_[i] == j + 1) {
				if (enemytime_ == j + 1) {
					Novice::DrawSprite(300 + 130 * i, 50, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (enemyHandAlive[i] == 0) { Novice::DrawSprite(300 + 130 * i, 50, dark_, 0.5f, 0.5f, 0.0f, WHITE); }
				}
				else {
					Novice::DrawSprite(300 + 130 * i, 0, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (enemyHandAlive[i] == 0) {
						Novice::DrawSprite(300 + 130 * i, 0, dark_, 0.5f, 0.5f, 0.0f, WHITE);
					}
				}


			}
		}

	}
}