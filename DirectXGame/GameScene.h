#pragma once
#include "KamataEngine.h"
#include"Player.h"

// ゲームシーン
class GameScene {
public:
	//3Dモデル
	KamataEngine::Model* model_ = nullptr;

	//ワールドトランクスフォーム
	KamataEngine::WorldTransform worldTransform_;

	//
	KamataEngine::Sprite* sprite_ = nullptr;

	//カメラ
	KamataEngine::Camera camera_;

	//自キャラ
	Player* player_ = nullptr;


	~GameScene();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;



};
