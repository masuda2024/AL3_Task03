#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;

// DirectXCommonインスタンスの取得
DirectXCommon* dxCommon = DirectXCommon::GetInstance();

enum class Scene 
{
	kUnknown = 0,
	kTitle,
	kGame,
};
Scene scene = Scene::kUnknown;

void ChangeScene();
void UpdateScene();
void DrawScene();
// タイトルシーンの生成
TitleScene* titleScene = nullptr;
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
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();
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

			// タイトルシーンの生成
			titleScene = new TitleScene;
			// タイトルシーンの初期化
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
	case Scene::kGame:
		gameScene->Draw();
		break;
	}
}
