#pragma once

//QTԭ���ļ�
#include <QtWidgets/QWidget>

//C++ԭ���ļ�
#include <memory>

//�Զ����ļ�
#include "CTitleBar.h"
#include "VideoWidget.h"
#include "CBottomCtrlBar.h"
#include "CRightPlayListWidget.h"
#include "CFrameLessWidgetBase.h"
#include "CVlcKits.h"

class MainWidget : public CFrameLessWidgetBase
{
	Q_OBJECT
public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
	void initUI();

	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private slots:
	void on_closeSlot();
	void onOpenFile(const QStringList& fileList);
	void onTimeSliderMoved(int value);
	void onPlay();

private:
	CTitleBar* m_pTitleBar; //������
	VideoWidget* m_pVideoWidget;
	CRightPlayListWidget* m_pRightPlayListWidget;
	CBottomCtrlBar* m_pBottomCtrlBar;
	

	std::unique_ptr<CVlcKits> m_pVlc;
	bool m_isPlay = false;
};
