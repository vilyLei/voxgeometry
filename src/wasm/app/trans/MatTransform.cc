
#include <iostream>
#include "MatTransform.h"

namespace app
{
	namespace trans
	{
		AbsTar::AbsTar()
			: body(nullptr)
		{
		}
		/// <summary>
		/// ///////////////////////////////
		/// </summary>
		MatTransTar::MatTransTar()
			: body_ry(0.0f)
			, tar0_ry(0.0f)
			, tar1_ry(0.0f)
			, part0(nullptr)
			, part1(nullptr)
			, tar0(nullptr)
			, tar1(nullptr)
		{
		}
		MatTransTar::~MatTransTar()
		{
			destroy();
		}

		void MatTransTar::update()
		{
			body->setRotationY(body_ry);

			tar0->setRotationY(tar0_ry);
			tar1->setRotationY(tar1_ry);
			//	tar0->update();
			//	tar1->update();
			body->update();

			body_ry += 0.1f;
			tar0_ry += 0.2f;
			tar1_ry += 0.3f;
		}

		void MatTransTar::destroy()
		{
			if (body != nullptr)
			{
				body->destroy();
				delete body;
				delete part0;
				delete part1;
				delete tar0;
				delete tar1;
				body = nullptr;
				part0 = nullptr;
				part1 = nullptr;
				tar0 = nullptr;
				tar1 = nullptr;
			}
		}
		/// <summary>
		/// ////////////////////////////////
		/// </summary>

		MatTransCar::MatTransCar()
			: zr(0.0f)
			, zrSpd(0.1f)
			, part0(nullptr)
			, part1(nullptr)
			, tar0(nullptr)
			, tar1(nullptr)
			, tar2(nullptr)
			, tar3(nullptr)
		{
		}
		MatTransCar::~MatTransCar()
		{
			destroy();
		}

		void MatTransCar::update()
		{
			part0->setRotationZ(zr);
			part1->setRotationZ(zr);
			zr += zrSpd;
			body->update();
		}

		void MatTransCar::destroy()
		{
			if (body != nullptr)
			{
				body->destroy();
				delete body;
				delete part0;
				delete part1;
				delete tar0;
				delete tar1;
				body = nullptr;
				part0 = nullptr;
				part1 = nullptr;
				tar0 = nullptr;
				tar1 = nullptr;
			}
		}
		

        /// ///////////////////////////////////////////////////////////	///
		
        VCG_Number MatTransform::s_initMatData[16]{
            1.0f,0.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
            0.0f,0.0f,0.0f,1.0f
        };
        MatTransform::MatTransform()
            : m_initBoo(true)
            , m_total(0)
			, m_index(0)
			, m_matrixDataTotal(0)
			, m_paramDataTotal(0)
            , m_matrixData(nullptr)
            , m_paramData(nullptr)
			, m_matContainer(nullptr)
			, m_tarsLen(0)
        {
        }
        MatTransform::~MatTransform()
        {
			if (m_matrixData != nullptr)
			{
				if (m_tarsLen > 0)
				{
					auto it = m_tars.begin();
					auto end = m_tars.end();
					for (; it != end; ++it)
					{
						(*it)->destroy();
						//(*it) = nullptr;
					}
					std::vector<AbsTar*>().swap(m_tars);
					m_tarsLen = 0;
				}
				delete[] m_matrixData;
				m_matrixData = nullptr;
			}
			if (m_paramData == nullptr)
			{
				delete[] m_paramData;
				m_paramData = nullptr;
			}
        }

		void MatTransform::allocate(unsigned int total)
		{
			if (m_initBoo && total > 0)
			{
				m_initBoo = false;
				m_total = total;
				size_t size = static_cast<size_t>(total);
				m_matrixDataTotal = size * 16 * 2;
				m_paramDataTotal = size * 16;
				m_matrixData = new VCG_Number[m_matrixDataTotal];
				
				// scale x,scale y,scale z,	rotation x,rotation y,rotation z,	position x,position y,position z
				m_paramData = new VCG_Number[m_paramDataTotal]{};

				size_t matTot = size * 2;
				size_t i = 0;
				for (; i < matTot; ++i)
				{
					std::memcpy(m_matrixData + i * 16, &s_initMatData, VCG_MATRIX4_DATA_SIZE);
				}
				for (i = 0; i < size; ++i)
				{
					createContainer();
				}
			}
		}

