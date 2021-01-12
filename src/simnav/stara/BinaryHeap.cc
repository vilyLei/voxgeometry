/**
Author: Vily

*/

#include "BinaryHeap.h"
namespace simnav
{
	namespace stara
	{

		BinaryHeap::BinaryHeap()
			: m_binaryHeapArr(nullptr)
			, m_listLen(1)
			, m_indexA(0)
			, m_indexB(0)
		{
		}

		BinaryHeap::~BinaryHeap()
		{
		}

		void BinaryHeap::initialize(std::vector<StNode*>* dataArr)
		{
			m_binaryHeapArr = dataArr;

			//如果数组中的第一个元素不是0,那么就在当前数组最前面在插入一个元素，并且让它为null
			//m_binaryHeapArr[0] = null;
			if (m_binaryHeapArr == nullptr)
			{
				m_binaryHeapArr = new std::vector<StNode*>();
				m_binaryHeapArr->push_back( nullptr );
			}
			else
			{
				if (m_binaryHeapArr->size() == 0)
				{
					m_binaryHeapArr->push_back(nullptr);
				}
				else if ((*m_binaryHeapArr)[0] != nullptr)
				{
					m_binaryHeapArr->insert(m_binaryHeapArr->begin(), nullptr);
				}
			}
			m_listLen = 1;
		}
		std::vector<StNode*>* BinaryHeap::getArray()
		{
			return m_binaryHeapArr;
		}
		void BinaryHeap::reset()
		{
			m_listLen = 1;
		}
		unsigned int BinaryHeap::getLength()
		{
			return m_listLen;
		}
		void BinaryHeap::insertEle(StNode* node)
		{
			//首先将需要插入的数据放到m_binaryHeapArr 的尾部
			auto& list = *m_binaryHeapArr;
			m_binaryHeapArr->push_back(node);
			m_listLen++;

			unsigned int currentIndex = m_listLen - 1;
			int t_index = 0;
			StNode *tn = nullptr;
			StNode *tnb = nullptr;
			while (true)
			{
				//找到新的父节点
				t_index = getParentNodeIndex(currentIndex);
				if (t_index < 0) {
					break;
				}
				tn = list[currentIndex];
				tnb = list[t_index];
				if (compareState(tn, tnb))
				{

					//如果新加入的节点比其父节点的特征值小,那么父节点就和此节点交换
					list[currentIndex] = tnb;
					list[t_index] = tn;
					currentIndex = t_index;
				}
				else
				{
					break;
				}
			}
		}
		StNode* BinaryHeap::getTopNode()
		{
			if (m_listLen > 1)
			{
				return (*m_binaryHeapArr)[1];
			}
			return nullptr;
		}
		void BinaryHeap::delTopEle()
		{
			unsigned int maxIndex = m_listLen - 1;
			auto& list = *m_binaryHeapArr;
			if (maxIndex > 2)
			{
				//将原来的m_binaryHeapArr[1]的元素删除,将此数组末尾的元素移到m_binaryHeapArr[1]的位置
				list[1] = list[maxIndex];
				list.pop_back();

				m_listLen--;

				unsigned int t_index = 0;
				unsigned int currentIndex = 1;
				StNode* tn = nullptr;

				while (true)
				{
					getSubNodeIndex(currentIndex, m_listLen, m_tempObj);

					if (m_tempObj.sai > 0 && m_tempObj.sbi > 0)
					{
						if (compareState(list[m_tempObj.sai], list[m_tempObj.sbi]))
						{
							t_index = m_tempObj.sai;
						}
						else
						{
							t_index = m_tempObj.sbi;
						}
					}
					else if (m_tempObj.sai > 0 && m_tempObj.sbi < 0)
					{
						t_index = m_tempObj.sai;
					}
					else if (m_tempObj.sai < 0 && m_tempObj.sbi > 0)
					{
						t_index = m_tempObj.sbi;
					}
					else
					{
						break;
					}
					if (compareState(list[t_index], list[currentIndex]))
					{
						//如果当前节点比其第一个子节点大就和此子节点交换，如果比这两个子节点都小，循环检测就停止
						tn = list[t_index];
						list[t_index] = list[currentIndex];
						list[currentIndex] = tn;
						currentIndex = t_index;
					}
					else
					{
						break;
					}
				}
			}
			else if (maxIndex == 2)
			{
				//将此数组末尾的元素移到m_binaryHeapArr[1]的位置
				list[1] = list[maxIndex];
				list.pop_back();
				m_listLen--;
			}
			else if (maxIndex == 1)
			{
				m_binaryHeapArr->pop_back();
				m_listLen--;
			}
		}
		bool BinaryHeap::compareState(StNode* objA, StNode* objB)
		{
			return objA->F < objB->F;
		}

