//
// SVAnimateSkin.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ANIMATE_SKIN_H
#define SV_ANIMATE_SKIN_H

#include "../base/SVGBase.h"
#include "../base/SVVec3.h"
#include "../base/SVVec4.h"
#include "../base/SVMat4.h"
#include "../base/SVQuat.h"
#include "../base/svstr.h"
#include "../base/SVMap.h"

#include <vector>

namespace sv {

    enum SVChanType {
        E_CN_T_TRANS = 0,
        E_CN_T_SCALE = 1,
        E_CN_T_ROT = 2,
        E_CN_T_WEIGHT = 3
    };
        
    //骨头
    class SVBone :public SVObject {
    public:
        SVBone();
        s32 m_id;           //骨头ID
        s32 m_nodeid;       //对应的node_id
        FVec3 m_tran;
        FVec3 m_scale;
        FVec4 m_rot;
        SVBonePtr m_pParent;
        FMat4 m_absoluteMat;
        FMat4 m_relaMat;
        FMat4 m_invertBindMat;
        FMat4 m_resultMat;
        SVString m_name;
        typedef std::vector<SVBonePtr> BONEPOOL;
        BONEPOOL m_children;
    public:
        void clear();
        
        void update();
    };
        
    //骨架
    class SVSkeleton :public SVObject {
    public:
        SVSkeleton();
        
        void addBone(SVBonePtr _bone); //需要单独对SVLoaderGLTF开放接口 **fuyizhou
        
        SVBonePtr getBoneByID(s32 _id);
        
        SVBonePtr getBoneByNodeID(s32 _id);
        
        SVBonePtr getBoneByName(cptr8 _name);
        
        s32 getBoneNum();
        
        void refresh();

        void destroy();
        
        SVString m_name;
        
        SVBonePtr m_root;
        SVArray<FMat4> m_mats;
        typedef SVArray<SVBonePtr> BONEPOOL;
        BONEPOOL m_boneArray;
    };
        
    //
    class SVASKey : public SVObject{
    public:
        SVASKey() {
            m_time = 0.0f;
        }
        ~SVASKey(){
        }
        f32 m_time;
        
    };

    //
    class SVASKeyPos : public SVASKey{
    public:
        SVASKeyPos() {
        }
        ~SVASKeyPos(){
            
        }
        FVec3 m_pos;
    };

    //
    class SVASKeyRot : public SVASKey{
    public:
        SVASKeyRot() {
        }
        ~SVASKeyRot(){
        }
        FVec4 m_rot;
    };

    //
    class SVASKeyScale : public SVASKey{
    public:
        SVASKeyScale() {
        }
        ~SVASKeyScale(){
        }
        FVec3 m_scale;
    };
        
    /*
     轨道
     */
    class SVChannel : public SVObject{
    public:
        SVChannel();
        
        ~SVChannel();
        
        void update(f32 _dt,f32 _acct,s32 _rate, SVBonePtr _bone);
        
        s32 findPreKey(f32 _acct,s32 _rate);
        
        s32 m_target_node;       //目标id
        s32 m_intertype_trans;    //插值方式 linear
        s32 m_intertype_rot;    //插值方式 linear
        s32 m_intertype_scale;    //插值方式 linear
        s32 m_intertype_weight;    //插值方式 linear
        f32 m_maxTime;
        f32 m_minTime;
        //数据关系
        typedef SVArray<SVASKeyPtr> ASKEYPOOL;
        ASKEYPOOL m_keyPool;
        SVString m_target_path;        //动作名称
    private:
        FVec3 _lerp_trans(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_pos1,FVec3 &_pos2);
        FVec3 _lerp_scale(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_scale1,FVec3 &_scale2);
        FVec4 _lerp_rot(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec4 &_rot1, FVec4 &_rot2);
        f32 _lerp_weights();
    };
        
    //动作表
    struct SVASAniTbl{
        SVString m_name;        //动作名称
        s32 m_beginKey;         //开始帧
        s32 m_endKe;            //结束阵
    };
        
    /*
     蒙皮动画 单个动画名称
     */
    class SVAnimateSkin : public SVGBaseEx{
    public:
        SVAnimateSkin(SVInstPtr _app,cptr8 _name);

        virtual ~SVAnimateSkin();
        
        void update(f32 _dt);
        
        void setSkes(std::vector<SVSkeletonPtr> &_skes);
        
        void clearSke();

        cptr8 getName();
        void setName(cptr8 ptr);
        
        void addChannel(SVChannelPtr _chan);
        
        void clearChannel();
        
        void play(cptr8 _name){}
        
    protected:
        //动画名称
        SVString m_name;
        //轨道
        typedef std::vector<SVSkeletonPtr> SKEPOOL;
        SKEPOOL m_skePool;
        //
        f32 m_accTime;
        f32 m_totalTime;
        //轨道
        typedef std::vector<SVChannelPtr> CHNPOOL;
        CHNPOOL m_chnPool;
        
        //动作表
        typedef std::vector<SVASAniTbl> ANITBLPOOL;
        ANITBLPOOL m_aniTblPool;
    };
        
    //骨架池
    class SVSkinMgr : public SVGBaseEx{
    public:
        SVSkinMgr(SVInstPtr _app);
        
        ~SVSkinMgr();
        
        void addSkin(SVAnimateSkinPtr _skin);
        
        void remvoeSkin(cptr8 _name);
        
    protected:
        typedef SVMap<SVString,SVAnimateSkinPtr> SKINPOOL;
        SKINPOOL m_skinPool;
    };

}//!namespace sv


#endif //SV_ANIMATE_SKIN_H
