//
//  CGDetectMgr.m
//  SYEngine-Demo
//
//  Created by 李晓帆 on 29/9/2020.
//  Copyright © 2020 徐子昱. All rights reserved.
//

#import "CGDetectMgr.h"
#import "CGDetectSenstime.h"
#include <sys/time.h>
@interface CGDetectMgr(){
    CGDetectSenstime  *m_pDetectST;
    unsigned char     *m_faceData;
    unsigned char     *m_faceDataExt;
    int               m_curType;
    //时间标志
    timeval timTagLast;
}
@end
static CGDetectMgr *mInst;
@implementation CGDetectMgr

+(instancetype) getInst{
    if(mInst == nil){
        mInst = [CGDetectMgr new];
    }
    return mInst;
}

- (instancetype)init{
    self = [super init];
    if (self) {
        m_curType = 2;
        int size = (1+4*(3+4+212))*sizeof(int);
        m_faceData = (unsigned char *)malloc(size);
        size = (4*(134))*sizeof(float);
        m_faceDataExt = (unsigned char *)malloc(size);
//        [self createFP];
//        [self createBD];
        [self createST];
    }
    return self;
}
//
- (void)dealloc{
    if (m_faceData) {
        free(m_faceData);
        m_faceData = NULL;
    }
    if (m_faceDataExt) {
        free(m_faceDataExt);
        m_faceDataExt = NULL;
    }
//    [self destroyFP];
//    [self destroyBD];
    [self destroyST];
}

- (void)initMgr{
    
}

//
//- (void)createFP{
//    m_pDetectFP = new SYDetectFacePP();
//    NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"megviifacepp_0_5_2_model" ofType:@""];
//    NSData* read = [NSData dataWithContentsOfFile:bundlePath];
//    m_pDetectFP->createDetect((void*)[read bytes], read.length, 4);
//}
//
//- (void)destroyFP{
//    if (m_pDetectFP) {
//        delete m_pDetectFP;
//        m_pDetectFP = NULL;
//    }
//}
//
//- (void)createBD{
//    m_pDetectBD = new SYDetectByteDance();
//    NSString *bundle_model_Path = [[NSBundle mainBundle] pathForResource:@"bytedance" ofType:@"bundle"];
//    NSString *model_Path = [NSString stringWithFormat:@"%@/ttfacemodel/tt_face_v8.2.model",bundle_model_Path];
//    NSString *model_extra_Path = [NSString stringWithFormat:@"%@/ttfacemodel/tt_face_extra_v11.0.model",bundle_model_Path];
//    NSString *byte_license_Path = [NSString stringWithFormat:@"%@/xinyang_test_20200922_20201021_com.soyoung.qingyang.medical_v3.9.2.2.licbag",bundle_model_Path];
//    NSString *model_attribute_Path = [NSString stringWithFormat:@"%@/tt_face_attribute_v6.1.model",bundle_model_Path];
//    m_pDetectBD->createDetect(model_Path.UTF8String, model_extra_Path.UTF8String,byte_license_Path.UTF8String, 0);
//   // m_pDetectBD->createAttribete(model_attribute_Path.UTF8String, byte_license_Path.UTF8String);
//}
//
//- (void)destroyBD{
//    if (m_pDetectBD) {
//        delete m_pDetectBD;
//        m_pDetectBD = NULL;
//    }
//}
//
- (void)createST{
    m_pDetectST = new CGDetectSenstime();
    NSString *bundle_st_model_Path = [[NSBundle mainBundle] pathForResource:@"senstime" ofType:@"bundle"];
    NSString *st_model_Path = [NSString stringWithFormat:@"%@/M_SenseME_Face_Video_7.0.3.model",bundle_st_model_Path];
    NSString *st_model_extra_Path = [NSString stringWithFormat:@"%@/M_SenseME_Face_Extra_Advanced_6.0.8.model",bundle_st_model_Path];
    NSString *st_model_Attribute= [NSString stringWithFormat:@"%@/M_SenseME_Attribute_1.0.1.model",bundle_st_model_Path];
    NSString *st_license_Path = [NSString stringWithFormat:@"%@/SENSEME.lic",bundle_st_model_Path];
    char active_code[1024];
    int active_code_len = 1024;
    m_pDetectST->createDetect([st_model_Path UTF8String], [st_model_extra_Path UTF8String], [st_license_Path UTF8String], active_code, active_code_len);
//    m_pDetectST->createAtrribute([st_model_Attribute UTF8String]);
}

- (void)destroyST{
    if (m_pDetectST) {
        delete m_pDetectST;
        m_pDetectST = NULL;
    }
}
//
//- (void)setDetectType:(int)_type{
//    m_curType = _type;
//}
//
- (unsigned char *)detectWithFormate:(enum CG_PIC_FORMATE)_formate buffer:(unsigned char *)_buffer width:(int)_width height:(int)_height{
    [self timeTag:true];
    if (m_curType == 2) {
        if (_formate == CG_PF_BGRA) {
            int pointsize;
            m_pDetectST->detect(_buffer, _width, _height,4*_width, 3, m_faceData,pointsize, 0,m_faceDataExt);
        }
    }
    [self timeTag:false];
    return m_faceData;
}
//
- (void)timeTag:(bool)_clear{
    if(_clear){
        gettimeofday(&timTagLast, nullptr);
    }else{
        timeval timTagCur;
        gettimeofday(&timTagCur, nullptr);
        int dt = int((timTagCur.tv_sec - timTagLast.tv_sec) * 1000.0f + (timTagCur.tv_usec - timTagLast.tv_usec) * 0.001f);
        timTagLast = timTagCur;
        NSLog(@"detect timeTag %d\n",dt);
    }
}

@end
