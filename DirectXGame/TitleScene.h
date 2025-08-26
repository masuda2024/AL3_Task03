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


	//ゲームシーン移行前
	bool finished_ = false;
	// チュートリアルシーン移行前
	bool finished2_ = false;



	// タイトルシーンを終了
	bool IsFinished() const { return finished_; }
	
	bool IsFinished2() const { return finished2_; }
	


	//==========処理==========//



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

	// 自キャラ
	Player* player_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;
	
	// 天球
	KamataEngine::Model* modelskydome_ = nullptr;
	// キューブ
	Skydome* skydome_ = nullptr;

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
