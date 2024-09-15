/**************************************************************************
 * @file TestCases.h
 * @author 	TAN Angus Yit Hoe
 * @param DP email: tan.a@digipen.edu [0067684]
 * @param Course: CS 350
 * @param Course: Advanced Computer Graphics II
 * @date  06/14/2024 (14 JUNE 2024)
 * @brief
 *
 * This file stores the boolean and enums for the checks to be tested.
 *
 *************************************************************************/


#pragma once

#ifndef TESTCASE_H
#define TESTCASE_H


#define PROJECT_ONE 1
#define PROJECT_TWO 0
#define PROJECT_THREE 0

namespace TESTCASE {




	enum testcases {

		SPHERE_VS_SPHERE = 0,
		AABB_VS_SPHERE,
		SPHERE_VS_AABB,
		AABB_VS_AABB,

		POINT_VS_SPHERE,
		POINT_VS_AABB,
		POINT_VS_PLANE,
		POINT_VS_TRIANGLE,

		RAY_VS_PLANE,
		RAY_VS_TRIANGLE,
		RAY_VS_AABB,
		RAY_VS_SPHERE,

		PLANE_VS_AABB,
		PLANE_VS_SPHERE
	};

	enum BVolume
	{
		BOUNDING_VOLUME_AABB = 0,
		BOUNDING_VOLUME_SPHERE_RITTER,
		BOUNDING_VOLUME_SPHERE_LARSSON,
		BOUNDING_VOLUME_SPHERE_PCA,
		BOUNDING_VOLUME_ORIGINAL_SPHERE
	};


	inline bool drawRectangle = false;
	inline bool Sphere_vs_Sphere = false;
	inline bool AABB_vs_Sphere = false;
	inline bool Sphere_vs_AABB = false;
	inline bool AABB_vs_AABB = false;

	inline bool Point_vs_Sphere = false;
	inline bool Point_vs_AABB = false;
	inline bool Point_vs_Plane = false;
	inline bool Point_vs_Triangle = false;

	inline bool Ray_vs_Plane = false;
	inline bool Ray_vs_Triangle = false;
	inline bool Ray_vs_AABB = false;
	inline bool Ray_vs_Sphere = false;

	inline bool Plane_vs_AABB = false;
	inline bool Plane_vs_Sphere = false;



	inline bool AABB_BOUNDING_VOLUME = false;
	inline bool SPHERE_RITTER = false;
	inline bool SPHERE_LARSSON = false;
	inline bool SPHERE_PCA = false;
	inline bool ORIGINAL_SPHERE = false;




	inline bool mouseEnabled = false;



	/**************************************************************************
	 * @brief On the selected, and OFF the rest.
	 * @param int : testCase using ENUM above
	 *************************************************************************/
	inline void turnOnOffTest(int testCase)
	{
		if (testCase == SPHERE_VS_SPHERE)
		{

			drawRectangle = false;
			Sphere_vs_Sphere = true;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
		}
		else if (testCase == AABB_VS_SPHERE)
		{
			drawRectangle = false;
			// Set the corresponding  ean variables for SPHERE_VS_AABB
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = true;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
		}
		else if (testCase == SPHERE_VS_AABB)
		{
			// Set the corresponding  ean variables for SPHERE_VS_AABB
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = true;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
		}
		else if (testCase == AABB_VS_AABB)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = true;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for AABB_VS_AABB
		}
		else if (testCase == POINT_VS_SPHERE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = true;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for POINT_VS_SPHERE
		}
		else if (testCase == POINT_VS_AABB)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = true;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for POINT_VS_AABB
		}
		else if (testCase == POINT_VS_PLANE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = true;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for POINT_VS_PLANE
		}
		else if (testCase == POINT_VS_TRIANGLE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = true;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for POINT_VS_TRIANGLE
		}
		else if (testCase == RAY_VS_PLANE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = true;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for RAY_VS_PLANE
		}
		else if (testCase == RAY_VS_TRIANGLE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = true;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for RAY_VS_TRIANGLE
		}
		else if (testCase == RAY_VS_AABB)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = true;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for RAY_VS_AABB
		}
		else if (testCase == RAY_VS_SPHERE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = true;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for RAY_VS_SPHERE
		}
		else if (testCase == PLANE_VS_AABB)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = true;
			Plane_vs_Sphere = false;
			// Set the corresponding  ean variables for PLANE_VS_AABB
		}
		else if (testCase == PLANE_VS_SPHERE)
		{
			Sphere_vs_Sphere = false;

			AABB_vs_Sphere = false;
			Sphere_vs_AABB = false;
			AABB_vs_AABB = false;

			Point_vs_Sphere = false;
			Point_vs_AABB = false;
			Point_vs_Plane = false;
			Point_vs_Triangle = false;

			Ray_vs_Plane = false;
			Ray_vs_Triangle = false;
			Ray_vs_AABB = false;
			Ray_vs_Sphere = false;

			Plane_vs_AABB = false;
			Plane_vs_Sphere = true;
			// Set the corresponding  ean variables for PLANE_VS_SPHERE
		}
	}



	inline void turnOnOffTestPROJECT2(int testCase)
	{
		if (testCase == BOUNDING_VOLUME_AABB)
		{
			AABB_BOUNDING_VOLUME = true;
			SPHERE_RITTER = false;
			SPHERE_LARSSON = false;
			SPHERE_PCA = false;
			ORIGINAL_SPHERE = false;
		}
		else if (testCase == BOUNDING_VOLUME_SPHERE_RITTER)
		{
			AABB_BOUNDING_VOLUME = false;
			SPHERE_RITTER = true;
			SPHERE_LARSSON = false;
			SPHERE_PCA = false;
			ORIGINAL_SPHERE = false;
		}
		else if (testCase == BOUNDING_VOLUME_SPHERE_LARSSON)
		{
			AABB_BOUNDING_VOLUME = false;
			SPHERE_RITTER = false;
			SPHERE_LARSSON = true;
			SPHERE_PCA = false;
			ORIGINAL_SPHERE = false;
		}
		else if (testCase == BOUNDING_VOLUME_SPHERE_PCA)
		{
			AABB_BOUNDING_VOLUME = false;
			SPHERE_RITTER = false;
			SPHERE_LARSSON = false;
			SPHERE_PCA = true;
			ORIGINAL_SPHERE = false;
		}
		else if(testCase == BOUNDING_VOLUME_ORIGINAL_SPHERE)
		{
			AABB_BOUNDING_VOLUME = false;
			SPHERE_RITTER = false;
			SPHERE_LARSSON = false;
			SPHERE_PCA = false;
			ORIGINAL_SPHERE = true;
		}
	}


}
#endif