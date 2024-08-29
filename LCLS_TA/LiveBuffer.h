#pragma once

#include "Frame.h"
#include <QtCore>

class LiveBuffer
{
public:
	LiveBuffer();
	LiveBuffer(int numFrames);
	
	std::vector<Frame> buffer;

	void update(Frame);

	QList<QPointF> getTA();
	QList<QPointF> getPumpOff();

private:
	int bufferCount;

	void increment();

	int bufferSize;
	
};

