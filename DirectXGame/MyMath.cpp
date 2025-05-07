#include "MyMath.h"
using namespace KamataEngine;
using namespace MathUtility;
KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3& scale, KamataEngine::Vector3& rotation, KamataEngine::Vector3& translation) {

	// スケーリング行列の作成
	Matrix4x4 matScale = MakeScaleMatrix(scale);

	// 回転の行列
	Matrix4x4 matRotX = MakeRotateXMatrix(rotation.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(rotation.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(rotation.z);
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動
	Matrix4x4 matTrans = MakeTranslateMatrix(translation);

	// スケーリング
	Matrix4x4 matWold = matScale * matRot * matTrans;

	return matWold;
}