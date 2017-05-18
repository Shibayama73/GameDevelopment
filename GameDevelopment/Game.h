//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "ADX2Le.h"
#include <GamePad.h>
#include "JoyPad.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();
	virtual ~Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;		//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureAttack;		//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureShield;		//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;	//スプライト表示スクリーン座標
	DirectX::SimpleMath::Vector2 m_origin;		//スプライトの原点

	std::unique_ptr<DirectX::Keyboard> m_keyboard;	//キーボード
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;			//キーボードのトラッカー

	bool m_showTexture;	//表示
	bool m_showNum;
	bool m_showRelease;

	bool m_attackSow;
	bool m_shieldShow;
	bool m_modeState;	//モード状態

	std::unique_ptr<DirectX::Mouse> m_mouse;	//マウス
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

	std::unique_ptr<DirectX::GamePad> m_gamePad;	//ゲームパッド
	DirectX::GamePad::ButtonStateTracker m_tracker;

	//	ジョイパッド
	std::unique_ptr<JoyPad> m_pJoyPad;


};
