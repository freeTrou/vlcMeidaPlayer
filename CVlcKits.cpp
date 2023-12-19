#include "CVlcKits.h"
#include <QMessageBox>
#include <iostream>
#include <QDir>

using namespace std;

//用于处理进度和声音的回调函数
void vlc_callback(const struct libvlc_event_t *p_event, void *p_data)
{
	//将指针转为原来类型
	CVlcKits* pThis = static_cast<CVlcKits*>(p_data);
	if (pThis == nullptr)
	{
		return;
		//QMessageBox::information(nullptr, u8"提示", u8"vlc_callback pThis failed");
		//exit(EXIT_FAILURE);
	}

	switch (p_event->type)
	{
		//视频播放进度信号
	case libvlc_MediaPlayerPositionChanged:
	{
		//获取播放位置 百分比
		float pos = libvlc_media_player_get_position(pThis->media_player());
		//改变视频进度条
		pThis->setTimeSliderPos(pos * 100);

		//进度条时间显示 ms / 1000 = s
		qint64 curSecs = libvlc_media_player_get_time(pThis->media_player()) / 1000; //获取当前播放时间
#ifdef _DEBUG
		cout << "curSecs = " << curSecs << endl;
#endif // DEBUG
		int curH = curSecs / 3600;
		int curMinute = (curSecs - curH * 3600) / 60;
		int curSec = curSecs - curH * 3600 - curMinute * 60;

		char buf1[256] = { 0 };
		sprintf(buf1, "%02d:%02d:%02d", curH, curMinute, curSec);
		QString str1(buf1);

		//格式化总时长
		qint64 totalSecs = pThis->getDurations() / 1000;
		int _hour = totalSecs / 3600;
		int _minute = (totalSecs - _hour * 3600) / 60;
		int _sec = totalSecs - _hour * 3600 - _minute * 60;

		char buf2[256] = { 0 };
		sprintf(buf2, "%02d:%02d:%02d", _hour, _minute, _sec);
		QString str2(str1 + "/" + buf2);

		pThis->setTimeText(str2);
	}
	break;
	//声音变化信号
	case libvlc_MediaPlayerAudioVolume:
	{
		//获取默认的声音值
		int volum = libvlc_audio_get_volume(pThis->media_player());
		pThis->setVolumeSliderPos(volum);//设置音量进度条位置
	}
	break;
	//用来控制播放信号  做列表播放的 每次播放视频都会触发一次这个信号
	case libvlc_MediaPlayerMediaChanged:
	{
		std::cout << "libvlc_MediaPlayerMediaChanged" << std::endl;
		pThis->addCurrentIndxe();
		int _index = pThis->getCurrentIndex();

		//开启循环播放
		int vSize = pThis->getVecDuration().size();
		if (_index > vSize)
		{
			if (_index % vSize == 0)
			{
				_index = vSize;
			}
			else
			{
				_index = _index % vSize;
			}
		}

		libvlc_time_t _duration = pThis->getVecDuration()[_index - 1];
		pThis->setCurrentDuration(_duration);
	}
	break;
	}
}

CVlcKits::CVlcKits():
	m_pInstance(nullptr), m_pMedia(nullptr), m_pMediaPlayer(nullptr)
	, m_pEvent_manaer(nullptr), m_CurrentDuration(0)
{

}

CVlcKits::~CVlcKits()
{
	if (m_pMediaPlayer != nullptr)
	{
		if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing ||
			libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
		{
			libvlc_media_player_release(m_pMediaPlayer);
			m_pMediaPlayer = nullptr;
		}
	}

	//最后释放
	if (m_pInstance != nullptr)
	{
		libvlc_release(m_pInstance);
		m_pInstance = nullptr;
	}
}

