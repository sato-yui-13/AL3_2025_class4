#include "GameScene.h"
#include "cassert"

using namespace KamataEngine;

Player::~Player() { 
	delete model_;

}

void Player::Initialize(Model* model, uint32_t textureHandle,Camera* camera) {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dもモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	//NULLポインタチェック
	assert(model);



}

void Player::Update() {

}

void Player::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// 3d
	sprite_ = Sprite ::Create(textureHandle_, {100, 50});

	// 3Dモデル描画
	model_->Draw(worldTransform_, camera_, textureHandle_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
