
#include <iostream>

#include "MatrixComputer.h"

namespace demo
{
	namespace math
	{
		MatrixComputer::MatrixComputer()
			: m_initBoo(true)
			, m_total(0)
			, m_data(nullptr)
			, m_paramData(nullptr)
			, m_iData(nullptr)
		{

		}
		void MatrixComputer::allocate(unsigned int total)
		{
			if (m_initBoo && total > 0)
			{
				m_initBoo = false;
				m_total = total;
				size_t size = static_cast<size_t>(total);
				m_data = new VCG_Number[size * 16];
				// scale x,scale y,scale z,	rotation x,rotation y,rotation z,	position x,position y,position z
				m_paramData = new VCG_Number[size * 9];
				m_iData = new unsigned char[total];
			}
		}
		unsigned int MatrixComputer::getTotal()
		{
			return m_total;
		}
		VCG_Number* MatrixComputer::getData()
		{
			return m_data;
		}
		VCG_Number* MatrixComputer::getParamData()
		{
			return m_paramData;
		}
		unsigned char* MatrixComputer::getIData()
		{
			return m_iData;
		}
		void MatrixComputer::calc(unsigned int total)
		{
			if (total > 0 && m_total > 0 && total < m_total)
			{
				unsigned int i = 0;
				unsigned int k = 0;
				auto pvs = m_paramData;
				for (; i < total; ++i)
				{
					m_mat4.copyFromF32Arr(m_data, i);
					m_mat4.setScaleXYZ(pvs[k], pvs[k+1], pvs[k+2]);
					m_mat4.setRotationEulerAngle(pvs[k+3], pvs[k+4], pvs[k+5]);
					m_mat4.setTranslationXYZ(pvs[k+6], pvs[k+7], pvs[k+8]);
					k += 9;
				}
			}
		}
		void MatrixComputer::coutThis()
		{
			std::cout << "MatrixComputer coutThis()..." << std::endl;
		}

	}
}