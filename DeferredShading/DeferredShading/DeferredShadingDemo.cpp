#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTmisc.h"
#include "DXUTcamera.h"
#include "DXUTsettingsdlg.h"

#include "SDKmisc.h"
#include "SDKmesh.h"

#include "resource.h"

#include "SceneManager.h"
#include "LightManager.h"
#include "GBuffer.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
float g_fCamFOV = D3DX_PI / 4;

CFirstPersonCamera			g_Camera;					// A first person camera
CDXUTDialogResourceManager	g_DialogResourceManager;	// Manager for shared resource of dialogs
CD3DSettingsDlg				g_SettingDlg;				// Device setting dialog		
CDXUTDialog					g_HUD;						// dialog for standard controls
CDXUTDialog					g_SampleUI;					// dialog for sample specific controls

CDXUTTextHelper*			g_pTextHelper = NULL;

// Direct3D 9 resource
extern ID3DXFont*			g_pFont9;
extern ID3DXSprite*			g_pSprite9;

// Direct3D 11 resources
ID3D11SamplerState*			g_pSamplerPoint  = NULL;
ID3D11SamplerState*			g_pSamplerLinear = NULL;
ID3D11VertexShader*			g_pGBufferVisVertexShader = NULL;
ID3D11PixelShader*			g_pGBufferVisPixelShader  = NULL;

ID3D11Device* g_pD3D11Device;

// Global systems
CSceneManager g_SceneManager;
CLightManager g_LightManager;
CGBuffer	  g_GBuffer;

// Test








