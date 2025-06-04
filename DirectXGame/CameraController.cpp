#include "CameraController.h"
#include "Player.h"
using namespace KamataEngine;
using namespace MathUtility;

void CameraController::Initialize() {
	// カメラの初期化
	camera_.Initialize();

}

void CameraController::Update() {
	
	const Vector3& targetVelocity = target_->GetVelocity();
	
	//追従対象のトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	targetPosition_ = targetWorldTransform.translation_ + target0ffset_ + targetVelocity * kVelocityBias;
	

	//座標補間によりゆったり追従
	camera_.translation_.x = Lerp(camera_.translation_.x, targetPosition_.x, kInterpolationRate);

	//移動範囲の制限
	camera_.translation_.x = max(camera_.translation_.x, targetPosition_.x + targetMargin.left);
	camera_.translation_.x = min(camera_.translation_.x, targetPosition_.x + targetMargin.right);
	camera_.translation_.y = max(camera_.translation_.y, targetPosition_.y + targetMargin.bottom);
	camera_.translation_.y = min(camera_.translation_.y, targetPosition_.y + targetMargin.top);

	camera_.translation_.x = max(camera_.translation_.x, movableArea_.left);
	camera_.translation_.x = min(camera_.translation_.x, movableArea_.right);
	camera_.translation_.y = max(camera_.translation_.y, movableArea_.bottom);
	camera_.translation_.y = min(camera_.translation_.y, movableArea_.top);



	// 行列を更新
	camera_.UpdateMatrix();
}

void CameraController::Reset() {
	//追従対象ワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	camera_.translation_ = targetWorldTransform.translation_ + target0ffset_;
}
