
#include <iostream>
#include "Vec3D.h"

namespace voxcgeom
{
	namespace base
	{
		Vec3D Vec3D::s_v3Stv0;
		Vec3D Vec3D::s_v3Stv1;

        const Vec3D Vec3D::X_AXIS{ 1.0f, 0.0f, 0.0f };
		const Vec3D Vec3D::Y_AXIS{ 0.0f, 1.0f, 0.0f};
		const Vec3D Vec3D::Z_AXIS{ 0.0f, 0.0f, 1.0f};
        const Vec3D Vec3D::ZERO{ 0.0f, 0.0f, 0.0f };

		Vec3D::Vec3D(float px, float py, float pz, float pw): x(px), y(py), z(pz), w(pw)
		{
		}
		void Vec3D::coutThis()
		{
			std::cout << "Vec3D(x="<<x<<",y="<<y<<",z="<<z<<",w="<<w<<")" << std::endl;
		}

        // 右手法则(为正)
        void static Cross(const Vec3D& a, const Vec3D& b, Vec3D& result)
        {
            result.x = a.y * b.z - a.z * b.y;
            result.y = a.z * b.x - a.x * b.z;
            result.z = a.x * b.y - a.y * b.x;
        }
        // (va1 - va0) 叉乘 (vb1 - vb0), 右手法则(为正)
        void Vec3D::CrossSubtract(const Vec3D& va0, const Vec3D& va1, const Vec3D& vb0, const Vec3D& vb1, Vec3D& result)
        {
            s_v3Stv0.x = va1.x - va0.x;
            s_v3Stv0.y = va1.y - va0.y;
            s_v3Stv0.z = va1.z - va0.z;

            s_v3Stv1.x = vb1.x - vb0.x;
            s_v3Stv1.y = vb1.y - vb0.y;
            s_v3Stv1.z = vb1.z - vb0.z;

            result.x = s_v3Stv0.y * s_v3Stv1.z - s_v3Stv0.z * s_v3Stv1.y;
            result.y = s_v3Stv0.z * s_v3Stv1.x - s_v3Stv0.x * s_v3Stv1.z;
            result.z = s_v3Stv0.x * s_v3Stv1.y - s_v3Stv0.y * s_v3Stv1.x;
        }
        void Vec3D::Subtract(const Vec3D& a, const Vec3D& b, Vec3D& result)
        {
            result.x = a.x - b.x;
            result.y = a.y - b.y;
            result.z = a.z - b.z;
        }
        VCG_Number Vec3D::DistanceSquared(const Vec3D& a, const Vec3D& b)
        {
            s_v3Stv0.x = a.x - b.x;
            s_v3Stv0.y = a.y - b.y;
            s_v3Stv0.z = a.z - b.z;
            return s_v3Stv0.getLengthSquared();
        }
        VCG_Number Vec3D::DistanceXYZ(VCG_Number x0, VCG_Number y0, VCG_Number z0, VCG_Number x1, VCG_Number y1, VCG_Number z1)
        {
            s_v3Stv0.x = x0 - x1;
            s_v3Stv0.y = y0 - y1;
            s_v3Stv0.z = z0 - z1;
            return s_v3Stv0.getLength();
        }
        VCG_Number Vec3D::Distance(const Vec3D& v0, const Vec3D& v1)
        {
            s_v3Stv0.x = v0.x - v1.x;
            s_v3Stv0.y = v0.y - v1.y;
            s_v3Stv0.z = v0.z - v1.z;
            return s_v3Stv0.getLength();
        }

        // calc Vec3D v0 and v1
        VCG_Number Vec3D::DegreeBetween(const Vec3D& v0, const Vec3D& v1)
        {
            v0.normalizeTo(s_v3Stv0);
            v1.normalizeTo(s_v3Stv1);
            return acos(s_v3Stv0.dot(s_v3Stv1)) * VCG_MATH_180_OVER_PI;
        }
        VCG_Number Vec3D::RadianBetween(const Vec3D& v0, const Vec3D& v1)
        {
            v0.normalizeTo(s_v3Stv0);
            v1.normalizeTo(s_v3Stv1);
            return acos(s_v3Stv0.dot(s_v3Stv1));
        }
        VCG_Number Vec3D::RadianBetween2(const Vec3D& v0, const Vec3D& v1)
        {
            //  // c^2 = a^2 + b^2 - 2*a*b * cos(x)
            //  // cos(x) = (a^2 + b^2 - c^2) / 2*a*b
            VCG_Number pa = v0.getLengthSquared();
            VCG_Number pb = v1.getLengthSquared();
            s_v3Stv0.x = v0.x - v1.x;
            s_v3Stv0.y = v0.y - v1.y;
            s_v3Stv0.z = v0.z - v1.z;
            return acos((pa + pb - s_v3Stv0.getLengthSquared()) / (2.0f * sqrt(pa) * sqrt(pb)));

        }
	}
}