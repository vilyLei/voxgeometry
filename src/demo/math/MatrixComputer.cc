#include <iostream>

#include "MatrixComputer.h"

namespace demo
{
	namespace math
	{
		VCG_Number MatrixComputer::s_initMatData[16]{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		};
		MatrixComputer::MatrixComputer()
			: m_initBoo(true)
			, m_total(0)
			, m_matrixData(nullptr)
			, m_paramData(nullptr)
			, m_iData(nullptr)
			, m_mat4(nullptr)
		{

		}
		void MatrixComputer::allocate(unsigned int total)
		{
			if (m_initBoo && total > 0)
			{
				m_initBoo = false;
				m_total = total;
				size_t size = static_cast<size_t>(total);
				m_matrixData = new VCG_Number[size * 16];

				// scale x,scale y,scale z,	rotation x,rotation y,rotation z,	position x,position y,position z
				m_paramData = new VCG_Number[size * 9]{};
				m_iData = new unsigned short[total]{};

				m_mat4 = new Matrix4(m_matrixData, 0);
				
				for (size_t i = 0; i < size; ++i)
				{
					std::memcpy(m_matrixData + i * 16, &s_initMatData, VCG_MATRIX4_DATA_SIZE);
				}
			}
		}
		unsigned int MatrixComputer::getMatTotal()
		{
			return m_total;
		}
#ifdef WASM_DEV_ENV
		emscripten::val MatrixComputer::getMatData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_total * 16, m_matrixData));
		}
		emscripten::val MatrixComputer::getParamData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_total * 9, m_paramData));
		}
		emscripten::val MatrixComputer::getIData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_total, m_iData));
		}
#else
		VCG_Number* MatrixComputer::getMatData()
		{
			return m_matrixData;
		}
		VCG_Number* MatrixComputer::getParamData()
		{
			return m_paramData;
		}
		unsigned short* MatrixComputer::getIData()
		{
			return m_iData;
		}
#endif

		void  MatrixComputer::setScaleXYZParamAt(VCG_Number psx, VCG_Number psy, VCG_Number psz, unsigned int index)
		{
			index *= 9;
			m_paramData[index] = psx;
			m_paramData[index+1] = psy;
			m_paramData[index+2] = psz;
		}
		void  MatrixComputer::setRotationEulerAngleParamAt(VCG_Number prx, VCG_Number pry, VCG_Number prz, unsigned int index)
		{
			index *= 9;
			m_paramData[index + 3] = prx;
			m_paramData[index + 4] = pry;
			m_paramData[index + 5] = prz;
		}
		void  MatrixComputer::setTranslationXYZParamAt(VCG_Number px, VCG_Number py, VCG_Number pz, unsigned int index)
		{
			index *= 9;
			m_paramData[index + 6] = px;
			m_paramData[index + 7] = py;
			m_paramData[index + 8] = pz;
		}
		void MatrixComputer::identityAt(unsigned int index)
		{
			size_t i = static_cast<size_t>(index) * 16;
			std::memcpy(m_matrixData + i, &s_initMatData, VCG_MATRIX4_DATA_SIZE);
		}
		void  MatrixComputer::setScaleXYZAt(VCG_Number psx, VCG_Number psy, VCG_Number psz, unsigned int index)
		{
			m_mat4->identity();
			m_mat4->setScaleXYZ(psx,psy,psz);
		}
		void  MatrixComputer::setRotationEulerAngleAt(VCG_Number prx, VCG_Number pry, VCG_Number prz, unsigned int index)
		{
			m_mat4->setRotationEulerAngle(prx, pry, prz);
		}
		void  MatrixComputer::setTranslationXYZAt(VCG_Number px, VCG_Number py, VCG_Number pz, unsigned int index)
		{
			m_mat4->setTranslationXYZ(px, py, pz);
			m_mat4->copyToF32Arr(m_matrixData, index);
		}
		void MatrixComputer::copyFromMatrixAt(const Matrix4& mat4, unsigned int index)
		{
			size_t i = static_cast<size_t>(index) * 16;
			std::memcpy(m_matrixData + i, mat4.getLocalFS32(), VCG_MATRIX4_DATA_SIZE);
		}

		void MatrixComputer::calcMotion(VCG_Number cx, VCG_Number cz, VCG_Number time, VCG_Number radius, VCG_Number size, unsigned int total)
		{
			if (m_total > 0 && total <= m_total)
			{
				VCG_Number px;
				VCG_Number py;
				VCG_Number pz;
				unsigned int i = 0;
				unsigned int k = 0;
				auto pvs = m_paramData;
				radius = 1.0f / radius;
				for (; i < total; ++i)
				{
					k = i * 9 + 6;
					px = pvs[k] - cx;
					py = pvs[k + 1];
					pz = pvs[k + 2] - cz;
					px = sin(time + std::sqrt(px * px + pz * pz) * radius);
					pvs[k + 1] = py + (size  * px);
				}
			}
		}
		void MatrixComputer::calc(unsigned int total)
		{
			if (m_total > 0 && total <= m_total)
			{
				unsigned int i = 0;
				unsigned int k = 0;
				auto pvs = m_paramData;
				auto& mat4 = *m_mat4;
				for (; i < total; ++i)
				{
					mat4.setF32ArrIndex(i * 16);
					//mat4.coutThis();
					mat4.setScaleXYZ(pvs[k], pvs[k+1], pvs[k+2]);
					mat4.setRotationEulerAngle(pvs[k+3] * VCG_MATH_PI_OVER_180, pvs[k+4] * VCG_MATH_PI_OVER_180, pvs[k+5] * VCG_MATH_PI_OVER_180);
					mat4.setTranslationXYZ(pvs[k+6], pvs[k+7], pvs[k+8]);
					//mat4.coutThis();
					k += 9;
				}
			}
		}
		void MatrixComputer::coutThisMatAt(unsigned int index)
		{
			index *= 16;
			std::cout << "\n" << m_matrixData[index + 0] << "," << m_matrixData[index + 1] << "," << m_matrixData[index + 2] << "," << m_matrixData[index + 3] << "\n"
				<< m_matrixData[index + 4] << "," << m_matrixData[index + 5] << "," << m_matrixData[index + 6] << "," << m_matrixData[index + 7] << "\n"
				<< m_matrixData[index + 8] << "," << m_matrixData[index + 9] << "," << m_matrixData[index + 10] << "," << m_matrixData[index + 11] << "\n"
				<< m_matrixData[index + 12] << "," << m_matrixData[index + 13] << "," << m_matrixData[index + 14] << "," << m_matrixData[index + 15] << "\n";
		}
		void MatrixComputer::coutThis()
		{
			std::cout << "MatrixComputer coutThis()..." << std::endl;
		}

		MatrixComputer::~MatrixComputer()
		{
			if (m_matrixData != nullptr)
			{
				m_total = 0;
				delete[] m_matrixData;
				delete[] m_paramData;
				delete[] m_iData;
				m_matrixData = nullptr;
				m_paramData = nullptr;
				m_iData = nullptr;

				delete m_mat4;
				m_mat4 = nullptr;
			}
		}

	}
}