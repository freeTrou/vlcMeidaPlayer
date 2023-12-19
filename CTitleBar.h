#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPoint>

/*
标题栏
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
	void mousePressEvent(QMouseEvent* event) override; //鼠标点击事件
	void mouseMoveEvent(QMouseEvent *event); //鼠标移动事件
	void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
	void mouseDoubleClickEvent(QMouseEvent* event) override; //鼠标双击事件

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

