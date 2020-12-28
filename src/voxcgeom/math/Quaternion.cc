
#include <assert.h>
#include <cmath>
#include "../cgeomPre.h"
#include "Quaternion.h"
#include "Vec3D.h"
#include "EulerAngles.h"
namespace voxcgeom
{
	namespace math
	{
			inline float vector3Mag(const Vec3D& a)
			{
				return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
			}
			const Quaternion kQuaternionIdentity;// = { 1.0f,0.0f,0.0f,0.0f };//�����д�� c++11��֧��
			// ��Ա����
			void Quaternion::setToRotateAboutX(VCG_Number rad_theta)
			{
				// ������
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = sin(thetaOver2);
				y = 0.0f;
				z = 0.0f;
			}
			void Quaternion::setToRotateAboutY(VCG_Number rad_theta)
			{
				// ������
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = 0.0f;
				y = sin(thetaOver2);
				z = 0.0f;
			}
			void Quaternion::setToRotateAboutZ(VCG_Number rad_theta)
			{
				// ������
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = 0.0f;
				y = 0.0f;
				z = sin(thetaOver2);
			}
			void Quaternion::setToRotateAboutAxis(const Vec3D &axis, VCG_Number rad_theta)
			{
				// ��ת������׼��
				assert(fabs(vector3Mag(axis) - 1.0f) < 0.01f);
				// ������
				float thetaOver2 = rad_theta * 0.5f;
				float sinThetaOver2 = sin( thetaOver2 );
				// ��ֵ
				w = cos(thetaOver2);
				x = axis.x * sinThetaOver2;
				y = axis.y * sinThetaOver2;
				z = axis.z * sinThetaOver2;
			}

			// ����ִ������--������ת����Ԫ��
			// ��λ������ŷ������ʽ����

			void Quaternion::setToRotateObjectToIntertial(const EulerAngles &orientation)
			{
				// �����ǵ� sin��cos
				VCG_Number sp, sb, sh;
				VCG_Number cp, cb, ch;
				SinCos(&sp,&cp,orientation.pitch * 0.5f);
				SinCos(&sb, &cb, orientation.bank * 0.5f);
				SinCos(&sh, &ch, orientation.heading * 0.5f);
				//
				w = ch * cp * cb + sh * sp * sb;
				x = ch * sp* cb + sh * cp * sb;
				y = -ch * sp * sb + sh * cp * cb;
				z = -sh * sp * cb + ch * cp * sb;
			}

			// ����ִ�� ���� -- ������ת��Ԫ��
			// ��λ������euler angle��ʽ����
			void Quaternion::setToRotateIntertialToObject(const EulerAngles &orientation)
			{
				// �����ǵ� sin��cos
				VCG_Number sp, sb, sh;
				VCG_Number cp, cb, ch;
				SinCos(&sp, &cp, orientation.pitch * 0.5f);
				SinCos(&sb, &cb, orientation.bank * 0.5f);
				SinCos(&sh, &ch, orientation.heading * 0.5f);
				//
				w = ch * cp * cb + sh * sp * sb;
				x = -ch * sp* cb - sh * cp * sb;
				y = ch * sp * sb - sh * cp * cb;
				z = sh * sp * cb - ch * cp * sb;
			}

			// ��Ԫ����������������Ӷ����λ��,�˵�˳���������
			Quaternion Quaternion::operator *(const Quaternion &a) const
			{
				Quaternion vs;
				vs.w = w * a.w - x * a.x - y*a.y - z * a.z;
				vs.x = w * a.x + x * a.w + z*a.y - y * a.z;
				vs.y = w * a.y + y * a.w + x*a.z - z * a.x;
				vs.z = w * a.z + z * a.w + y*a.x - x * a.y;
				return vs;
			}

