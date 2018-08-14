#include "DXUT.h"
#include "DXUTcamera.h"
#include "GBuffer.h"

extern ID3D11Device*      g_pD3D11Device;
extern CFirstPersonCamera g_Camera;

#pragma pack(push, 1)
struct CB_GBUFFER_UNPACK
{
	D3DXVECTOR4 PerspectiveValues;
	D3DXMATRIX  ViewInv;
};
#pragma pack(pop)

CGBuffer::CGBuffer() : m_pGBufferUnpackCB(NULL),
					   m_pDepthStencilRT(NULL), m_pColorSpecIntensityRT(NULL), m_pNormalRT(NULL), m_pSpecPowerRT(NULL),
					   m_pDepthStencilDSV(NULL), m_pDepthStencilReadOnlyDSV(NULL),
					   m_pColorSpecIntensityRTV(NULL), m_pNormalRTV(NULL), m_pSpecPowerRTV(NULL),
					   m_pDepthStencilSRV(NULL),
					   m_pColorSpecIntensitySRV(NULL), m_pNormalSRV(NULL), m_pSpecPowerSRV(NULL),
					   m_pDepthStencilState(NULL)
{
}

CGBuffer::~CGBuffer()
{
}

HRESULT CGBuffer::Init(UINT width, UINT height)
{
	HRESULT hr;

	Deinit();		// Clear the previous targets

	// Texture formats
	static const DXGI_FORMAT depthStencilRTFormat       = DXGI_FORMAT_R24G8_TYPELESS;
	static const DXGI_FORMAT colorSpecIntensityRTFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalRTFormat    = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowerRTFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Render view formats
	static const DXGI_FORMAT depthStencilViewFormat         = DXGI_FORMAT_D24_UNORM_S8_UINT;
	static const DXGI_FORMAT colorSpecIntensityRTViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalRTViewFormat             = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowerRTViewFormat          = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Resource view formats
	static const DXGI_FORMAT depthStencilResourceViewFormat       = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	static const DXGI_FORMAT colorSpecIntensityResourceViewFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT normalResourceViewFormat             = DXGI_FORMAT_R11G11B10_FLOAT;
	static const DXGI_FORMAT specPowerResourceViewFormat          = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Allocate the depth stencil target
	D3D11_TEXTURE2D_DESC dtd =
	{
		width, height,
		1,						// UINT MipLevels;
		1,						// UINT ArraySize;
		DXGI_FORMAT_UNKNOWN,	// DXGI_FORMAT Format;
		1,						// DXGI_SAMPLE_DESC SampleDesc;
		0,
		D3D11_USAGE_DEFAULT,								   // D3D11_USAGE Usage;
		D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE, // UINT Bind Flags;
		0,		// UINT CPUAccessFlags;
		0		// UINT MiscFlags;
	};

	dtd.Format = depthStencilRTFormat;
	V_RETURN( g_pD3D11Device->CreateTexture2D( &dtd, 
											   NULL, 
											   &m_pDepthStencilRT ) );
	DXUT_SetDebugName(m_pDepthStencilRT, "GBuffer - Depth Stencil");

	// Allocate the base color with specular intensity target
	dtd.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	dtd.Format    = colorSpecIntensityRTFormat;
	V_RETURN( g_pD3D11Device->CreateTexture2D( &dtd,
											   NULL,
											   &m_pColorSpecIntensityRT ) );
	DXUT_SetDebugName( m_pColorSpecIntensityRT, "GBuffer - Base Color Specular Intensity" );

	// Allocate the normal target
	dtd.Format = normalRTFormat;
	V_RETURN( g_pD3D11Device->CreateTexture2D( &dtd,
											   NULL,
											   &m_pNormalRT ) );
	DXUT_SetDebugName( m_pNormalRT, "GBuffer - Normal" );

	// Allocate the specular power target
	dtd.Format = specPowerRTFormat;
	V_RETURN( g_pD3D11Device->CreateTexture2D( &dtd,
											   NULL,
											   &m_pSpecPowerRT ) );
	DXUT_SetDebugName(m_pSpecPowerRT, "GBuffer - Specular Power");

	// Create the render target views
	// 1. Depth-Stencil target view
	// 2. Render target view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd =
	{
		depthStencilViewFormat,
		D3D11_DSV_DIMENSION_TEXTURE2D
	};
	V_RETURN(g_pD3D11Device->CreateDepthStencilView(m_pDepthStencilRT, &dsvd, &m_pDepthStencilDSV));
	DXUT_SetDebugName(m_pDepthStencilDSV, "GBuffer - Depth Stencil DSV");

	D3D11_RENDER_TARGET_VIEW_DESC rtvd =
	{
		colorSpecIntensityRTViewFormat,
		D3D11_RTV_DIMENSION_TEXTURE2D
	};
	V_RETURN(g_pD3D11Device->CreateRenderTargetView(m_pColorSpecIntensityRT, &rtvd, &m_pColorSpecIntensityRTV));
	DXUT_SetDebugName(m_pColorSpecIntensityRTV, "GBuffer - Color Spec Intensity RTV");




}

void CGBuffer::Deinit()
{

}

