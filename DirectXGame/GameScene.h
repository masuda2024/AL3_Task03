#pragma once
#include "CameraController.h"
#include "DeathParticle.h"
#include "Enemy.h"
#include "Fade.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include"Goal.h"
// ゲームシーン

class GameScene
{
public:
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終了フラグ
	bool finished1_ = false;
	// デスフラグのgetter
	bool IsFinishedGame1() const { return finished1_; }



	//クリアフラグ
	bool finished2_ = false;
	bool IsFinishedGame2() const { return finished2_; }

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバックカメラの生成
	// debugCamera_ = new DebugCamera();

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// キューブ
	Skydome* skydome_ = nullptr;

	// 3D
	KamataEngine::Model* cube_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;
	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 天球
	KamataEngine::Model* modelskydome_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 表示ブロックの生成
	void GenerateBlocks();

	// カメラコントロール
	CameraController* cameraController_ = nullptr;
	// void Initialize();
	// KamataEngine::Model* cameraModel_;

	// 敵
	KamataEngine::Model* modelEnemy_ = nullptr;
	// 敵(複数)
	// Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;


	//ゴール
	Goal* goal_ = nullptr;
	KamataEngine::Model* modelGoal_ = nullptr;


	// 全ての当たり判定
	void CheckAllCollisions();

	// パーティクル
	KamataEngine::Model* modelParticle_ = nullptr;

	// モデルパーティクル
	DeathParticle* deathParticles_ = nullptr;

	// ゲームのフェーズ(型)
	enum class Phase 
	{
		kFadeIn,  // フェードイン
		kPlay,    // ゲームプレイ
		kDeath,   // デス演出
		kClear,
		kFadeOut, // フェードアウト
	};

	// ゲームの現在フェーズから開始
	Phase phase_;

	// フェーズの切り替え
	void ChangePhase();

	

	// フェード
	Fade* fade_ = nullptr;
};