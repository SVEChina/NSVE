//
// IMICube.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMICube.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../core/IMIGeoGen.h"
#include "../mtl/IMISurface.h"

using namespace imi;

IMICube::IMICube(IMIInstPtr _app)
:IMINode(_app) {
    ntype = "IMICube";
    m_size.set(100.0f, 100.0f, 100.0f);
    m_aabbBox.clear();
    m_aabbBox.expand(m_size*-0.5f);
    m_aabbBox.expand(m_size*0.5f);
    m_cube_mesh = IMIGeoGen::genAABB(mApp,m_aabbBox);
    m_drawBox = true;
}

IMICube::~IMICube() {
    m_cube_mesh = nullptr;
}

void IMICube::setSize(FVec3& _size) {
    if(m_size!=_size) {
        m_size = _size;
        m_aabbBox.clear();
        m_aabbBox.expand(m_size*-0.5f);
        m_aabbBox.expand(m_size*0.5f);
        //m_cube_mesh = IMIGeoGen::genAABB(mApp,m_aabbBox);
    }
}

void IMICube::update(f32 _dt) {
    IMINode::update(_dt);
    if(m_surface) {
        if( mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS ) {
            //metal需要转至一下矩阵
            FMat4 tt = transpose(m_localMat);
            m_surface->setParam("matModel",tt);
        }else{
            m_surface->setParam("matModel",m_localMat);
        }
    }
}

void IMICube::render() {
    if ( m_visible && m_cube_mesh && m_mtl){
        IMIDispatch::dispatchMeshDraw(mApp,
                                     m_cube_mesh,
                                     m_mtl ,
                                     m_surface,
                                     E_RSM_SOLID,
                                     "IMICube");
    }
    IMINode::render();
}
