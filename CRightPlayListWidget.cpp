#include "CRightPlayListWidget.h"

CRightPlayListWidget::CRightPlayListWidget(QWidget* p)
	: QWidget(p)
{
	//��ֹ��������ʽӰ���Ӵ���
	setAttribute(Qt::WA_StyledBackground);

	this->setFixedWidth(400);// ���ù̶����

}

CRightPlayListWidget::~CRightPlayListWidget()
{

}