#include "GameScene.h"
#include "CameraController.h"
#include "Enemy.h"
#include "Fade.h"
#include "MapChipField.h"
#include "MyMath.h"
#include "Player.h"
#include "Skydome.h"
#include "Goal.h"
using namespace KamataEngine;

// 初期化
void GameScene::Initialize() 
{
	
	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	sprite_ = Sprite::Create(textureHandle_, {100, 50});


	// Springin 戦闘-4 爆発1
	Explosion_ = Audio::GetInstance()->LoadWave("Sounds/Explosion_1.mp3");
	
	cube_ = Model::CreateFromOBJ("block");

	// マップチップフィールドの生成
	mapChipField_ = new MapChipField;

	// ブロックを開く
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	// 表示ブロックの生成
	GenerateBlocks();

	#pragma region プレイヤー


	// 3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("Player003", true);

	// playerHPのスプライト
	playerhpHandle_ = TextureManager::Load("hp.png");
	playerhpSprite_ = KamataEngine::Sprite::Create(playerhpHandle_, {0, 0});
	
	// パーティクルの3Dモデルデータの生成
	modelParticle_ = Model::CreateFromOBJ("deathParticle", true);

	// 自キャラの生成
	player_ = new Player();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	player_->Initialize(modelPlayer_, &camera_, playerPosition);
	player_->SetMapChipField(mapChipField_); // 自キャラの生成と初期化

	
	// パーティクル
	deathParticles_ = new DeathParticle();
	deathParticles_->Initialize(modelParticle_, &camera_, playerPosition);


	#pragma endregion


	#pragma region 敵


	modelEnemy_ = Model::CreateFromOBJ("r", true);

	// 敵の生成
	// enemy_ = new Enemy();
	for (int32_t i = 0; i < 5; i++) 
	{
		for (int32_t j = 0; j < 3; j++)
		{
			Enemy* newEnemy = new Enemy();
			KamataEngine::Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(32 + i * 20, 18 - j * 3);
			newEnemy->Initialize(modelEnemy_, &camera_, enemyPosition);

			enemies_.push_back(newEnemy);
		}
	}

	#pragma endregion

	#pragma region ゴール


	// ゴール
	modelGoal_ = Model::CreateFromOBJ("goal", true);
	// ゴールの生成
	goal_ = new Goal();
	// ゴールの座標
	Vector3 goalPosition = mapChipField_->GetMapChipPositionByIndex(80, 18);
	goal_->Initialize(modelGoal_, &camera_, goalPosition);
	goal_->SetMapChipField(mapChipField_);



	#pragma endregion




	
	// 3Dモデルの生成
	modelskydome_ = Model::CreateFromOBJ("skydome", true);
	
	// スカイドームの生成
	skydome_ = new Skydome();

	// スカイドームの初期化
	skydome_->Initialize(modelskydome_, textureHandle_, &camera_);





	
	


	
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();


	// デバックカメラの生成
	debugCamera_ = new DebugCamera(100, 200);


	// カメラの初期化
	camera_.Initialize();
	// カメラコントローラの初期化
	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);

	
	// フェーズインから開始
	phase_ = Phase::kFadeIn;

	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

