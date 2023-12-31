#pragma once
#include <QWidget>
#include <QPushButton>

#include <QSlider>
#include <QAbstractNativeEventFilter>
#include "CVideoWidgetTopWidget.h"
#include <QAbstractNativeEventFilter>

/*
视频播放窗口类
*/
class VideoWidget : public QWidget, public QAbstractNativeEventFilter
{
	Q_OBJECT
public:
	VideoWidget(QWidget* p = nullptr);
	~VideoWidget();

	void showTopWidget(bool show);
	void setPlayStatus(bool play);
protected:
	bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;
	void resizeEvent(QResizeEvent* event) override;
	/*void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;*/

private slots:
	void onSliderMoved(int value);

signals:
	void sig_OpenFile(const QStringList& fileList);
	void sig_OpenFloder(QString path);
	void sig_OpenPlaylist();
	void sig_Totalms(const qint64& duration);   //发给主界面
	void sig_VideoPositionChanged(const qint64& pos);   //发给主界面
	void sig_SliderMoved(int value);

private:
	QPoint m_dPos;   //VideoWidget相对于父窗口的位置
	CVideoWidgetTopWidget* m_pTopWidget = nullptr;
	bool m_isPlay = false;
};

