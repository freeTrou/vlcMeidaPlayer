#include "CTitleBar.h"
#include "qss.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QMenu>

#pragma comment(lib, "user32.lib")
#include <qt_windows.h>


CTitleBar::CTitleBar(QWidget* p):
	QWidget(p)
{
	this->setAttribute(Qt::WA_DeleteOnClose);

	initUI();
}

CTitleBar::~CTitleBar()
{
}

void CTitleBar::initUI()
{
	//��ֹ������Ӱ���Ӵ�����ʽ
	setAttribute(Qt::WA_StyledBackground);
	this->setFixedHeight(32 + 5 * 2);
	this->setStyleSheet("background-color:rgb(54,54,54)");

	//���ⰴť
	m_pLogoBtn = new QPushButton(this);
	m_pLogoBtn->setFixedSize(138, 32);
	m_pLogoBtn->setText(u8"QQӰ��");
	//m_pLogoBtn->setIcon(QIcon("D:\\QTproject\\QtAdvanced\\04\\QVideoWedgetTest\\04MyMeidaPlayer\\resources\\logo.png"));
	m_pLogoBtn->setStyleSheet(QString::fromStdString(logo_button_qss));

	//���������˵�
	QMenu* pMenu = new QMenu(this);
	pMenu->setStyleSheet(QString::fromStdString(menu_qss));

	QAction* pAc1 = new QAction(u8"���ļ�", this);
	QAction* pAc2 = new QAction(u8"���ļ���", this);
	QAction* pAc3 = new QAction(u8"����˵��", this);
	QAction* pAc4 = new QAction(u8"�˳�", this);

	pMenu->addAction(pAc1);
	pMenu->addAction(pAc2);
	pMenu->addAction(pAc3);
	pMenu->addAction(pAc4);
	m_pLogoBtn->setMenu(pMenu);

	//
	m_pMinimodeBtn = new QPushButton(this);
	m_pMinimodeBtn->setFixedSize(32, 32);
	m_pMinimodeBtn->setStyleSheet(QString::fromStdString(minimode_qss));

	m_pSettopBtn = new QPushButton(this);
	m_pSettopBtn->setFixedSize(32, 32);
	m_pSettopBtn->setStyleSheet(QString::fromStdString(settop_qss));

	m_pMinBtn = new QPushButton(this);
	m_pMinBtn->setFixedSize(32, 32);
	m_pMinBtn->setStyleSheet(QString::fromStdString(min_qss));

	m_pMaxBtn = new QPushButton(this);
	m_pMaxBtn->setFixedSize(32, 32);
	m_pMaxBtn->setStyleSheet(QString::fromStdString(max_qss));

	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setFixedSize(32, 32);
	m_pCloseBtn->setStyleSheet(QString::fromStdString(close_qss));

	QHBoxLayout* pHlay = new QHBoxLayout(this);
	pHlay->addWidget(m_pLogoBtn);

	pHlay->addStretch();
	pHlay->addWidget(m_pMinimodeBtn);
	QSpacerItem* pItem = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem);

	pHlay->addWidget(m_pSettopBtn);
	QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem1);

	pHlay->addWidget(m_pMinBtn);
	QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem2);
	pHlay->addWidget(m_pMaxBtn);

	QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem3);   // ����ÿ��ʹ��ʱ��new�����������ظ�ʹ��
	pHlay->addWidget(m_pCloseBtn);

	pHlay->setContentsMargins(5, 5, 5, 5);

	connect(m_pMinBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pMaxBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pCloseBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
}

//if (event->button() == Qt::LeftButton)//�����жϣ��Ƿ������������£�ֻ��������´��ڲ����ƶ�

void CTitleBar::mousePressEvent(QMouseEvent* event)
{
	/*
		����ƶ��ޱ߿򴰿�ʹ��������
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
		
	}*/

	// �����������¼�
	if (event->button() == Qt::LeftButton)
	{
		// ��¼������״̬
		m_leftButtonPressed = true;
		//��¼�������Ļ�е�λ��
		m_start = event->globalPos();
	}
}

void CTitleBar::mouseMoveEvent(QMouseEvent *event)
{
	// ������ס������Ӧ�¼�
	if (m_leftButtonPressed)
	{
		//���������ƶ���������ԭ����λ�ü�������ƶ���λ�ã�event->globalPos()-m_start
		parentWidget()->move(parentWidget()->geometry().topLeft() +
			event->globalPos() - m_start);
		//���������Ļ�е�λ���滻Ϊ�µ�λ��
		m_start = event->globalPos();
	}

}

void CTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	// �������ͷ�
	if (event->button() == Qt::LeftButton)
	{
		// ��¼���״̬
		m_leftButtonPressed = false;
	}
}


void CTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	emit m_pMaxBtn->clicked();
}

void CTitleBar::onClicked()
{
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());

	QWidget* pWindow = this->window();

	if (pButton == m_pMinBtn)
	{
		pWindow->showMinimized();
	}
	else if (pButton == m_pMaxBtn)
	{
		if (pWindow->isMaximized())
		{
			pWindow->showNormal();
			m_pMaxBtn->setStyleSheet("QPushButton{background-image:url(:/titlebar/resources/titleBar/normal.svg);border:none}" \
				"QPushButton:hover{" \
				"background-color:rgb(99, 99, 99);" \
				"background-image:url(:/titlebar/resources/titleBar/normal_hover.svg);border:none;}");
		}
		else
		{
			pWindow->showMaximized();
			m_pMaxBtn->setStyleSheet("QPushButton{background-image:url(:/titlebar/resources/titleBar/max.svg);border:none}" \
				"QPushButton:hover{" \
				"background-color:rgb(99, 99, 99);" \
				"background-image:url(:/titlebar/resources/titleBar/max_hover.svg);border:none;}");
		}
	}
	else if (pButton == m_pCloseBtn)
	{
		emit sig_close();
	}
}

