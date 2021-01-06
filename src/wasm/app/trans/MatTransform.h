

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
		class MatTransTar
		{
		public:
			MatTransTar();
			~MatTransTar();


			VCG_Number body_ry;
			VCG_Number tar0_ry;
			VCG_Number tar1_ry;

			Matrix4Container* body;
			Matrix4Container* part0;
			Matrix4Container* part1;
			Matrix4Container* tar0;
			Matrix4Container* tar1;

			void update();
			void destroy();
		private:

		};
		class MatTransform
		{
		public:
			MatTransform();
			~MatTransform();


			void allocate(unsigned int total);
			unsigned int getMatTotal();
			void identityAt(unsigned int index);
			void updateParam();
			void calc();

#ifdef WASM_DEV_ENV
			emscripten::val getMatData();
			emscripten::val getParamData();
			//	emscripten::val getIData();
#else
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
			VCG_Number								*m_matrixData;
			VCG_Number								*m_paramData;
			Matrix4Container						*m_matContainer;
			size_t									m_tarsLen;
			std::vector<MatTransTar*>				m_tars;

			void createContainer();

		};
	}
}
typedef app::trans::MatTransform MatTransform;