		void MatTransform::allocate2(unsigned int total)
		{
			if (m_initBoo && total > 0)
			{
				m_initBoo = false;
				m_total = total;
				size_t size = static_cast<size_t>(total);
				m_matrixDataTotal = size * 16 * 5;
				m_paramDataTotal = size * 16;
				m_matrixData = new VCG_Number[m_matrixDataTotal];

				// scale x,scale y,scale z,	rotation x,rotation y,rotation z,	position x,position y,position z
				m_paramData = new VCG_Number[m_paramDataTotal]{};

				size_t matTot = size * 5;
				size_t i = 0;
				for (; i < matTot; ++i)
				{
					std::memcpy(m_matrixData + i * 16, &s_initMatData, VCG_MATRIX4_DATA_SIZE);
				}
				for (i = 0; i < size; ++i)
				{
					createContainer2();
				}
			}
		}

		unsigned int MatTransform::getMatTotal()
		{
			return m_total;
		}
		void MatTransform::identityAt(unsigned int index)
		{
			size_t i = static_cast<size_t>(index) * 16;
			std::memcpy(m_matrixData + i, &s_initMatData, VCG_MATRIX4_DATA_SIZE);
		}

		void MatTransform::updateParam2()
		{
			int k = 0;
			auto pvs = m_paramData;
			auto it = m_tars.begin();
			auto end = m_tars.end();
			VCG_Number scale = 1.0f;
			for (; it != end; ++it)
			{
				auto tar = dynamic_cast<MatTransCar*>(*it);
				auto& body = *(tar->body);
				body.setXYZ(pvs[k], pvs[k + 1], pvs[k + 2]);

				//std::cout << "pvs[k + 2]: " << pvs[k + 4] << std::endl;
				body.setRotationXYZ(pvs[k + 3], pvs[k + 4], pvs[k + 5]);
				scale = pvs[k + 6];
				body.setScaleXYZ(scale, scale, scale);
				tar->part0->setXYZ(pvs[k + 9], pvs[k + 10], 0.0f);
				tar->part1->setXYZ(-pvs[k + 9], pvs[k + 10], 0.0f);
				scale = pvs[k + 11];
				tar->tar0->setZ(scale);
				tar->tar1->setZ(-scale);
				tar->tar2->setZ(scale);
				tar->tar3->setZ(-scale);
				//std::cout << "pvs[k + 4]: " << pvs[k + 4] << std::endl;

				tar->zr = pvs[k + 12];
				tar->zrSpd = pvs[k + 13];
				scale = pvs[k + 14];
				tar->tar0->setScaleXYZ(scale, scale, scale);
				tar->tar1->setScaleXYZ(scale, scale, scale);
				tar->tar2->setScaleXYZ(scale, scale, scale);
				tar->tar3->setScaleXYZ(scale, scale, scale);

				body.update();
				k += 15;
			}
		}

		void MatTransform::updateParam2MIn()
		{
			int k = 0;
			auto pvs = m_paramData;
			auto it = m_tars.begin();
			auto end = m_tars.end();
			VCG_Number scale = 1.0f;
			for (; it != end; ++it)
			{
				auto tar = dynamic_cast<MatTransCar*>(*it);
				auto& body = *(tar->body);
				body.setXYZ(pvs[k], pvs[k + 1], pvs[k + 2]);

				//std::cout << "pvs[k + 2]: " << pvs[k + 4] << std::endl;
				body.setRotationXYZ(pvs[k + 3], pvs[k + 4], pvs[k + 5]);
				scale = pvs[k + 6];
				body.setScaleXYZ(scale, scale, scale);

				body.update();
				k += 15;
			}
		}
		void MatTransform::updateParam()
		{
			int k = 0;
			auto pvs = m_paramData;
			auto it = m_tars.begin();
			auto end = m_tars.end();
			for (; it != end; ++it)
			{
				auto tar = dynamic_cast<MatTransTar*>(*it);
				tar->tar0_ry = pvs[k + 4];
				auto& body = *(tar->body);
				body.setScaleXYZ(pvs[k], pvs[k + 1], pvs[k + 2]);
				//std::cout << "pvs[k + 4]: " << pvs[k + 4] << std::endl;
				body.setRotationXYZ(pvs[k + 3], pvs[k + 4], pvs[k + 5]);
				body.setXYZ(pvs[k + 6], pvs[k + 7], pvs[k + 8]);
				body.update();
				k += 9;
			}
		}
		void MatTransform::calc()
		{
			auto it = m_tars.begin();
			auto end = m_tars.end();
			for (; it != end; ++it)
			{
				(*it)->update();
			}
		}
#ifdef WASM_DEV_ENV
		emscripten::val MatTransform::getMatData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_matrixDataTotal, m_matrixData));
		}
		emscripten::val MatTransform::getParamData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_paramDataTotal, m_paramData));
		}
		//	emscripten::val MatTransform::getIData()
		//	{
		//		return emscripten::val(emscripten::typed_memory_view(m_total, m_iData));
		//	}
