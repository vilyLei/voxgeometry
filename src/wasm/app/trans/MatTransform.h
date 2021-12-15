

/**
Author: Vily

*/
#pragma once
#include <cmath>
#include "../../../voxcgeom/cgeomPre.h"
#include "../../../voxcgeom/math/Matrix4.h"
#include "../../../voxcgeom/math/Matrix4Container.h"
#ifdef WASM_DEV_ENV
#include <emscripten.h>
#include <emscripten/val.h>
#endif // WASM_DEV_ENV

namespace app
{
	namespace trans
	{
		class AbsTar
		{
		public:
			AbsTar();
			Matrix4Container				*body;

			virtual void update() = 0;
			virtual void destroy() = 0;
		};
		class MatTransTar: public AbsTar
		{
		public:
			MatTransTar();
			~MatTransTar();


			VCG_Number body_ry;
			VCG_Number tar0_ry;
			VCG_Number tar1_ry;

			//Matrix4Container* body;
			Matrix4Container* part0;
			Matrix4Container* part1;
			Matrix4Container* tar0;
			Matrix4Container* tar1;

			virtual void update() override;
			virtual void destroy() override;
		private:

		};

		class MatTransCar : public AbsTar
		{
		public:
			MatTransCar();
			~MatTransCar();

			VCG_Number zr;
			VCG_Number zrSpd;

			Matrix4Container* part0;
			Matrix4Container* part1;

			Matrix4Container* tar0;
			Matrix4Container* tar1;
			Matrix4Container* tar2;
			Matrix4Container* tar3;

			virtual void update() override;
			virtual void destroy() override;
		private:

		};

		class MatTransform
		{
		public:
			MatTransform();
			~MatTransform();


			void allocate(unsigned int total);
			void allocate2(unsigned int total);
			unsigned int getMatTotal();
			void identityAt(unsigned int index);
			void updateParam2();
			void updateParam2MIn();
			void updateParam();
			void calc();

#ifdef WASM_DEV_ENV
			emscripten::val getStatusData();
			emscripten::val getMatData();
			emscripten::val getParamData();
			//	emscripten::val getIData();
#else
			VCG_Uint16* getStatusData();
			VCG_Number* getMatData();
			VCG_Number* getParamData();
			//	unsigned short* getIData();
#endif
			void coutThisParamAt(unsigned int index);
			void coutThisMatAt(unsigned int index);
			void coutThis();
		private:

			static VCG_Number						s_initMatData[16];
			bool									m_initBoo;
			unsigned int							m_total;
			unsigned int							m_index;
			size_t									m_statusDataTotal;
			size_t									m_matrixDataTotal;
			size_t									m_paramDataTotal;
			VCG_Uint16								*m_statusData;
			VCG_Number								*m_matrixData;
			VCG_Number								*m_paramData;
			Matrix4Container						*m_matContainer;
			size_t									m_tarsLen;
			std::vector<AbsTar*>					m_tars;

			void createContainer2();
			void createContainer();

		};
	}
}
typedef app::trans::MatTransform MatTransform;