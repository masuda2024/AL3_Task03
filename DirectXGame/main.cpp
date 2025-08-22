#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include"Tutorial.h"
#include"GameOver.h"
//#include"GameClear.h"

#include <Windows.h>

using namespace KamataEngine;

// DirectXCommonインスタンスの取得
DirectXCommon* dxCommon = DirectXCommon::GetInstance();

enum class Scene 
{
	kUnknown = 0,
	kTitle,
	kTutorial,
	kGame,
	kGameOver,
	//kGameClear,
};
Scene scene = Scene::kUnknown;

void ChangeScene();
void UpdateScene();
void DrawScene();
// タイトルシーンの生成
TitleScene* titleScene = nullptr;
//チュートリアルシーンの生成
Tutorial* tutorial = nullptr;
// ゲームシーンのインスタンス生成
GameScene* gameScene = nullptr;

// ゲームオーバーシーンの生成
GameOver* gameover = nullptr;
// ゲームクリアシーンの生成
//GameClear* gameclear = nullptr;




// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	KamataEngine::Initialize(L"LE2D_21_マスダ_アキヒロ_AL3");

	

	// 最初のシーンの初期化
	//タイトルシーンから開始
	scene = Scene::kTitle;
	
	
	// タイトルシーンの初期化
	titleScene = new TitleScene;
	titleScene->Initialize();

	// チュートリアルシーンの初期化
	tutorial = new Tutorial;
	tutorial->Initialize();
	
	//ゲームオーバーシーンの初期化(準備)
	gameover = new GameOver;
	gameover->Initialize();

	// ゲームクリアシーンの初期化(準備)
	// gameclear = new GameClear;
	// gameclear->Initialize();
	
	
	/*
	//ゲームシーンの初期化
	gameScene->Initialize();
	*/

	while (true) 
	{
		// エンジンの更新
		if (KamataEngine::Update()) 
		{
			break;
		}

		// シーン切り替え
		ChangeScene();
		// 現在シーン更新
		UpdateScene();

		// タイトルシーンの更新
		// titleScene->Update();
		// ゲームシーンの更新
		// ameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// タイトルシーンの更新
		// titleScene->Draw();
		// ゲームシーンの描画
		// gameScene->Draw();

		// 現在シーンの描画
		DrawScene();

		// 描画終了
		dxCommon->PostDraw();
	}

	// タイトルシーンの解放
	delete titleScene;

	//チュートリアルシーンの解放
	delete tutorial;

	// ゲームシーンの解放
	delete gameScene;

	// ゲームオーバーシーンの解放
	delete gameover;

	// ゲームクリアシーンの解放
	//delete gameclear;


	// nullptrの代入

	gameScene = nullptr;

	KamataEngine::Finalize();

	return 0;
}

void UpdateScene() 
{
	switch (scene)
	{
	case Scene::kTitle:
		titleScene->Update();
		break;
	
	case Scene::kTutorial:
		tutorial->Update();
		break;
	
	case Scene::kGame:
		gameScene->Update();
		break;
		
	case Scene::kGameOver:
		gameover->Update();
		break;
/*
	case Scene::kGameClear:
		gameclear->Update();
		break;
		*/
	}
}

void ChangeScene()
{

	switch (scene)
	{
	case Scene::kTitle:


		// ゲームシーンへ
		if (titleScene->IsFinished())
		{
			// シーンの変更
			scene = Scene::kGame;
			
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();
		} //チュートリアルシーンへ
		else if (titleScene->IsFinished2())
		{
			// シーンの変更
			scene = Scene::kTutorial;

			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;

			// 新シーンの生成と初期化
			tutorial = new Tutorial();
			tutorial->Initialize();
		}


		break;
	case Scene::kTutorial:

		if (tutorial->IsFinishedTutorial())
		{
			// シーンの変更
			scene = Scene::kTitle;
			
			// 旧シーンの解放
			delete tutorial;
			tutorial = nullptr;
			
			// タイトルシーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	case Scene::kGame:
		
		//ゲームシーンで敵に当たったら
		if (gameScene->IsFinishedGame1())
		{
			// シーンの変更
			scene = Scene::kGameOver;

			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;

			// タイトルシーンの生成と初期化
			//titleScene = new TitleScene;
			//titleScene->Initialize();
		
			//ゲームオーバーシーンへ
		    gameover = new GameOver;
			gameover->Initialize();
		}

		/*
		else if(gameScene->IsFinishedGame2())
		{
		// シーンの変更
		    scene = Scene::kGameClear;

		    // 旧シーンの解放
		    delete gameScene;
		    gameScene = nullptr;

		    
			//ゲームクリアシーンへ
		    gameclear = new GameClear;
		    gameclear->Initialize();
		}
		
		
		
		
		
		*/



		break;

     
    case Scene::kGameOver:
		
		if (gameover->IsFinishedGameOver())
		{
		    // シーンの変更
		    scene = Scene::kTitle;

		    // 旧シーンの解放
		    delete gameover;
		    gameover = nullptr;

		    // タイトルシーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;


/*
	case Scene::kGameClear:
		if (gameover->IsFinishedOver())
		{
		    // シーンの変更
		    scene = Scene::kTitle;

		    // 旧シーンの解放
		    delete gameclear;
		    gameclear = nullptr;

		    // タイトルシーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
     */






	}//switch (scene)
}//void ChangeScene()

void DrawScene()
{
	switch (scene) 
	{
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kTutorial:
		tutorial->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
		/*
		case Scene::kGameOver:
		gameover->Draw();
		break
		case Scene::kGameClear:
		gameclear->Draw();
		break
		
		
		*/






	}
}
