#include "TCore.h"
#include "TPlaneObj.h"
#include "TDxRT.h"

class TFullScreen : public TPlaneObj
{
public:
	ID3D11ShaderResourceView* m_pSRV;
	bool Render()
	{
		PreRender();
		m_pContext->UpdateSubresource(
			m_dxObj.m_pConstantBuffer.Get(), 0, NULL,
			&m_cbData, 0, 0);

		if (m_pTexture[0] != nullptr)
			m_pContext->PSSetShaderResources(0, 1, &m_pSRV);

		m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);
		m_pContext->OMSetBlendState(m_pBlendState, 0, 0xff);

		PostRender();
		return true;

	}
};
class Sample : public TCore
{
	TDxRT   m_DxRT;
	TPlaneObj m_PlaneObj;
	TFullScreen m_FullScreenObj;
public:
	bool  Init()
	{
		RECT rt = { 0,0,800, 600 };
		m_PlaneObj.SetScreenRect(rt);
		m_PlaneObj.Create(m_pd3dDevice,
			m_pContext,
			L"Lin1.jpg",
			L"ShapeShader.txt");
		m_PlaneObj.m_pBlendState = TDxState::g_pBSAlphaBlend;
		m_PlaneObj.m_pSamplerState = TDxState::g_pSamplerState;

		//m_FullScreenObj.SetScreenRect(rt);
		m_FullScreenObj.Create(m_pd3dDevice,
			m_pContext,
			L"Lin2.jpg",
			L"ShapeShader.txt");
		m_FullScreenObj.m_pBlendState = TDxState::g_pBSAlphaBlend;
		m_FullScreenObj.m_pSamplerState = TDxState::g_pSamplerState;

		m_DxRT.Create(m_pd3dDevice, 1024, 1024);
		m_Camera.m_matView.ViewMatrix(
			{ 0, 0, -5.0f },
			{ 0, 0, 0.0f },
			{ 0, 1, 0.0f });
		m_Camera.m_matProj.PerspectiveFovLH(
			1.0f,
			100.0f,
			TBASIS_PI * 0.25f,
			g_rtClient.right / g_rtClient.bottom);
		return true;
	}
	bool  Render()
	{
		m_DxRT.Begin(m_pContext);
		m_PlaneObj.SetMatrix(NULL, &m_Camera.m_matView, &m_Camera.m_matProj);
		m_PlaneObj.Render();
		m_DxRT.End(m_pContext);
		ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		m_pContext->PSSetShaderResources(0, 16, pSRVs);

		PreRender();
		m_FullScreenObj.SetMatrix(NULL, NULL, NULL);
		m_FullScreenObj.m_pSRV = m_DxRT.m_pRT_SRV.Get();
		m_FullScreenObj.Render();
		return true;
	}
	bool  Release()
	{
		m_PlaneObj.Release();
		m_FullScreenObj.Release();
		return true;
	}
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
	{
		// Unbind all objects from the immediate context
		if (pd3dDeviceContext == NULL) return;

		ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11DepthStencilView* pDSV = NULL;
		ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		// Shaders
		pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

		// IA clear
		pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
		pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
		pd3dDeviceContext->IASetInputLayout(NULL);

		// Constant buffers
		pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

		// Resources
		pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

		// Samplers
		pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

		// Render targets
		pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

		// States
		FLOAT blendFactor[4] = { 0,0,0,0 };
		pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
		pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
		pd3dDeviceContext->RSSetState(NULL);
	}
};

TWINGAME;