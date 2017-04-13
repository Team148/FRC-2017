/*
 * PinholeCamera.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: james_tonthat
 */

#include <Util/PinholeCamera.h>

/**
 * Will calculate distance to goal and angle offset
 * Need to call update every time new target information is acquired to return proper Yaw/Distance
 */
PinholeCamera::PinholeCamera(int pixel_width, int pixel_height, float FOV_width,
		float FOV_height, int angle_offset, float target_height) {
	// TODO Auto-generated constructor stub
	m_pixel_width = pixel_width;
	m_pixel_height = pixel_height;
	m_FOV_width = (FOV_width*2*M_PI)/360;		//converts to radians
	m_FOV_height = (FOV_height*2*M_PI)/360;		//converts to radians
	m_angle_offset = angle_offset;
	m_target_height = target_height;			//in inches

	m_target_horizontal_pixel = pixel_height/2;
	m_target_vertical_pixel = pixel_width/2;

	//averages focal lengths
	m_focal_length = (((float)m_pixel_width/(2*tan(m_FOV_width/2))) + ((float)m_pixel_height/(2*tan(m_FOV_width/2)))) / 2.0;
}

/***
 * Call this with new target info to update Pinhole Camera Model
 */
void PinholeCamera::Update(int target_horizontal_pixel, int target_vertical_pixel) {
	m_target_horizontal_pixel = target_horizontal_pixel;
	m_target_vertical_pixel = target_vertical_pixel;
}

/***
 * Gets Pitch Angle (Up/Down) and Adds the Camera offset (assuming camera isn't horizontal)
 * Returns Radians
 */
float PinholeCamera::GetPitchAngle() {
	return m_angle_offset + atan((m_target_vertical_pixel - (m_pixel_height/2)/m_focal_length));
}

/***
 * Returns Pitch Angle (Up/Down) in Degrees
 */
float PinholeCamera::GetPitchAngleDegrees() {
	return (GetPitchAngle()/(2*M_PI))*360.0;
}

/***
 * Returns Yaw Angle (left/right) in Radians
 */
float PinholeCamera::GetYawAngle() {
	return atan((m_target_horizontal_pixel - (m_pixel_width/2)/m_focal_length));
}

/***
 * Returns Yaw Angle (left/right) in Degrees
 */
float PinholeCamera::GetYawAngleDegrees() {
	return (GetYawAngle()/(2*M_PI))*360.0;
}

/***
 * Returns Distance to Target in Inches
 */
float PinholeCamera::GetDistance() {
	return m_target_height*tan(GetPitchAngle());
}
