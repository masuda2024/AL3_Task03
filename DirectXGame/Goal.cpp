#include"Goal.h"
#include "GameScene.h"
#include "cassert"
#include <algorithm>
#include <numbers>

#define NOMINMAX
#include "MapChipField.h"
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

KamataEngine::Vector3 Goal::GetWorldPosition()
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Goal::GetAABB() 
{
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Goal::OnCollition(const Player* player) { (void)player; }

void Goal::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position)
{
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;

	camera_ = camera;

	// 速度を設定する
	//velocity_ = {-kWalkSpeed, 0, 0};

	//walkTimer_ = 0.0f;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	worldTransform_.Initialize();
}

void Goal::Update() 
{
	// プレイヤーの座標の計算
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Goal::Draw(){ model_->Draw(worldTransform_, *camera_); }
