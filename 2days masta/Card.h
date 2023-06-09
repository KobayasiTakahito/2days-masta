﻿#pragma once
class Card
{
public:
	Card();

	void Initialize();
	void Shuffile();
	void Distibute();
	bool Select();
	void TutolialCpu();
	void Cpu();
	bool Calculation();
	void Draw();
	void NumDraw(int number);
	bool WinLose();
private:
	static const int maxNum = 10;
	static const int handNum = 5;
	int number_[maxNum];
	int textureHandle_[maxNum];
	int numberCard[10];
	//手札
	int hand_[handNum];
	int handAlive_[handNum];
	int enemyHand_[handNum];
	int enemyHandAlive[handNum];
	int end_;
	int select_;
	//ダークカバー
	int dark_;
	//時間
	int time_;
	int breakTime_;
	int enemytime_;
	//フラグ
	bool winF_;
	bool loseF_;
};

