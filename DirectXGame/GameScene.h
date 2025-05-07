#pragma once
#include <KamataEngine.h>
#include"Player.h"
#include<vector>
#include "MyMath.h"


// ゲームシーン
class GameScene {
public:
	~GameScene();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

private:
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Model* modelBlock_ = nullptr;

	// ワールドトランクスフォーム
	//KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// 自キャラ
	Player* player_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;

	//デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;


};
