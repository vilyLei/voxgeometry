/**
Author: Vily

*/
#include "StNode.h"

namespace simnav
{
	namespace stara
	{
		const unsigned int		StNode::STA_NONE{ 0 };
		const unsigned int		StNode::STA_OPEN{ 1 };
		const unsigned int		StNode::STA_CLOSE{ 2 };
		StNode::StNode()
			: G(0), H(0), F(0)
			, r(0), c(0)
			, go(0), b(0), sta(0), index(0)
			, father(nullptr)
		{
		}

		StNode::~StNode()
		{
			father = nullptr;
		}
	}
}