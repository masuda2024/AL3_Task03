#pragma once
#include "KamataEngine.h"

#include "Fade.h"

#include "Player.h"
#include "Skydome.h"
class TitleScene 
{
public:
	enum class Phase 
	{
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	//==========終了フラグ==========//


	// チュートリアルシーン移行前
	bool finished_ = false;
	
	


	// タイトルシーンを終了
	bool IsFinished() const { return finished_; }
	

	void Initialize();
	void Update();
	void Draw();

	// デストラクタ
	~TitleScene();
	// void ChangeScene();
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	
	// マップチップフィールド
	MapChipField* mapChipField_;
	
	
private:
	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;
	
	// カメラ
	KamataEngine::Camera camera_;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	

	uint32_t titleHandle_ = 0;
	KamataEngine::Sprite* titleSprite_ = nullptr;



	// フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	uint32_t Botan_ = 0;
};
