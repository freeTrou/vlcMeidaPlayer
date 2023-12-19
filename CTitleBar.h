#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPoint>

/*
������
*/
class CTitleBar : public QWidget
{
	Q_OBJECT

public:
	CTitleBar(QWidget* p = nullptr);
	~CTitleBar();

private:
	void initUI();

private:
	void mousePressEvent(QMouseEvent* event) override; //������¼�
	void mouseMoveEvent(QMouseEvent *event); //����ƶ��¼�
	void mouseReleaseEvent(QMouseEvent *event); //����ͷ��¼�
	void mouseDoubleClickEvent(QMouseEvent* event) override; //���˫���¼�

private slots:
	void onClicked();

signals:
	void sig_close();

private:
	QPushButton* m_pLogoBtn;
	//QLabel* m_pTitleTextLabel;
	
	QPushButton* m_pMinimodeBtn;
	QPushButton* m_pSettopBtn;
	QPushButton* m_pMinBtn;
	QPushButton* m_pMaxBtn;
	QPushButton* m_pCloseBtn;

	bool m_leftButtonPressed;
	QPoint m_start;
};

