
/**
Author: Vily

*/
#include <cmath>
#include "cgeomPre.h"
extern VCG_Number SafeACos(VCG_Number x)
{
    if (x <= -1.0f)
    {
        return VCG_MATH_PI;
    }
    if (x >= 1.0f)
    {
        return 0.0f;
    }
    return std::acos(x);
}
// ����Ƕȵ�sin �� cos ֵ
                // ��ĳЩƽ̨�ϣ������Ҫ������ֵ��ͬʱ����Ҫ�ȷֿ������
extern void SinCos(VCG_Number* returnSin, VCG_Number* returnCos, VCG_Number rad_theta)
{
    // Ϊ�˼���򵥣�����ֻʹ�ñ�׼���Ǻ���
    *returnSin = std::sin(rad_theta);
    *returnCos = std::cos(rad_theta);
}