//
//  CGDef.h
//  IMISample
//
//  Created by 李晓帆 on 21/10/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#ifndef CGDef_h
#define CGDef_h
//渲染核心
#define IMI_GLES  1001
#define IMI_GL    1002
#define IMI_METAL 1003
#define IMI_VULKAN 1004
#define IMI_D3D   1005
#define IMI_WEBGL 1006

#define IMI_CORE IMI_GLES

//相机图片格式
enum CG_PIC_FORMATE {
    CG_PF_GRAY8 = 0,
    CG_PF_YV12,
    CG_PF_I420,
    CG_PF_NV12,
    CG_PF_NV21,
    CG_PF_BGRA,
    CG_PF_RGBA,
    CG_PF_RGB,
    CG_PF_NULL
};
#endif /* CGDef_h */
