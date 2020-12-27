
/**
Author: Vily

*/
#pragma once
#include <cmath>
#include "../../voxcgeom/cgeomPre.h"
#include "../../voxcgeom/math/Matrix4.h"
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
			unsigned int getTotal();
			VCG_Number* getData();
			VCG_Number* getParamData();
			unsigned char* getIData();
			void calc(unsigned int total);
			void coutThis();
			virtual ~MatrixComputer()																= default;
		private:
			bool				m_initBoo;
			unsigned int		m_total;
			VCG_Number*			m_data;
			VCG_Number*			m_paramData;
			unsigned char*		m_iData;
			Matrix4				m_mat4;
		};
	}
}
typedef demo::math::MatrixComputer MatrixComputer;