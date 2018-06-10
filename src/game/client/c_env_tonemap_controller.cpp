//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================
#include "cbase.h"

#include "tier0/memdbgon.h"

extern bool g_bUseCustomAutoExposureMin;
extern bool g_bUseCustomAutoExposureMax;
extern bool g_bUseCustomBloomScale;
extern float g_flCustomAutoExposureMin;
extern float g_flCustomAutoExposureMax;
extern float g_flCustomBloomScale;
extern float g_flCustomBloomScaleMinimum;

EHANDLE g_hTonemapControllerInUse = NULL;

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class C_EnvTonemapController : public C_BaseEntity
{
	DECLARE_CLASS( C_EnvTonemapController, C_BaseEntity );
public:
	DECLARE_CLIENTCLASS();

	C_EnvTonemapController();
	~C_EnvTonemapController();
	virtual void	OnDataChanged( DataUpdateType_t updateType );

private:
	bool m_bUseCustomAutoExposureMin;
	bool m_bUseCustomAutoExposureMax;
	bool m_bUseCustomBloomScale;
	float m_flCustomAutoExposureMin;
	float m_flCustomAutoExposureMax;
	float m_flCustomBloomScale;
	float m_flCustomBloomScaleMinimum;
private:
	C_EnvTonemapController( const C_EnvTonemapController & );

	friend void GetTonemapSettingsFromEnvTonemapController();
};

IMPLEMENT_CLIENTCLASS_DT( C_EnvTonemapController, DT_EnvTonemapController, CEnvTonemapController )
	RecvPropInt( RECVINFO(m_bUseCustomAutoExposureMin) ),
	RecvPropInt( RECVINFO(m_bUseCustomAutoExposureMax) ),
	RecvPropInt( RECVINFO(m_bUseCustomBloomScale) ),
	RecvPropFloat( RECVINFO(m_flCustomAutoExposureMin) ),
	RecvPropFloat( RECVINFO(m_flCustomAutoExposureMax) ),
	RecvPropFloat( RECVINFO(m_flCustomBloomScale) ),
	RecvPropFloat( RECVINFO(m_flCustomBloomScaleMinimum) ),
END_RECV_TABLE()

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
C_EnvTonemapController::C_EnvTonemapController( void )
{
	m_bUseCustomAutoExposureMin = false;
	m_bUseCustomAutoExposureMax = false;
	m_bUseCustomBloomScale = false;
	m_flCustomAutoExposureMin = 0;
	m_flCustomAutoExposureMax = 0;
	m_flCustomBloomScale = 0.0f;
	m_flCustomBloomScaleMinimum = 0.0f;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
C_EnvTonemapController::~C_EnvTonemapController( void )
{
	if ( g_hTonemapControllerInUse == this )
	{
		g_bUseCustomAutoExposureMin = false;
		g_bUseCustomAutoExposureMax = false;
		g_bUseCustomBloomScale = false;
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void C_EnvTonemapController::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged(updateType);

	g_bUseCustomAutoExposureMin = m_bUseCustomAutoExposureMin;
	g_bUseCustomAutoExposureMax = m_bUseCustomAutoExposureMax;
	g_bUseCustomBloomScale = m_bUseCustomBloomScale;
	g_flCustomAutoExposureMin = m_flCustomAutoExposureMin;
	g_flCustomAutoExposureMax = m_flCustomAutoExposureMax;
	g_flCustomBloomScale = m_flCustomBloomScale;
	g_flCustomBloomScaleMinimum = m_flCustomBloomScaleMinimum;

	g_hTonemapControllerInUse = this;
}

void GetTonemapSettingsFromEnvTonemapController()
{
	C_BasePlayer *localPlayer = C_BasePlayer::GetLocalPlayer();
	if ( localPlayer )
	{
		if ( C_EnvTonemapController *tonemapController = dynamic_cast< C_EnvTonemapController * >(localPlayer->m_hTonemapController.Get()) )
		{
			g_bUseCustomAutoExposureMin = tonemapController->m_bUseCustomAutoExposureMin;
			g_bUseCustomAutoExposureMax = tonemapController->m_bUseCustomAutoExposureMax;
			g_bUseCustomBloomScale = tonemapController->m_bUseCustomBloomScale;
			g_flCustomAutoExposureMin = tonemapController->m_flCustomAutoExposureMin;
			g_flCustomAutoExposureMax = tonemapController->m_flCustomAutoExposureMax;
			g_flCustomBloomScale = tonemapController->m_flCustomBloomScale;
			g_flCustomBloomScaleMinimum = tonemapController->m_flCustomBloomScaleMinimum;
			return;
		}
	}

	g_bUseCustomAutoExposureMax = false;
	g_bUseCustomBloomScale = false;
}