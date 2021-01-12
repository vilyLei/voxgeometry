/**
Author: Vily

*/

#pragma once
#include <vector>
#include <iostream>
#include "StNode.h"
namespace simnav
{
	namespace stara
	{
		class StObj
		{
		public:
			StObj()											= default;
			~StObj()										= default;
			int												sai;
			int												sbi;
		};

		class BinaryHeap
		{
		public:
			BinaryHeap();
			~BinaryHeap();

			void initialize(std::vector<StNode*>* dataArr);
			std::vector<StNode*>* getArray();
			void reset();
			unsigned int getLength();
			void insertEle(StNode* dataObj);
			StNode* getTopNode();
			void delTopEle();
			bool compareState(StNode* objA, StNode* objB);

		private:
			std::vector<StNode*>							*m_binaryHeapArr;
			unsigned int									m_listLen;
			unsigned int									m_indexA;
			unsigned int									m_indexB;
			StObj											m_tempObj;

			int getParentNodeIndex(unsigned int currentIndex);
			void getSubNodeIndex(unsigned int currentIndex, unsigned int t_len, StObj& obj);
		};

	}
}

typedef simnav::stara::BinaryHeap BinaryHeap;
