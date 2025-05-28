#define NOMINMAX
#include "GameScene.h"
#include "MyMath.h"
#include "cassert"
#include <algorithm>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {

	// NULLポインタチェック
	assert(model);

	// 3Dもモデルの生成
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	camera_ = camera;

	// ワールドの変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {
	

	// 移動入力

	// 左右移動動作
	if (onGrand_) {

		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 施回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 施回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
			}
			// 加速/減速
			velocity_ += acceleration;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {

			if (Input::GetInstance()->PushKey(DIK_UP)) {
				// 初速
				velocity_ += Vector3(0, kJumpAcceleration, 0);
			}
		}
	} else {
		//
		velocity_.x += (1.0f - kAcceleration);

		// 落下
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		velocity_.y = std::max(velocity_.y, -kLimitRunSpeed);
	}

	// 着地フラグ
	bool landing = false;

	// 地面との当たり判定
	if (velocity_.y < 0) {
		// Y座標が地面いかになったら着地
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	if (onGrand_) {

		if (velocity_.y > 0.0f) {
			// 空中
			onGrand_ = false;
		}
		
	} else {
		//着地
		if (landing) {
		//めり込み
			worldTransform_.translation_.y = 1.0f;
			//摩擦で横方向速度
			velocity_.x *= (1.0f-kAcceleration);
			//下方向速度をリセット
			velocity_.y = 0.0f;
			//着地状態に行こう
			onGrand_ = true;

		}



	}

	// 移動
	worldTransform_.translation_ += velocity_;

	// 行列更新

	// 制御
	// 左右の自キャラ角度テーブル
	if (turnTimer_ > 0.0f) {
		turnTimer_ = 1.0f / 60.0f;

		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f

		};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自機キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
	}


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
