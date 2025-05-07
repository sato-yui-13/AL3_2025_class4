#include "GameScene.h"
#include "cassert"

using namespace KamataEngine;


void Player::Initialize(Model* model, uint32_t textureHandle,Camera* camera) {

	// NULLポインタチェック
	assert(model);

	// ファイル名を指定してテ                                                                     クスチャを読み込む
	textureHandle_ = textureHandle;
	// 3Dもモデルの生成
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	camera_ = camera;

}

void Player::Update() { 
	worldTransform_.TransferMatrix(); 
}

void Player::Draw() {

	// DirectXCommonインスタンスの取得
	//DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	//Model::PreDraw(dxCommon->GetCommandList());

	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);

	// 3Dモデル描画後処理
	//Model::PostDraw();
}
