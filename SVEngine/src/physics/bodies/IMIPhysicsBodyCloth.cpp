//
// IMIPhysicsBodyCloth.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsBodyCloth.h"
#include "../../base/IMIDataSwap.h"
#include "../../core/IMIVertDef.h"

using namespace imi;

IMIPhysicsBodyCloth::IMIPhysicsBodyCloth(IMIInstPtr _app, btSoftBodyWorldInfo& _worldInfo, const FVec3& _corner00,
                                       const FVec3& _corner10,
                                       const FVec3& _corner01,
                                       const FVec3& _corner11,
                                       s32 _resx,
                                       s32 _resy,
                                       s32 _fixeds,
                                       bool gendiags):IMIPhysicsBodySoft(_app) {
    m_type = E_PHYSICS_BODY_CLOTH;
    m_vertexCount = 0;
    m_pVertexData = MakeSharedPtr<IMIDataSwap>();
    m_softBody = btSoftBodyHelpers::CreatePatch(_worldInfo, btVector3(_corner00.x, _corner00.y, _corner00.z),
                                                     btVector3(_corner10.x, _corner10.y, _corner10.z),
                                                     btVector3(_corner01.x, _corner01.y, _corner01.z),
                                                     btVector3(_corner11.x, _corner11.y, _corner11.z),
                                                     _resx, _resy,
                                                     _fixeds, gendiags);
    
//    m_softBody->getCollisionShape()->setMargin(0.5);
    m_softBody->m_materials[0]->m_kLST = 0.005;
//    m_softBody->m_materials[0]->m_kAST = 0.001;
    m_softBody->generateBendingConstraints(2, m_softBody->m_materials[0]);
    m_softBody->setTotalMass(150);
}

IMIPhysicsBodyCloth::IMIPhysicsBodyCloth(IMIInstPtr _app, btSoftBodyWorldInfo& _worldInfo, const f32 *_vertices, const s32 *_indices, s32 _ntrangles,
                   bool randomizeConstraints ):IMIPhysicsBodySoft(_app){
    m_type = E_PHYSICS_BODY_CLOTH;
    m_vertexCount = 0;
    m_pVertexData = MakeSharedPtr<IMIDataSwap>();
    m_softBody = btSoftBodyHelpers::CreateFromTriMesh(_worldInfo, _vertices,
                                                           _indices,
                                                           _ntrangles);
    btSoftBody::Material* pm = m_softBody->appendMaterial();
    pm->m_kLST = 0.005;
//    pm->m_flags -= btSoftBody::fMaterial::DebugDraw;
    m_softBody->generateBendingConstraints(2, pm);
    m_softBody->m_cfg.piterations = 2;
    m_softBody->m_cfg.kDF = 0.5;
    m_softBody->randomizeConstraints();
    m_softBody->scale(btVector3(6, 6, 6));
        m_softBody->setTotalMass(150);
//    m_softBody->setMass(0, 0);
}

IMIPhysicsBodyCloth::~IMIPhysicsBodyCloth() {
    m_pVertexData = nullptr;
}

void IMIPhysicsBodyCloth::init(){
    
}

void IMIPhysicsBodyCloth::destroy(){
    if (m_softBody) {
        delete m_softBody;
    }
}

void IMIPhysicsBodyCloth::update(f32 _dt){
    _updateFaceVertexData();
}

void IMIPhysicsBodyCloth::_updateFaceVertexData(){
    /* Faces    */
    if (m_softBody && m_pVertexData) {
        s32 t_facesSize = m_softBody->m_faces.size();
        s32 t_vertexSize = t_facesSize*3;
        V3 vertexData[t_vertexSize];
        for (s32 i = 0; i < t_facesSize; i++) {
            const btSoftBody::Face& f = m_softBody->m_faces[i];
            vertexData[i*3 + 0].x = f.m_n[0]->m_x[0];
            vertexData[i*3 + 0].y = f.m_n[0]->m_x[1];
            vertexData[i*3 + 0].z = f.m_n[0]->m_x[2];
            //
            vertexData[i*3 + 1].x = f.m_n[1]->m_x[0];
            vertexData[i*3 + 1].y = f.m_n[1]->m_x[1];
            vertexData[i*3 + 1].z = f.m_n[1]->m_x[2];
            //
            vertexData[i*3 + 2].x = f.m_n[2]->m_x[0];
            vertexData[i*3 + 2].y = f.m_n[2]->m_x[1];
            vertexData[i*3 + 2].z = f.m_n[2]->m_x[2];
        }
        m_pVertexData->writeData(&vertexData[0], sizeof(V3)*t_vertexSize);
        m_vertexCount = t_vertexSize;
    }
}

void *IMIPhysicsBodyCloth::getFaceVertexData(){
    return m_pVertexData->getData();
}

u32   IMIPhysicsBodyCloth::getFaceVertexDataSize(){
    return m_pVertexData->getSize();
}

u32   IMIPhysicsBodyCloth::getFaceVertexCount(){
    return m_vertexCount;
}
