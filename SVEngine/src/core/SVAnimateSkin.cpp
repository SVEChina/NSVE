//
// SVAnimateSkin.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVAnimateSkin.h"
#include "../base/SVPreDeclare.h"

//清理
using namespace sv;

SVBone::SVBone() {
    m_name = "";
    m_id = 0;
    m_tran.set(0.0f, 0.0f, 0.0f);
    m_scale.set(1.0f, 1.0f, 1.0f);
    m_rot.set(0.0f, 0.0f, 0.0f,1.0f);
    m_pParent = nullptr;
    m_children.clear();
    m_absoluteMat.setIdentity();
}

void SVBone::clear() {
    m_pParent = nullptr;
    for(s32 i=0;i<m_children.size();i++) {
        m_children[i]->clear();
    }
    m_children.clear();
}

void SVBone::update() {
    FMat4 t_transMat;
    t_transMat.setIdentity();
    t_transMat.setTranslate(m_tran);
    
    FMat4 t_scaleMat;
    t_scaleMat.setIdentity();
    t_scaleMat.setScale(m_scale);
    
    FMat4 t_rotMat;
    t_rotMat.setIdentity();
    t_rotMat.set(SVQuat(m_rot));
    
    m_relaMat = t_transMat*t_rotMat*t_scaleMat;
    if(m_pParent) {
        m_absoluteMat = m_pParent->m_absoluteMat*m_relaMat;
    }else{
        m_absoluteMat = m_relaMat;
    }
    //计算父子关系的逆矩阵
    m_resultMat = m_absoluteMat*m_invertBindMat;
    for(s32 i=0;i<m_children.size();i++) {
        m_children[i]->update();
    }
}

//
SVSkeleton::SVSkeleton(){
    m_name = "ske";
    m_root = nullptr;
    m_boneArray.clear();
    m_mats.clear();
}

void SVSkeleton::refresh() {
    //骨架刷新 计算各自的绝对矩阵
    if(m_root) {
        m_root->update();
    }
    //
    if (m_mats.size() != m_boneArray.size()) {
        m_mats.clear();
        m_mats.resize(m_boneArray.size());
    }
    s32 len = m_boneArray.size();
    for (s32 i = 0; i < len; i++) {
        m_mats[i] = m_boneArray[i]->m_resultMat;
    }
    
}

void SVSkeleton::addBone(SVBonePtr _bone) {
    m_boneArray.append(_bone);
}

s32 SVSkeleton::getBoneNum() {
    return m_boneArray.size();
}

SVBonePtr SVSkeleton::getBoneByID(s32 _id) {
    for(s32 i=0;i<m_boneArray.size();i++) {
        if( m_boneArray[i]->m_id == _id ) {
            return m_boneArray[i];
        }
    }
    return nullptr;
}

SVBonePtr SVSkeleton::getBoneByNodeID(s32 _id) {
    for(s32 i=0;i<m_boneArray.size();i++) {
        if( m_boneArray[i]->m_nodeid == _id ) {
            return m_boneArray[i];
        }
    }
    return nullptr;
}

SVBonePtr SVSkeleton::getBoneByName(cptr8 _name) {
    for(s32 i=0;i<m_boneArray.size();i++) {
        if( m_boneArray[i]->m_name == _name ) {
            return m_boneArray[i];
        }
    }
    return nullptr;
}

void SVSkeleton::destroy() {
    //
    m_boneArray.clear();
    //
    if(m_root) {
        m_root->clear();
        m_root = nullptr;
    }
}

//专门用于骨骼动画的时间轴
SVChannel::SVChannel() {
    m_target_node = 0;
    m_intertype_trans = -1;    //插值方式 linear
    m_intertype_rot = -1;    //插值方式 linear
    m_intertype_scale = -1;    //插值方式 linear
    m_intertype_weight = -1;    //插值方式 linear
    m_maxTime = 0.0f;
    m_minTime = 0.0f;
}

SVChannel::~SVChannel() {
    m_keyPool.destroy();
}
    
void SVChannel::update(f32 _dt,f32 _acct,s32 _rate, SVBonePtr _bone) {
    //二分法取key
    s32 t_preKey = findPreKey(_acct,_rate);
    s32 t_aftKey = t_preKey+1;
    if(t_aftKey>=m_keyPool.size()) {
        t_aftKey = t_preKey;
    }

    //插值
    SVASKeyPtr pKey = m_keyPool[t_preKey];
    SVASKeyPtr aKey = m_keyPool[t_aftKey];
    //
    
    if (m_target_path == "translation") {
        SVASKeyPosPtr p0 = DYN_TO_SHAREPTR(SVASKeyPos, pKey);
        SVASKeyPosPtr p1 = DYN_TO_SHAREPTR(SVASKeyPos, aKey);
        _bone->m_tran = _lerp_trans(0, pKey->m_time, aKey->m_time, _acct, p0->m_pos, p1->m_pos);
    } else if(m_target_path == "rotation") {
        SVASKeyRotPtr p0 = DYN_TO_SHAREPTR(SVASKeyRot, pKey);
        SVASKeyRotPtr p1 = DYN_TO_SHAREPTR(SVASKeyRot, aKey);
        _bone->m_rot = _lerp_rot(0, pKey->m_time, aKey->m_time, _acct, p0->m_rot, p1->m_rot);
    } else if(m_target_path == "scale") {
        SVASKeyScalePtr p0 = DYN_TO_SHAREPTR(SVASKeyScale, pKey);
        SVASKeyScalePtr p1 = DYN_TO_SHAREPTR(SVASKeyScale, aKey);
        _bone->m_scale = _lerp_scale(0, pKey->m_time, aKey->m_time, _acct, p0->m_scale, p1->m_scale);
    } else if(m_target_path == "weights") {
//        SVASKeyScalePtr p0 = DYN_TO_SHAREPTR(SVASKeyScale, pKey);
//        SVASKeyScalePtr p1 = DYN_TO_SHAREPTR(SVASKeyScale, aKey);
        
    }
    
}

