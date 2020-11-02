//
// SVCube.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCube.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderMgr.h"
#include "../core/SVGeoGen.h"
#include "../mtl/SVSurface.h"

using namespace sv;

SVCube::SVCube(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SVCube";
    m_size.set(100.0f, 100.0f, 100.0f);
    m_aabbBox.clear();
    m_aabbBox.expand(m_size*-0.5f);
    m_aabbBox.expand(m_size*0.5f);
    m_cube_mesh = SVGeoGen::genAABB(mApp,m_aabbBox);
    m_drawBox = true;
}

SVCube::~SVCube() {
    m_cube_mesh = nullptr;
}

void SVCube::setSize(FVec3& _size) {
    if(m_size!=_size) {
        m_size = _size;
        m_aabbBox.clear();
        m_aabbBox.expand(m_size*-0.5f);
        m_aabbBox.expand(m_size*0.5f);
        //m_cube_mesh = SVGeoGen::genAABB(mApp,m_aabbBox);
    }
}

void SVCube::update(f32 _dt) {
    SVNode::update(_dt);
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

void SVCube::render() {
    if ( m_visible && m_cube_mesh && m_mtl){
        SVDispatch::dispatchMeshDraw(mApp,
                                     m_cube_mesh,
                                     m_mtl ,
                                     m_surface,
                                     E_RSM_SOLID,
                                     "SVCube");
    }
    SVNode::render();
}
