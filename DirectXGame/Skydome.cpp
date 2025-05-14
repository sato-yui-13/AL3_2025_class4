#include "Skydome.h"

using namespace KamataEngine;

void Skydome::Intialize(Model* model, uint32_t textureHandle, Camera* camera) 
{ 

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = textureHandle;
	// 3Dもモデルの生成
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	camera_ = camera;
}

void Skydome::Update() 
{ 
	 	worldTransform_.TransferMatrix();	 
}

void Skydome::Draw() 
{
	model_->Draw(worldTransform_, *camera_);
}