#else
		VCG_Number* MatTransform::getMatData()
		{
			return m_matrixData;
		}
		VCG_Number* MatTransform::getParamData()
		{
			return m_paramData;
		}
		//	unsigned short* MatTransform::getIData()
		//	{
		//		return m_iData;
		//	}
#endif

		void MatTransform::coutThisParamAt(unsigned int index)
		{
			index *= 9;
			std::cout << "\n" << m_paramData[index + 0] << "," << m_paramData[index + 1] << "," << m_paramData[index + 2] << "\n"
				<< m_paramData[index + 3] << "," << m_paramData[index + 4] << "," << m_paramData[index + 5] << "\n"
				<< m_paramData[index + 6] << "," << m_paramData[index + 7] << "," << m_paramData[index + 8] << "\n";
		}
		void MatTransform::coutThisMatAt(unsigned int index)
		{
			index *= 16;
			std::cout << "\n" << m_matrixData[index + 0] << "," << m_matrixData[index + 1] << "," << m_matrixData[index + 2] << "," << m_matrixData[index + 3] << "\n"
				<< m_matrixData[index + 4] << "," << m_matrixData[index + 5] << "," << m_matrixData[index + 6] << "," << m_matrixData[index + 7] << "\n"
				<< m_matrixData[index + 8] << "," << m_matrixData[index + 9] << "," << m_matrixData[index + 10] << "," << m_matrixData[index + 11] << "\n"
				<< m_matrixData[index + 12] << "," << m_matrixData[index + 13] << "," << m_matrixData[index + 14] << "," << m_matrixData[index + 15] << "\n";
		}
		void MatTransform::createContainer2()
		{
			auto bodyMat = new Matrix4(m_matrixData, 16 * m_index++);
			Matrix4Container* body = new Matrix4Container(bodyMat);
			Matrix4Container* part0 = new Matrix4Container();
			Matrix4Container* part1 = new Matrix4Container();

			//	std::cout << "MatTransform::createContainer2(), part0 uid: " << part0->getUid() << std::endl;
			//	std::cout << "MatTransform::createContainer2(), part1 uid: " << part1->getUid() << std::endl;
			body->addChild(part0);
			body->addChild(part1);

			auto tar0Mat = new Matrix4(m_matrixData, 16 * m_index++);
			auto tar1Mat = new Matrix4(m_matrixData, 16 * m_index++);
			auto tar2Mat = new Matrix4(m_matrixData, 16 * m_index++);
			auto tar3Mat = new Matrix4(m_matrixData, 16 * m_index++);

			Matrix4Container* tar0 = new Matrix4Container(tar0Mat);
			Matrix4Container* tar1 = new Matrix4Container(tar1Mat);
			Matrix4Container* tar2 = new Matrix4Container(tar2Mat);
			Matrix4Container* tar3 = new Matrix4Container(tar3Mat);

			part0->addChild(tar0);
			part0->addChild(tar1);
			part1->addChild(tar2);
			part1->addChild(tar3);

			//body->update();

			//std::cout << "MatTransform::createContainer2(), m_index: " << m_index << std::endl;
			auto tar = new MatTransCar();
			tar->body = body;
			tar->part0 = part0;
			tar->part1 = part1;
			tar->tar0 = tar0;
			tar->tar1 = tar1;
			tar->tar2 = tar2;
			tar->tar3 = tar3;
			m_tars.push_back(tar);
			m_tarsLen++;
		}
		void MatTransform::createContainer()
		{
			Matrix4Container* body = new Matrix4Container();
			Matrix4Container* part0 = new Matrix4Container();
			Matrix4Container* part1 = new Matrix4Container();

			part0->setXYZ(-250.0f, 0.0f, 0.0f);
			part1->setXYZ(250.0f, 0.0f, 0.0f);
			body->addChild(part0);
			body->addChild(part1);

			auto tar01Mat = new Matrix4(m_matrixData, 16 * m_index++);
			auto tar02Mat = new Matrix4(m_matrixData, 16 * m_index++);

			Matrix4Container* tar0 = new Matrix4Container(tar01Mat);
			Matrix4Container* tar1 = new Matrix4Container(tar02Mat);

			part0->addChild(tar0);
			part1->addChild(tar1);
			
			body->update();

			//std::cout << "MatTransform::createContainer(), m_index: " << m_index << std::endl;
			auto tar = new MatTransTar();
			tar->body = body;
			tar->part0 = part0;
			tar->part1 = part1;
			tar->tar0 = tar0;
			tar->tar1 = tar1;
			m_tars.push_back(tar);
			m_tarsLen++;
		}

        void MatTransform::coutThis()
        {
            std::cout << "MatTransform::coutThis()." << std::endl;
        }
	}
}