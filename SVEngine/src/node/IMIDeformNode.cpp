//
//  IMIDeformNode.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIDeformNode.h"
#include "../core/IMIDeformImageMove.h"

using namespace imi;

IMIDeformNode::IMIDeformNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIDeformNode";
    
}

IMIDeformNode::~IMIDeformNode(){
    
}

void IMIDeformNode::init(){

}

void IMIDeformNode::destroy(){
    m_deformPool.clear();
}

void IMIDeformNode::update(f32 _dt){
    IMINode::update(_dt);
    for(s32 i=0;i<m_deformPool.size();i++){
        m_deformPool[i]->update(_dt);
    }
}

void IMIDeformNode::render(){
    for(s32 i=0;i<m_deformPool.size();i++){
        m_deformPool[i]->render();
    }
    m_deformPool.clear();
}

void IMIDeformNode::pushDeform(IMIArray<IMIDeformImageMovePtr> _deformArray){
    m_deformPool.append(_deformArray);
}

bool IMIDeformNode::procEvent(IMIEventPtr _event){
 
    return true;
}
