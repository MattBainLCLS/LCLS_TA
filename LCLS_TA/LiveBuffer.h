#pragma once

#include "Frame.h"
#include <QtCharts>

class LiveBuffer
{
	LiveBuffer();
	
	std::vector<Frame> buffer;

	void update(Frame);

	QList<QPointF> getTA(std::vector<double> xVals);
	Spectrum getPumpOff();
	Spectrum getPumpOn();

private:
	int bufferCount;

	void increment();
	
};

