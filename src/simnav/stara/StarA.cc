/**
Author: Vily

*/
#include <cmath>
#include "StarA.h"

namespace simnav
{
	namespace stara
	{
		StarA::StarA()
			: m_startStNode(nullptr), m_endStNode(nullptr)
			, m_rn(0), m_cn(0)
			, m_maxR(0), m_maxC(0), m_maxSteps(100)
			, m_pathDataTot(0), m_pathTot(0)
			, m_isPath(false), m_isSearch(false)
			, m_allocateBoo(true)
			, m_pathData(nullptr)
		{

		}
		StarA::~StarA()
		{
		}
		void StarA::allocate(unsigned int total)
		{
			if (m_allocateBoo && total > 0)
			{
				m_pathDataTot = static_cast<size_t>(total) * 2;
				m_pathData = new unsigned short[m_pathDataTot];
			}
		}
#ifdef WASM_DEV_ENV
		emscripten::val StarA::getPathData()
		{
			return emscripten::val(emscripten::typed_memory_view(m_pathDataTot, m_pathData));
		}
#else
		unsigned short* StarA::getPathData()
		{
			return m_pathData;
		}
#endif
		unsigned int StarA::getPathDataTotal()
		{
			return m_pathTot;
		}
		void StarA::buildTest()
		{
			std::cout << "StarA::buildTest()..." << std::endl;

			m_openBH.initialize(&m_openList);
			std::vector<unsigned int> stvs{
			0,0,0,0,0,0,
			0,0,1,1,0,0,
			0,0,0,0,0,0,
			0,0,0,1,0,0,
			0,0,0,1,0,0,
			0,0,0,0,0,0
			};

			/*
			StNode* node0 = new StNode();
			node0->F = 11;
			StNode* node1 = new StNode();
			node1->F = 13;
			StNode* node2 = new StNode();
			node2->F = 12;
			StNode* node3 = new StNode();
			node3->F = 9;
			m_openBH.insertEle(node0);
			m_openBH.insertEle(node2);
			m_openBH.insertEle(node1);
			m_openBH.insertEle(node3);

			StNode* node = m_openBH.getTopNode();

			std::cout << "StarA::buildTest()...top node.F: " << node->F << std::endl;
			//*/
			initStateByGoValueList(stvs,6,6,100);
			
			//	std::vector<StNode*>* path = searchPathByRC(0,0,4,4);
			//	std::cout << "StarA::buildTest().. path != nullptr: "<< (path != nullptr) << std::endl;
			//	if (path != nullptr)
			//	{
			//		size_t len = path->size();
			//		std::cout << "StarA::buildTest().. path->size(len): " << len << std::endl;
			//	}

			searchPathDataByRC(0, 0, 4, 4);
			unsigned int dataLen = getPathDataTotal();
			std::cout << "StarA::buildTest().. path dataLen: " << dataLen << std::endl;
			std::cout << "StarA::buildTest().. run end."<< std::endl;
		}

		void StarA::initStateByGoValueList(std::vector<unsigned int>& stvs, unsigned int rn, unsigned int cn, unsigned int maxSteps)
		{
			m_mapStNodesArr.clear();
//#define	TEST_STAR_1 1
#ifdef TEST_STAR_1

			initialize(rn, cn, maxSteps);
#endif // TEST_STAR_1

			int r = 0;
			int c = 0;
			int tot = rn * cn;
			int i = 0;
			for (; i < tot; ++i)
			{
#ifdef TEST_STAR_1

				setGoValueByRC(stvs[i], r, c);
#else

				StNode* st = new StNode();
				st->r = r;
				st->c = c;
				st->go = stvs[i];
				m_mapStNodesArr.push_back(st);
#endif // TEST_STAR_1
				c++;
				if (c >= cn)
				{
					c = 0;
					r++;
				}
			}
#ifndef TEST_STAR_1

			initialize(rn, cn, maxSteps);
#endif // TEST_STAR_1
		}

