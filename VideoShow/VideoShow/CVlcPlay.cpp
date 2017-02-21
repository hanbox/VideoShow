#include "Stdafx.h"
#include <cmath>

CVlcPlay::CVlcPlay(void) :
m_pVLC_Inst(NULL),
m_pVLC_Player(NULL),
m_hWnd(NULL),
m_pfn(NULL)
{
}

CVlcPlay::~CVlcPlay(void)
{
    Release();
}

void CVlcPlay::Init()
{
    if (! m_pVLC_Inst)
    {
		const char * const vlc_args[] = {
			"-I", "dumy",      // No special interface
			"--ignore-config", // Don't use VLC's config
			"--plugin-path=./plugins" };

        m_pVLC_Inst =libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    }
}

void CVlcPlay::Release()
{
    Stop();

	libvlc_media_player_release(m_pVLC_Player);
    if (m_pVLC_Inst)
    {
        libvlc_release (m_pVLC_Inst);
        m_pVLC_Inst   = NULL;
    }	
}

bool CVlcPlay::Play(const std::string &strPath)
{
    if (! m_pVLC_Inst)
    {
        Init();
    }

    if(strPath.empty() || ! m_pVLC_Inst)
    {
        return false;
    }

    Stop();

    bool bRet = false;
    libvlc_media_t *m;

    if (m = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str()))
    {
        if (m_pVLC_Player = libvlc_media_player_new_from_media(m))
        {
            libvlc_media_player_set_hwnd(m_pVLC_Player, m_hWnd);
            libvlc_media_player_play(m_pVLC_Player);

            bRet = true;
        }

        libvlc_media_release(m);
    }

    return bRet;
}

bool CVlcPlay::PlaySteam(const std::string &strUrl)
{
	if (! m_pVLC_Inst)
	{
		Init();
	}

	if(strUrl.empty() || ! m_pVLC_Inst)
	{
		return false;
	}

	Stop();

	bool bRet = false;
	libvlc_media_t *m;

	if (m = libvlc_media_new_location(m_pVLC_Inst, strUrl.c_str()))
	{
		if (m_pVLC_Player = libvlc_media_player_new_from_media(m))
		{
			libvlc_media_player_set_hwnd(m_pVLC_Player, m_hWnd);
			libvlc_media_player_play(m_pVLC_Player);

			bRet = true;
		}

		libvlc_media_release(m);
	}

	return bRet;
}

void CVlcPlay::FullSceen()
{
	//要一起设置
	libvlc_video_set_mouse_input(m_pVLC_Player,0);
	libvlc_video_set_key_input(m_pVLC_Player,0);
	libvlc_set_fullscreen(this->m_pVLC_Player, 0);
}

void CVlcPlay::Stop()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_stop (m_pVLC_Player);      /* Stop playing */    
        libvlc_media_player_release (m_pVLC_Player);   /* Free the media_player */
        m_pVLC_Player = NULL;
    }

    /* Stop the media */
    //if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
}

void CVlcPlay::Play()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_play(m_pVLC_Player);
    }
}

void CVlcPlay::Pause()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_pause(m_pVLC_Player);
    }
}

void CVlcPlay::Mute()
{
	if (m_pVLC_Player)
	{
		libvlc_audio_toggle_mute(m_pVLC_Player);
	}
}

BOOL CVlcPlay::IsMute()
{
	BOOL bRet = FALSE;
	if (m_pVLC_Player)
	{
		int iRet = libvlc_audio_get_mute(m_pVLC_Player);
		if ( iRet != 1 )
		{
			bRet = TRUE;
		}
	}

	return bRet;
}

void CVlcPlay::Volume(int nVol)
{
    if (m_pVLC_Player)
    {
        libvlc_audio_set_volume(m_pVLC_Player,nVol);
    }
}

void CVlcPlay::VolumeIncrease()
{
    if (m_pVLC_Player)
    {
        int nVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)ceil(nVol * 1.1));
    }
}

void CVlcPlay::VolumeReduce()
{
	if (m_pVLC_Player)
	{
		int nVol = libvlc_audio_get_volume(m_pVLC_Player);
		Volume((int)ceil(nVol * 0.9));
	}
}

BOOL CVlcPlay::SnapShot()
{
	BOOL bRet = FALSE;
    if (m_pVLC_Player)
    {
        int iRet = libvlc_video_take_snapshot(m_pVLC_Player, 0, "C:\\SceenTmp\\asd.png", 100, 100);
		if ( iRet == 0 )
		{
			bRet = TRUE;
		}
    }

	return bRet;
}

float CVlcPlay::GetPos()
{   
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_position(m_pVLC_Player);
    }

    return 0;
}

void CVlcPlay::SeekTo(float fPos)
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_set_position(m_pVLC_Player, fPos);
    }
}

void CVlcPlay::SeekForward()
{
    SeekTo(GetPos() + 0.01);
}

void CVlcPlay::SeekBackward()
{
	SeekTo(GetPos() - 0.01);
}

void CVlcPlay::SetHWND( HWND hwnd )
{
    if (::IsWindow(hwnd))
    {
        m_hWnd = hwnd;
    }
}

HWND CVlcPlay::GetHWND()
{
    return m_hWnd;
}

void CVlcPlay::SetCallback( pfnPosChanged pfn )
{
    m_pfn = pfn;
}

pfnPosChanged CVlcPlay::GetCallback()
{
    return m_pfn;
}

BOOL CVlcPlay::IsOpen()
{
    return NULL != m_pVLC_Player;
}

BOOL CVlcPlay::IsPlaying()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_is_playing(m_pVLC_Player);
    }

    return FALSE;
}

__int64 CVlcPlay::GetTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_time(m_pVLC_Player);
    }

    return 0;
}

libvlc_time_t CVlcPlay::GetLength()
{	
	libvlc_time_t time;
	if (m_pVLC_Player)
	{
		time = libvlc_media_player_get_length(m_pVLC_Player);	
	}

	return time;
}

void CVlcPlay::SetTime(libvlc_time_t time)
{	
	if (m_pVLC_Player)
	{
		libvlc_media_player_set_time(m_pVLC_Player, time);	
	}
}

libvlc_state_t CVlcPlay::GetState()
{
	libvlc_state_t stste = libvlc_NothingSpecial;
	if (m_pVLC_Player)
	{
		return libvlc_media_player_get_state(m_pVLC_Player);
	}

	return stste;
}
