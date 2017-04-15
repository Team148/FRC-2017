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
	PinholeCamera(float pixel_width, float pixel_height, float FOV_width,
			float FOV_height, float yaw_angle_offset, float target_height = 64.5);
	void Update(int target_horizontal_pixel, int target_vertical_pixel);
	float GetPitchAngle();
	float GetPitchAngleDegrees();
	float GetYawAngle();
	float GetYawAngleDegrees();
	float GetDistance();
	float GetFocalLength();
	void SetNeutralAxisOffset(float angle);
	float GetNeutralAxisOffset();

private:
	float m_pixel_width;
	float m_pixel_height;
	float m_target_horizontal_pixel;
	float m_target_vertical_pixel;
	float m_neutral_horizontal_pixel;
	float m_neutral_vertical_pixel;
	float m_yaw_angle_offset;
	float m_target_height;
//	float m_diagonal_FOV;
	float m_FOV_width;
	float m_FOV_height;
//	float m_aspect_ratio;
	float m_focal_length;

};

#endif /* SRC_UTIL_PINHOLECAMERA_H_ */
