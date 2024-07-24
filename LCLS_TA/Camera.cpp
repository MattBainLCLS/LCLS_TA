#include "Camera.h"

Camera::Camera()
{
	initialized_ = false;
	width_ = 8192;
	height_ = 500;

	num_elements_ = width_ * height_;

	board_name_ = "Xtium2-CLHS_PX8_1";
	camera_name_ = "CameraLink HS Mono";
	board_configuration_file_ = "C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\D_Linea_ML_8k_Mono_8k_10kHz_500_frame.ccf";
}

bool Camera::initialize()
{
	board_location_ = SapLocation(board_name_, 0);
	acquisition_ = SapAcquisition(board_location_, board_configuration_file_);
	buffer_ = SapBuffer(1, &acquisition_);
	transfer_node_ = SapAcqToBuf(&acquisition_, &buffer_);

	transfer_node_.SetStartMode(SapTransfer::StartSynchronous);

	try
	{
		if (!acquisition_.Create())
		{
			throw(1);
		}

		if (!buffer_.Create())
		{
			throw(2);
		}

		if (!transfer_node_.Create())
		{
			throw(3);
		}
	}
	catch (int error_code)
	{
		terminate();
		return false;
	}

	bytes_per_pixel_ = buffer_.GetBytesPerPixel();

	image_buffer_ = operator new(bytes_per_pixel_ * num_elements_);

	initialized_ = true;
	return true;
}

bool Camera::isInitialized()
{
	return initialized_;
}

uint16_t* Camera::snap()
{
	transfer_node_.Snap();
	buffer_.Read(0, num_elements_, image_buffer_);

	return (uint16_t*)image_buffer_;
}

bool Camera::terminate()
{
	operator delete(image_buffer_);
	transfer_node_.Destroy();
	buffer_.Destroy();
	acquisition_.Destroy();
	initialized_ = false;
	return true;
}
