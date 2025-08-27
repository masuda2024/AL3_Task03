#include "GameClear.h"
#include "MapChipField.h"


using namespace KamataEngine;

void GameClear::Initialize() 
{
	// 3Dモデルの生成
	// model_ = Model::CreateFromOBJ("titleFont");
	// modelPlayer_ = Model::CreateFromOBJ("player");
	modelGameClear_ = Model::CreateFromOBJ("GAMECLEARFont");
	model_ = Model::CreateFromOBJ("SPACE_UI");
	
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

void GameClear::Update() 
{
	switch (phase_)
	{
	case Phase::kMain:
		// チュートリアルシーンの終了条件
		if (Input::GetInstance()->PushKey(DIK_SPACE))
		{
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
			finishedGameClear_ = true;
		}
		break;
	}
}

void GameClear::Draw()
{
	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	modelGameClear_->Draw(worldTransform_, camera_);
	model_->Draw(worldTransform_, camera_);
	
	// modelPlayer_->Draw(worldTransformPlayer_, camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
	// フェード
	fade_->Draw();
}

GameClear::~GameClear()
{
	// モデル
	delete modelGameClear_;
	delete model_;
	delete modelPlayer_;
	// フェード
	delete fade_;
}
