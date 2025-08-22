#pragma once
#include "KamataEngine.h"

#include "Fade.h"

#include "Player.h"
/**/
class Tutorial
{
public:
	enum class Phase
	{
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	// 終了フラグ
	bool finishedTutorial_ = false;
	// デスフラグのgetter
	bool IsFinishedTutorial() const { return finishedTutorial_; }

	void Initialize();
	void Update();
	void Draw();

	// デストラクタ
	~Tutorial();
	// void ChangeScene();
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

private:
	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;
	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransformPlayer_;

	// フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;
};
