#pragma once
#include "GameScene.h"
#include "MyMath.h"
#include <KamataEngine.h>

class MapChipField;

// ゲームシーン
class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();


	//移動
	void InputMove();

	// 左右
	enum class LRDirection {
		kRight,
		kLeft,

	};


	//角
	enum Corner {
		kRightBottom,//右下
		kLeftBottom,//左下
		kRightTop,//右上
		kLeftTop,//左上

		kNumCorner//要素数

	};

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3&center,Corner corner);

	// マップチップと当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	void SetMapChipField(MapChipField* mapChipField) { mapChipField; }

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);

	void CheckMapCollisionDown(CollisionMapInfo& info);

	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void AnimateTurn();
	
	//着地
	void CheckMaplanding(const CollisionMapInfo& info);
	
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }


	
	void CheckMapMove(const CollisionMapInfo& info);

	//
	//
	void CheckMapCeiling(const CollisionMapInfo& info);
	void CheckMapWall(const CollisionMapInfo& info);

	void CheckMapLanding(const CollisionMapInfo& info);

private:
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.1f;
	static inline const float kLimitRunSpeed = 2;
	static inline const float kAttenuation = 0.1f;
	static inline const float kAttenuationLanding = 0.0f;
	static inline const float kGroundSearchHeight = 0.0f;


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

	bool onGround_ = true;

	// キャラの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.8f;

	

};
