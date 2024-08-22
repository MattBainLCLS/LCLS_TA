#pragma once
#include "SapClassBasic.h"

#include <armadillo>


class Camera
{

private:
	int height_;
	int width_;
	int num_elements_;

	int bytes_per_pixel_;

	void* image_buffer_;
	uint16_t* image_buffer_uint_;
	double* image_buffer_dbl_;

	bool initialized_;

	const char *board_name_;
	const char *camera_name_;
	const char *board_configuration_file_;

	SapAcquisition acquisition_;
	SapAcqDevice acquisition_device_;
	SapLocation board_location_;
	SapBuffer buffer_;
	SapTransfer transfer_node_;

public:
	Camera();
	~Camera();
	bool initialize();
	//arma::Mat<double> snap();
	void snap();
	bool terminate();

	bool isInitialized();
};

