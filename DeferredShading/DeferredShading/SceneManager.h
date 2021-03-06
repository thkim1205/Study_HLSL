#pragma once

#include "winerror.h"

#include "D3D11.h"
#include "SDKmesh.h"


class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	HRESULT Init();
	void    Deinit();

	void RenderScene(ID3D11DeviceContext* pd3dImmediateContext);

private:
	// Scene meshes
	CDXUTSDKMesh m_MeshOpqaue;
	CDXUTSDKMesh m_MeshSphere;

	// Scene meshes shader constant buffers
	ID3D11Buffer* m_pSceneVertexShaderCB;
	ID3D11Buffer* m_pScenePixelShaderCB;

	// Depth prepass vertex shader
	ID3D11InputLayout*  m_pSceneVSLayout;
	ID3D11VertexShader* m_pSceneVertexShader;
	ID3D11PixelShader*  m_pScenePixelShader;
};