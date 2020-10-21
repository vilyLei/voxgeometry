
/**
Author: Vily

*/
#pragma once
#include <cmath>
#include "../cgeomPre.h"
namespace voxcgeom
{
	namespace base
	{
		class Vec3D
		{
		public:
			float x,y,z,w;
			Vec3D()												                        = default;
			Vec3D(VCG_Number px, VCG_Number py, VCG_Number pz, VCG_Number pw = 1.0f);
			Vec3D(const Vec3D& v3)								                        = default;
			Vec3D(Vec3D&& rhs)									                        = default;
			Vec3D& operator=(const Vec3D& rhs)					                        = default;
			Vec3D& operator=(Vec3D&& rhs)						                        = default;
			void coutThis();
			
			static const Vec3D									                        X_AXIS;
			static const Vec3D									                        Y_AXIS;
			static const Vec3D									                        Z_AXIS;
			static const Vec3D									                        ZERO;


            inline void setXYZ(VCG_Number px, VCG_Number py, VCG_Number pz)
            {
                x = px;
                y = py;
                z = pz;
            }
            inline void setXYZW(VCG_Number px, VCG_Number py, VCG_Number pz, VCG_Number pw)
            {
                x = px;
                y = py;
                z = pz;
                w = pw;
            }
            inline void copyFrom(const Vec3D& v3)
            {
                x = v3.x;
                y = v3.y;
                z = v3.z;
            }
            inline VCG_Number dot(const Vec3D& v3) const
            {
                return x * v3.x + y * v3.y + z * v3.z;
            }
            inline void multBy(const Vec3D& v3)
            {
                x *= v3.x;
                y *= v3.y;
                z *= v3.z;
            }
            inline void normalize()
            {
                VCG_Number d = sqrt(x * x + y * y + z * z);
                if (d > VCG_MATH_MIN_POSITIVE)
                {
                    x /= d;
                    y /= d;
                    z /= d;
                }
            }
            inline void normalizeTo(Vec3D& v3) const
            {
                VCG_Number d = sqrt(x * x + y * y + z * z);
                if (d > VCG_MATH_MIN_POSITIVE)
                {
                    v3.x = x/d;
                    v3.y = y/d;
                    v3.z = z/d;
                }
            }
            inline void scaleBy(VCG_Number s)
            {
                x *= s;
                y *= s;
                z *= s;
            }
            inline void negate()
            {
                x = -x;
                y = -y;
                z = -z;
            }
            inline bool equalsXYZ(const Vec3D& v3)
            {
                return abs(x - v3.x) < VCG_MATH_MIN_POSITIVE && abs(y - v3.y) < VCG_MATH_MIN_POSITIVE && abs(z - v3.z) < VCG_MATH_MIN_POSITIVE;
            }
            inline bool equalsAll(const Vec3D& v3)
            {
                return abs(x - v3.x) < VCG_MATH_MIN_POSITIVE && abs(y - v3.y) < VCG_MATH_MIN_POSITIVE && abs(z - v3.z) < VCG_MATH_MIN_POSITIVE && abs(w - v3.w) < VCG_MATH_MIN_POSITIVE;
            }
            inline void project()
            {
                VCG_Number t = 1.0f / w;
                x *= t;
                y *= t;
                z *= t;
            }
            inline VCG_Number getLength() const
            {
                return sqrt(x * x + y * y + z * z);
            }
            inline VCG_Number getLengthSquared() const
            {
                return x * x + y * y + z * z;
            }
            inline void addBy(const Vec3D& v3)
            {
                x += v3.x;
                y += v3.y;
                z += v3.z;
            }
            inline void subtractBy(const Vec3D& v3)
            {
                x -= v3.x;
                y -= v3.y;
                z -= v3.z;
            }
            // RVO
            inline Vec3D subtract(const Vec3D& v3)
            {
                return Vec3D(x - v3.x, y - v3.y, z - v3.z);
            }
            // RVO
            inline Vec3D add(const Vec3D& v3)
            {
                return Vec3D(x + v3.x, y + v3.y, z + v3.z);
            }
            // RVO
            inline Vec3D cross(const Vec3D& v3)
            {
                return Vec3D(
                    y * v3.z - z * v3.y
                    , z * v3.x - x * v3.z
                    , x * v3.y - y * v3.x
                    );
            }
            // RVO
            inline Vec3D crossProduct(const Vec3D& a)
            {
                return Vec3D(
                    y * a.z - z * a.y
                    , z * a.x - x * a.z
                    , x * a.y - y * a.x
                    );
            }
            inline void crossBy(const Vec3D& v3)
            {
                auto&& px = y * v3.z - z * v3.y;
                auto&& py = z * v3.x - x * v3.z;
                auto&& pz = x * v3.y - y * v3.x;
                x = px;
                y = py;
                z = pz;
            }
            inline void reflectBy(const Vec3D& nv)
            {
                VCG_Number idotn2 = (x * nv.x + y * nv.y + z * nv.z) * 2.0f;
                x = x - idotn2 * nv.x;
                y = y - idotn2 * nv.y;
                z = z - idotn2 * nv.z;
            }
            void subVecsTo(const Vec3D& va, const Vec3D& vb)
            {
                x = va.x - vb.x;
                y = va.y - vb.y;
                z = va.z - vb.z;
            }
            void addVecsTo(const Vec3D& va, const Vec3D& vb)
            {
                x = va.x + vb.x;
                y = va.y + vb.y;
                z = va.z + vb.z;
            }

            inline void crossVecsTo(const Vec3D& va, const Vec3D& vb)
            {
                x = va.y * vb.z - va.z * vb.y;
                y = va.z * vb.x - va.x * vb.z;
                z = va.x * vb.y - va.y * vb.x;
            }
            // positive direction: right hand rule
            static void Cross(const Vec3D& a, const Vec3D& b, Vec3D& result);
            // (va1 - va0) cross (vb1 - vb0), positive direction: right hand rule
            static void CrossSubtract(const Vec3D& va0, const Vec3D& va1, const Vec3D& vb0, const Vec3D& vb1, Vec3D& result);
            static void Subtract(const Vec3D& a, const Vec3D& b, Vec3D& result);
            static VCG_Number DistanceSquared(const Vec3D& a, const Vec3D& b);
            static VCG_Number DistanceXYZ(VCG_Number x0, VCG_Number y0, VCG_Number z0, VCG_Number x1, VCG_Number y1, VCG_Number z1);
            static VCG_Number Distance(const Vec3D& v0, const Vec3D& v1);
            
            // calc Vec3D v0 and v1
            static VCG_Number DegreeBetween(const Vec3D& v0, const Vec3D& v1);
            static VCG_Number RadianBetween(const Vec3D& v0, const Vec3D& v1);
            static VCG_Number RadianBetween2(const Vec3D& v0, const Vec3D& v1);
            static void Reflect(const Vec3D& iv, const Vec3D& nv, Vec3D& rv);
			virtual ~Vec3D()									        = default;
		private:

            static Vec3D                                                s_v3Stv0;
            static Vec3D                                                s_v3Stv1;
		};
	}
}
typedef voxcgeom::base::Vec3D Vec3D;