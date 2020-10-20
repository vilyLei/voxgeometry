
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class RadialLine : public GeomBase
		{
		public:
			RadialLine();
			virtual ~RadialLine()			= default;


			Vec3D tv;					// diretion normalized vec3d
			virtual void update()		override;
			virtual void updateFast()	override;
			// test intersect between the radial line and a triangle(three points construct a triangle)
			static int IntersectionTri(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& triva, const Vec3D& trivb, const Vec3D& trivc, Vec3D& outV);
			// @return ���õ����������������ĵ�, 1��ʾ�ཻ,1��ʾ���ཻ
			static int IntersectionLS(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& lspva, const Vec3D& lspvb, Vec3D& outV, VCG_Number radius = 1.0f);
			// @return ���õ����������������ĵ�, 1��ʾ�ཻ,0��ʾ���ཻ
			static int IntersectioNearSphere2(const Vec3D& rlpv, const Vec3D& rltv, Vec3D& cv, VCG_Number radius, Vec3D& outV);
			static int IntersectioNearSphere(const Vec3D& rlpv, const Vec3D& rltv, Vec3D& cv, VCG_Number radius, Vec3D& outV);
			static bool IntersectSphere(const Vec3D& rlpv, const Vec3D& rltv, const Vec3D& cv, VCG_Number radius);

		protected:
				static Vec3D __tAv;
		private:

		};
	}
}
typedef voxcgeom::base::RadialLine RadialLine;