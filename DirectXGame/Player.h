#include "KamataEngine.h"
#include <vector>
class MapChipField;
// 自キャラ
class Player {
	enum LRDirection {
		kRiget,
		kLeft,
	};

	// 角
	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数
	};

private:
	// マップとの当たり判定情報
	struct CollisionMapInfo {

		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	uint32_t textureHandle_ = 0u;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformPlayer_;

	KamataEngine::Vector3 velocity_ = {};

	// 移動
	static inline const float kAcceleration = 0.2f;

	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.1f;

	// 自機の回転
	LRDirection lrDirection_ = LRDirection::kRiget;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.3f;

	// 着地状態フラグ
	bool onGround_ = true;

	// 重力加速度
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度
	static inline const float kLimitFallSpeed = 0.5f;
	// ジャンプ初速
	static inline const float kJumpAcceleration = 1.0f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank = 0.1f;

public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();

	void InputMove();

	void AnimateTurn();

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);
#pragma once
#include "KamataEngine.h"
#include "MyMath.h"
	using namespace KamataEngine;

	class MapChipField;

	// 02_10 21枚目
	class Enemy;

	class Player {
	public:
		// 左右
		enum class LRDirection {
			kRight,
			kLeft,
		};

		// 角 02_07スライド16枚目
		enum Corner { kRightBottom, kLeftBottom, kRightTop, kLeftTop, kNumCorner };

		/// 初期化
		void Initialize(Model* model, Camera* camera, const Vector3& position);

		/// 更新
		void Update();

		/// 描画
		void Draw();

		// getter(02_06スライド11枚目で追加)
		const WorldTransform& GetWorldTransform() const { return worldTransform_; }

		// 02_06スライド28枚目で追加
		const Vector3& GetVelocity() const { return velocity_; }

		// 02_07 スライド4枚目
		void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

		// 02_10 10枚目 ワールド座標を取得
		Vector3 GetWorldPosition();

		// 02_10 13枚目
		AABB GetAABB();

		// 02_10 21枚目 衝突応答
		void OnCollision(const Enemy* enemy);

	private:
		// ワールド変換データ
		WorldTransform worldTransform_;
		// モデル
		Model* model_ = nullptr;
		// テクスチャハンドル
		uint32_t textureHandle_ = 0u;
		Camera* camera_ = nullptr;
		// 02_05 移動量
		Vector3 velocity_ = {};
		// 02_05  フレームごとの加速度
		static inline const float kAcceleration = 0.1f;
		// 02_05 非入力時の摩擦係数
		static inline const float kAttenuation = 0.05f;
		// 02_05 最高速度
		static inline const float kLimitRunSpeed = 0.3f;
		// 02_05 顔の向き
		LRDirection lrDirection_ = LRDirection::kRight;
		// 02_05 旋回開始時の角度
		float turnFirstRotationY_ = 0.0f;
		// 02_05 旋回タイマー
		float turnTimer_ = 0.0f;
		// 02_05 旋回時間 <秒>
		static inline const float kTimeTurn = 0.3f;
		// 02_05 着地フラグ
		bool onGround_ = true;
		// 02_05 ジャンプ定数もろもろ
		static inline const float kJumpAcceleration = 20.0f;
		static inline const float kGravityAcceleration = 0.98f;
		static inline const float kLimitFallSpeed = 0.5f;

		// 02_07 マップチップによるフィールド
		MapChipField* mapChipField_ = nullptr;
		// 02_07 キャラクターの当たり判定サイズ
		static inline const float kWidth = 0.8f;
		static inline const float kHeight = 0.8f;
		// 02_07スライド34枚目
		static inline const float kBlank = 0.04f;

		// 02_07スライド10枚目 移動入力
		void InputMove();
		// 02_07 スライド12枚目
		struct CollisionMapInfo {
			bool ceiling = false;
			bool landing = false;
			bool hitWall = false;
			Vector3 move;
		};
		// 02_07 スライド13枚目
		void CheckMapCollision(CollisionMapInfo& info);
		// 02_07 スライド14枚目
		void CheckMapCollisionUp(CollisionMapInfo& info);
		void CheckMapCollisionDown(CollisionMapInfo& info);
		void CheckMapCollisionRight(CollisionMapInfo& info);
		void CheckMapCollisionLeft(CollisionMapInfo& info);
		// 02_07 スライド17枚目
		Vector3 CornerPosition(const Vector3& center, Corner corner);

		// 02_08スライド14枚目 設置状態の切り替え処理
		void UpdateOnGround(const CollisionMapInfo& info);

		// 02_08 スライド27枚目 壁接触している場合の処理
		void UpdateOnWall(const CollisionMapInfo& info);

		// 02_08スライド16枚目 着地時の速度減衰率
		static inline const float kAttenuationLanding = 0.0f;
		// 02_08スライド21枚目 微小な数値
		static inline const float kGroundSearchHeight = 0.06f;
		// 02_08スライド27枚目 着地時の速度減衰率
		static inline const float kAttenuationWall = 0.2f;
	};
	void CheckMapCollisionDown(CollisionMapInfo& info);

	void CheckMapCollisionRight(CollisionMapInfo& info);

	void CheckMapCollisionLeft(CollisionMapInfo& info);

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetValocity() const { return velocity_; }
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	void MapHitMove(const CollisionMapInfo& info);
	void CheckMapCeiling(const CollisionMapInfo& info);
};