#pragma once

#include "winerror.h"
#include <vector>

#include "d3dx9math.h"

#include "d3d11.h"

class CLightManager
{
public:
	
	CLightManager();
	~CLightManager();

	HRESULT Init();
	void    Deinit();

	void Update();

	// Set the ambient values
	void SetAmbient(const D3DXVECTOR3& aAmbientLowerColor, const D3DXVECTOR3& aAmbientUpperColor)
	{
		m_vAmbientLowerColor = aAmbientLowerColor;
		m_vAmbientUpperColor = aAmbientUpperColor;
	}

	// Set the directional light values
	void SetDirectionalLightParams(const D3DXVECTOR3& aDirection, const D3DXVECTOR3& aColor)
	{
		D3DXVec3Normalize(&m_vDirectionalLightDir, &aDirection);
		m_vDirectionalLightColor = aColor;
	}

	// Clear the lights from the previous frame
	void ClearLights()
	{
		m_ActiveLights.clear();
	}

	// Add a single point light
	void AddPointLight(const D3DXVECTOR3& aPointPosition,
					   float aPointRange,
					   const D3DXVECTOR3& aPointColor)
	{
		LIGHT pointLight;

		pointLight.eLightType = LT_POINT;
		pointLight.vPosition  = aPointPosition;
		pointLight.vColor     = aPointColor;

		m_ActiveLights.push_back(pointLight);
	}

	// Add a single spot light
	void AddSpotLight(const D3DXVECTOR3& aSpotPosition, const D3DXVECTOR3& aSpotDirection,
					  float aSpotRange,
					  float aSpotOuterAngle, float aSpotInnerAngle,
					  const D3DXVECTOR3& aSpotColor)
	{
		LIGHT spotLight;

		spotLight.eLightType = LT_SPOT;
		spotLight.vPosition  = aSpotPosition;
		spotLight.vDirection = aSpotDirection;
		spotLight.vColor     = aSpotColor;
		spotLight.fRange     = aSpotRange;
		spotLight.fInnerAngle = aSpotInnerAngle;
		spotLight.fOuterAngle = aSpotOuterAngle;

		m_ActiveLights.push_back(spotLight);
	}

	// Add a single capsule light
	void AddCapsuleLight(const D3DXVECTOR3& aCapsulePosition, const D3DXVECTOR3& aCapsuleDirection,
						 float aCapsuleRange, float aCapsuleLength,
						 const D3DXVECTOR3& aCapsuleColor)
	{
		LIGHT capsuleLight;

		capsuleLight.eLightType = LT_CAPSULE;
		capsuleLight.vPosition  = aCapsulePosition;
		capsuleLight.vDirection = aCapsuleDirection;
		capsuleLight.vColor     = aCapsuleColor;
		capsuleLight.fLength    = aCapsuleLength;
		capsuleLight.fRange     = aCapsuleRange;

		m_ActiveLights.push_back(capsuleLight);
	}


private:

	typedef enum
	{
		LT_POINT = 0,
		LT_SPOT,
		LT_CAPSULE,
	} LIGHT_TYPE;

	// Light storage
	typedef struct
	{
		LIGHT_TYPE  eLightType;
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vDirection;
		D3DXVECTOR3 vColor;
		float fRange;
		float fLength;
		float fOuterAngle;
		float fInnerAngle;
	} LIGHT;
	
	// Ambient light information
	D3DXVECTOR3 m_vAmbientLowerColor;
	D3DXVECTOR3 m_vAmbientUpperColor;

	// Directional light shaders & buffer
	ID3D11VertexShader* m_pDirectionalLightVS;
	ID3D11PixelShader*  m_pDirectionalLightPS;
	ID3D11Buffer*       m_pDirectionalLightCB;

	// Directional light information
	D3DXVECTOR3 m_vDirectionalLightDir;
	D3DXVECTOR3 m_vDirectionalLightColor;

	// Linked list with the active lights
	std::vector<LIGHT> m_ActiveLights;

	// Do the directional light calculation
	void CalcDirectionalLight(ID3D11DeviceContext* pd3dImmediateContext);

	// Depth state with no writes and stencil test on
	ID3D11DepthStencilState* m_pNoDepthWriteLessStencilMaskState;
};

class LightManager
{
public:
	LightManager();
	~LightManager();
};
