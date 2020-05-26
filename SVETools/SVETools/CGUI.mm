//
//  CGUI.m
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGUI.h"
//#import "ui/WinCtrl.h"
//#import "ui/gift/WinCtrlGift.h"
//#import "ui/beauty/WinCtrlBeauty.h"
//#import "ui/filter/WinCtrlFilter.h"
//#import "ui/game/WinCtrlGame.h"
//#import "ui/common/CGUIFrameMain.h"
//#import "ui/common/CGUIFrameGL.h"
//#import "ui/MainWindow.h"
//#import "ui/MainGLView.h"
//#import "ui/CGMenuMain.h"
//#import "WinDelegate.h"
//#import "ui/CGUIFrameAni.h"
//#import "ui/gift/CGUIFrameTop.h"
//#import "ui/gift/CGUIFrameRight.h"
//#import "ui/CGUIPropSpine.h"
//#import "ui/CGUIPropSprite.h"
//#import "ui/CGUIPropParticle.h"
//#include "uiframe/SVFrameBase.h"
//#import "CGInst.h"
//#import "file/CGEditModelData.h"
//#import "data/CGDataMgr.h"

static CGUI *mInst;

@interface CGUI() {
//    MainWindow* m_pMainwin;
//    sv::frame::SVFrameBase* m_pFrameRoot;
}
@end

@implementation CGUI

+ (instancetype) getInst {
    if(mInst == nil){
        mInst = [CGUI new];
    }
    return mInst;
}

- (instancetype)init{
    self = [super init];
    if (self) {
    }
    return self;
}

-(void)dealloc {
}

-(void)cgInit:(int)_mode {
//    //
//    //[self createGLWin];
//    //
//    [self createMetalWin];
//    //创建窗口
//    [self createWin:_mode];
//    //创建菜单
//    [self createMenu:_mode];
}

