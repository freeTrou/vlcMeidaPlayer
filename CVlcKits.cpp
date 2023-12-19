#include "CVlcKits.h"
#include <QMessageBox>
#include <iostream>
#include <QDir>

using namespace std;

//���ڴ�����Ⱥ������Ļص�����
void vlc_callback(const struct libvlc_event_t *p_event, void *p_data)
{
	//��ָ��תΪԭ������
	CVlcKits* pThis = static_cast<CVlcKits*>(p_data);
	if (pThis == nullptr)
	{
		return;
		//QMessageBox::information(nullptr, u8"��ʾ", u8"vlc_callback pThis failed");
		//exit(EXIT_FAILURE);
	}

	switch (p_event->type)
	{
		//��Ƶ���Ž����ź�
	case libvlc_MediaPlayerPositionChanged:
	{
		//��ȡ����λ�� �ٷֱ�
		float pos = libvlc_media_player_get_position(pThis->media_player());
		//�ı���Ƶ������
		pThis->setTimeSliderPos(pos * 100);

		//������ʱ����ʾ ms / 1000 = s
		qint64 curSecs = libvlc_media_player_get_time(pThis->media_player()) / 1000; //��ȡ��ǰ����ʱ��
#ifdef _DEBUG
		cout << "curSecs = " << curSecs << endl;
#endif // DEBUG
		int curH = curSecs / 3600;
		int curMinute = (curSecs - curH * 3600) / 60;
		int curSec = curSecs - curH * 3600 - curMinute * 60;

		char buf1[256] = { 0 };
		sprintf(buf1, "%02d:%02d:%02d", curH, curMinute, curSec);
		QString str1(buf1);

		//��ʽ����ʱ��
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
	//�����仯�ź�
	case libvlc_MediaPlayerAudioVolume:
	{
		//��ȡĬ�ϵ�����ֵ
		int volum = libvlc_audio_get_volume(pThis->media_player());
		pThis->setVolumeSliderPos(volum);//��������������λ��
	}
	break;
	//�������Ʋ����ź�  ���б��ŵ� ÿ�β�����Ƶ���ᴥ��һ������ź�
	case libvlc_MediaPlayerMediaChanged:
	{
		std::cout << "libvlc_MediaPlayerMediaChanged" << std::endl;
		pThis->addCurrentIndxe();
		int _index = pThis->getCurrentIndex();

		//����ѭ������
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

	//����ͷ�
	if (m_pInstance != nullptr)
	{
		libvlc_release(m_pInstance);
		m_pInstance = nullptr;
	}
}

/*
���ܣ�
	��ʼ��libvlc
������
	��
����ֵ��
	0-sucesss
	-1 ʧ��
	-2 ʧ��
*/
int CVlcKits::initVLC()
{
	//vlcʵ����ʼ��
	m_pInstance = libvlc_new(0, nullptr);//vlcʵ������
	if (m_pInstance == nullptr) //ʧ��
	{
		return -1; //libvlc_new failed
	}

	//�ɹ� ��ʼ��ý��ʵ��
	m_pMediaPlayer = libvlc_media_player_new(m_pInstance);
	if (m_pMediaPlayer == nullptr)
	{
		libvlc_release(m_pInstance);//ʧ���ͷ�ʵ��
		return -2; //libvlc_media_player_new failed
	}

	//vlc��Ƶ���¼����� ��Ƶ���� ��������
	m_pEvent_manaer = libvlc_media_player_event_manager(m_pMediaPlayer);//���ڴ�����Ƶ�¼�
	//���������¼��Ļص� �������¼�������� ��Ƶ�����ź� �����źŵĻص����� ��ȡ������߱�����ָ��
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
���ܣ�
	������Ƶ
������
	QString fileName �ļ�·����
	void * hwnd ������Ƶ�Ĵ��ھ��
����ֵ��
	0 sucesss
	-1 ʧ��
*/ /*
int CVlcKits::play(QString fileName, void * hwnd)
{
	//���ñ��ز���·�� ����ʵ�� �� ��Ƶ·��
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
		//����ͷ�
		if (m_pInstance != nullptr)
		{
			libvlc_release(m_pInstance);
			m_pInstance = nullptr;
		}
		return -1;
	}

	//����media
	cout << "before libvlc_media_parse" << endl;
	libvlc_media_parse(m_pMedia);
	cout << "after libvlc_media_parse" << endl;

	//����media
	libvlc_media_player_set_media(m_pMediaPlayer, m_pMedia);

	//���ò��ŵĴ��ھ��
	libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);

	//��ȡ��Ƶ��ʱ�� ��λ ms ����
	m_totalSecs = libvlc_media_get_duration(m_pMedia);

	//����Ĭ��������С 
	int volum = 60;
	libvlc_audio_set_volume(m_pMediaPlayer, volum);
	setVolumeSliderPos(volum);

	//�ͷ�media
	libvlc_media_release(m_pMedia);

	//������Ƶ
	libvlc_media_player_play(m_pMediaPlayer);

	return 0;
}*/

int CVlcKits::play(QStringList fileList, void * hwnd)
{
	//��ʼ���б���ʵ��
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
		//��ÿ��ý����ӵ��б���
		libvlc_media_list_add_media(m_medialist, _pMedia);
		
		//�õ�ÿ��ý���ʱ��
		cout << "before parse" << endl;
		libvlc_media_parse(_pMedia);
		cout << "after parse" << endl;
		libvlc_time_t _duration = libvlc_media_get_duration(_pMedia);// ���ظ�ý���ʱ�� ��λ����
		if (_duration == -1)
		{
			return -2;
		}

		cout << "before push vec" << endl;
		//����ȡ����ʱ��ŵ�������
		m_vecDurations.push_back(_duration);
		cout << "after push vec" << endl;

		//����Ĭ��������С 
		int volum = 60;
		libvlc_audio_set_volume(m_pMediaPlayer, volum);
		setVolumeSliderPos(volum);

		libvlc_media_release(_pMedia);
	}

	//���ò���ģʽ
	libvlc_media_list_player_set_playback_mode(m_pMediaPlayerList, libvlc_playback_mode_loop);

	libvlc_media_list_player_set_media_list(m_pMediaPlayerList, m_medialist);
	libvlc_media_list_player_set_media_player(m_pMediaPlayerList, m_pMediaPlayer);

	

	//���ò��ŵĴ��ھ��
	libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);
	//����
	libvlc_media_list_player_play(m_pMediaPlayerList);

	return 0;
}

void CVlcKits::play()
{
	//�ж���Ƶ״̬   ֹͣ ���� ��ͣ
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Stopped ||
		libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
	{
		//����
		libvlc_media_player_play(m_pMediaPlayer);
	}
}

void CVlcKits::pause()
{
	//�ж���Ƶ״̬   ����
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing)
	{
		//��ͣ
		libvlc_media_player_pause(m_pMediaPlayer);
	}
}

void CVlcKits::stop()
{
	//�ж���Ƶ״̬   ���� ���� ��ͣ
	if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing ||
		libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
	{
		//ֹͣ
		libvlc_media_player_stop(m_pMediaPlayer);
	}
}

void CVlcKits::setVideoPostion(int value)
{
	libvlc_media_player_set_position(m_pMediaPlayer, value / 100.0);
}
