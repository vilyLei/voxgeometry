/**
Author: Vily
 * matrix container for concurrent compute strategy...
 * 1.parent matrix does change child transform
 * 2.child matrix does not change parent transform 
*/

#include <iostream>
#include "assert.h"
#include "Matrix4Container.h"

namespace voxcgeom
{
    namespace math
    {
        class Matrix4Pool;

        int Matrix4Container::s_uid{0};
        VCG_Number Matrix4Container::s_initData[16]{
                1.0f,0.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,0.0f,
                0.0f,0.0f,1.0f,0.0f,
                0.0f,0.0f,0.0f,1.0f
        };
        const unsigned int Matrix4Container::UPDATE_NONE{ 0 };
        const unsigned int Matrix4Container::UPDATE_POSITION{ 1 };
        const unsigned int Matrix4Container::UPDATE_ROTATION{ 2 };
        const unsigned int Matrix4Container::UPDATE_SCALE{ 4 };
        const unsigned int Matrix4Container::UPDATE_TRANSFORM{ 7 };
        const unsigned int Matrix4Container::UPDATE_PARENT_MAT{ 8 };

        Matrix4Container::Matrix4Container()
            : version(0)
            , m_uid(Matrix4Container::s_uid++)
            , m_invMatEnabled(false)
            , m_updatedStatus(1)
            , m_updateStatus(Matrix4Container::UPDATE_TRANSFORM)
            , m_parentMat(nullptr)
            , m_invOmat(nullptr)
            , m_childListLen(0)
            , m_parent(nullptr)
        {
            std::memcpy(m_fs32, &s_initData, VCG_MATRIX4_DATA_SIZE);
            m_omat = new Matrix4();
            m_localMat = m_omat;
        }
        Matrix4Container::Matrix4Container(Matrix4* mat)
            : version(0)
            , m_uid(Matrix4Container::s_uid++)
            , m_invMatEnabled(false)
            , m_updatedStatus(1)
            , m_updateStatus(Matrix4Container::UPDATE_TRANSFORM)
            , m_parentMat(nullptr)
            , m_invOmat(nullptr)
            , m_childListLen(0)
            , m_parent(nullptr)
        {
            assert(mat != nullptr);
            m_localMat = m_omat = mat;
            std::memcpy(m_fs32, &s_initData, VCG_MATRIX4_DATA_SIZE);
        }
        Matrix4Container::~Matrix4Container()
        {
            std::cout << "Matrix4Container::deconstructor()..." << std::endl;
            destroy();
        }
        void Matrix4Container::addChild(Matrix4Container *child)
        {
            if (child != nullptr && child->m_parent == nullptr && child != this)
            {
                child->m_parent = this;
                child->setParentMatrix(getMatrix());
                m_childList.push_back(child);
                m_childListLen++;
            }
        }
        void Matrix4Container::removeChild(Matrix4Container* child)
        {
            if (child != nullptr && child->m_parent == this)
            {
                //std::vector<int>::iterator it = vector.begin();
                auto it = m_childList.begin();
                auto end = m_childList.end();

                for (; it != end; ++it)
                {
                    if (*it == child)
                    {
                        m_childList.erase(it);
                        m_childListLen--;
                        //  std::cout << "find a child, and remove it." <<", m_childListLen: "<< m_childListLen << std::endl;
                        break;
                    }
                }
            }
        }
        int Matrix4Container::getUid(){ return m_uid; }
        VCG_Number Matrix4Container::getX() { return m_fs32[12]; }
        VCG_Number Matrix4Container::getY() { return m_fs32[13]; }
        VCG_Number Matrix4Container::getZ() { return m_fs32[14]; }
        void Matrix4Container::setX(VCG_Number p){ m_updateStatus |= 1; m_updatedStatus |= 1; m_fs32[12] = p; }
        void Matrix4Container::setZ(VCG_Number p){ m_updateStatus |= 1; m_updatedStatus |= 1; m_fs32[14] = p; }
        void Matrix4Container::setY(VCG_Number p){ m_updateStatus |= 1; m_updatedStatus |= 1; m_fs32[13] = p; }
        void Matrix4Container::setXYZ(VCG_Number px, VCG_Number py, VCG_Number pz)
        {
            m_fs32[12] = px;
            m_fs32[13] = py;
            m_fs32[14] = pz;
            m_updateStatus |= 1;
            m_updatedStatus |= 1;
        }
        void Matrix4Container::setPosition(const Vec3D& pv)
        {
            m_fs32[12] = pv.x;
            m_fs32[13] = pv.y;
            m_fs32[14] = pv.z;
            m_updateStatus |= 1;
            m_updatedStatus |= 1;
        }
        void Matrix4Container::getPosition(Vec3D & pv)
        {
            pv.x = m_fs32[12];
            pv.y = m_fs32[13];
            pv.z = m_fs32[14];
        }
        void Matrix4Container::copyPositionFrom(Matrix4Container& t)
        {
            m_fs32[12] = t.m_fs32[12];
            m_fs32[13] = t.m_fs32[13];
            m_fs32[14] = t.m_fs32[14];
            m_updateStatus |= 1;
            m_updatedStatus |= 1;
        }
        VCG_Number Matrix4Container::getRotationX(){ return m_fs32[1]; }
        VCG_Number Matrix4Container::getRotationY(){ return m_fs32[6]; }
        VCG_Number Matrix4Container::getRotationZ(){ return m_fs32[9]; }
        void Matrix4Container::setRotationX(VCG_Number degrees){ m_fs32[1] = degrees; m_updateStatus |= 2; m_updatedStatus |= 2; }
        void Matrix4Container::setRotationY(VCG_Number degrees){ m_fs32[6] = degrees; m_updateStatus |= 2; m_updatedStatus |= 2; }
        void Matrix4Container::setRotationZ(VCG_Number degrees){ m_fs32[9] = degrees; m_updateStatus |= 2; m_updatedStatus |= 2; }
        void Matrix4Container::setRotationXYZ(VCG_Number rx, VCG_Number ry, VCG_Number rz)
        {
            m_fs32[1] = rx;
            m_fs32[6] = ry;
            m_fs32[9] = rz;
            m_updateStatus |= 2;
            m_updatedStatus |= 2;
        }
        VCG_Number Matrix4Container::getScaleX(){ return m_fs32[0]; }
        VCG_Number Matrix4Container::getScaleY(){ return m_fs32[5]; }
        VCG_Number Matrix4Container::getScaleZ(){ return m_fs32[10]; }
        void Matrix4Container::setScaleX(VCG_Number p){ m_fs32[0] = p; m_updateStatus |= 4; m_updatedStatus |= 4; }
        void Matrix4Container::setScaleY(VCG_Number p){ m_fs32[5] = p; m_updateStatus |= 4; m_updatedStatus |= 4; }
        void Matrix4Container::setScaleZ(VCG_Number p){ m_fs32[10] = p; m_updateStatus |= 4; m_updatedStatus |= 4; }
        void Matrix4Container::setScaleXYZ(VCG_Number sx, VCG_Number sy, VCG_Number sz)
        {
            m_fs32[0] = sx;
            m_fs32[5] = sy;
            m_fs32[10] = sz;

            m_updateStatus |= 4;
            m_updatedStatus |= 4;
        }
        void Matrix4Container::setScale(VCG_Number s)
        {
            m_fs32[0] = s;
            m_fs32[5] = s;
            m_fs32[10] = s;
            m_updateStatus |= 4;
            m_updatedStatus |= 4;
        }
        void Matrix4Container::localToGlobal(Vec3D& pv)
        {
            getMatrix()->transformVectorSelf(pv);
        }
        void Matrix4Container::globalToLocal(Vec3D& pv)
        {
            getInvMatrix()->transformVectorSelf(pv);
        }
        // maybe need call update function
        Matrix4* Matrix4Container::getInvMatrix()
        {
            if (m_invOmat != nullptr)
            {
                if (m_invMatEnabled)
                {
                    m_invOmat->copyFrom(*m_omat);
                    m_invOmat->invert();
                }
            }
            else
            {
                //m_invOmat = Matrix4Pool::GetMatrix();
                m_invOmat = new Matrix4();
                m_invOmat->copyFrom(*m_omat);
                m_invOmat->invert();
            }
            m_invMatEnabled = false;
            return m_invOmat;
        }
        Matrix4* Matrix4Container::getLocalMatrix()
        {
            if (m_updateStatus > 0)
            {
                update();
            }
            return m_localMat;
        }
        // get local to world matrix, maybe need call update function
        Matrix4* Matrix4Container::getMatrix()
        {
            if (m_updateStatus)
            {
                update();
            }
            return m_omat;
        }

