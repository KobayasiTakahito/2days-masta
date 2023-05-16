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
	dark_ = Novice::LoadTexture("./Resources./dark.png");
	//

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
void Card::Select() {
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
		for (int i = 0; i < 5; i++) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && handAlive_[i]) {
				breakTime_ = hand_[select_];
				handAlive_[select_] = false;
				
			}
		}
	}

	
}

void Card::TutolialCpu() {
	int top = 0;
	enemytime_ = enemyHand_[top];
	enemyHandAlive[top] = false;
	top++;
}
//計算
void Card::Calculation() {
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

	}
	else if (time_ <= 0) {
		loseF_ = true;

	}
	for (int i = 0; i < 5; i++) {

		if (handAlive_[i] == false) {
			end_ += 1;
		}
		else { break; }

		if (end_ == 5) {
			if (time_ <= 12) {
				loseF_ = true;

			}
			else if (time_ > 12) {
				winF_ = true;

			}
		}
	}
}
//描画
void Card::Draw() {
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
					Novice::DrawSprite(300 + 130 * i, 150, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (enemyHandAlive[i] == 0) { Novice::DrawSprite(300 + 130 * i, 150, dark_, 0.5f, 0.5f, 0.0f, WHITE); }
				}
				else {
					Novice::DrawSprite(300 + 130 * i, 100, textureHandle_[j], 0.5f, 0.5f, 0.0f, WHITE);
					if (enemyHandAlive[i] == 0) {
						Novice::DrawSprite(300 + 130 * i, 100, dark_, 0.5f, 0.5f, 0.0f, WHITE);
					}
				}


			}
		}

	}
}