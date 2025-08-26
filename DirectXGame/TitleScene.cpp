#include "TitleScene.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"

using namespace KamataEngine;
//初期化
void TitleScene::Initialize()
{
	// 3Dモデルの生成
	model_ = Model::CreateFromOBJ("titleFont");
	modelPlayer_ = Model::CreateFromOBJ("player");
	// 3Dモデルの生成
	modelskydome_ = Model::CreateFromOBJ("skydome", true);
	// スカイドームの生成
	skydome_ = new Skydome();

	// スカイドームの初期化
	skydome_->Initialize(modelskydome_, textureHandle_, &camera_);
	
	
	
	
	
	/*(仮設コード)
	modelGameOver_ = Model::CreateFromOBJ("overFont");
	modelGameClear_ = Model::CreateFromOBJ("clearFont");
	*/
	
	
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

//更新
void TitleScene::Update()
{

	switch (phase_) 
	{
	case Phase::kMain:
		// タイトルシーンの終了条件
		if (Input::GetInstance()->PushKey(DIK_SPACE))
		{
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);

			finished_ = true;
			
		}

		//Tを押してチュートリアルシーンへ分岐
		if (Input::GetInstance()->PushKey(DIK_T)) 
		{
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);

			finished2_ = true;
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
			finished_ = true;
		}
		break;
	}

	/*
	// タイトルシーンの終了条件
	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
	    finished_ = true;
	}
	// フェード
	fade_->Update();
	*/
	/*
	// 自キャラの更新
	player_->Update();
	*/

	skydome_->Update();
}


//描画
void TitleScene::Draw() 
{
	// DirectXCommonインスタンスの取得
	//DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	

	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	model_->Draw(worldTransform_, camera_);
	//modelPlayer_->Draw(worldTransformPlayer_, camera_);

	modelskydome_->Draw(worldTransformPlayer_, camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
	// フェード
	fade_->Draw();
}

//デストラクタ
TitleScene::~TitleScene()
{
	// モデル
	delete model_;
	//delete modelPlayer_;
	// フェード
	delete fade_;

	delete skydome_;
}