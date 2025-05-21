#include "GameScene.h"
#include "MyMath.h"
#include "cassert"

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {

	// NULLポインタチェック
	assert(model);

	// 3Dもモデルの生成
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	camera_ = camera;
}

void Player::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	

	worldTransform_.TransferMatrix();

}


void Player::Draw() {

	// DirectXCommonインスタンスの取得
	// DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	// Model::PreDraw(dxCommon->GetCommandList());

	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_);

	// 3Dモデル描画後処理
	// Model::PostDraw();
}