        VCG_Number* Matrix4Container::getMatrixFS32()
        {
            return getMatrix()->getLocalFS32();
        }
        void Matrix4Container::copyMatrixTo(Matrix4& mat)
        {
            if (m_updateStatus)
            {
                update();
            }
            mat.copyFrom(*m_omat);
        }
        // local to world matrix
        void Matrix4Container::setParentMatrix(Matrix4 *matrix)
        {
            if (matrix != nullptr)
            {
                m_parentMat = matrix;
                m_invMatEnabled = true;
                if (m_parentMat != nullptr)
                {
                    if (m_localMat == m_omat)
                    {
                        m_updateStatus = Matrix4Container::UPDATE_TRANSFORM;
                        m_localMat = new Matrix4();
                    }
                    else
                    {
                        m_updateStatus |= Matrix4Container::UPDATE_PARENT_MAT;
                    }
                }
            }
        }
        void Matrix4Container::updateMatrixData(Matrix4& matrix)
        {
            m_updateStatus = 0;
            m_invMatEnabled = true;
            m_omat->copyFrom(matrix);
        }
        void Matrix4Container::destroy()
        {
            if (m_omat != nullptr)
            {
                if (m_childListLen > 0)
                {
                    for (size_t i = 0; i < m_childListLen; i++)
                    {
                        m_childList[i]->destroy();
                        m_childList[i] = nullptr;
                    }
                    // clear ele and retrieve memory space
                    std::vector<Matrix4Container*>().swap(m_childList);
                    m_childListLen = 0;
                }
                // 当自身被完全移出RenderWorld之后才能执行自身的destroy
                if (m_invOmat != nullptr) delete m_invOmat;
                if (m_omat != nullptr && m_omat != m_localMat) delete m_omat;
                if (m_localMat != nullptr) delete m_localMat;
                m_invOmat = nullptr;
                m_localMat = nullptr;
                m_omat = nullptr;
                m_parentMat = nullptr;
                m_updateStatus = Matrix4Container::UPDATE_TRANSFORM;

            }
        }

