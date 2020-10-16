//
// SVResDsp.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RESDSP_H
#define SV_RESDSP_H

#include "../base/SVObject.h"
#include "../base/SVDataSwap.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVParamTbl.h"
#include "../rendercore/SVRenderDef.h"
#include "../core/SVVertDef.h"

#include <vector>
#include <map>

namespace sv {

/*
 vert dsp
 */

//最大支持10个流
#define SV_MAX_STREAM_NUM 10
//
//1.AOS模式  混合流
//2.SOA模式  拆分流
class SVVertStreamDsp :public SVObject {
public:
    SVVertStreamDsp(BUFFERMODE _mode) {
        _bufMode = _mode;           //E_BFM_AOS;
        _bufType = E_BFT_STATIC_DRAW;
        _vertCnt = 0;
        _indexCnt = 0;
        _bufSize = 0;
        reset();
    };
    
    ~SVVertStreamDsp() {
        _bufMode = E_BFM_AOS;
        _bufType = E_BFT_STATIC_DRAW;
        _vertCnt = 0;
        _indexCnt = 0;
        _bufSize = 0;
        reset();
    };
    
    //推送类型
    void push(VFTYPE _stype) {
        std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
        if( it == m_streamData.end() ) {
            m_streamDsp.push_back(_stype);
            m_streamData.insert(std::make_pair(_stype,nullptr));
        }
    }
    
    //设置BUF-TYPE
    void setBufType(BUFFERTYPE _btype) {
        _bufType = _btype;
    }
    
    //设置顶点数
    void setVertCnt(s32 _cnt) {
        _vertCnt = _cnt;
    }
    
    //设置索引个数
    void setIndexCnt(s32 _cnt) {
        _indexCnt = _cnt;
    }
    
    void buildWithVert(BUFFERTYPE _btype,s32 _cnt) {
        setBufType(_btype);
        setVertCnt(_cnt);
    }
    
    void buildWithIndex(BUFFERTYPE _btype,s32 _cnt) {
        setBufType(_btype);
        setIndexCnt(_cnt);
    }
    
    //重置
    void reset() {
        _bufData = nullptr;
        m_streamDsp.clear();
        m_streamData.clear();
    }
    
    //数据顶点描述
    VFTYPE getVertType() {
        s32 t_vt = 0;
        for(s32 i=0;i<m_streamDsp.size();i++) {
            t_vt = t_vt | s32(m_streamDsp[i]);
        }
        return VFTYPE(t_vt);
    }
    
    static s32 getVertSize(VFTYPE _vf) {
        s32 t_size = 0;
        if (_vf & E_VF_INDEX) {
            t_size += sizeof(u16);
        }
        if (_vf & E_VF_V2) {
            t_size += 2 * sizeof(f32);
        }
        if (_vf & E_VF_V3) {
            t_size += 3 * sizeof(f32);
        }
        if (_vf & E_VF_NOR) {
            t_size += 3 * sizeof(f32);
        }
        if (_vf & E_VF_TAG) {
            t_size += 4 * sizeof(f32);
        }
        if (_vf & E_VF_BTAG) {
            t_size += 4 * sizeof(f32);
        }
        if (_vf & E_VF_C0) {
            t_size += 4 * sizeof(u8);
        }
        if (_vf & E_VF_T0) {
            t_size += 2 * sizeof(f32);
        }
        if (_vf & E_VF_T1) {
            t_size += 2 * sizeof(f32);
        }
        if (_vf & E_VF_BONE) {
            t_size += 4 * sizeof(u16);
        }
        if (_vf & E_VF_BONE_W) {
            t_size += 4 * sizeof(f32);
        }
        return t_size;
    }
    
    //设置流数据
    bool setStreamData(VFTYPE _stype,SVDataSwapPtr _data) {
        if(_bufMode == E_BFM_AOS) {
            //混合流模式，设定给单一目标就好
            _bufData = _data;
            return true;
        } else {
            //单一流模式，需要按流分开存储
            std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
            if( it == m_streamData.end() ) {
                return false;
            }
            m_streamData[_stype] = _data;
            return true;
        }
    }
    
    bool setStreamData(VFTYPE _stype,void* _data,s32 _len) {
           if(_bufMode == E_BFM_AOS) {
               //混合流模式，设定给单一目标就好
               if(!_bufData) {
                   _bufData = MakeSharedPtr<SVDataSwap>();
               }
               _bufData->appendData(_data,_len);
               return true;
           } else {
               //单一流模式，需要按流分开存储
               std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
               if( it == m_streamData.end() ) {
                   return false;
               }
               if( !m_streamData[_stype] ) {
                   m_streamData[_stype] = MakeSharedPtr<SVDataSwap>();
               }
               m_streamData[_stype]->appendData(_data,_len);
               return true;
           }
       }
    
    //
    BUFFERMODE _bufMode;    //E_BFM_AOS 混合流，E_BFM_SOA 单一流
    //数据类型
    BUFFERTYPE _bufType;    //BUFFER类型
    //顶点个数
    s32 _vertCnt;           //顶点数目
    //索引个数
    s32 _indexCnt;          //索引数目
    //数据尺寸
    s32 _bufSize;           //buf 尺寸
    //流描述
    std::vector<VFTYPE> m_streamDsp;  //流描述
    //流数据
    std::map<VFTYPE,SVDataSwapPtr> m_streamData;
    //数据
    SVDataSwapPtr _bufData;
};
    
class SVIndexStreamDsp :public SVObject {
public:
    SVIndexStreamDsp() {
        _indexCnt = 0;
        _bufData = nullptr;
    };
    
