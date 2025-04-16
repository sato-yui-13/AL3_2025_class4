#pragma once
#include "KamataEngine.h"

// ゲームシーン
class Player {
public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle,Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransfrom_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};