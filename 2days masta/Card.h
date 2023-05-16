#pragma once
class Card
{
public:
	
	void Initialize();
	void Shuffile();
	void Distibute();
	void Select();
	void TutolialCpu();
	void Calculation();
	void Draw();
private:
	static const int maxNum = 10;
	static const int handNum = 5;
	int number_[maxNum];
	int textureHandle_[maxNum];
	
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

