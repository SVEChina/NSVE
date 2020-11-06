//
//  IMIDeformMgr.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIDeformMgr.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMICameraMgr.h"
#include "../core/IMIDeformImageMove.h"
#include "../basesys/IMIScene.h"
#include "../work/IMITdCore.h"

using namespace imi;

IMIDeformMgr::IMIDeformMgr(IMIInstPtr _app)
:IMISysBase(_app){
    m_deformArray.clear();
    m_defromLock = MakeSharedPtr<IMILock>();
}

IMIDeformMgr::~IMIDeformMgr() {
    m_defromLock = nullptr;
}

void IMIDeformMgr::init() {
    
}

void IMIDeformMgr::destroy(){
    clear();
}

void IMIDeformMgr::update(f32 _dt){
    m_defromLock->lock();
    for(int i=0;i<m_deformArray.size();i++){
        m_deformArray[i]->update(_dt);
        m_deformArray[i]->render();
    }
    removeEnd();
    m_defromLock->unlock();
}

void IMIDeformMgr::pushDeform(IMIDeformImageMovePtr deform){
    m_defromLock->lock();
    m_deformArray.append(deform);
    m_defromLock->unlock();
}

IMIDeformImageMovePtr IMIDeformMgr::getDeform(s32 _postion){
    if(m_deformArray.size()>_postion){
         return m_deformArray.get(_postion);
    }
    return nullptr;
}

void IMIDeformMgr::clear(){
    m_defromLock->lock();
    m_deformArray.clear();
    m_defromLock->unlock();
}

void IMIDeformMgr::removeEnd(){
    for(s32 i = 0; i < m_deformArray.size(); i++){
        if(m_deformArray[i]->m_rule){
            m_deformArray.remove(i);
            i--;
            continue;
        }
    }
}
