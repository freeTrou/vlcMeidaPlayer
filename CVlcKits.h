#pragma once

#include <QObject>
#include <vector>

//���vlc��ʹ�ô���
#ifdef WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif // 
#include "vlc/vlc.h"

/*
libvlc���ܷ�װ
*/
class CVlcKits : public QObject
{
	Q_OBJECT
public:
	CVlcKits();
	~CVlcKits();

	int initVLC(); //��ʼ��vlc
	libvlc_time_t getDurations(); //������Ƶʱ�� ms
	libvlc_media_player_t* media_player();//����m_pMediaPlayerý��ʵ��
	std::vector<libvlc_time_t> getVecDuration(); //���ؼ�¼��Ƶ���ȵ�����
	int getCurrentIndex();
	void addCurrentIndxe();
	void setCurrentDuration(libvlc_time_t value);

	void setTimeSliderPos(int value); //���ò��Ž������ؼ�
	void setVolumeSliderPos(int value); //���������������ؼ�
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
	libvlc_instance_t* m_pInstance; //vlcʵ��
	libvlc_media_player_t* m_pMediaPlayer; //ý��ʵ��
	libvlc_media_t* m_pMedia;

	libvlc_event_manager_t * m_pEvent_manaer;//�¼�ʵ��
	libvlc_time_t m_CurrentDuration; //��Ƶʱ��
	std::vector<libvlc_time_t> m_vecDurations; //��¼���ý�����Ƶʱ��
	int m_CurrentIndex = 0; // ��ʾ��Ƶ���

	//�б���
	libvlc_media_list_player_t* m_pMediaPlayerList;
	libvlc_media_list_t* m_medialist;
};

