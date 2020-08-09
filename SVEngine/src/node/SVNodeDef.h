//
// SVNodeDef.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_NODEDEF_H
#define SV_NODEDEF_H

#include "SVNodeDeclare.h"
#include "../base/SVVec3.h"
#include "../base/SVMat4.h"

//动画状态(停止 播放 暂停)
//停止:不更新+不渲染
//播放:更新+渲染
//暂停:不更新+渲染

namespace sv {

    enum E_ANISTATE{
        tANI_STATE_STOP = 0,
        tANI_STATE_PLAY,
        tANI_STATE_PAUSE,
        tANI_STATE_WAIT
    };

    //锚点
    enum EUIARCHO {
        E_ARCHO_LT = 0,
        E_ARCHO_CT,
        E_ARCHO_RT,
        E_ARCHO_LC,
        E_ARCHO_CC,
        E_ARCHO_RC,
        E_ARCHO_LB,
        E_ARCHO_CB,
        E_ARCHO_RB
    };

    //渲染属性
    struct SVRenderProp {
        s8 m_shadow_create;     //产生阴影
        s8 m_shadow_receive;    //接收阴影
        s8 m_refelct;           //接收反射
        s8 m_light_receive;     //接收光照
        s8 m_render_type;       //渲染类型
    };

    //位移属性
    struct SVTransProp {
        FVec3 m_pos;
        FVec3 m_rot;
        FVec3 m_scale;
    };

    //位置属性
    struct SVAttriPos {
        
        SVAttriPos() {
            m_pos.set(0.0f);
            m_rot.set(0.0f);
            m_scale.set(1.0f);
        };
        
        FMat4 getMatrix() {
            FMat4 t_mat;
            FMat4 t_mat_pos,t_mat_rot_x,t_mat_rot_y,t_mat_rot_z,t_mat_scale;
            t_mat_pos.setIdentity();
            t_mat_pos.setTranslate(m_pos);
            t_mat_scale.setIdentity();
            t_mat_scale.setScale(m_scale);
            t_mat_rot_x.setIdentity();
            t_mat_rot_x.setRotateX(m_rot.x);
            t_mat_rot_y.setIdentity();
            t_mat_rot_y.setRotateY(m_rot.y);
            t_mat_rot_z.setIdentity();
            t_mat_rot_z.setRotateZ(m_rot.z);
            t_mat = t_mat_scale*t_mat_rot_x*t_mat_rot_y*t_mat_rot_z*t_mat_pos;
            return t_mat;
        };
        
        FVec3 m_pos;
        FVec3 m_rot;
        FVec3 m_scale;
    };


}//!namespace sv

#endif //SV_NODEDEF_H
