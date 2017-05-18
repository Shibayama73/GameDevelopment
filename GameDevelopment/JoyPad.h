/// <summary>
/// �R���g���[���������N���X
/// </summary>
#pragma once

//DirectInput�o�[�W�������w��
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
	JoyPad();	//	�R���X�g���N�^
	~JoyPad();	//	�f�X�g���N�^

	bool Initialize(HWND window);	//������
	void Update();					//�X�V


private:

	//	�W���C�p�b�h1���̏��
	struct  JpyPadSet
	{
		//	�R���X�g���N�^
		JpyPadSet() {
			inputDevice = NULL;
		}

		//	�W���C�p�b�h
		LPDIRECTINPUTDEVICE8 inputDevice;
		//	���͏��
		DIJOYSTATE2 joypad;
		//	�O��̓��͏��
		DIJOYSTATE2 joypadOld;

	};

	//DirectInput�C���X�^���X
	LPDIRECTINPUT8 m_pDInput;

	//	�W���C�p�b�h�z��
	std::vector<JpyPadSet> m_joyPadSet;


};