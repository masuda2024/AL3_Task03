#include "Enemy.h"
#include "GameScene.h"
#include "cassert"
#include <algorithm>
#include <numbers>

#define NOMINMAX
#include "MapChipField.h"
#include <algorithm>
using namespace KamataEngine;
using namespace MathUtility;

void Enemy::Initialize(Model* model, Camera* camera, KamataEngine::Vector3& position) {
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;

	camera_ = camera;

	// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	worldTransform_.Initialize();
}

void Enemy::Update() {

	/*
	// 1.移動入力



	//InputMove();



	// 2.移動量を加速して衝突判定する
	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;
	// マップ衝突チェック
	CheckMapCollision(collisionMapInfo);
	// 3.判定結果を反映して移動させる
	CheckMapMove(collisionMapInfo);
	// 4.天井に接触している場合の処理
	CheckMapCeiling(collisionMapInfo);
	// 5.壁に接触している場合の処理
	CheckMapWall(collisionMapInfo);
	// 6.接地状態の切り替え
	CheckMapLanding(collisionMapInfo);

	// 7.旋回制御
	AnimateTurn();

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // 敵の座標の計算
	*/

	worldTransform_.translation_ += velocity_;

	walkTimer_ += 5.0f / 60.0f;

	worldTransform_.rotation_.x = sin(walkTimer_);

	// プレイヤーの座標の計算
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }

KamataEngine::Vector3 Enemy::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Enemy::GetAABB() {
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

// 衝突応答
void Enemy::OnCollition(const Player* player) { (void)player; }
