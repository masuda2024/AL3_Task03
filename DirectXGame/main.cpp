#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include"Tutorial.h"
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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	KamataEngine::Initialize(L"LE2D_21_マスダ_アキヒロ_AL3");

	/**/

	// 最初のシーンの初期化
	scene = Scene::kTitle;
	titleScene = new TitleScene;

	// タイトルシーンの初期化
	titleScene->Initialize();


	//チュートリアルシーンの初期化
	tutorial->Initialize();
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
	}
}

void ChangeScene()
{

	switch (scene)
	{
	case Scene::kTitle:
		if (titleScene->IsFinished())
		{
			// シーンの変更
			scene = Scene::kGame;
			// シーンの変更
			scene = Scene::kTutorial;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();

			
			// 新シーンの生成と初期化
			tutorial = new Tutorial();
			tutorial->Initialize();
		}
		break;
	case Scene::kTutorial:
		if (tutorial->IsFinished())
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

		if (gameScene->IsFinished())
		{
			// シーンの変更
			scene = Scene::kTitle;

			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;

			// タイトルシーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}

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
	}
}
