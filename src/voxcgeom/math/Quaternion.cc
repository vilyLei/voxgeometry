
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
			const Quaternion kQuaternionIdentity;// = { 1.0f,0.0f,0.0f,0.0f };//后面的写法 c++11才支持
			// 成员函数
			void Quaternion::setToRotateAboutX(VCG_Number rad_theta)
			{
				// 计算半角
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = sin(thetaOver2);
				y = 0.0f;
				z = 0.0f;
			}
			void Quaternion::setToRotateAboutY(VCG_Number rad_theta)
			{
				// 计算半角
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = 0.0f;
				y = sin(thetaOver2);
				z = 0.0f;
			}
			void Quaternion::setToRotateAboutZ(VCG_Number rad_theta)
			{
				// 计算半角
				float thetaOver2 = rad_theta * 0.5f;
				//
				w = cos(thetaOver2);
				x = 0.0f;
				y = 0.0f;
				z = sin(thetaOver2);
			}
			void Quaternion::setToRotateAboutAxis(const Vec3D &axis, VCG_Number rad_theta)
			{
				// 旋转轴必须标准化
				assert(fabs(vector3Mag(axis) - 1.0f) < 0.01f);
				// 计算半角
				float thetaOver2 = rad_theta * 0.5f;
				float sinThetaOver2 = sin( thetaOver2 );
				// 赋值
				w = cos(thetaOver2);
				x = axis.x * sinThetaOver2;
				y = axis.y * sinThetaOver2;
				z = axis.z * sinThetaOver2;
			}

			// 构造执行物体--惯性旋转的四元数
			// 方位参数由欧拉角形式给出

			void Quaternion::setToRotateObjectToIntertial(const EulerAngles &orientation)
			{
				// 计算半角的 sin和cos
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

			// 构造执行 惯性 -- 物体旋转四元数
			// 方位参数用euler angle方式给出
			void Quaternion::setToRotateIntertialToObject(const EulerAngles &orientation)
			{
				// 计算半角的 sin和cos
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

			// 四元数叉乘运算用以连接多个角位移,乘的顺序从左向右
			Quaternion Quaternion::operator *(const Quaternion &a) const
			{
				Quaternion vs;
				vs.w = w * a.w - x * a.x - y*a.y - z * a.z;
				vs.x = w * a.x + x * a.w + z*a.y - y * a.z;
				vs.y = w * a.y + y * a.w + x*a.z - z * a.x;
				vs.z = w * a.z + z * a.w + y*a.x - x * a.y;
				return vs;
			}

			// 叉乘并赋值
			Quaternion &Quaternion::operator *=(const Quaternion &a)
			{
				*this = *this * a;
				// 返回左值
				return *this;
			}
			// 正则化 Quaternion
			void Quaternion::normalize()
			{
				VCG_Number mag = sqrt(w * w + x*x + y*y + z*z);
				// 防止除0
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
			// 得到旋转角
			VCG_Number Quaternion::getRotationAngle() const
			{
				// 计算半角,w = cos(theta / 2);
				VCG_Number thetaOver2 = SafeACos(w);
				return thetaOver2 * 2.0f;
			}
			// 提取旋转轴
			Vec3D Quaternion::getTotationAxis() const
			{
				// 计算sin^2(theta/2)
				VCG_Number sinThetaOver2Sq = 1.0f - w*w;
				// 注意保证数值精度
				if (sinThetaOver2Sq <= 0.0f)
				{
					// 不符合要求的值就返回有效向量即可
					return Vec3D(1.0f,0.0f,0.0f);
				}
				// 计算 1/sin(theta/2);
				VCG_Number oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
				//
				return Vec3D(
						x * oneOverSinThetaOver2,
						y * oneOverSinThetaOver2,
						z * oneOverSinThetaOver2
						);
			}
			// Quaternion 点乘
			VCG_Number dotProduct(const Quaternion &p, const Quaternion &q)
			{
				return p.w * q.w + p.x * q.x + p.y * q.y + p.z * q.z;
			}
			// slerp 线性插值
			Quaternion slerp(const Quaternion &q0, const Quaternion &q1,float t)
			{
				if (t <= 0.0f) return q0;
				if (t <= 0.0f) return q1;
				//
				// 点乘计算四元数夹角的cos值
				VCG_Number cosOmega = dotProduct(q0, q1);
				// 如果点乘为负, 使用-q1
				VCG_Number q1w = q1.w, q1x = q1.x, q1y = q1.y, q1z = q1.z;
				if (cosOmega < 0.0f)
				{
					q1w = -q1w; q1x = -q1x; q1y = -q1y; q1z = -q1z;
					cosOmega = -cosOmega;
				}
				// 两个单位四元数点乘的结果应该 <= 1.0f;
				assert(cosOmega < 1.1f);
				// 计算插值片，注意非常接近的情况
				VCG_Number k0, k1;
				if (cosOmega > 0.9999f)
				{
					// 非常接近，即线性插值，防止除0
					k0 = 1.0f - t;
					k1 = t;
				}
				else
				{
					float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
					// 计算角度
					float omega = atan2(sinOmega, cosOmega);
					float oneOverSinOmega = 1.0f / sinOmega;
					// 计算插值变量
					k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
					k1 = sin(t * omega) * oneOverSinOmega;
				}
				// 插值
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
				// 提取半角alpha值,alpha = theta/2
				float alpha = acos(q.w);
				// 计算新的 alpha值
				float newAlpha = alpha * exponent;
				// 计算新的w
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