//平移插值
FVec3 SVChannel::_lerp_trans(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_pos1, FVec3 &_pos2) {
    f32 t_dert = (_timecur - _timepre)/(_timenxt - _timepre);
    FVec3 t_result = _pos1 *(1.0f-t_dert) + _pos2*t_dert;
    return t_result;
}

//缩放插值
FVec3 SVChannel::_lerp_scale(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec3 &_scale1, FVec3 &_scale2) {
    f32 t_dert = (_timecur - _timepre)/(_timenxt - _timepre);
    FVec3 t_result = _scale1 *(1.0f-t_dert) + _scale2*t_dert;
    return t_result;
}

//旋转插值
FVec4 SVChannel::_lerp_rot(s32 _mod, f32 _timepre, f32 _timenxt, f32 _timecur, FVec4 &_rot1, FVec4 &_rot2) {
    //四元数差值
    f32 t_dert = (_timecur - _timepre)/(_timenxt - _timepre);
    SVQuat q1(_rot1);
    SVQuat q2(_rot2);
    SVQuat t_quat= slerp(q1,q2,t_dert);
    FVec4 t_value(t_quat);
    return t_value;
}

//权重插值
f32 SVChannel::_lerp_weights() {
    return 0.0f;
}

//
s32 SVChannel::findPreKey(f32 _acct,s32 _rate) {
    //卡帧
    //修正时间
    s32 length = m_keyPool.size();
    //error
    if(length == 0 ) {
        return 0;
    }
    //最后一帧
    if( m_keyPool[length - 1]->m_time < _acct ) {
        return length - 1;
    }
    //第一帧
    if(_acct <m_keyPool[0]->m_time) {
        return 0;
    }
    s32 left = 0;
    s32 right = length - 1;
    s32 middle = 0;
    f32 t_tt = 0.0f;
    while(left <= right) {
        middle = (left + right) >> 1;
        t_tt = m_keyPool[middle]->m_time;
        if( _acct>t_tt) {
            if(right-left == 1) {
                return left;    //中间没有帧了
            }
            if(right == left) {
                return left;
            }
            //
            left = middle;
        } else if(_acct < t_tt ) {
            if(right-left == 1) {
                return left;    //中间没有帧了
            }
            if(right == left) {
                return left-1;
            }
            //
            right = middle;
        } else {
            return middle;
        }
    }
    if(right<left) {
        return middle;
    }
    if(right == left) {
        return middle;
    }
    return middle;
}

//
SVAnimateSkin::SVAnimateSkin(SVInstPtr _app,cptr8 _name)
:SVGBaseEx(_app)
,m_name(_name){
    m_accTime = 0;
    m_totalTime = 0.0f;
    clearSke();
    clearChannel();
}

SVAnimateSkin::~SVAnimateSkin() {
    clearSke();
    clearChannel();
}

cptr8 SVAnimateSkin::getName() {
    return m_name.c_str();
}

void SVAnimateSkin::setName(cptr8 ptr) {
    m_name = ptr;
}

void SVAnimateSkin::addChannel(SVChannelPtr _chan) {
    if(_chan) {
        m_totalTime = m_totalTime>_chan->m_maxTime?m_totalTime:_chan->m_maxTime;
        m_chnPool.push_back(_chan);
    }
}

void SVAnimateSkin::clearChannel() {
    m_chnPool.clear();
}

void SVAnimateSkin::setSkes(std::vector<SVSkeletonPtr> &_skes) {
    m_skePool = _skes;
}

void SVAnimateSkin::clearSke(){
    m_skePool.clear();
}

void SVAnimateSkin::update(f32 _dt) {
    //计算时间
    m_accTime += _dt;
    bool t_end = false;;
    if(m_accTime>m_totalTime) {
        m_accTime = m_totalTime;
        t_end = true;
    }
    
    if(m_skePool.size() == 0) {
        //没有骨架就不用跑动画了
        return ;
    }
            
    //根据Skeleton更新所有的Bone信息
    for (int sIndex = 0; sIndex < m_skePool.size(); sIndex++) {
        SVSkeletonPtr _ske = m_skePool[sIndex];
        //
        for(s32 i=0;i<m_chnPool.size();i++) {
            SVChannelPtr _channel = m_chnPool[i];
            SVBonePtr _bone = _ske->getBoneByNodeID(_channel->m_target_node);
            if (!_bone) {
                continue;
            }
            _channel->update(_dt, m_accTime, 30, _bone);
        }
        //更新
        _ske->refresh();
    }
    
    
    if(t_end) {
        m_accTime = 0;
    }
}

//
SVSkinMgr::SVSkinMgr(SVInstPtr _app)
:SVGBaseEx(_app){
}

SVSkinMgr::~SVSkinMgr() {
    
}

void SVSkinMgr::addSkin(SVAnimateSkinPtr _skin) {
    //m_skinPool
}

void SVSkinMgr::remvoeSkin(cptr8 _name) {
    
}
