//
// IMIAnimateSkin.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ANIMATE_SKIN_H
#define IMI_ANIMATE_SKIN_H

#include "../base/IMIGBase.h"
#include "../base/IMIVec3.h"
#include "../base/IMIVec4.h"
#include "../base/IMIMat4.h"
#include "../base/IMIQuat.h"
#include "../base/imistr.h"
#include "../base/IMIMap.h"

#include <vector>

namespace imi {

    enum IMIChanType {
        E_CN_T_TRANS = 0,
        E_CN_T_SCALE = 1,
        E_CN_T_ROT = 2,
        E_CN_T_WEIGHT = 3
    };
        
    //骨头
    class IMIBone :public IMIObject {
    public:
        IMIBone();
        s32 m_id;           //骨头ID
        s32 m_nodeid;       //对应的node_id
        FVec3 m_tran;
        FVec3 m_scale;
        FVec4 m_rot;
        IMIBonePtr m_pParent;
        FMat4 m_absoluteMat;
        FMat4 m_relaMat;
        FMat4 m_invertBindMat;
        FMat4 m_resultMat;
        IMIString m_name;
        typedef std::vector<IMIBonePtr> BONEPOOL;
        BONEPOOL m_children;
    public:
        void clear();
        
        void update();
    };
        
    //骨架
    class IMISkeleton :public IMIObject {
    public:
        IMISkeleton();
        
        void addBone(IMIBonePtr _bone); //需要单独对IMILoaderGLTF开放接口 **fuyizhou
        
        IMIBonePtr getBoneByID(s32 _id);
        
        IMIBonePtr getBoneByNodeID(s32 _id);
        
        IMIBonePtr getBoneByName(cptr8 _name);
        
        s32 getBoneNum();
        
        void refresh();

        void destroy();
        
        IMIString m_name;
        
        IMIBonePtr m_root;
        IMIArray<FMat4> m_mats;
        typedef IMIArray<IMIBonePtr> BONEPOOL;
        BONEPOOL m_boneArray;
    };
        
    //
    class IMIASKey : public IMIObject{
    public:
        IMIASKey() {
            m_time = 0.0f;
        }
        ~IMIASKey(){
        }
        f32 m_time;
        
    };

    //
    class IMIASKeyPos : public IMIASKey{
    public:
        IMIASKeyPos() {
        }
        ~IMIASKeyPos(){
            
        }
        FVec3 m_pos;
    };

    //
    class IMIASKeyRot : public IMIASKey{
    public:
        IMIASKeyRot() {
        }
        ~IMIASKeyRot(){
        }
        FVec4 m_rot;
    };

    //
    class IMIASKeyScale : public IMIASKey{
    public:
        IMIASKeyScale() {
        }
        ~IMIASKeyScale(){
        }
        FVec3 m_scale;
    };
        
    /*
     轨道
     */
    class IMIChannel : public IMIObject{
    public:
        IMIChannel();
        
        ~IMIChannel();
        
        void update(f32 _dt,f32 _acct,s32 _rate, IMIBonePtr _bone);
        
        s32 findPreKey(f32 _acct,s32 _rate);
        
        s32 m_target_node;       //目标id
        s32 m_intertype_trans;    //插值方式 linear
        s32 m_intertype_rot;    //插值方式 linear
        s32 m_intertype_scale;    //插值方式 linear
        s32 m_intertype_weight;    //插值方式 linear
        f32 m_maxTime;
        f32 m_minTime;
        //数据关系
        typedef IMIArray<IMIASKeyPtr> ASKEYPOOL;
        ASKEYPOOL m_keyPool;
        IMIString m_target_path;        //动作名称
    private:
        FVec3 _lerp_trans(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_pos1,FVec3 &_pos2);
        FVec3 _lerp_scale(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_scale1,FVec3 &_scale2);
        FVec4 _lerp_rot(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec4 &_rot1, FVec4 &_rot2);
        f32 _lerp_weights();
    };
        
    //动作表
    struct IMIASAniTbl{
        IMIString m_name;        //动作名称
        s32 m_beginKey;         //开始帧
        s32 m_endKe;            //结束阵
    };
        
    /*
     蒙皮动画 单个动画名称
     */
    class IMIAnimateSkin : public IMIGBaseEx{
    public:
        IMIAnimateSkin(IMIInstPtr _app,cptr8 _name);

        virtual ~IMIAnimateSkin();
        
        void update(f32 _dt);
        
        void setSkes(std::vector<IMISkeletonPtr> &_skes);
        
        void clearSke();

        cptr8 getName();
        
        void addChannel(IMIChannelPtr _chan);
        
        void clearChannel();
        
        void play(cptr8 _name){}
        
    protected:
        //动画名称
        IMIString m_name;
        //轨道
        typedef std::vector<IMISkeletonPtr> SKEPOOL;
        SKEPOOL m_skePool;
        //
        f32 m_accTime;
        f32 m_totalTime;
        //轨道
        typedef std::vector<IMIChannelPtr> CHNPOOL;
        CHNPOOL m_chnPool;
        
        //动作表
        typedef std::vector<IMIASAniTbl> ANITBLPOOL;
        ANITBLPOOL m_aniTblPool;
    };
        
    //骨架池
    class IMISkinMgr : public IMIGBaseEx{
    public:
        IMISkinMgr(IMIInstPtr _app);
        
        ~IMISkinMgr();
        
        void addSkin(IMIAnimateSkinPtr _skin);
        
        void remvoeSkin(cptr8 _name);
        
    protected:
        typedef IMIMap<IMIString,IMIAnimateSkinPtr> SKINPOOL;
        SKINPOOL m_skinPool;
    };

}//!namespace imi


#endif //IMI_ANIMATE_SKIN_H
