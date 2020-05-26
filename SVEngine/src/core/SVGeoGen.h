//
// SVGeoGen.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_GEOMETRYBASE_H
#define SV_GEOMETRYBASE_H

//基本图元
#include "SVVertDef.h"
#include "../base/SVBounds.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../node/SVNodeDef.h"

namespace sv {
    
    class SVGeoGen {
    public:
        //三角形
        static render::SVRenderMeshPtr genTri(SVInst* _app,f32 _len,util::SVBoundBox& _aabb);
        
        //方形
        static render::SVRenderMeshPtr genRect(SVInst* _app,f32 _w,f32 _h,f32 _inx,f32 _iny,f32 _inw,f32 _inh,util::SVBoundBox& _aabb);
        
        //
        static render::SVRenderMeshPtr genRectARCHO(SVInst* _app,f32 _w,f32 _h,EUIARCHO _archo,util::SVBoundBox& _aabb);
        
        //菱形
        static render::SVRenderMeshPtr genLing(SVInst* _app,f32 _len,util::SVBoundBox& _aabb);
        
        //五边
        static render::SVRenderMeshPtr genFiveEdage(SVInst* _app,f32 _len,util::SVBoundBox& _aabb);
        
        //六边
        static render::SVRenderMeshPtr genSixEdage(SVInst* _app,f32 _len,util::SVBoundBox& _aabb);
        
        //圆形
        static render::SVRenderMeshPtr genCircle(SVInst* _app,f32 _len,util::SVBoundBox& _aabb);
        
        //AABB盒
        static render::SVRenderMeshPtr genAABB(SVInst* _app,util::SVBoundBox& _aabb);
        
        //创建矩形mesh
        static render::SVRenderMeshPtr createRectMesh(SVInst* _app,f32 _w ,f32 _h , s32 _wPointCount , s32 _hPointCont);
        
        //
        static render::SVRenderMeshPtr createNetGrid(SVInst* _app,s32 _size,s32 _axis);
        
    private:
        static render::SVRenderMeshPtr _getPolygonDiy(SVInst* _app,s32 _edagenum,f32 _startangle,f32 _len,util::SVBoundBox& _aabb);
    };
    
}



#endif //SV_GEOMETRYBASE_H
