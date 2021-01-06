
/**
Author: Vily

*/
#pragma once
#include <cmath>
#include "../../voxcgeom/cgeomPre.h"
#include "../../voxcgeom/math/Matrix4.h"
#ifdef WASM_DEV_ENV
#include <emscripten.h>
#include <emscripten/val.h>
#endif // WASM_DEV_ENV

namespace demo
{
	namespace math
	{
		class MatrixComputer
		{
		public:

            MatrixComputer();
			MatrixComputer(const MatrixComputer& v3)												= delete;
			MatrixComputer(MatrixComputer&& rhs)													= delete;
			MatrixComputer& operator=(const MatrixComputer& rhs)									= delete;
			MatrixComputer& operator=(MatrixComputer&& rhs)											= delete;

			void allocate(unsigned int total);
			unsigned int getMatTotal();

#ifdef WASM_DEV_ENV
			emscripten::val getMatData();
			emscripten::val getParamData();
			emscripten::val getIData();
#else
			VCG_Number* getMatData();
			VCG_Number* getParamData();
			unsigned short* getIData();
#endif
			void setScaleXYZParamAt(VCG_Number psx, VCG_Number psy, VCG_Number psz, unsigned int index);
			void setRotationEulerAngleParamAt(VCG_Number prx, VCG_Number pry, VCG_Number prz, unsigned int index);
			void setTranslationXYZParamAt(VCG_Number px, VCG_Number py, VCG_Number pz, unsigned int index);
			void identityAt(unsigned int index);
			void setScaleXYZAt(VCG_Number psx, VCG_Number psy, VCG_Number psz, unsigned int index);
			void setRotationEulerAngleAt(VCG_Number prx, VCG_Number pry, VCG_Number prz, unsigned int index);
			void setTranslationXYZAt(VCG_Number px, VCG_Number py, VCG_Number pz, unsigned int index);
			void copyFromMatrixAt(const Matrix4& mat4, unsigned int index);
			void calcMotion(VCG_Number cx, VCG_Number cz, VCG_Number time, VCG_Number radius, VCG_Number size, unsigned int total);
			void calc(unsigned int total);
			void coutThisMatAt(unsigned int index);
			void coutThis();
			virtual ~MatrixComputer();
		private:
			static VCG_Number	s_initMatData[16];
			bool				m_initBoo;
			unsigned int		m_total;
			VCG_Number			*m_matrixData;
			VCG_Number			*m_paramData;
			unsigned short		*m_iData;
			Matrix4				*m_mat4;
		};
	}
}
typedef demo::math::MatrixComputer MatrixComputer;