    ~SVIndexStreamDsp() {
        _bufData = nullptr;
    };
    
    //设置索引个数
    void setIndexCnt(s32 _cnt) {
        _indexCnt = _cnt;
    }
    
    //设置流数据
    bool setStreamData(SVDataSwapPtr _data) {
        _bufData = _data;
        return true;
    }
    
protected:
    //索引个数
    s32 _indexCnt;          //索引数目
    //数据
    SVDataSwapPtr _bufData;
    //数据类型
    BUFFERTYPE _bufType;    //BUFFER类型
};

class SVInstStreamDsp :public SVObject {
public:
    SVInstStreamDsp() {
        _instCnt = 0;
        _bufData = nullptr;
    };
    
    ~SVInstStreamDsp() {
        _bufData = nullptr;
    };
    
    //设置索引个数
    void setInstCnt(s32 _cnt) {
        _instCnt = _cnt;
    }
    
    //设置流数据
    bool setStreamData(SVDataSwapPtr _data) {
        _bufData = _data;
        return true;
    }
    
protected:
    //实例个数
    s32 _instCnt;
    //数据
    SVDataSwapPtr _bufData;
    //数据类型
    BUFFERTYPE _bufType;    //BUFFER类型
};

struct SVRMeshDsp {
    SVRMeshDsp() {
        m_draw_method = 0;
        m_draw_num = 0;
    }
    s32 m_draw_method;
    s32 m_draw_num;
};

/*
 shader
 */

/*
 * 采样器描述
 */
struct SamplerDsp {
    s32 m_chn;
    s32 m_stage; //0:vs 1:fs 2:gs
    SVString m_warps;
    SVString m_warpt;
    SVString m_min;
    SVString m_mag;
};

/*
 * 参数表描述
 */
struct ParamTblDsp {
    s32 m_id;               //传递的bufid
    s32 m_stage;            //0:vs, 1:fs
    SVParamTblPtr m_tbl;    //表
};

/*
 * shader描述
*/
struct ShaderDsp {
    ShaderDsp() {
        m_dsp = 0;
        m_programme_fname = "null";
        m_vs_fname = "null";
        m_fs_fname = "null";
        m_gs_fname = "null";
        m_cs_fname = "null";
        m_tse_fname = "null";
        m_tsd_fname = "null";
        m_pass = "null";
        m_vft.clear();
    };
    //
    s32 m_dsp;
    //顶点描述
    std::vector<s32> m_vft;
    SVString m_programme_fname;
    SVString m_vs_fname;
    SVString m_fs_fname;
    SVString m_gs_fname;
    SVString m_cs_fname;
    SVString m_tsd_fname;
    SVString m_tse_fname;
    //使用的pass
    SVString m_pass;
    
    //采样器
    std::vector<SamplerDsp> m_samplers;
    
    //参数表
    std::vector<ParamTblDsp> m_paramtbl;
};

/*texture*/

/*
 逻辑层面的纹理
 */

struct SVTextureDsp {
    SVTextureDsp() {
        m_image_type = SV_IMAGE_2D;
        m_data_formate = SV_FORMAT_RGBA8;    // 数据格式
        m_warp_s = E_TEX_CLAMP;             // S方向环绕
        m_warp_t = E_TEX_CLAMP;             // T方向环绕
        m_width = 1;                        // 宽
        m_height = 1;                       // 高
        m_depth = 1;                        // 深度    //3d纹理使用
        m_minmap = true;                    // 是否开启mipmap
        m_computeWrite = false;             // metal
        m_renderTarget = false;             // 是否renderTarget
        m_srgb = false;                     // metal
        //
        for(s32 i=0;i<6;i++) {
            m_pData[i] = nullptr;
        }
    };
    
    SV_TEXTYPE m_image_type;
    SV_TEXFORMATE m_data_formate;      //数据格式
    SV_TEXWRAP m_warp_s;
    SV_TEXWRAP m_warp_t;
    s32 m_width;            //宽
    s32 m_height;           //高
    s32 m_depth;            //深度    //3d纹理使用
    bool m_minmap;          //是否开启mipmap
    bool m_computeWrite;    //metal 是否可以
    bool m_renderTarget;    //metal 是否是renderTarget
    bool m_srgb;
    //数据
    SVDataSwapPtr m_pData[6];
};

/*
 target
 */

//目标描述
struct SVTargetDsp {
    //
    SVTargetDsp() {
        m_width = 512;
        m_height = 512;
        m_target_num = 1;
        memset(m_color_texid,0,sizeof(s32)*SV_SUPPORT_MAX_TAREGT);
        m_use_depth = true;
        m_use_stencil = true;
        m_color_r = 0.0f;
        m_color_g = 0.0f;
        m_color_b = 0.0f;
        m_color_a = 1.0f;
        m_depth_value = 1.0f;
        m_stencil_value = 0;
    }
    s32 m_width;
    s32 m_height;
    s32 m_target_num;
    s32 m_color_texid[SV_SUPPORT_MAX_TAREGT];
    bool m_use_depth;
    bool m_use_stencil;
    f32 m_color_r;
    f32 m_color_g;
    f32 m_color_b;
    f32 m_color_a;
    f32 m_depth_value;
    s32 m_stencil_value;
};
    

}//!namespace sv


#endif //SV_RESDSP_H