		void StarA::searchPathDataByRC(unsigned int r0, unsigned int c0, unsigned int r1, unsigned int c1)
		{
			m_start.r = r0;
			m_start.c = c0;
			m_end.r = r1;
			m_end.c = c1;
			searchPath(&m_start, &m_end);
		}
		std::vector<StNode*>* StarA::searchPathByRC(unsigned int r0, unsigned int c0, unsigned int r1, unsigned int c1)
		{
			m_start.r = r0;
			m_start.c = c0;
			m_end.r = r1;
			m_end.c = c1;
			return searchPath(&m_start, &m_end);
		}

		void StarA::setMaxStepsNum(unsigned int p_m)
		{
			m_maxSteps = p_m;
		}
		void StarA::setGoValueByRC(unsigned int go, unsigned int r, unsigned int c)
		{
			auto node = m_mapStNodesArr[r * m_cn + c];
			node->go = go;
			//std::cout << "r,c: " << r <<","<<c<<", sr,sc:"<< node->r<<","<<node->c << std::endl;
		}
		void StarA::initialize(unsigned int rn, unsigned int cn, unsigned int maxSteps)
		{
			if ((rn * cn) > 4 && maxSteps > 2)
			{
				m_rn = rn;
				m_cn = cn;

				int tot = 0;
				if (m_mapStNodesArr.size() > 0 && m_mapStNodesArr.size() == (rn * cn))
				{
					tot = rn * cn;
				}
				else if(m_mapStNodesArr.size() < 1)
				{
					tot = rn * cn;
					int r = 0;
					int c = 0;
					int i = 0;
					StNode* st;
					for (; i < tot; ++i)
					{
						st = new StNode();
						st->r = r;
						st->c = c;
						st->go = 0;
						m_mapStNodesArr.push_back(st);
						c++;
						if (c >= cn)
						{
							c = 0;
							r++;
						}
					}
				}
				if (tot > 0)
				{
					m_maxR = m_rn - 1;
					m_maxC = m_cn - 1;
					m_maxSteps = maxSteps;

					std::cout << "StarA::initState(), mapNodesArr.size(): " << m_mapStNodesArr.size() << std::endl;
					m_openBH.initialize(&m_openList);
				}
			}
		}
		std::vector<StNode*>* StarA::searchPath(StNode* start, StNode* end)
		{
			m_pathTot = 0;
			m_isSearch = false;
			m_roadArr.clear();
			auto& list = m_mapStNodesArr;
			//std::cout << "StarA::searchPath(), m_mapStNodesArr.size(): " << m_mapStNodesArr.size() << std::endl;
			size_t len = m_openList.size();
			size_t i = 0;
			if (len > 1) {
				for (i = len - 1; i > 0; i--)
				{
					m_openList[i]->sta = StNode::STA_NONE;
					m_openList.pop_back();
				}
			}
			//trace("m_openList.len: ",m_openList.length);
			len = m_closeList.size();
			if (len > 0) {
				for (i = len - 1; i >= 0; i--)
				{
					m_closeList[i]->sta = StNode::STA_NONE;
				}
				m_closeList.clear();
			}
			m_openBH.reset();
			//保证参数节点是地图数据节点
			//	m_startStNode = m_mapStNodesArr[start->r][start->c];//start;//获得寻路起点
			//	m_endStNode = m_mapStNodesArr[end.r][end.c];//end;//获得要到达的目的地


			m_startStNode = list[start->r * m_cn + start->c];
			m_endStNode = list[end->r * m_cn + end->c];//end;//获得要到达的目的地

			m_startStNode->father = nullptr;
			m_endStNode->father = nullptr;

			addToOpenList(m_startStNode);//将起点加入开启列表			
			//

			StNode *thisNode = nullptr;

			if (m_endStNode->go == 0) {
				while (true) {

					if (m_openBH.getLength() < 2) {//无路可走
						std::cout<<("无路可走 A")<<std::endl;
						return &m_roadArr;
						break;
					}

					thisNode = m_openBH.getTopNode();//m_openList.splice(getMinF(),1)[0];//每次取出开启列表中的第一个节点
					thisNode->sta = 0;
					m_openBH.delTopEle();
					//m_openList.splice(getMinF(),1)[0])会导致thisNode可能为null;
					//trace(thisNode);
					//当搜寻步骤太多且超过规定的上限，那么就提前终止搜寻
					if (m_openList.size() >= m_maxSteps) {
						//trace("too many nodes.");
						m_endStNode = thisNode;
					}
					if (thisNode == m_endStNode) {//找到路径
						//trace("找到路径");
						//从终点开始往回找父节点，以生成路径列表，直到父节点为起始点

						while (thisNode->father != m_startStNode->father) {

							m_roadArr.push_back(thisNode);
							thisNode = thisNode->father;
						}

						//return m_roadArr;//返回路径列表
						//trace("m_roadArr:", m_roadArr.length);
						return getKeyNodes(m_roadArr);
						//return getKeyNodes(m_roadArr);
						break;
					}
					//trace(thisNode.r +",,,,,"+thisNode.c);
					addToCloseList(thisNode);//把当前节点加入关闭列表
					//
					addAroundNode(thisNode);//开始检查当前节点四周的节点

				}//End while
			}
			else {
				while (true) {

					if (m_openBH.getLength() < 2) {//无路可走

						std::cout << ("无路可走 B") << std::endl;
						return &m_roadArr;
						break;
					}

					thisNode = m_openBH.getTopNode();//每次取出开启列表中的第一个节点->F值最小的节点
					thisNode->sta = 0;
					m_openBH.delTopEle();
					//m_openList.splice(getMinF(),1)[0])会导致thisNode可能为undefined;
					//当搜寻步骤太多且超过规定的上限，那么就提前终止搜寻
					if (m_openList.size() >= m_maxSteps) {
						//trace("too many nodes.");
						m_endStNode = thisNode;
					}
					if (thisNode == m_endStNode) {//找到路径
						//trace("找到路径");
						//从终点开始往回找父节点，以生成路径列表，直到父节点为起始点
						while (thisNode->father != m_startStNode->father) {
							m_roadArr.push_back(thisNode);
							thisNode = thisNode->father;
						}

						return getKeyNodes(m_roadArr);
						break;
					}

					addToCloseList(thisNode);//把当前节点加入关闭列表
					addAroundNode2(thisNode);//开始检查当前节点四周的节点

				}//End while
			}

			std::cout << ("无 is null.") << std::endl;
			return nullptr;
		}

