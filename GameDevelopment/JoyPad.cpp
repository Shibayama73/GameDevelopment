#include "JoyPad.h"

//	���o�����W���C�p�b�h�̏����i�[���邽�߂̍\����
struct  SearchJoyPadSet
{
	//DirectInput
	LPDIRECTINPUT8 dinput;
	//�e�R���g���[�����̃f�o�C�X
	std::vector<LPDIRECTINPUTDEVICE8> joyPadDev;

	//�R���X�g���N�^
	SearchJoyPadSet() {
		dinput = NULL;
	}
};

////	���o�������̓I�u�W�F�N�g1���ɌĂ΂��
//BOOL CALLBACK EnumObjectCallBack(LPCDIDEVICEOBJECTINSTANCE pInstance, void* pvRef)
//{
//	//	��������
//	return DIENUM_CONTINUE;
//}

//	���o�����W���C�p�b�h���ɌĂ΂��
BOOL CALLBACK EnumJoyPadCallBack(LPCDIDEVICEINSTANCE lpddi, void* pvRef)
{
	//����
	HRESULT ret;

	//	����������e
	SearchJoyPadSet* param = (SearchJoyPadSet*)pvRef;
	//SearchJoyPadSet* param = reinterpret_cast<SearchJoyPadSet*>(pvRef);

	//	�f�o�C�X�̃|�C���^
	LPDIRECTINPUTDEVICE8 dev;

	//	�R���g���[�����Ƀf�o�C�X�𐶐�
	ret = param->dinput->CreateDevice(lpddi->guidInstance, &dev, NULL);


	//	���s�����Ƃ�
	if (ret != DI_OK) {
		goto NEXT;
	}

	//	�f�[�^�`���̐ݒ�(�g���@�\�t���W���C�X�e�B�b�N)
	ret = dev->SetDataFormat(&c_dfDIJoystick2);

	//	���s�����Ƃ�
	if (ret != DI_OK) {
		goto NEXT;
	}

	//	�z��ɒǉ�
	param->joyPadDev.push_back(dev);


NEXT:
	//	��������
	return DIENUM_CONTINUE;
}

JoyPad::JoyPad()
{
}

JoyPad::~JoyPad()
{
	//	�z��ɂ���f�o�C�X���J��
	std::vector<JpyPadSet>::iterator it;
	for (it = m_joyPadSet.begin(); it != m_joyPadSet.end(); it++)
	{
		//NULL�̂Ƃ��͌Ăяo����Ȃ�
		SafeRelease(it->inputDevice);
	}
}

bool JoyPad::Initialize(HWND window)
{
	//����
	HRESULT ret;

	//DirectInput�̍쐬
	ret = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);

	//	���s�����Ƃ�
	if (ret != DI_OK) {
		return false;
	}

	//	�󂯓n���p�p�����[�^
	SearchJoyPadSet param;
	param.dinput = m_pDInput;

	//	���p�\�ȃf�o�C�X��񋓂���(�R���g���[���ǂݎ��)
	ret = m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyPadCallBack, &param, DIEDFL_ATTACHEDONLY);


	//	�f�o�C�X�z��
	std::vector<LPDIRECTINPUTDEVICE8>::iterator it;
	for (it = param.joyPadDev.begin(); it != param.joyPadDev.end(); it++)
	{
		LPDIRECTINPUTDEVICE8 dev = *it;

		//	�A�v�����A�N�e�B�u���̓f�o�C�X��r���A�N�Z�X�ɐݒ�
		ret = dev->SetCooperativeLevel(window, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		//	���s�����Ƃ�
		if (ret != DI_OK) {
			continue;
		}

		//	�A�N�Z�X����v��
		ret = dev->Acquire();

		//	���s�����Ƃ�
		if (ret != DI_OK) {
			continue;
		}

		//	�f�o�C�X1���̏��
		JpyPadSet initPad;
		initPad.inputDevice = dev;

		//	����z��ɒǉ�
		m_joyPadSet.push_back(initPad);


	}

	return true;
}

void JoyPad::Update()
{
	//	�S�Ẵf�o�C�X�ɂ��ď�������
	std::vector<JpyPadSet>::iterator it;
	for (it = m_joyPadSet.begin(); it != m_joyPadSet.end(); it++)
	{
		HRESULT ret;
		//	�����X�V����
		it->inputDevice->Poll();
		if (ret != DI_OK) {
			//	�A�N�Z�X����v��
			ret = it->inputDevice->Acquire();
			while (ret==DIERR_INPUTLOST)
			{
				//	�A�N�Z�X����v��
				ret = it->inputDevice->Acquire();
			}
		}

		//�O�t���[���̓��͏����o�b�N�A�b�v
		it->joypadOld = it->joypad;
		//	���͏����擾
		ret = it->inputDevice->GetDeviceState(sizeof(DIJOYSTATE2), &it->joypad);

		//	���s�����Ƃ�
		if (ret != DI_OK) {
			continue;
		}

		if ((BYTE)(it->joypad.rgbButtons[0] & 0x80 == 0))
		{
			//	�{�^����������Ă���

		}

	}
}