			// ��˲���ֵ
			Quaternion &Quaternion::operator *=(const Quaternion &a)
			{
				*this = *this * a;
				// ������ֵ
				return *this;
			}
			// ���� Quaternion
			void Quaternion::normalize()
			{
				VCG_Number mag = sqrt(w * w + x*x + y*y + z*z);
				// ��ֹ��0
				if (mag > 0.0f)
				{
					float oneOverMag = 1.0f / mag;
					w *= oneOverMag;
					x *= oneOverMag;
					y *= oneOverMag;
					z *= oneOverMag;
				}
				else
				{
					assert(false);
					// release version
					identity();
				}
			}
			// �õ���ת��
			VCG_Number Quaternion::getRotationAngle() const
			{
				// ������,w = cos(theta / 2);
				VCG_Number thetaOver2 = SafeACos(w);
				return thetaOver2 * 2.0f;
			}
			// ��ȡ��ת��
			Vec3D Quaternion::getTotationAxis() const
			{
				// ����sin^2(theta/2)
				VCG_Number sinThetaOver2Sq = 1.0f - w*w;
				// ע�Ᵽ֤��ֵ����
				if (sinThetaOver2Sq <= 0.0f)
				{
					// ������Ҫ���ֵ�ͷ�����Ч��������
					return Vec3D(1.0f,0.0f,0.0f);
				}
				// ���� 1/sin(theta/2);
				VCG_Number oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
				//
				return Vec3D(
						x * oneOverSinThetaOver2,
						y * oneOverSinThetaOver2,
						z * oneOverSinThetaOver2
						);
			}
			// Quaternion ���
			VCG_Number dotProduct(const Quaternion &p, const Quaternion &q)
			{
				return p.w * q.w + p.x * q.x + p.y * q.y + p.z * q.z;
			}
			// slerp ���Բ�ֵ
			Quaternion slerp(const Quaternion &q0, const Quaternion &q1,float t)
			{
				if (t <= 0.0f) return q0;
				if (t <= 0.0f) return q1;
				//
				// ��˼�����Ԫ���нǵ�cosֵ
				VCG_Number cosOmega = dotProduct(q0, q1);
				// ������Ϊ��, ʹ��-q1
				VCG_Number q1w = q1.w, q1x = q1.x, q1y = q1.y, q1z = q1.z;
				if (cosOmega < 0.0f)
				{
					q1w = -q1w; q1x = -q1x; q1y = -q1y; q1z = -q1z;
					cosOmega = -cosOmega;
				}
				// ������λ��Ԫ����˵Ľ��Ӧ�� <= 1.0f;
				assert(cosOmega < 1.1f);
				// �����ֵƬ��ע��ǳ��ӽ������
				VCG_Number k0, k1;
				if (cosOmega > 0.9999f)
				{
					// �ǳ��ӽ��������Բ�ֵ����ֹ��0
					k0 = 1.0f - t;
					k1 = t;
				}
				else
				{
					float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
					// ����Ƕ�
					float omega = atan2(sinOmega, cosOmega);
					float oneOverSinOmega = 1.0f / sinOmega;
					// �����ֵ����
					k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
					k1 = sin(t * omega) * oneOverSinOmega;
				}
				// ��ֵ
				Quaternion vs;
				vs.x = k0 * q0.x + k1 * q1x;
				vs.y = k0 * q0.y + k1 * q1y;
				vs.z = k0 * q0.z + k1 * q1z;
				vs.w = k0 * q0.w + k1 * q1w;
				//
				return vs;
			}
			// conjugate
			Quaternion conjugate(const Quaternion &q)
			{
				Quaternion r;
				r.w = q.w;
				r.x = -q.x;
				r.y = -q.y;
				r.z = -q.z;
				return r;
			}
			// pow
			Quaternion pow(const Quaternion &q,float exponent)
			{
				if (fabs(q.w) > 0.9999)
				{
					return q;
				}
				// ��ȡ���alphaֵ,alpha = theta/2
				float alpha = acos(q.w);
				// �����µ� alphaֵ
				float newAlpha = alpha * exponent;
				// �����µ�w
				Quaternion r;
				r.w = cos(newAlpha);
				//
				float mult = sin(newAlpha) / sin(alpha);
				r.x = q.x * mult;
				r.y = q.y * mult;
				r.z = q.z * mult;
				return r;
			}
			//	std::string Quaternion::toString()const
			//	{
			//		return "Quaternion(w=" + anyTypeToString(w) + ",x=" + anyTypeToString(x) + ",y=" + anyTypeToString(y) + ",z=" + anyTypeToString(z) + ")";
			//	}

	}
}