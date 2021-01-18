/**
Author: Vily

*/

#pragma once
#include <vector>
//#include <array>
#include <iostream>
#include "StNode.h"
#include "BinaryHeap.h"

#ifdef WASM_DEV_ENV
#include <emscripten.h>
#include <emscripten/val.h>
#endif // WASM_DEV_ENV

namespace simnav
{
	namespace stara
	{
		class StarA
		{
		public:
			StarA();
			virtual ~StarA();

			static void Calc(unsigned int total);

			void allocate(unsigned int total);
#ifdef WASM_DEV_ENV
			emscripten::val getPathData();
#else
			unsigned short* getPathData();
#endif
			unsigned int getPathDataTotal();
			void buildTest();
			void initStateByGoValueList(std::vector<unsigned int>& stvs, unsigned int rn, unsigned int cn, unsigned int maxSteps = 200);
			void initialize(unsigned int rn = 20, unsigned int cn = 20, unsigned int maxSteps = 200);
			void searchPathDataByRC(unsigned int r0, unsigned int c0, unsigned int r1, unsigned int c1);
			std::vector<StNode*>* searchPathByRC(unsigned int r0, unsigned int c0, unsigned int r1, unsigned int c1);
			void setGoValueByRC(unsigned int go, unsigned int r, unsigned int c);
			void setMaxStepsNum(unsigned int p_m);
		private:

			StNode								*m_startStNode;// = null;// begin
			StNode								*m_endStNode;// = null;// dst end

			BinaryHeap							m_openBH;
			unsigned int						m_rn;
			unsigned int						m_cn;
			unsigned int						m_maxR;
			unsigned int						m_maxC;
			//记录允许的最大的搜寻步骤
			unsigned int						m_maxSteps;// 100;
			size_t								m_pathDataTot;
			unsigned int						m_pathTot;

			bool								m_isPath;// = false;//是否找到路径
			bool								m_isSearch;// = false;//寻路状态,即是否正在寻路
			bool								m_allocateBoo;

			std::vector<StNode*>				m_mapStNodesArr;
			std::vector<StNode*>				m_openList;//开启列表
			std::vector<StNode*>				m_closeList;//关闭列表			
			//临时path
			std::vector<StNode*>				m_roadArr;//返回的路径
			std::vector<StNode*>				m_keyNodeArr;//返回的路径
			StNode								m_start;
			StNode								m_end;
			unsigned short						*m_pathData;

			std::vector<StNode*>* searchPath(StNode* start, StNode* end);
			int getClosedRelativeDire(StNode *currStNode, StNode* targetStNode);
			// 将节点添加到开启列表
			void addToOpenList(StNode *o);
			// 将节点添加到关闭列表
			void addToCloseList(StNode *o);

			std::vector<StNode*>* getKeyNodes(std::vector<StNode*>& road_Arr);
			void addAroundNode(StNode* thisStNode);
			void addAroundNode2(StNode* thisStNode);


			//设置节点的G/H/F值－－－－－－－－－－－－－－－－－－－－－－－－－－－－》
			void setGHF(StNode* point, StNode* thisStNode, unsigned int g);

			//检查新的G值以判断新的路径是否更优
			void checkG(StNode* point, StNode* thisStNode);

		};
	}
}

typedef simnav::stara::StarA StarA;