//
// SVFaceMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FACEMESHDATA_H
#define SV_FACEMESHDATA_H

#include "../base/SVGBase.h"
#include "../base/SVMap.h"
#include "../rendercore/SVRenderDeclare.h"

namespace sv {
    
    class SVFaceMesh : public SVGBaseEx{
    public:
        SVFaceMesh(SVInstPtr _app);
        
        ~SVFaceMesh();
        
        static SVRenderMeshPtr createFaceMeshSt(SVInstPtr _app,bool _simp = true);
        
        static SVRenderMeshPtr createFaceMeshFp(SVInstPtr _app,bool _simp = true);
        
        static SVRenderMeshPtr createFaceMeshAS(SVInstPtr _app,bool _simp = true);
        
    protected:
        static SVRenderMeshPtr _loadFaceMesh(SVInstPtr _app,cptr8 _indexfile,cptr8 _datafile);
    };

//    struct StanderFace{
//        s32 facepoints_count;
//        s32 face_top = 0;
//        s32 face_left = 0;
//        s32 face_bottom = 0;
//        s32 face_right = 0;
//        f32 face_yaw = 0;
//        f32 face_roll = 0;
//        f32 face_pitch = 0;
//        s32 design_img_width;
//        s32 design_img_height;
//        f32 points[800];
//    };
};

#endif /* SV_FACEMESHDATA_H */
