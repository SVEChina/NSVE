//
// IMIResDsp.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RESDSP_H
#define IMI_RESDSP_H

#include "../base/IMIObject.h"
#include "../base/IMIDataSwap.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIParamTbl.h"
#include "../rendercore/IMIRenderDef.h"
#include "../core/IMIVertDef.h"

#include <vector>
#include <map>

namespace imi {

/*
 vert dsp
 */

//最大支持10个流
#define IMI_MAX_STREAM_NUM 10
//
//1.AOS模式  混合流
//2.SOA模式  拆分流
class IMIVertStreamDsp :public IMIObject {
public:
    IMIVertStreamDsp(BUFFERMODE _mode) {
        _bufMode = _mode;
        _bufType = E_BFT_STATIC_DRAW;
        _vertCnt = 0;
        _bufSize = 0;
        reset();
    };
    
    ~IMIVertStreamDsp() {
        _bufMode = E_BFM_AOS;
        _bufType = E_BFT_STATIC_DRAW;
        _vertCnt = 0;
        _bufSize = 0;
        reset();
    };
    
    //推送类型
    void push(VFTYPE _stype) {
        std::map<VFTYPE,IMIDataSwapPtr>::iterator it = m_streamData.find(_stype);
        if( it == m_streamData.end() ) {
            m_streamData.insert(std::make_pair(_stype,nullptr));
            m_streamDsp.push_back(_stype);
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
    
    //重置
    void reset() {
        m_mixStreamData = nullptr;
        m_streamDsp.clear();
        m_streamData.clear();
    }
    
    //
    s32 getVertSize(VFTYPE _vf) {
        s32 t_size = 0;
        if (_vf == E_VF_V2) {
            return 2 * sizeof(f32);
        } else if (_vf == E_VF_V3) {
            return 3 * sizeof(f32);
        } else if (_vf == E_VF_NOR) {
            return 3 * sizeof(f32);
        } else  if (_vf == E_VF_TAG) {
            return 3 * sizeof(f32);
        } else if (_vf == E_VF_BTAG) {
            return 3 * sizeof(f32);
        } else if (_vf == E_VF_C0) {
            return 4 * sizeof(u8);
        } else if (_vf == E_VF_T0) {
            return 2 * sizeof(f32);
        } else if (_vf == E_VF_T1) {
            return 2 * sizeof(f32);
        } else if (_vf == E_VF_BONE) {
            return 4 * sizeof(u16);
        } else if (_vf == E_VF_BONE_W) {
            return 4 * sizeof(f32);
        }
        return t_size;
    }
    
    s32 getVertSize() {
        s32 t_size = 0;
        for(s32 i=0;i<m_streamDsp.size();i++) {
            t_size += getVertSize( m_streamDsp[i] );
        }
        return t_size;
    }
    
    //设置流数据
    bool setSigleStreamData(VFTYPE _stype,IMIDataSwapPtr _data) {
        if(_bufMode == E_BFM_SOA) {
            //单一流模式，需要按流分开存储
            std::map<VFTYPE,IMIDataSwapPtr>::iterator it = m_streamData.find(_stype);
            if( it == m_streamData.end() ) {
                return false;
            }
            m_streamData[_stype] = _data;
            return true;
        }
        return false;
    }
    
    bool setSigleStreamData(VFTYPE _stype,void* _data,s32 _len) {
        if(_bufMode == E_BFM_SOA) {
            //单一流模式，需要按流分开存储
            std::map<VFTYPE,IMIDataSwapPtr>::iterator it = m_streamData.find(_stype);
            if( it == m_streamData.end() ) {
                return false;
            }
            if( !m_streamData[_stype] ) {
                m_streamData[_stype] = MakeSharedPtr<IMIDataSwap>();
            }
            m_streamData[_stype]->writeData(_data,_len);
            return true;
        }
        return false;
    }
    
    //设置流数据
    bool setMixStreamData(IMIDataSwapPtr _data) {
        if(_bufMode == E_BFM_AOS) {
            //混合流模式，设定给单一目标就好
            m_mixStreamData = _data;
            return true;
        }
        return false;
    }
    
    bool setMixStreamData(void* _data,s32 _len) {
        if(_bufMode == E_BFM_AOS) {
            m_mixStreamData = nullptr;
            m_mixStreamData = MakeSharedPtr<IMIDataSwap>();
            m_mixStreamData->writeData(_data,_len);
           return true;
        }
        return false;
    }
    
    BUFFERMODE _bufMode;    //E_BFM_AOS 混合流，E_BFM_SOA 单一流
    //数据类型
    BUFFERTYPE _bufType;    //BUFFER类型
    //顶点个数
    s32 _vertCnt;           //顶点数目
    //数据尺寸
    s32 _bufSize;           //buf 尺寸
    //流描述
    std::vector<VFTYPE> m_streamDsp;  //流描述
    //单一流数据
    std::map<VFTYPE,IMIDataSwapPtr> m_streamData;
    //混合流数据
    IMIDataSwapPtr m_mixStreamData;
};
    
class IMIIndexStreamDsp :public IMIObject {
public:
    IMIIndexStreamDsp() {
        _dataType = 16;
        _bufSize = 0;
        _bufData = nullptr;
    };
    
    ~IMIIndexStreamDsp() {
        _bufData = nullptr;
    };
    
    void setBufType(BUFFERTYPE _type) {
        _bufType = _type;
    }
    
    //设置索引个数
    void setIndexCnt(s32 _cnt) {
        _indexCnt = _cnt;
    }
    
    //设置流数据
    bool setDataType(s32 _size) {
        _dataType = _size;
        return true;
    }
    
    //设置流数据
    bool setStreamData(IMIDataSwapPtr _data) {
        _bufData = _data;
        return true;
    }
    
    bool setStreamData(void* _data,s32 _len) {
        if(_data) {
            _bufData = nullptr;
            _bufData = MakeSharedPtr<IMIDataSwap>();
            _bufData->writeData(_data,_len);
            _bufSize = _len;
            return true;
        }
        return false;
    }
    //索引个数
    s32 _indexCnt;
    //buf 尺寸
    s32 _bufSize;
    //数据类型
    s32 _dataType;
    //BUFFER类型
    BUFFERTYPE _bufType;
    //数据
    IMIDataSwapPtr _bufData;
};

class IMIInstStreamDsp :public IMIObject {
public:
    IMIInstStreamDsp() {
        _instCnt = 0;
        _bufSize = 0;
        _bufData = nullptr;
    };
    
    ~IMIInstStreamDsp() {
        _bufData = nullptr;
    };
    
    void setBufType(BUFFERTYPE _type) {
        _bufType = _type;
    }
    
    //设置索引个数
    void setInstCnt(s32 _cnt) {
        _instCnt = _cnt;
    }
    
    //设置流数据
    bool setStreamData(IMIDataSwapPtr _data) {
        _bufData = _data;
        return true;
    }
    
    bool setStreamData(void* _data,s32 _len) {
        if(_data) {
            _bufData = nullptr;
            _bufData = MakeSharedPtr<IMIDataSwap>();
            _bufData->writeData(_data,_len);
            _bufSize = _len;
            return true;
        }
        return false;
    }

    //实例个数
    s32 _instCnt;
    //buf 尺寸
    s32 _bufSize;
    //BUFFER类型
    BUFFERTYPE _bufType;
    //数据
    IMIDataSwapPtr _bufData;
};

struct IMIRMeshDsp {
    IMIRMeshDsp() {
        m_draw_method = 0;
        m_draw_num = 0;
        m_draw_buffer_type = 0;
    }
    s32 m_draw_method;
    s32 m_draw_num;
    s32 m_draw_buffer_type;
};

/*
 shader
 */

/*
 * 采样器描述
 */
struct SamplerDsp {
    SamplerDsp() {
        m_chn = -1;
        m_stage = -1; //0:vs 1:fs 2:gs
        m_name = "";
        m_warps = "";
        m_warpt = "";
        m_min = "";
        m_mag = "";
    };
    s32 m_chn;
    s32 m_stage; //0:vs 1:fs 2:gs
    IMIString m_name;
    IMIString m_warps;
    IMIString m_warpt;
    IMIString m_min;
    IMIString m_mag;
};

/*
 * 参数表描述
 */
struct ParamTblDsp {
    ParamTblDsp() {
        m_id = -1;
        m_stage = -1;
        m_tbl = nullptr;
    }
    s32 m_id;               //传递的bufid
    s32 m_stage;            //0:vs, 1:fs
    IMIParamTblPtr m_tbl;    //表
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
//    s32 getDefCode() {
//        if(m_defs.size() == 0) {
//            return 0;
//        }
//        
//        return 0;
//    };
    //
    s32 m_dsp;
    //顶点描述
    std::vector<s32> m_vft;
    IMIString m_programme_fname;
    IMIString m_vs_fname;
    IMIString m_fs_fname;
    IMIString m_gs_fname;
    IMIString m_cs_fname;
    IMIString m_tsd_fname;
    IMIString m_tse_fname;
    //宏定义
    std::vector<IMIString> m_defs;
    //使用的pass
    IMIString m_pass;
    //采样器
    std::vector<SamplerDsp> m_samplers;
    //参数表
    std::vector<ParamTblDsp> m_paramtbl;
};

/*texture*/

/*
 逻辑层面的纹理
 */

struct IMITextureDsp {
    IMITextureDsp() {
        m_image_type = IMI_IMAGE_2D;
        m_data_formate = IMI_FORMAT_RGBA8;    // 数据格式
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
    
    IMI_TEXTYPE m_image_type;
    IMI_TEXFORMATE m_data_formate;      //数据格式
    IMI_TEXWRAP m_warp_s;
    IMI_TEXWRAP m_warp_t;
    s32 m_width;            //宽
    s32 m_height;           //高
    s32 m_depth;            //深度    //3d纹理使用
    bool m_minmap;          //是否开启mipmap
    bool m_computeWrite;    //metal 是否可以
    bool m_renderTarget;    //metal 是否是renderTarget
    bool m_srgb;
    //数据
    IMIDataSwapPtr m_pData[6];
};

/*
 target
 */

//目标描述
struct IMITargetDsp {
    //
    IMITargetDsp() {
        m_width = 512;
        m_height = 512;
        m_target_num = 1;
        memset(m_color_texid,0,sizeof(s32)*IMI_SUPPORT_MAX_TAREGT);
        m_use_depth = true;
        m_use_stencil = true;
        m_color_r = 1.0f;
        m_color_g = 1.0f;
        m_color_b = 1.0f;
        m_color_a = 0.0f;
        m_depth_value = 1.0f;
        m_stencil_value = 0;
    }
    s32 m_width;
    s32 m_height;
    s32 m_target_num;
    IMI_TEXIN m_color_texid[IMI_SUPPORT_MAX_TAREGT];
    bool m_use_depth;
    bool m_use_stencil;
    f32 m_color_r;
    f32 m_color_g;
    f32 m_color_b;
    f32 m_color_a;
    f32 m_depth_value;
    s32 m_stencil_value;
};
    

}//!namespace imi


#endif //IMI_RESDSP_H