-(void)cgDestroy {
//    //
//    m_pMainwin = nil;
//    //
//    if(m_pFrameRoot){
//        m_pFrameRoot = nullptr;
//    }
}
//
//-(void*)getFrameRoot {
//    return m_pFrameRoot;
//}
//
////设置模式
//-(void)setEditMode:(int)_mode {
//    //主窗口
//    [self createWin:_mode];
//    //主菜单
//    [self.m_pMainMenu changeMode:_mode];
//    //刷新主窗口
//    if(m_pMainwin) {
//        [m_pMainwin refreshWinSize];
//    }
//}
//
//-(void)createGLWin {
//    //创建GL窗口
//    NSRect t_rc;
//    t_rc.origin.x = 0;
//    t_rc.origin.y = 0;
//    t_rc.size.width = 800;
//    t_rc.size.height = 400;
//    self.frameGL = [[CGUIFrameGL alloc] initWithFrame: t_rc];
//    //创建win窗口
//    self.m_pWinCtrl = [[WinCtrl alloc] initWithWindowNibName:@"MainWindowCtrl"];
//    m_pMainwin = (MainWindow*)[self.m_pWinCtrl window];
//    [m_pMainwin winInit];
//    [m_pMainwin setTitle: @"光子工作室——测试"];
//    [m_pMainwin setAcceptsMouseMovedEvents: YES];
//    [m_pMainwin setDelegate: [[WinDelegate alloc] init]];
//    [m_pMainwin setReleasedWhenClosed: NO];
//    [m_pMainwin makeKeyAndOrderFront:self]; // shows and focuses the window
//    [m_pMainwin center];
//    //
//    [self.m_pWinCtrl showWindow:nil];
//    m_pFrameRoot = (sv::frame::SVFrameBase*)[self.m_pWinCtrl.frameMain getFrameNode];
//    m_pFrameRoot->setDock(sv::frame::E_DOCK_M_FILL);
//}
//
//-(void)createMetalWin {
//    //创建GL窗口
//    NSRect t_rc;
//    t_rc.origin.x = 0;
//    t_rc.origin.y = 0;
//    t_rc.size.width = 800;
//    t_rc.size.height = 400;
//    self.frameGL = [[CGUIFrameGL alloc] initWithFrame: t_rc];
//    //创建win窗口
//    self.m_pWinCtrl = [[WinCtrl alloc] initWithWindowNibName:@"MainWindowCtrl"];
//    m_pMainwin = (MainWindow*)[self.m_pWinCtrl window];
//    [m_pMainwin winInit];
//    [m_pMainwin setTitle: @"光子工作室——测试"];
//    [m_pMainwin setAcceptsMouseMovedEvents: YES];
//    [m_pMainwin setDelegate: [[WinDelegate alloc] init]];
//    [m_pMainwin setReleasedWhenClosed: NO];
//    [m_pMainwin makeKeyAndOrderFront:self]; // shows and focuses the window
//    [m_pMainwin center];
//    //
//    [self.m_pWinCtrl showWindow:nil];
//    m_pFrameRoot = (sv::frame::SVFrameBase*)[self.m_pWinCtrl.frameMain getFrameNode];
//    m_pFrameRoot->setDock(sv::frame::E_DOCK_M_FILL);
//}
//
//-(void)createMenu:(int)_mode {
//    self.m_pMainMenu = [[CGMenuMain alloc] initWithTitle:@"sveGift"];
//    [self.m_pMainMenu changeMode:_mode];
//    [NSApp setMainMenu:self.m_pMainMenu];
//}
//
////窗口模式
//-(void)createWin:(int)_mode {
//    //清理所有子view
//    for(int i=0;i<[self.m_pWinCtrl.frameMain.subviews count];i++) {
//        [self.m_pWinCtrl.frameMain.subviews[i] removeFromSuperview];
//    }
//    //清理框架数据
//    if(m_pFrameRoot) {
//        m_pFrameRoot->clearFrame();
//    }
//    //
//    [self.frameGL removeFromSuperview];
//    //t_mainwin.contentView
//    //根据模式架子不同的资源
//    if(_mode == E_EDIT_M_BASE) {
//        //
//
//        //
//    }else if(_mode == E_EDIT_M_GIFT) {
//        self.m_pWinCtrlGift = [[WinCtrlGift alloc] init];
//        NSArray* t_array_object;
//        BOOL loatRet = [[NSBundle mainBundle] loadNibNamed:@"WinCtrlGift" owner:self.m_pWinCtrlGift topLevelObjects:&t_array_object];
//        if (loatRet) {
//            //挂ui
//            [self.m_pWinCtrl.frameMain addSubview:self.m_pWinCtrlGift.frameMain];
//            [self.m_pWinCtrlGift assign:m_pFrameRoot];
//        }
//        //
//    }else if(_mode == E_EDIT_M_BEAUTY) {
//        self.m_pWinCtrlBeauty = [[WinCtrlBeauty alloc] init];
//        NSArray* t_array_object;
//        BOOL loatRet = [[NSBundle mainBundle] loadNibNamed:@"WinCtrlBeauty" owner:self.m_pWinCtrlBeauty topLevelObjects:&t_array_object];
//        if (loatRet) {
//            [self.m_pWinCtrl.frameMain addSubview:self.m_pWinCtrlBeauty.frameMain];
//            [self.m_pWinCtrlBeauty assign:m_pFrameRoot];
//        }
//        //
//    }else if(_mode == E_EDIT_M_FILTER) {
//        self.self.m_pWinCtrlFilter = [[WinCtrlFilter alloc] init];
//        NSArray* t_array_object;
//        BOOL loatRet = [[NSBundle mainBundle] loadNibNamed:@"WinCtrlFilter" owner:self.m_pWinCtrlFilter topLevelObjects:&t_array_object];
//        if (loatRet) {
//            //挂ui
//            [self.m_pWinCtrl.frameMain addSubview:self.m_pWinCtrlFilter.frameMain];
//            [self.m_pWinCtrlFilter assign:m_pFrameRoot];
//        }
//    }else if(_mode == E_EDIT_M_GAME) {
//        self.self.m_pWinCtrlGame = [[WinCtrlGame alloc] init];
//        NSArray* t_array_object;
//        BOOL loatRet = [[NSBundle mainBundle] loadNibNamed:@"WinCtrlGame" owner:self.m_pWinCtrlGame topLevelObjects:&t_array_object];
//        if (loatRet) {
//            //挂ui
//            [self.m_pWinCtrl.frameMain addSubview:self.m_pWinCtrlGame.frameMain];
//            [self.m_pWinCtrlGame assign:m_pFrameRoot];
//        }
//    }
//}
//
////刷新UI尺寸
//-(void)refreshUI:(NSRect)_rc {
//    if( m_pFrameRoot ) {
//        //刷新所有UI
//        sv::frame::SVRC frame_rc;
//        frame_rc.m_x = _rc.origin.x;
//        frame_rc.m_y = _rc.origin.y;
//        frame_rc.m_width = _rc.size.width;
//        frame_rc.m_height = _rc.size.height;
//        m_pFrameRoot->refreshUI(frame_rc);
//        //更新所有控件尺寸
//        [self.m_pWinCtrl refreshUISize];
//        //
//        int t_editmode = [[CGInst getInst] getEditMode];
//        if( t_editmode == E_EDIT_M_GIFT) {
//            if(self.m_pWinCtrlGift) {
//                [self.m_pWinCtrlGift refreshUISize];
//            }
//        }else if( t_editmode == E_EDIT_M_BEAUTY) {
//            if(self.m_pWinCtrlBeauty) {
//                [self.m_pWinCtrlBeauty refreshUISize];
//            }
//
//        }else if( t_editmode == E_EDIT_M_FILTER) {
//            if(self.m_pWinCtrlFilter) {
//                [self.m_pWinCtrlFilter refreshUISize];
//            }
//        }else if( t_editmode == E_EDIT_M_GAME) {
//            if(self.m_pWinCtrlGame) {
//                [self.m_pWinCtrlGame refreshUISize];
//            }
//        }
//    }
//}
//
//-(void)setPropVis:(bool)_vis {
//    //礼物模式下才有的prop
//    int t_editmode = [[CGInst getInst] getEditMode];
//    if( t_editmode == E_EDIT_M_GIFT) {
//        sv::frame::SVFrameBase* t_fnode = (sv::frame::SVFrameBase*)[self.m_pWinCtrlGift.frameRight getFrameNode];
//        if(t_fnode) {
//            t_fnode->setVisible(_vis);
//        }
//        if(m_pMainwin){
//            [m_pMainwin refreshWinSize];
//        }
//        //设置数据
//        CGEditDataNodeUISetPtr t_uiset = [[CGInst getInst].m_pDataMgr getUISet];
//        if(t_uiset) {
//            t_uiset->m_vis_prop = _vis;
//        }
//    }
//}
//
//-(void)setAniVis:(bool)_vis {
////    sv::frame::SVFrameBase* t_fnode = (sv::frame::SVFrameBase*)[self.m_pWinCtrlGift.frameAni getFrameNode];
////    if(t_fnode) {
////        t_fnode->setVisible(_vis);
////    }
////    if(m_pMainwin){
////        [m_pMainwin refreshWinSize];
////    }
//}
//
//-(void)setToolbarVis:(bool)_vis {
//    //礼物模式下才有的toolbar
//    int t_editmode = [[CGInst getInst] getEditMode];
//    if( t_editmode == E_EDIT_M_GIFT) {
//        sv::frame::SVFrameBase* t_fnode = (sv::frame::SVFrameBase*)[self.m_pWinCtrlGift.frameTop getFrameNode];
//        if(t_fnode) {
//            t_fnode->setVisible(_vis);
//        }
//        if(m_pMainwin){
//            [m_pMainwin refreshWinSize];
//        }
//        //设置数据
//        CGEditDataNodeUISetPtr t_uiset = [[CGInst getInst].m_pDataMgr getUISet];
//        if(t_uiset) {
//            t_uiset->m_vis_toolbar = _vis;
//        }
//    }
//}
//
////定时器刷新
//-(void)updateTimer {
//    //不同模式下，定时器不同的刷新
//    int t_editmode = [[CGInst getInst] getEditMode];
//    if( t_editmode == E_EDIT_M_GIFT) {
//        if(self.m_pWinCtrlGift) {
//            [self.m_pWinCtrlGift updateTimer];
//        }
//    }else if( t_editmode == E_EDIT_M_BEAUTY) {
//        if(self.m_pWinCtrlBeauty) {
//            [self.m_pWinCtrlBeauty updateTimer];
//        }
//
//    }else if( t_editmode == E_EDIT_M_FILTER) {
//        if(self.m_pWinCtrlFilter) {
//            [self.m_pWinCtrlFilter updateTimer];
//        }
//    }else if( t_editmode == E_EDIT_M_GAME) {
//        if(self.m_pWinCtrlGame) {
//            [self.m_pWinCtrlGame updateTimer];
//        }
//    }
//}

@end