        void Matrix4Container::updateLocal()
        {
            if (m_updateStatus > 0)
            {
                if ((m_updateStatus & Matrix4Container::UPDATE_TRANSFORM) > 0)
                {
                    m_localMat->copyFromF32Arr(m_fs32, 0);
                    if ((m_updatedStatus & Matrix4Container::UPDATE_ROTATION) == Matrix4Container::UPDATE_ROTATION)
                    {
                        m_localMat->setRotationEulerAngle(m_fs32[1] * VCG_MATH_PI_OVER_180, m_fs32[6] * VCG_MATH_PI_OVER_180, m_fs32[9] * VCG_MATH_PI_OVER_180);
                    }
                }
                if (m_omat != m_localMat)
                {
                    m_omat->copyFrom(*m_localMat);
                }
                m_updateStatus = 0;
            }
        }
        void Matrix4Container::update()
        {
            if (m_updateStatus > 0)
            {
                if ((m_updateStatus & Matrix4Container::UPDATE_TRANSFORM) > 0)
                {
                    m_localMat->copyFromF32Arr(m_fs32, 0);
                    if ((m_updatedStatus & Matrix4Container::UPDATE_ROTATION) == Matrix4Container::UPDATE_ROTATION)
                    {
                        m_localMat->setRotationEulerAngle(m_fs32[1] * VCG_MATH_PI_OVER_180, m_fs32[6] * VCG_MATH_PI_OVER_180, m_fs32[9] * VCG_MATH_PI_OVER_180);
                    }

                    if (m_parentMat != nullptr)
                    {
                        m_updateStatus |= Matrix4Container::UPDATE_PARENT_MAT;
                    }
                }
                if (m_omat != m_localMat)
                {
                    m_omat->copyFrom(*m_localMat);
                }
                if ((m_updateStatus & Matrix4Container::UPDATE_PARENT_MAT) == Matrix4Container::UPDATE_PARENT_MAT)
                {
                    m_omat->append(*m_parentMat);
                }
                m_updateStatus = 0;

                if (m_childListLen > 0)
                {
                    //std::cout << "m_childListLen: " << m_childListLen <<",uid: "<< getUid()<< std::endl;
                    for (size_t i = 0; i < m_childListLen; i++)
                    {
                        m_childList[i]->setParentMatrix(m_omat);
                        m_childList[i]->update();
                    }
                }
            }
            else
            {
                if (m_childListLen > 0)
                {
                    for (size_t i = 0; i < m_childListLen; i++)
                    {
                        m_childList[i]->update();
                    }
                }
            }
        }

    }
}