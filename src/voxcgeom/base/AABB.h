
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
			// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
			bool containsXY(VCG_Number vx, VCG_Number vy) const;
			// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
			bool containsXZ(VCG_Number vx, VCG_Number vz) const;
			// �Ƿ����ĳһ��(ͬһ����ռ�ĵ�)
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

			// ������ߺ�AABB�Ƿ��ཻ,����ཻ������������� outV ��, ����������Ǿ�׼��Ч��
			// @param				ltv		���ߵ�����
			// @param				lpv		�����ϵ�һ��
			// @param				ab		updateFast() ���� AABB ʵ��
			// @param				outV	��Ž���� Vector3Dʵ��
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