/*
功能：
	初始化libvlc
参数：
	无
返回值：
	0-sucesss
	-1 失败
	-2 失败
*/
int CVlcKits::initVLC()
{
	//vlc实例初始化
	m_pInstance = libvlc_new(0, nullptr);//vlc实例创建
	if (m_pInstance == nullptr) //失败
	{
		return -1; //libvlc_new failed
	}

	//成功 初始化媒体实例
	m_pMediaPlayer = libvlc_media_player_new(m_pInstance);
	if (m_pMediaPlayer == nullptr)
	{
		libvlc_release(m_pInstance);//失败释放实例
		return -2; //libvlc_media_player_new failed
	}

	//vlc视频的事件管理 视频进度 声音控制
	m_pEvent_manaer = libvlc_media_player_event_manager(m_pMediaPlayer);//用于处理视频事件
	//关联处理事件的回调 参数：事件管理对象 视频进度信号 处理信号的回调函数 获取对象或者变量的指针
	libvlc_event_attach(m_pEvent_manaer, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
	libvlc_event_attach(m_pEvent_manaer, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
	libvlc_event_attach(m_pEvent_manaer, libvlc_MediaPlayerMediaChanged, vlc_callback, this);

	return 0;
}

void CVlcKits::setTimeSliderPos(int value)
{
	emit sig_TimeSliderPos(value);
}

void CVlcKits::setVolumeSliderPos(int value)
{
	emit sig_VolumeSliderPos(value);
}

libvlc_time_t CVlcKits::getDurations()
{
	return m_CurrentDuration;
}

libvlc_media_player_t * CVlcKits::media_player()
{
	return this->m_pMediaPlayer;
}

std::vector<libvlc_time_t> CVlcKits::getVecDuration()
{
	return this->m_vecDurations;
}

int CVlcKits::getCurrentIndex()
{
	return m_CurrentIndex;
}

void CVlcKits::addCurrentIndxe()
{
	m_CurrentIndex++;
}

void CVlcKits::setCurrentDuration(libvlc_time_t value)
{
	m_CurrentDuration = value;
}

void CVlcKits::setTimeText(const QString str)
{
	emit sig_UpdateTimeText(str);
}

/*
功能：
	播放视频
参数：
	QString fileName 文件路径名
	void * hwnd 播放视频的窗口句柄
返回值：
	0 sucesss
	-1 失败
*/ /*
int CVlcKits::play(QString fileName, void * hwnd)
{
	//设置本地播放路径 传入实例 和 视频路径
	m_pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());
	if (m_pMedia == nullptr)
	{
		if (m_pMediaPlayer != nullptr)
		{
			if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing ||
				libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
			{
				libvlc_media_player_release(m_pMediaPlayer);
				m_pMediaPlayer = nullptr;
			}
		}
		//最后释放
		if (m_pInstance != nullptr)
		{
			libvlc_release(m_pInstance);
			m_pInstance = nullptr;
		}
		return -1;
	}

	//解析media
	cout << "before libvlc_media_parse" << endl;
	libvlc_media_parse(m_pMedia);
	cout << "after libvlc_media_parse" << endl;

	//设置media
	libvlc_media_player_set_media(m_pMediaPlayer, m_pMedia);

	//设置播放的窗口句柄
	libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);

	//获取视频总时长 单位 ms 毫秒
	m_totalSecs = libvlc_media_get_duration(m_pMedia);

	//设置默认声音大小 
	int volum = 60;
	libvlc_audio_set_volume(m_pMediaPlayer, volum);
	setVolumeSliderPos(volum);

	//释放media
	libvlc_media_release(m_pMedia);

	//播放视频
	libvlc_media_player_play(m_pMediaPlayer);

	return 0;
}*/

int CVlcKits::play(QStringList fileList, void * hwnd)
{
	//初始化列表播放实例
	m_pMediaPlayerList = libvlc_media_list_player_new(m_pInstance);
	m_medialist = libvlc_media_list_new(m_pInstance);

	int size = fileList.size();
	for (int i = 0; i < size; i++)
	{
		QString fileName = fileList[i];
		fileName = QDir::toNativeSeparators(fileName);

		libvlc_media_t* _pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());
		if (_pMedia == nullptr)
		{
			return -1;
		}
		//将每个媒体添加到列表中
		libvlc_media_list_add_media(m_medialist, _pMedia);
		
		//拿到每个媒体的时间
		cout << "before parse" << endl;
		libvlc_media_parse(_pMedia);
		cout << "after parse" << endl;
		libvlc_time_t _duration = libvlc_media_get_duration(_pMedia);// 返回该媒体的时间 单位毫秒
		if (_duration == -1)
		{
			return -2;
		}

		cout << "before push vec" << endl;
		//将获取到的时间放到容器中
		m_vecDurations.push_back(_duration);
		cout << "after push vec" << endl;

		//设置默认声音大小 
		int volum = 60;
		libvlc_audio_set_volume(m_pMediaPlayer, volum);
		setVolumeSliderPos(volum);

		libvlc_media_release(_pMedia);
	}

	//设置播放模式
	libvlc_media_list_player_set_playback_mode(m_pMediaPlayerList, libvlc_playback_mode_loop);

	libvlc_media_list_player_set_media_list(m_pMediaPlayerList, m_medialist);
	libvlc_media_list_player_set_media_player(m_pMediaPlayerList, m_pMediaPlayer);

	

	//设置播放的窗口句柄
	libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);
	//播放
	libvlc_media_list_player_play(m_pMediaPlayerList);

	return 0;
}

void CVlcKits::play()
{
	//判断视频状态   停止 或者 暂停
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Stopped ||
		libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
	{
		//播放
		libvlc_media_player_play(m_pMediaPlayer);
	}
}

void CVlcKits::pause()
{
	//判断视频状态   播放
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing)
	{
		//暂停
		libvlc_media_player_pause(m_pMediaPlayer);
	}
}

void CVlcKits::stop()
{
	//判断视频状态   播放 或者 暂停
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing ||
		libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
	{
		//停止
		libvlc_media_player_stop(m_pMediaPlayer);
	}
}

void CVlcKits::setVideoPostion(int value)
{
	libvlc_media_player_set_position(m_pMediaPlayer, value / 100.0);
}
