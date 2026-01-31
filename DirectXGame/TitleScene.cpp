#include "TitleScene.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"

using namespace KamataEngine;
//初期化
void TitleScene::Initialize()
{
	

	
	// Springin ボタン・システム　決定1
	Botan_ = Audio::GetInstance()->LoadWave("Sounds/Decision1.mp3");

	
	titleHandle_ = TextureManager::Load("Title.png");
	titleSprite_ = Sprite::Create(titleHandle_, {0, 0});
	
	
	
	// カメラの初期化
	camera_.Initialize();
	// ワールド変換の初期化
	worldTransform_.Initialize();
	

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
			Audio::GetInstance()->PlayWave(Botan_);

			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);

			finished_ = true;
			
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

	

	
}


//描画
void TitleScene::Draw() 
{
	

	Sprite::PreDraw();

	titleSprite_->Draw();

	Sprite::PostDraw();



	
	// フェード
	fade_->Draw();
}

//デストラクタ
TitleScene::~TitleScene()
{
	// モデル
	delete model_;
	

	delete titleSprite_;


	// フェード
	delete fade_;

}