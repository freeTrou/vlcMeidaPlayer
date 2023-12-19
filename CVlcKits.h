#pragma once

#include <QObject>
#include <vector>

//解决vlc库使用错误
#ifdef WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif // 
#include "vlc/vlc.h"

/*
libvlc功能封装
*/
class CVlcKits : public QObject
{
	Q_OBJECT
public:
	CVlcKits();
	~CVlcKits();

	int initVLC(); //初始化vlc
	libvlc_time_t getDurations(); //返回视频时长 ms
	libvlc_media_player_t* media_player();//返回m_pMediaPlayer媒体实例
	std::vector<libvlc_time_t> getVecDuration(); //返回记录视频长度的容器
	int getCurrentIndex();
	void addCurrentIndxe();
	void setCurrentDuration(libvlc_time_t value);

	void setTimeSliderPos(int value); //设置播放进度条控件
	void setVolumeSliderPos(int value); //设置音量进度条控件
	void setTimeText(const QString str);

	//int play(QString fileName, void* hwnd);
	int play(QStringList fileList, void* hwnd);
	void play();
	void pause();
	void stop();

	void setVideoPostion(int value);

signals:
	void sig_TimeSliderPos(const int value);
	void sig_VolumeSliderPos(const int value);
	void sig_UpdateTimeText(const QString str);

private:
	libvlc_instance_t* m_pInstance; //vlc实例
	libvlc_media_player_t* m_pMediaPlayer; //媒体实例
	libvlc_media_t* m_pMedia;

	libvlc_event_manager_t * m_pEvent_manaer;//事件实例
	libvlc_time_t m_CurrentDuration; //视频时间
	std::vector<libvlc_time_t> m_vecDurations; //记录多个媒体的视频时间
	int m_CurrentIndex = 0; // 表示视频编号

	//列表播放
	libvlc_media_list_player_t* m_pMediaPlayerList;
	libvlc_media_list_t* m_medialist;
};

