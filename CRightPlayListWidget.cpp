#include "CRightPlayListWidget.h"

CRightPlayListWidget::CRightPlayListWidget(QWidget* p)
	: QWidget(p)
{
	//禁止父窗口样式影响子窗口
	setAttribute(Qt::WA_StyledBackground);

	this->setFixedWidth(400);// 设置固定宽度

}

CRightPlayListWidget::~CRightPlayListWidget()
{

}