#pragma once
#include <KamataEngine.h>


//前方宣言
class Player;

class CameraController {
public:
	void Initialize();
	void Update();
	void SetTarget(Player* target) { target_ = target; }
	void Reset();

	const KamataEngine::Camera& GetViewProjection() const { return camera_; }
	
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};
	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};
	
	void SetMovadleArea(Rect area) { movableArea_ = area; }
	
private:
	//カメラ
	KamataEngine::Camera camera_;

	Player* target_ = nullptr;
	
	//追従対象とカメラの座標の差(オフセット)
	KamataEngine::Vector3 target0ffset_ = {0.0f,0.0f,-15.0f};
	//カメラの目標座標
	KamataEngine::Vector3 targetPosition_;

	//座標補間割合
	static inline const float kInterpolationRate = 0.0f;

	//速度掛け率
	static inline const float kVelocityBias = 30.0f;

	//追徒対象の各方向へのカメラ遺贈範囲
	static inline const Rect targetMargin = {-9.0f,9.0f,-5.0f,5.0f};
};
