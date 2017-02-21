#ifndef __AVPlayer_H__
#define __AVPlayer_H__
#include <iostream>

typedef void (* pfnPosChanged) (void *data, int iPos);  // 文件位置变化

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class CVlcPlay
{
public:
    CVlcPlay(void);
    ~CVlcPlay(void);

    bool Play(const std::string &strPath);  // 播放路径为strPath的文件
	bool PlaySteam(const std::string &strUrl);
    void Play ();                           // 播放
    void Pause();                           // 暂停
    void Stop ();                           // 停止
	void Mute();							//静音
	BOOL IsMute(); //是否静音
	BOOL SnapShot();	//截图

    void Volume(int nVol);                  // 音量设置为nVol
    void VolumeIncrease();                  // 音量增大
    void VolumeReduce();                    // 音量减小 

    void SeekTo(float fPos);                  // 跳到指定位置nPos
    void SeekForward();                     // 快进
    void SeekBackward();                    // 快退

    void SetHWND(HWND hwnd);                // 设置视频显示的窗口句柄
    HWND GetHWND();                         // 获取视频显示的窗口句柄

    void SetCallback(pfnPosChanged pfn);    // 设置文件位置改变时的回调函数
	libvlc_time_t GetLength();
	libvlc_state_t GetState();
    pfnPosChanged GetCallback();     
	void FullSceen();
	void SetTime(libvlc_time_t time);

    BOOL    IsOpen();                       
    BOOL    IsPlaying();                   
    float     GetPos();                       
    __int64 GetTime();                     

protected:
    libvlc_instance_t			*m_pVLC_Inst;  
    libvlc_media_player_t   *m_pVLC_Player; 
	libvlc_time_t					m_TotalTime;
    HWND                    m_hWnd;         // 视频显示的窗口句柄
    pfnPosChanged           m_pfn;          // 文件位置改变时的回调函数

private:
    void Init();                        
    void Release();                       
};

#endif
