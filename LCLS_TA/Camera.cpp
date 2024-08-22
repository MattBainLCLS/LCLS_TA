#include "Camera.h"

Camera::Camera()
{
	initialized_ = false;
	//width_ = 8192;
	//height_ = 100;

	//num_elements_ = width_ * height_;

	

	board_name_ = "Xtium2-CLHS_PX8_1";
	camera_name_ = "CameraLink HS Mono";
	//board_configuration_file_ = "C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\D_Linea_ML_8k_Mono_8k_10kHz_500_frame.ccf";
	//board_configuration_file_ = "C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\D_Linea_ML_8k_Mono_8k_1kHz_100_frame_ext_trigger.ccf";
	board_configuration_file_ = "C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\grabber_config_matt_8_1_1kHz.ccf";
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

	width_ = buffer_.GetWidth();
	height_ = buffer_.GetHeight();
	bytes_per_pixel_ = buffer_.GetBytesPerPixel();

	num_elements_ = width_ * height_;

	image_buffer_uint_ = new uint16_t[num_elements_];
	//image_buffer_dbl_ = new double[num_elements_];


	

	image_buffer_ = operator new(bytes_per_pixel_ * num_elements_);

	initialized_ = true;
	return true;
}

bool Camera::isInitialized()
{
	return initialized_;
}

void Camera::snap()
{
	transfer_node_.Snap();
	buffer_.Read(0, num_elements_, image_buffer_);

	image_buffer_uint_ = (uint16_t*)image_buffer_;

	//arma::Col<double> myCol(num_elements_, arma::fill::ones);

	//for (int i = 0; i < num_elements_; i++)
	//{
	//	//myCol(i) = (double)image_buffer_uint[i];
	//}

	//image_buffer_dbl_ = (double*)image_buffer_;

	//arma::Mat<double>::fixed<8192, 100> mytest(arma::fill::ones);

	//arma::Mat<double> mytest = arma::conv_to<arma::Mat<double>::fixed<8192, 100>>::from(myCol);
	//mytest = arma::conv_to<arma::Mat<double>>::from(myCol);
	
	//arma::Mat<double> mytest = arma::mat(&image_buffer_dbl_[0], width_, height_, true, false);
	//arma::Mat<double> mytest = arma::Mat<double>(8192, 100, arma::fill::ones);

	//return mytest;
	//return (uint16_t*)image_buffer_;
}

//void Camera::snap()
//{
//	transfer_node_.Snap();
//	buffer_.Read(0, num_elements_, image_buffer_);
//	image_buffer_dbl_ = (double*)image_buffer_;
//	arma::mat mytest  = arma::mat(&image_buffer_dbl_[0], width_, height_, false);
//
//	mytest.t();
//}

bool Camera::terminate()
{
	operator delete(image_buffer_);
	transfer_node_.Destroy();
	buffer_.Destroy();
	acquisition_.Destroy();
	initialized_ = false;
	return true;
}

Camera::~Camera()
{
	delete image_buffer_;
	delete image_buffer_uint_;
	delete image_buffer_dbl_;
}