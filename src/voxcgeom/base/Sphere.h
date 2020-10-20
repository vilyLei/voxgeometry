
/**
Author: Vily

*/
#pragma once
#include "GeomBase.h"

namespace voxcgeom
{
	namespace base
	{
		class Sphere : public GeomBase
		{
		public:
			Sphere();
			virtual ~Sphere()			= default;


			VCG_Number radius;
			virtual void update()		override;
			virtual void updateFast()	override;
			/**
			 * �ж������Ƿ�������ཻ,����ཻ�򽫾��������������Ľ����¼�� outV ��
			 * @param			lpv			ֱ���ϵ�һ��
			 * @param			ltv			ֱ�ߵ�����
			 * @param			spCV		���ĵ�
			 * @param			spRadius	����뾶
			 * @param			outV		��ž������߷��������������
			 * @return			���� true ��ʾ�ཻ, ����false ��ʾ���ཻ
			 * */
			static bool IntersectionRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV);
			/**
			 * �ж������Ƿ�������ཻ,����ཻ�򽫾��������������Ľ����¼�� outV ��
			 * @param			lpv			ֱ���ϵ�һ��
			 * @param			ltv			ֱ�ߵ�����
			 * @param			spCV		���ĵ�
			 * @param			spRadius	����뾶
			 * @param			outV		��ž������߷��������������
			 * @param			outV		��������������ž������߷�����Զ�������
			 * @return			���� true ��ʾ�ཻ, ����false ��ʾ���ཻ
			 * */
			static bool IntersectionTwoRLByV2(const Vec3D& lpv, const Vec3D& ltv, const Vec3D& spCV, VCG_Number spRadius, Vec3D& outV, Vec3D& outV2);
		protected:
				static Vec3D __sphAv;
				static Vec3D __sphBv;
		private:

		};
	}
}
typedef voxcgeom::base::Sphere Sphere;