#include "GameOver.h"
#include "MapChipField.h"
#include "Skydome.h"

using namespace KamataEngine;


void GameOver::Initialize() 
{
	// 3Dモデルの生成
	// model_ = Model::CreateFromOBJ("titleFont");
	// modelPlayer_ = Model::CreateFromOBJ("player");
	modelGameOver_ = Model::CreateFromOBJ("GAMEOVERFont");
	model_ = Model::CreateFromOBJ("SPACE_UI");
	// スカイドームの生成
	modelskydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	
	
	// Springin ボタン・システム　決定1
	Botan_ = Audio::GetInstance()->LoadWave("Sounds/Decision1.mp3");

	
	// カメラの初期化
	camera_.Initialize();
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void GameOver::Update()
{
	switch (phase_)
	{
	case Phase::kMain:
		// チュートリアルシーンの終了条件
		if (Input::GetInstance()->PushKey(DIK_SPACE))
		{
			Audio::GetInstance()->PlayWave(Botan_);
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;
	case Phase::kFadeIn:
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kFadeOut:
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			finishedGameOver_ = true;
		}
		break;
	}
}


void GameOver::Draw()
{
	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	modelGameOver_->Draw(worldTransform_, camera_);
	model_->Draw(worldTransform_, camera_);
	// modelPlayer_->Draw(worldTransformPlayer_, camera_);

	modelskydome_->Draw(worldTransformPlayer_, camera_);


	// 3Dモデル描画後処理
	Model::PostDraw();
	// フェード
	fade_->Draw();
}

GameOver::~GameOver() 
{
	// モデル
	delete modelGameOver_;
	delete model_;
	delete modelPlayer_;
	delete skydome_;
	// フェード
	delete fade_;
}
