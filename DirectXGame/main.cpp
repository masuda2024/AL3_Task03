#include <Windows.h>
#include"KamataEngine.h"
using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{



	DirectXCommon* dxCommon = DirectXCommon::GetInstance();








	KamataEngine::Initialize(L"LE2D_21_マスダ_アキヒロ_AL3");

	while (true)
	{
		if (KamataEngine::Update())
		{
			break;
		}



		dxCommon->PreDraw();

		dxCommon->PostDraw();







	}

	KamataEngine::Finalize();

	return 0;
}