		int StarA::getClosedRelativeDire(StNode* currNode, StNode* targetNode)
		{
			if (targetNode->c < currNode->c && targetNode->r == currNode->r) {
				//左
				return 0;
			}
			else if (targetNode->c < currNode->c && targetNode->r < currNode->r) {
				//左上
				return 1;
			}
			else if (targetNode->c == currNode->c && targetNode->r < currNode->r) {
				//上
				return 2;
			}
			else if (targetNode->c > currNode->c && targetNode->r < currNode->r) {
				//右上
				return 3;
			}
			else if (targetNode->c > currNode->c && targetNode->r == currNode->r) {
				//右
				return 4;
			}
			else if (targetNode->c > currNode->c && targetNode->r > currNode->r) {
				//右下
				return 5;
			}
			else if (targetNode->c == currNode->c && targetNode->r > currNode->r) {
				//下
				return 6;
			}
			else if (targetNode->c < currNode->c && targetNode->r > currNode->r) {
				//左下
				return 7;
			}
			return -1;
		}
		void StarA::addToOpenList(StNode* o)
		{
			m_openBH.insertEle(o);
			o->sta = StNode::STA_OPEN;
		}
		void StarA::addToCloseList(StNode* o)
		{
			m_closeList.push_back(o);
			o->sta = StNode::STA_CLOSE;
		}

