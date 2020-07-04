#include "TCamera.h"

bool TCamera::Init()
{
    m_vPos = Vector3(0, 0, -5.0f);
    m_vTarget = Vector3(0, 0, 0.0f);
    m_vUp = Vector3(0, 1, 0.0f);
    m_matView.ViewMatrix(
        m_vPos,
        m_vTarget,
        m_vUp);
    
    float Aspect = g_rtClient.right / g_rtClient.bottom;

    m_matProj.PerspectiveFovLH(
        1.f,
        100.f,
        TBASIS_PI * 0.25f,
        Aspect);

    return true ;
}
