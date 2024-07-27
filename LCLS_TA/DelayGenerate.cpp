#include "DelayGenerate.h"

DelayGenerate::DelayGenerate(QWidget* parent) : QWidget(parent)
{
	windowLabel = new QLabel(this);

	windowLabel->setText("Generate Delays");
}
