/*
 * PinholeCamera.h
 *
 *  Created on: Apr 12, 2017
 *      Author: james_tonthat
 */

#ifndef SRC_UTIL_PINHOLECAMERA_H_
#define SRC_UTIL_PINHOLECAMERA_H_

#include <math.h>


class PinholeCamera {
public:
	PinholeCamera(int pixel_width, int pixel_height, float FOV_width, float FOV_height, int angle_offset, float target_height = 68);
	void Update(int target_horizontal_pixel, int target_vertical_pixel);
	float GetPitchAngle();
	float GetPitchAngleDegrees();
	float GetYawAngle();
	float GetYawAngleDegrees();
	float GetDistance();

private:
	int m_pixel_width;
	int m_pixel_height;
	int m_target_horizontal_pixel;
	int m_target_vertical_pixel;
	int m_angle_offset;
	float m_target_height;
//	float m_diagonal_FOV;
	float m_FOV_width;
	float m_FOV_height;
//	float m_aspect_ratio;
	float m_focal_length;

};

#endif /* SRC_UTIL_PINHOLECAMERA_H_ */