		std::vector<StNode*>* StarA::getKeyNodes(std::vector<StNode*>& road_Arr)
		{
			m_keyNodeArr.clear();
			//m_pathTot
			size_t len = road_Arr.size();
			size_t i = 0;
			if (len < 2) {

				//return &road_Arr;
				for (size_t i = 0; i < len; ++i)
				{
					m_keyNodeArr.push_back(road_Arr[i]);
				}
				//	return &m_keyNodeArr;
				//	std::vector<StNode*>* path = &road_Arr;
				//	std::cout << "getKeyNodes() B, path length: " << path->size() << std::endl;
				//	return path;
			}
			else
			{
				//	for (i = 0; i < len; i++)
				//	{
				//		auto st = road_Arr[i];
				//		std::cout << "A key node r,c: " << st->r << "," << st->c << std::endl;
				//	}
				StNode* currStNode = road_Arr[0];
				m_keyNodeArr.push_back(currStNode);

				int pre_deric = -1;
				int curr_deric = pre_deric = getClosedRelativeDire(currStNode, road_Arr[1]);
				currStNode = road_Arr[1];

				for (i = 2; i < len; i++) {
					curr_deric = getClosedRelativeDire(currStNode, road_Arr[i]);
					if (curr_deric != pre_deric) {
						//出现拐弯的拐点
						m_keyNodeArr.push_back(currStNode);
						pre_deric = curr_deric;
					}
					currStNode = road_Arr[i];
				}
				m_keyNodeArr.push_back(road_Arr[len - 1]);

			}
			len = m_keyNodeArr.size();
			m_pathTot = static_cast<unsigned int>(len);
			unsigned int k = 0;
			for (i = 0; i < len; i++)
			{
				auto st = m_keyNodeArr[i];
				//std::cout << "B key node r,c: " << st->r << "," << st->c << std::endl;
				m_pathData[k] = st->r;
				m_pathData[k+1] = st->c;
				k += 2;
			}

			return &m_keyNodeArr;
		}
		void StarA::addAroundNode(StNode* thisNode)
		{
			auto& list = m_mapStNodesArr;
			unsigned int c_i = thisNode->c;//当前节点横向索引
			unsigned int r_i = thisNode->r;//当前节点纵向索引
			//添加左右两个直点的同时过滤四个角点，以提高速度。
			//即如果左边点不存在或不可通过则左上左下两角点就不需检查，右边点不存在或不可通过则右上右下两角点不需检查
			//后面添加四个为角点，角点的判断为，自身可通过&&它相邻的两个当前点的直点都可通过
			//try{

			StNode* tnode0 = nullptr;
			StNode* tnode1 = nullptr;
			if (c_i > 0)
			{
				tnode0 = list[r_i * m_cn + c_i - 1];
				if (tnode0->go == 0) {//加入左边点
					//if (!inArr(m_mapStNodesArr[r_i][c_i - 1],m_closeList)) {//是否在关闭列表中
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//m_openList.push(m_mapStNodesArr[r_i][c_i - 1]);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
					//加入左上点
					if (r_i > 0)
					{
						tnode0 = list[(r_i - 1) * m_cn + c_i - 1];
						tnode1 = list[(r_i - 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//m_openList.push(m_mapStNodesArr[r_i-1][c_i - 1]);//加入节点
							}//End if
						}//End if
					}
					//加入左下点
					if (r_i < m_maxR)
					{
						tnode0 = list[(r_i + 1) * m_cn + c_i - 1];
						tnode1 = list[(r_i + 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}//End if
					}
				}//End if
			}
			if (c_i < m_maxC)
			{
				tnode0 = list[(r_i)*m_cn + c_i + 1];
				if (tnode0->go == 0) {//加入右边点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
					//加入右上点
					if (r_i > 0)
					{
						tnode1 = list[(r_i - 1) * m_cn + c_i + 1];
						tnode0 = list[(r_i - 1) * m_cn + c_i];
						if (tnode1->go == 0 && tnode0->go == 0) {
							if (tnode1->sta == StNode::STA_NONE) {
								setGHF(tnode1, thisNode, 14);//计算GHF值
								addToOpenList(tnode1);//加入节点
							}//End if
						}//End if
					}
					if (r_i < m_maxR)
					{
						//加入右下点
						tnode0 = list[(r_i + 1) * m_cn + c_i + 1];
						tnode1 = list[(r_i + 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}//End if
					}
				}//End if
			}

			//try{
			if (r_i > 0)
			{
				tnode0 = list[(r_i - 1) * m_cn + c_i];
				if(tnode0->go == 0) {//加入上面点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
				}//End if
			}
			if (r_i < m_maxR)
			{
				tnode0 = list[(r_i + 1) * m_cn + c_i];
				if (tnode0->go == 0) {//加入下面点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
				}//End if
			}
		}
		void StarA::addAroundNode2(StNode* thisNode)
		{
			auto& list = m_mapStNodesArr;
			unsigned int c_i= thisNode->c;//当前节点横向索引
			unsigned int r_i= thisNode->r;//当前节点纵向索引
			//添加左右两个直点的同时过滤四个角点，以提高速度。
			//即如果左边点不存在或不可通过则左上左下两角点就不需检查，右边点不存在或不可通过则右上右下两角点不需检查
			//后面添加四个为角点，角点的判断为，自身可通过&&它相邻的两个当前点的直点都可通过
			//try{

			StNode* tnode0 = nullptr;
			StNode* tnode1 = nullptr;
			if (c_i > 0)
			{
				tnode0 = list[(r_i)*m_cn + c_i - 1];
				if (tnode0->go == 0) {//加入左边点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
					//加入左上点
					if (r_i > 0)
					{
						tnode0 = list[(r_i - 1) * m_cn + c_i - 1];
						tnode1 = list[(r_i - 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}
						else if (tnode0->go == 1) {//End if
						   //假如左上边的节点是障碍节点，而且左上边的节点就是终点，那么就提前结束搜寻，并且认为
						   //当前的thisNode就是终点
							if (tnode0 == m_endStNode) {
								m_endStNode = thisNode;
								addToOpenList(thisNode);
								return;
							}
						}
					}
					if (r_i < m_maxR)
					{
						//加入左下点
						tnode0 = list[(r_i + 1) * m_cn + c_i - 1];
						tnode1 = list[(r_i + 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}
						else if (tnode0->go == 1) {//End if
						   //假如左下边的节点是障碍节点，而且左下边的节点就是终点，那么就提前结束搜寻，并且认为
						   //当前的thisNode就是终点
							if (tnode0 == m_endStNode) {
								m_endStNode = thisNode;
								addToOpenList(thisNode);
								return;
							}
						}
					}
				}
				else if (tnode0->go == 1) {//End if
				   //假如左边的节点是障碍节点，而且左边的节点就是终点，那么就提前结束搜寻，并且认为
				   //当前的thisNode就是终点
					if (tnode0 == m_endStNode) {
						m_endStNode = thisNode;
						//trace("-----------");
						addToOpenList(thisNode);
						return;
					}
				}
			}

			if (c_i < m_maxC)
			{
				tnode0 = list[(r_i)*m_cn + c_i - 1];
				if (tnode0->go == 0) {//加入右边点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
					//加入右上点
					if (r_i > 0)
					{
						tnode0 = list[(r_i - 1) * m_cn + c_i + 1];
						tnode1 = list[(r_i - 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}
						else if (tnode0->go == 1) {//End if
						   //假如右上边的节点是障碍节点，而且右上边的节点就是终点，那么就提前结束搜寻，并且认为
						   //当前的thisNode就是终点
							if (tnode0 == m_endStNode) {
								m_endStNode = thisNode;
								addToOpenList(thisNode);
								return;
							}
						}
					}
					//加入右下点
					if (r_i < m_maxR)
					{
						tnode0 = list[(r_i + 1) * m_cn + c_i + 1];
						tnode1 = list[(r_i + 1) * m_cn + c_i];
						if (tnode0->go == 0 && tnode1->go == 0) {
							if (tnode0->sta == StNode::STA_NONE) {
								setGHF(tnode0, thisNode, 14);//计算GHF值
								addToOpenList(tnode0);//加入节点
							}//End if
						}
						else if (tnode0->go == 1) {//End if
						   //假如右上边的节点是障碍节点，而且右下边的节点就是终点，那么就提前结束搜寻，并且认为
						   //当前的thisNode就是终点
							if (tnode0 == m_endStNode) {
								m_endStNode = thisNode;
								addToOpenList(thisNode);
								return;
							}
						}
					}
				}
				else if (tnode0->go == 1) {//End if
				   //假如右边的节点是障碍节点，而且右边的节点就是终点，那么就提前结束搜寻，并且认为
				   //当前的thisNode就是终点
					if (tnode0 == m_endStNode) {
						m_endStNode = thisNode;
						addToOpenList(thisNode);
						return;
					}
				}
			}

			if (r_i > 0)
			{
				tnode0 = list[(r_i - 1) * m_cn + c_i];
				if (tnode0->go == 0) {//加入上面点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
				}
				else if (tnode0->go == 1) {//End if
				   //假如上边的节点是障碍节点，而且上边的节点就是终点，那么就提前结束搜寻，并且认为
				   //当前的thisNode就是终点
					if (tnode0 == m_endStNode) {
						m_endStNode = thisNode;
						addToOpenList(thisNode);
						return;
					}
				}
			}

			if (r_i < m_maxR)
			{
				tnode0 = list[(r_i + 1) * m_cn + c_i];
				if (tnode0->go == 0) {//加入下面点
					if (tnode0->sta != StNode::STA_CLOSE) {//是否在关闭列表中
						if (tnode0->sta != StNode::STA_OPEN) {//是否在开启列表中
							setGHF(tnode0, thisNode, 10);//计算GHF值
							addToOpenList(tnode0);//加入节点
						}
						else {
							checkG(tnode0, thisNode);//检查G值
						}//End if
					}//End if
				}
				else if (tnode0->go == 1) {//End if
				   //假如下边的节点是障碍节点，而且下边的节点就是终点，那么就提前结束搜寻，并且认为
				   //当前的thisNode就是终点
					if (tnode0 == m_endStNode) {
						m_endStNode = thisNode;
						addToOpenList(thisNode);
						return;
					}
				}
			}
		}


		//设置节点的G/H/F值－－－－－－－－－－－－－－－－－－－－－－－－－－－－》
		void StarA::setGHF(StNode* point, StNode* thisNode, unsigned int g)
		{
			//	if (!thisNode->G) {
			//		thisNode->G = 0;
			//	}
			point->G = thisNode->G + g;
			//H值为当前节点的横纵向到重点的节点数×10
			point->H = (abs(static_cast<int>(point->c - m_endStNode->c)) + abs(static_cast<int>(point->r - m_endStNode->r))) * 10;
			point->F = point->H + point->G;//计算F值
			point->father = thisNode;//指定父节点
		}

		//检查新的G值以判断新的路径是否更优
		void StarA::checkG(StNode* chkNode, StNode* thisNode)
		{
			unsigned int g = thisNode->G + 10;//新G值为当前节点的G值加上10（因为只检查当前节点的直点）
			if (g <= chkNode->G)
			{//如果新的G值比原来的G值低或相等，说明新的路径会更好
				chkNode->G = g;//更新G值
				chkNode->F = chkNode->H + g;//同时F值重新被计算
				chkNode->father = thisNode;//将其父节点更新为当前点
			}//End if
		}
	}
}