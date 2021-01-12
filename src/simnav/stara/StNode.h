/**
Author: Vily

*/

#pragma once
namespace simnav
{
	namespace stara
	{
		class StNode
		{
		public:
			StNode();
			~StNode();
			const static unsigned int		STA_NONE;// = 0;
			const static unsigned int		STA_OPEN;// = 1;
			const static unsigned int		STA_CLOSE;// = 2;

			//标志值
			unsigned int					G;//= 0;
			unsigned int					H;//= 0;
			unsigned int					F;//= 0;
			//
			unsigned int					r;//= 0;//相当于行号
			unsigned int					c;//= 0;//相当于列号

			//是否可以通过,0表示可以通过, 1表示不可以通过
			unsigned int					go;// = 0;
			// 记录当前格子是否被遮挡, 0表示没被遮挡, 1表示被着挡住了
			unsigned int					b;// = 0;
			// 记录自己的状态,1(STA_OPEN)表示自身在开启列表,2(STA_CLOSE)表示自身在关闭列表,0(STA_NONE)表示自身没在任何列表
			unsigned int					sta;// = 0;
			// 序号		
			unsigned int					index;// = 0;
			//记录自己的父节点
			StNode							*father;// = null;
		};
	}
}