#pragma once
#include "GameScene.h"
#include "MyMath.h"
#include <KamataEngine.h>

// 左右
enum class LRDirection {
	kRight,
	kLeft,

};

// ゲームシーン
class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {};

	static inline const float kAcceleration = 1;
	static inline const float kLimitRunSpeed = 1;
	static inline const float kAttenuation = 1;

	LRDirection lrDirection_ = LRDirection::kRight;

	// 施回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 施回タイマー
	float turnTimer_ = 0.0f;

	// 施回時間<秒>
	static inline const float kTimeTurn = 0.1f;

	static inline const float kGravityAcceleration = 1;
	static inline const float kLimitFallSpeed = 1;
	static inline const float kJumpAcceleration = 1;

	bool onGrand_ = true;

	
};
