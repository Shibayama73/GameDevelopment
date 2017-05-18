/// <summary>
/// コントローラを扱うクラス
/// </summary>
#pragma once

//DirectInputバージョンを指定
#define DIRECTINPUT_VERSION 0x800

#include <dinput.h>
#include <vector>

template<typename T>
void SafeRelease(T*& p)
{
	if (p)
	{
		p->Release();
		p = NULL;
	}
}

class JoyPad
{
public:
	JoyPad();	//	コンストラクタ
	~JoyPad();	//	デストラクタ

	bool Initialize(HWND window);	//初期化
	void Update();					//更新


private:

	//	ジョイパッド1個分の情報
	struct  JpyPadSet
	{
		//	コンストラクタ
		JpyPadSet() {
			inputDevice = NULL;
		}

		//	ジョイパッド
		LPDIRECTINPUTDEVICE8 inputDevice;
		//	入力情報
		DIJOYSTATE2 joypad;
		//	前回の入力情報
		DIJOYSTATE2 joypadOld;

	};

	//DirectInputインスタンス
	LPDIRECTINPUT8 m_pDInput;

	//	ジョイパッド配列
	std::vector<JpyPadSet> m_joyPadSet;


};