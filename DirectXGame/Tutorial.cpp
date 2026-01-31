#include "Tutorial.h"
#include "MapChipField.h"
#include "Player.h"

using namespace KamataEngine;



void Tutorial::Initialize()
{
	
	
	tutorialHandle_ = TextureManager::Load("Tutorial.png");
	tutorialSprite_ = Sprite::Create(tutorialHandle_, {0, 0});



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

void Tutorial::Update() 
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
			finishedTutorial_ = true;
		}
		break;
	}
}

void Tutorial::Draw()
{

	Sprite::PreDraw();

	tutorialSprite_->Draw();

	Sprite::PostDraw();
	
	
	// フェード
	fade_->Draw();
}

Tutorial::~Tutorial()
{
	delete tutorialSprite_;
	// フェード
	delete fade_;
}
