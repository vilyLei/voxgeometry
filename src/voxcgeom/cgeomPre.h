
/**
Author: Vily

*/
#pragma once

#define VCG_MATH_E								2.71828182845904523536					// e
#define VCG_MATH_LOG2E							1.44269504088896340736					// log2(e)
#define VCG_MATH_LOG10E							0.43429448190325182765					// log10(e)
#define VCG_MATH_LN2							0.69314718055994530941					// ln(2)
#define VCG_MATH_LN10							2.30258509299404568402					// ln(10)
#define VCG_MATH_PI								3.14159265358979323846					// pi
#define VCG_MATH_2PI							6.28318530717958647652					// 2pi
#define VCG_MATH_PI_OVER_2						1.57079632679489661923					// pi/2
#define VCG_MATH_PI_OVER_4						0.78539816339744830962					// pi/4
#define VCG_MATH_1_OVER_PI						0.31830988618379067154					// 1/pi
#define VCG_MATH_2_OVER_PI						0.63661977236758134308					// 2/pi
#define VCG_MATH_180_OVER_PI					57.29577951308232286465					// 180/pi
#define VCG_MATH_PI_OVER_180					0.01745329251994329547					// pi/180
#define VCG_MATH_2_OVER_SQRTPI					1.12837916709551257390					// 2/sqrt(pi)
#define VCG_MATH_SQRT2							1.41421356237309504880					// sqrt(2)
#define VCG_MATH_1_OVER_SQRT2					0.70710678118654752440					// 1/sqrt(2)

#ifdef WASM_DEV_ENV
typedef double									VCG_Number;
#else
typedef double									VCG_Number;
#endif
const size_t									VCG_Number_SIZE = sizeof(VCG_Number);
const size_t									VCG_MATRIX4_DATA_SIZE = VCG_Number_SIZE * 16;
const VCG_Number								VCG_MATH_MIN_POSITIVE = 1e-7f;
const VCG_Number								VCG_MATH_MAX_POSITIVE = 3.4e20f;
const VCG_Number								VCG_MATH_MIN_NEGATIVE = -3.4e20f;
const VCG_Number								VCG_MATH_MAX_NEGATIVE = -1e-7f;
#ifndef __VCG_MATH_H__
#define __VCG_MATH_H__
extern VCG_Number SafeACos(VCG_Number x);
extern void SinCos(VCG_Number* returnSin, VCG_Number* returnCos, VCG_Number rad_theta);
#endif