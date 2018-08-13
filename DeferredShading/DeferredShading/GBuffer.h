#pragma once

#include <winbase.h>
#include "D3D11.h"


class CGBuffer
{
public:
	CGBuffer();
	~CGBuffer();

	HRESULT Init(UINT width, UINT height);
	void Deinit();

	void PreRender       (ID3D11DeviceContext* pD3DImmediateContext);
	void PostRender      (ID3D11DeviceContext* pD3DImmediateContext);
	void PrepareForUnpack(ID3D11DeviceContext* pD3DImmediateContext);

	ID3D11Texture2D* GetColorTexture() { return m_pColorSpecIntensityRT; }

	ID3D11DepthStencilView* GetDepthDSV() { return m_pDepthStencilDSV; }
	ID3D11DepthStencilView* GetDepthReadOnlyDSV() { return m_pDepthStencilReadOnlyDSV; }

	ID3D11ShaderResourceView* GetDepthView()     { return m_pDepthStencilSRV; }
	ID3D11ShaderResourceView* GetColorView()     { return m_pColorSpecIntensitySRV; }
	ID3D11ShaderResourceView* GetNormalView()    { return m_pNormalSRV; }
	ID3D11ShaderResourceView* GetSpecPowerView() { return m_pSpecPowerSRV; }


private:
	ID3D11Buffer * m_pGBufferUnpackCB;

	// GBuffer textures
	ID3D11Texture2D* m_pDepthStencilRT;
	ID3D11Texture2D* m_pColorSpecIntensityRT;
	ID3D11Texture2D* m_pNormalRT;
	ID3D11Texture2D* m_pSpecPowerRT;

	// GBuffer render views
	ID3D11DepthStencilView* m_pDepthStencilDSV;
	ID3D11DepthStencilView* m_pDepthStencilReadOnlyDSV;
	ID3D11RenderTargetView* m_pColorSpecIntensityRTV;
	ID3D11RenderTargetView* m_pNormalRTV;
	ID3D11RenderTargetView* m_pSpecPowerRTV;

	// GBuffer shader resource views
	ID3D11ShaderResourceView* m_pDepthStencilSRV;
	ID3D11ShaderResourceView* m_pColorSpecIntensitySRV;
	ID3D11ShaderResourceView* m_pNormalSRV;
	ID3D11ShaderResourceView* m_pSpecPowerSRV;

	ID3D11DepthStencilState *m_pDepthStencilState;
};