
/**
Author: Vily

*/
#pragma once
#include <vector>
#include "Vec3D.h"

namespace voxcgeom
{
	namespace base
	{
		class AABB
		{
		public:
            AABB()												                        = default;
            AABB(const Vec3D& minV, const Vec3D& maxV);
            AABB(VCG_Number minX, VCG_Number minY, VCG_Number minZ, VCG_Number maxX, VCG_Number maxY, VCG_Number maxZ);
			AABB(const AABB& v3)								                        = default;
			AABB(AABB&& rhs)									                        = default;
			AABB& operator=(const AABB& rhs)					                        = default;
			AABB& operator=(AABB&& rhs)													= default;
			virtual ~AABB() = default;


			Vec3D min, max, center;
			VCG_Number radius;
			VCG_Number radius2;

			inline void reset()
			{
				min.setXYZ(VCG_MATH_MAX_POSITIVE, VCG_MATH_MAX_POSITIVE, VCG_MATH_MAX_POSITIVE);
				max.setXYZ(VCG_MATH_MIN_NEGATIVE, VCG_MATH_MIN_NEGATIVE, VCG_MATH_MIN_NEGATIVE);
			}
			bool containsPosition(const Vec3D& v) const;
			// 是否包含某一点(同一坐标空间的点)
			bool containsXY(VCG_Number vx, VCG_Number vy) const;
			// 是否包含某一点(同一坐标空间的点)
			bool containsXZ(VCG_Number vx, VCG_Number vz) const;
			// 是否包含某一点(同一坐标空间的点)
			bool containsYZ(VCG_Number vy, VCG_Number vz) const;
			bool intersect(const AABB& ab);
			void unionThis(const AABB& ab);
			void addPosition(const Vec3D& pv);
			void addXYZ(VCG_Number pvx, VCG_Number pvy, VCG_Number pvz);
			void update();
			void coutThis();
			/**
			 * Radial line intersect a AABB
			 */
			static bool IntersectionRL2(std::vector<Vec3D>& vecs, unsigned int rsigns[4], Vec3D& ltInvtv, Vec3D& ltv, const Vec3D& lpv, Vec3D& outV);

			// 检测射线和AABB是否相交,如果相交计算出交点存放于 outV 中, 这个检测计算是精准高效的
			// @param				ltv		射线的切向
			// @param				lpv		射线上的一点
			// @param				ab		updateFast() 过的 AABB 实例
			// @param				outV	存放交点的 Vector3D实例
			//
			static bool IntersectionRL(const Vec3D& ltv, const Vec3D& lpv, const AABB& ab, Vec3D& outV);
		private:

			VCG_Number			m_long;
			VCG_Number			m_width;
			VCG_Number			m_height;
			Vec3D				m_tempV;
            static Vec3D		s_v3Stv0;
            static Vec3D		s_v3Stv1;
		};
	}
}
typedef voxcgeom::base::AABB AABB;