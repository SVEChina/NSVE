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
        static SVRenderMeshPtr genTri(SVInstPtr _app,f32 _len,SVBoundBox& _aabb);
        
        //方形
        static SVRenderMeshPtr genRect(SVInstPtr _app,f32 _w,f32 _h,SVBoundBox& _aabb);
        
        //
        static SVRenderMeshPtr genRectARCHO(SVInstPtr _app,f32 _w,f32 _h,EUIARCHO _archo,SVBoundBox& _aabb);
        
        //菱形
        static SVRenderMeshPtr genLing(SVInstPtr _app,f32 _len,SVBoundBox& _aabb);
        
        //五边
        static SVRenderMeshPtr genFiveEdage(SVInstPtr _app,f32 _len,SVBoundBox& _aabb);
        
        //六边
        static SVRenderMeshPtr genSixEdage(SVInstPtr _app,f32 _len,SVBoundBox& _aabb);
        
        //圆形
        static SVRenderMeshPtr genCircle(SVInstPtr _app,f32 _len,SVBoundBox& _aabb);
        
        //AABB盒
        static SVRenderMeshPtr genAABB(SVInstPtr _app,SVBoundBox& _aabb);
        
        //创建矩形mesh
        static SVRenderMeshPtr createRectMesh(SVInstPtr _app,f32 _w ,f32 _h , s32 _wPointCount , s32 _hPointCont);
        
        //
        static SVRenderMeshPtr createNetGrid(SVInstPtr _app,s32 _size,s32 _axis);
        
    private:
        static SVRenderMeshPtr _getPolygonDiy(SVInstPtr _app,s32 _edagenum,f32 _startangle,f32 _len,SVBoundBox& _aabb);
    };


}//!namespace



#endif //SV_GEOMETRYBASE_H
