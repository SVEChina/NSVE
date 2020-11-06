//
// IMIGeoGen.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GEOMETRYBASE_H
#define IMI_GEOMETRYBASE_H

//基本图元
#include "IMIVertDef.h"
#include "../base/IMIBounds.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../node/IMINodeDef.h"

namespace imi {
    
    class IMIGeoGen {
    public:
        //三角形
        static IMIRenderMeshPtr genTri(IMIInstPtr _app,f32 _len,IMIBoundBox& _aabb);
        
        //方形
        static IMIRenderMeshPtr genRect(IMIInstPtr _app,f32 _w,f32 _h,IMIBoundBox& _aabb);
        
        //
        static IMIRenderMeshPtr genRectARCHO(IMIInstPtr _app,f32 _w,f32 _h,EUIARCHO _archo,IMIBoundBox& _aabb);
        
        //菱形
        static IMIRenderMeshPtr genLing(IMIInstPtr _app,f32 _len,IMIBoundBox& _aabb);
        
        //五边
        static IMIRenderMeshPtr genFiveEdage(IMIInstPtr _app,f32 _len,IMIBoundBox& _aabb);
        
        //六边
        static IMIRenderMeshPtr genSixEdage(IMIInstPtr _app,f32 _len,IMIBoundBox& _aabb);
        
        //圆形
        static IMIRenderMeshPtr genCircle(IMIInstPtr _app,f32 _len,IMIBoundBox& _aabb);
        
        //AABB盒
        static IMIRenderMeshPtr genAABB(IMIInstPtr _app,IMIBoundBox& _aabb);
        
        //创建矩形mesh
        static IMIRenderMeshPtr createRectMesh(IMIInstPtr _app,f32 _w ,f32 _h , s32 _wPointCount , s32 _hPointCont);
        
        //
        static IMIRenderMeshPtr createNetGrid(IMIInstPtr _app,s32 _size,s32 _axis);
        
    private:
        static IMIRenderMeshPtr _getPolygonDiy(IMIInstPtr _app,s32 _edagenum,f32 _startangle,f32 _len,IMIBoundBox& _aabb);
    };


}//!namespace



#endif //IMI_GEOMETRYBASE_H
