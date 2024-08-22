#include "LiveBuffer.h"

LiveBuffer::LiveBuffer()
{
	bufferCount = 0;
}

void LiveBuffer::increment()
{
	if (bufferCount < buffer.size()-1) // Guards against < buffersize then incrementing to buffersize
	{
		bufferCount++;
	}
	else
	{
		bufferCount = 0;
	}

}

void LiveBuffer::update(Frame newFrame)
{
	buffer[bufferCount] = newFrame;
	increment();
}

QList<QPointF> LiveBuffer::getTA(std::vector<double> xVals)
{
	QList<QPointF> timeSeries;
	QPointF point;

	int bufferSize = buffer.size();

	for (int i = 0; i < 8192; i++)
	{
		point.setY(0);
		point.setX(xVals[i]);

		for (int j = 0; j < bufferSize; j++)
		{
			//point.setY(point.y() + buffer[j].transientAbsorption.intensities[i]);
		}
		point.setY(point.y() / bufferSize);
		
		timeSeries.push_back(point);

	}
}
