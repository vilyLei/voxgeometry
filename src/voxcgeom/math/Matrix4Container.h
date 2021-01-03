/**
Author: Vily
 * matrix container for concurrent compute strage...
 * 1.父级的matrix变换会影响子类
 * 2.子级的matrix变换不会影响父级
*/

#pragma once
#include <vector>
#include "Matrix4.h"

namespace voxcgeom
{
    namespace math
    {
        class Matrix4Container
        {
        public:
            Matrix4Container();
            Matrix4Container(Matrix4* mat);
            virtual ~Matrix4Container();

            static int                                  s_uid;
            const static unsigned int                   UPDATE_NONE;// = 0;
            const static unsigned int                   UPDATE_POSITION;// = 1;
            const static unsigned int                   UPDATE_ROTATION;// = 2;
            const static unsigned int                   UPDATE_SCALE;// = 4;
            const static unsigned int                   UPDATE_TRANSFORM;// = 7;
            const static unsigned int                   UPDATE_PARENT_MAT;// = 8;

            int                                         version;
        private:
            static VCG_Number                           s_initData[16];
            VCG_Number                                  m_fs32[16];
            int                                         m_uid;
            // It is a flag that need inverted mat yes or no
            bool                                        m_invMatEnabled;// = false;
            int                                         m_updatedStatus;// = 1;
            int                                         m_updateStatus;// = 7;

            // local to world spcae matrix
            Matrix4                                     *m_omat;
            Matrix4                                     *m_localMat;
            Matrix4                                     *m_parentMat;
            // word to local matrix
            Matrix4                                     *m_invOmat;

            size_t                                      m_childListLen;
            std::vector<Matrix4Container*>              m_childList;
            Matrix4Container                            *m_parent;

            void addChild(Matrix4Container* child);
            int getUid();
            VCG_Number getX();
            VCG_Number getY();
            VCG_Number getZ();
            void setX(VCG_Number p);
            void setY(VCG_Number p);
            void setZ(VCG_Number p);
            void setXYZ(VCG_Number px, VCG_Number py, VCG_Number pz);
            void setPosition(const Vec3D& p);
            void getPosition(Vec3D& pv);
            void copyPositionFrom(Matrix4Container& t);
            VCG_Number getRotationX();
            VCG_Number getRotationY();
            VCG_Number getRotationZ();
            void setRotationX(VCG_Number degrees);
            void setRotationY(VCG_Number degrees);
            void setRotationZ(VCG_Number degrees);
            void setRotationXYZ(VCG_Number rx, VCG_Number ry, VCG_Number rz);
            VCG_Number getScaleX();
            VCG_Number getScaleY();
            VCG_Number getScaleZ();
            void setScaleX(VCG_Number p);
            void setScaleY(VCG_Number p);
            void setScaleZ(VCG_Number p);
            void setScaleXYZ(VCG_Number sx, VCG_Number sy, VCG_Number sz);
            void setScale(VCG_Number s);

            void localToGlobal(Vec3D& pv);
            void globalToLocal(Vec3D& pv);

            VCG_Number* getMatrixFS32();
            // maybe need call update function
            Matrix4* getInvMatrix();
            Matrix4* getLocalMatrix();
            // get local to world matrix, maybe need call update function
            Matrix4* getMatrix();
            void copyMatrixTo(Matrix4& ma);
            // local to world matrix, 使用的时候注意数据安全->防止多个显示对象拥有而出现多次修改的问题,因此此函数尽量不要用
            void setParentMatrix(Matrix4 *matrix);
            void updateMatrixData(Matrix4& matrix);
            void destroy();
            void update();
        };
    }
}
typedef voxcgeom::math::Matrix4Container Matrix4Container;