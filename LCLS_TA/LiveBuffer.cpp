#include "LiveBuffer.h"

LiveBuffer::LiveBuffer()
{
	bufferSize = 3;
	bufferCount = 0;
}

LiveBuffer::LiveBuffer(int numFrames)
{
	bufferSize = numFrames;
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

	if (buffer.size() < bufferSize)
	{
		buffer.push_back(newFrame);
	}
	else
	{
		buffer[bufferCount] = newFrame;
	}
	increment();
}

QList<QPointF> LiveBuffer::getPumpOff()
{
	QList<QPointF> timeSeries;
	QPointF point;

	int bufferSize = buffer.size();

	if (bufferSize == 0)
	{
		for (int i = 0; i < 8192; i++)
		{
			point.setY(10);
			point.setX(i);

			timeSeries.push_back(point);

		}
	}
	else
	{
		for (int i = 0; i < 8192; i++)
		{
			point.setY(1);
			point.setX(i);

			for (int j = 0; j < bufferSize; j++)
			{
				point.setY(point.y() + buffer[j].pumpOffIntensities()->at(i));
			}
			point.setY(point.y() / bufferSize);

			timeSeries.push_back(point);

		}
	}
	
	return timeSeries;
}

QList<QPointF> LiveBuffer::getTA()
{
	QList<QPointF> timeSeries;
	QPointF point;

	int bufferSize = buffer.size();

	if (bufferSize == 0)
	{
		for (int i = 0; i < 8192; i++)
		{
			point.setY(10);
			point.setX(i);

			timeSeries.push_back(point);

		}
	}
	else
	{
		for (int i = 0; i < 8192; i++)
		{
			point.setY(1);
			point.setX(i);

			for (int j = 0; j < bufferSize; j++)
			{
				point.setY(point.y() + buffer[j].transientAbsorptionIntensities()->at(i));
			}
			point.setY(point.y() / bufferSize);

			timeSeries.push_back(point);

		}
	}
	
	return timeSeries;
}
