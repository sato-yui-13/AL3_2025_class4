#pragma once

#include <KamataEngine.h>
#include<vector>

class Skydome {
public:
	void Intialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	void Update();

	void Draw();

	private:

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;
	
	KamataEngine::Camera* camera_ = nullptr;

		// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};