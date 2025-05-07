#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {

	delete model_;
	delete player_;
	delete debugCamera_;

	for (std::vector<WorldTransform*>& worldTransformBlocklone : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlocklone) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dもモデルの生成
	model_ = Model::Create();

	modelBlock_ = Model::CreateFromOBJ("cube");

	// ワールドトランスフォームの初期化
	// worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	player_ = new Player();

	player_->Initialize(model_, textureHandle_, &camera_);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;

	// ブロック一個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if ((i + j) % 2 == 0) {
				worldTransformBlocks_[i][j] = new WorldTransform;
				worldTransformBlocks_[i][j]->Initialize();
				worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
				worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
			}
		}
	}
}

void GameScene::Update() {
	player_->Update();

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			
		

					if (!worldTransformBlock) {
						continue;
					}
			
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			// 転送
			worldTransformBlock->TransferMatrix();
		}
	}

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	//カメラの処理
	if (isDebugCameraActive_) {
		// デバックカメラの更新
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		camera_.TransferMatrix();
	
	} else {
		camera_.UpdateMatrix();
	}


}

void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	player_->Draw();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock) {
				continue;
			}
			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
}
