#pragma once
#include "SapClassBasic.h"


class Camera
{

private:
	int height_;
	int width_;
	int num_elements_;

	int bytes_per_pixel_;

	void* image_buffer_;

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
	bool initialize();
	uint16_t* snap();
	bool terminate();

	bool isInitialized();
};

