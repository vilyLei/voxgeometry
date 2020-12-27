
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
// 计算角度的sin 和 cos 值
                // 在某些平台上，如果需要这两个值，同时计算要比分开计算快
extern void SinCos(VCG_Number* returnSin, VCG_Number* returnCos, VCG_Number rad_theta)
{
    // 为了计算简单，这里只使用标准三角函数
    *returnSin = std::sin(rad_theta);
    *returnCos = std::cos(rad_theta);
}