		int BinaryHeap::getParentNodeIndex(unsigned int currentIndex)
		{
			if (currentIndex % 2 == 0)
			{
				//如果当前索引为偶数
				return currentIndex >> 1;
			}
			else
			{
				if (currentIndex == 1)
				{
					//说明已经到了binaryHeaps的顶端
					return -1;
				}
				return (currentIndex - 1) >> 1;
			}

		}
		void BinaryHeap::getSubNodeIndex(unsigned int currentIndex, unsigned int t_len, StObj& obj)
		{
			obj.sai = currentIndex * 2;
			if (obj.sai >= t_len)
			{
				obj.sai = -1;
			}

			obj.sbi = currentIndex * 2 + 1;
			if (obj.sbi >= t_len)
			{
				obj.sbi = -1;
			}
		}
	}
}
/*
	public class BinaryHeap{
		private var m_binaryHeapArr:Array = null;
		private var listLen:int = 1;
		// 临时变量
		//private var indexA:int = 0;
		//private var indexB:int = 0;
		private var m_tempObj:Object = {};
		public function BinaryHeap(dataArr:Array = null){
			init(dataArr);
		}
		public function getArray():Array{
			return m_binaryHeapArr;
		}
		private function init(dataArr:Array):void{
			m_binaryHeapArr = dataArr;

			//如果数组中的第一个元素不是0,那么就在当前数组最前面在插入一个元素，并且让它为null
			//m_binaryHeapArr[0] = null;
			if(m_binaryHeapArr == null){
				m_binaryHeapArr = [];
				m_binaryHeapArr[0] = null;
			}else{
				if(m_binaryHeapArr.length == 0){
					m_binaryHeapArr[0] = null;
				}else if(m_binaryHeapArr[0] != null){
					m_binaryHeapArr.splice(0,0,null);
				}
			}
			listLen = 1;
		}
		public function reset():void{
			listLen = 1;
		}
		public function getLength():int{
			return listLen;
		}
		//插入新元素
		public function insertEle(dataObj:Node):void{

			//首先将需要插入的数据放到m_binaryHeapArr 的尾部
			m_binaryHeapArr.push(dataObj);
			listLen ++;

			//获取新插入的节点当前的索引值
			var currentIndex:int = listLen -1;
			var t_index:int = 0;
			var tn:Node = null;
			var tnb:Node = null;
			//for(;;){
			while(true){
				//找到新的父节点
				t_index = getParentNodeIndex(currentIndex);
				if(t_index<0){
					break;
				}
				tn = m_binaryHeapArr[currentIndex];
				tnb = m_binaryHeapArr[t_index];
				if(compareState(tn,tnb)){

					//如果新加入的节点比其父节点的特征值小,那么父节点就和此节点交换
					//tn = m_binaryHeapArr[currentIndex];
					m_binaryHeapArr[currentIndex] = tnb;//m_binaryHeapArr[t_index];
					m_binaryHeapArr[t_index] = tn;
					currentIndex = t_index;

				}else{
					break;
				}
			}
		}
		// 获取F值最小的节点
		public function getTopNode():Node{
			if(listLen > 1){
				return m_binaryHeapArr[1];
			}
			return null;
		}
		//删除元素,这个元素肯定是堆顶端的元素
		public function delTopEle():void{

			//首先删除m_binaryHeapArr[1]元素

			//var t_len:int = listLen;//m_binaryHeapArr.length;
			var maxIndex:int = listLen - 1;//t_len - 1;
			if(maxIndex>2){

				//将原来的m_binaryHeapArr[1]的元素删除,将此数组末尾的元素移到m_binaryHeapArr[1]的位置
				m_binaryHeapArr[1] = m_binaryHeapArr[maxIndex];
				m_binaryHeapArr.pop();
				//
				listLen --;
				//
				//t_len --;
				var t_index:int = 0;
				var currentIndex:int = 1;
				var tn:Node = null;

				//for(;;){
				while(true){
					//把m_binaryHeapArr[1]选作获作当前节点,和其子节点做比较如果比子节点小就终止操作
					//获取子节点
					//t_obj = getSubNodeIndex(currentIndex,listLen
					getSubNodeIndex(currentIndex,listLen,m_tempObj);
					//breakCount = 0;
					//选出两个子节点中F值最小的节点
					if(m_tempObj.sai > 0 && m_tempObj.sbi > 0){
						if(compareState(m_binaryHeapArr[m_tempObj.sai],m_binaryHeapArr[m_tempObj.sbi])){
							t_index = m_tempObj.sai;
						}else{
							t_index = m_tempObj.sbi;
						}
					}else if(m_tempObj.sai>0 && m_tempObj.sbi < 0){
						t_index = m_tempObj.sai;
					}else if(m_tempObj.sai<0 && m_tempObj.sbi > 0){
						t_index = m_tempObj.sbi;
					}else{
						break;
					}
					if(compareState(m_binaryHeapArr[t_index],m_binaryHeapArr[currentIndex])){
						//如果当前节点比其第一个子节点大就和此子节点交换，如果比这两个子节点都小，循环检测就停止
						tn = m_binaryHeapArr[t_index];
						m_binaryHeapArr[t_index] = m_binaryHeapArr[currentIndex];
						m_binaryHeapArr[currentIndex] = tn;
						currentIndex = t_index;
					}else{
						break;
					}
				}
			}else if(maxIndex == 2){
				//将此数组末尾的元素移到m_binaryHeapArr[1]的位置
				m_binaryHeapArr[1] = m_binaryHeapArr[maxIndex];
				m_binaryHeapArr.pop();
				listLen --;
			}else if(maxIndex == 1){
				m_binaryHeapArr.pop();
				listLen --;
			}
		}
		public function compareState(objA:Node,objB:Node):Boolean{
			return objA.F < objB.F;
		}
		// 计算当前节点的父节点在一维数组中的下标
		private function getParentNodeIndex(currentIndex:int):int{

			if(currentIndex%2 == 0){
				//如果当前索引为偶数
				return currentIndex/2;
			}else{
				if(currentIndex == 1){
					//说明已经到了binaryHeaps的顶端
					return -1;
				}
				return (currentIndex - 1)/2;
			}
		}

		// 计算当前节点的子节点的索引值
		private function getSubNodeIndex(currentIndex:int,t_len:int,obj:Object):void{

			obj.sai = currentIndex * 2;
			if(obj.sai >= t_len){
				obj.sai = -1;
			}

			obj.sbi = currentIndex * 2 + 1;
			if(obj.sbi >= t_len){
				obj.sbi = -1;
			}
		}
	}
}
//*/