// ブロック
void GameScene::GenerateBlocks() 
{
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
	// const float kBlockWidth = 2.0f;
	// const float kBlockHeight = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	////キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++)
	{
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++)
	{
		for (uint32_t j = 0; j < numBlockHorizontal; j++)
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) // 1マス分にボックスの形にしたいなら(i + j)にする
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

// デストラクタ
GameScene::~GameScene() 
{
	delete sprite_;

	delete skydome_;

	delete player_;

	delete deathParticles_;

	// フェード
	delete fade_;

	for (Enemy* enemy : enemies_) 
	{
		delete enemy;
	}

	delete goal_;

	// delete enemy_;

	// 3Dモデルデータの解放
	delete model_;

	// デバッグカメラの解放
	delete debugCamera_;

	// マップチップフィールドの解放
	delete mapChipField_;

	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) 
		{
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

// 更新
void GameScene::Update()
{

	// フェード
	fade_->Update();

	// プレイヤーHP
	float hpRatio = (float)player_->GetHP() / (float)player_->GetMaxHP();
	hpRatio = std::clamp(hpRatio, 0.0f, 1.0f);
	playerhpSprite_->SetSize({hpRatio * 200.0f, 20.0f}); // 例：幅200px、高さ20px
	playerhpSprite_->SetPosition({0, 0});                // 左上に表示



	switch (phase_) 
	{
	case Phase::kPlay:

		// 全ての当たり判定
		CheckAllCollisions();

		// ゲームプレイフェーズの処理
		if (player_->IsDead() == true)
		{
			Audio::GetInstance()->PlayWave(Explosion_);
			// デス演出フェーズに切り替え
			phase_ = Phase::kDeath;

			// 自キャラの座標を取得
			const KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();

			// パーティクル
			deathParticles_ = new DeathParticle();
			deathParticles_->Initialize(modelParticle_, &camera_, deathParticlesPosition);
		}
		else if (player_->IsGoal() == true) 
		{
			phase_ = Phase::kClear;
			// 自キャラの座標を取得
			const KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();
		}
		break;

	case Phase::kDeath:
		// デス演出フェーズの処理

		// デスパーティクルの更新
		deathParticles_->Update();
		if (deathParticles_ && deathParticles_->isFinished_)
		{
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}

		/*
		if ("deathParticle", true)
		{
		    // フェードアウト開始
		    phase_ = Phase::kFadeOut;
		    fade_->Start(Fade::Status::FadeOut, 1.0f);
		    deathParticles_->Update();
		    finished_ = deathParticles_->isFinished_;
		}
		*/

		break;

		case Phase::kClear:



		// フェードアウト開始
	    phase_ = Phase::kFadeOut2;
	    fade_->Start(Fade::Status::FadeOut, 1.0f);

		break;
	case Phase::kFadeIn:
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			phase_ = Phase::kPlay;
		}
		break;
	case Phase::kFadeOut:
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			finished1_ = true;
		}
		break;
	case Phase::kFadeOut2:
		// フェード
		fade_->Update();
		if (fade_->IsFinished2()) 
		{
			finished2_ = true;
		}
		break;


	}

	// 自キャラの更新
	player_->Update();

	// 天球の更新
	skydome_->Update();

	// 敵の更新
	// enemy_->Update();
	for (Enemy* enemy : enemies_)
	{
		enemy->Update();
	}

	//ゴールの更新
	goal_->Update();

	// カメラコントローラーの更新
	cameraController_->Update();

	// 行列を定義バッファに転送
	// worldTransform_.TransferMatrix();

	// debugCamera_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0))
	{
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

#endif // _DEBUG

	if (isDebugCameraActive_)
	{
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else 
	{
		camera_.matView = cameraController_->GetViewProjection().matView;
		camera_.matProjection = cameraController_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の更新と転送
		camera_.TransferMatrix();
	}
	// ブロックの更新
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{

			if (!worldTransformBlock)
			{
				continue;
			}

			// アフィン変換行列の作成

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			////定数バッファに転送する

			worldTransformBlock->TransferMatrix();
		}
	}
}

// 描画
void GameScene::Draw() 
{

	// DirectXCommonインスタンスの取得
	//DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw();

	// 3Dモデル描画
	//
	//model_->Draw(worldTransform_, camera_, textureHandle_);

	// 自キャラの描画
	if (phase_ == Phase::kPlay || phase_ == Phase::kFadeIn)
	{
		player_->Draw();
	}

	// パーティクル
	if ("deathParticle", true)
	{
		deathParticles_->Draw();
	}

	// 敵の描画
	// enemy_->Draw();
	for (Enemy* enemy : enemies_)
	{
		enemy->Draw();
	}


	

	//ゴールの描画
	goal_->Draw();




	// ブロックの描画
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) 
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) 
		{
			if (!worldTransformBlock) 
			{
				continue;
			}
			cube_->Draw(*worldTransformBlock, camera_);
		}
	}

	skydome_->Draw();

	// 3Dモデル描画前処理
	Model::PostDraw(); // プログラムの終了

	// HPバーの描画
	Sprite::PreDraw();
	playerhpSprite_->Draw();
	Sprite::PostDraw();


	// フェード
	fade_->Draw();
}

// 衝突判定
void GameScene::CheckAllCollisions() 
{
	// 判定対象1と2の座標

	// aabb1 プレイヤー

	// aabb2 敵

	// aabb3 ゴール

	AABB aabb1, aabb2;
	
#pragma region 自キャラと敵キャラの当たり判定

	

	aabb1 = player_->GetAABB();
	
	// 自キャラと敵全ての当たり判定
	for (Enemy* enemy : enemies_)
	{
		// 敵弾の座標
		aabb2 = enemy->GetAABB();

		// AABB同士の交差判定
		if (IsCollition(aabb1, aabb2)) 
		{
			// 自キャラの衝突時関数を呼び出す
			player_->OnCollition(enemy);
			// 敵の衝突時関数を呼び出す
			enemy->OnCollition(player_);
		}
	}
#pragma endregion

	

#pragma region プレイヤーとゴールの当たり判定
	AABB2 aabb4, aabb3;
	aabb4 = player_->GetAABB2();
	aabb3 = goal_->GetAABB2();
	/*
    if (goal_) // nullチェック（推奨）
	{
		aabb3 = goal_->GetAABB2();

		if (IsCollitionGoal(aabb4, aabb3)) 
		{
			player_->OnCollitionGoal(goal_);
			goal_->OnCollitionGoal(player_);
		}
	}*/
	if (IsCollitionGoal(aabb4, aabb3))
	{
		player_->OnCollitionGoal(goal_);
		goal_->OnCollitionGoal(player_);
	}


#pragma endregion




}

// フェーズ
void GameScene::ChangePhase() 
{

	switch (phase_) 
	{
	case Phase::kPlay:
		// ゲームプレイフェーズの処理

		if (player_->IsDead() == true)
		{
			// デス演出フェーズに切り替え
			phase_ = Phase::kDeath;

			// 自キャラの座標を取得
			const KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();

			// パーティクル
			deathParticles_ = new DeathParticle();
			deathParticles_->Initialize(modelParticle_, &camera_, deathParticlesPosition);
		}
		else if (player_->IsGoal() == true)
		{
			finished2_ = true;
			phase_ = Phase::kClear;
			// 自キャラの座標を取得
			//const KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();
		}

		break;

	case Phase::kDeath:
		// デス演出フェーズの処理

		if (deathParticles_)
		{
			// シーン終了
			finished1_ = true;
		}

		break;

	case Phase::kClear:
		
		finished2_ = true;

		break;
	}
}
