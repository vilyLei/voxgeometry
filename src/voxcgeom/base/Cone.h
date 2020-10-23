
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class Cone : public GeomBase
		{
		public:
			Cone();
			virtual ~Cone()					= default;

			// position																					// cone top peak position
			Vec3D tv;																					// from cone top peak to bottom diretion normalized vec3d
			VCG_Number height;																			// the height of a cone
			VCG_Number radius;																			// cone botttom circle plane radius
			
			virtual void update()			override;
			virtual void updateFast()		override;

			bool containsPosition(const Vec3D& pv);														// test cone contains a point yes or no
			
			bool intersectionSL(const Vec3D& slpv, const Vec3D& sltv, Vec3D& outV0, Vec3D& outV1);		// test intersection between astraight line and a cone
			VCG_Number getRadiusByHeight(VCG_Number ph);
			VCG_Number getHalfAngleCos();
		protected:
			
			VCG_Number m_rhk;																			// its value is (radius / height)
			VCG_Number m_mcos;																			// its value is (height / sqrt(height * height + radius * radius))
			VCG_Number m_mcos2;																			// its value is (m_mcos * m_mcos)
			static Vec3D __cotV0;
			static Vec3D __cotV1;
			static Vec3D __cotV2;
		private:

		};
	}
}
typedef voxcgeom::base::Cone Cone;