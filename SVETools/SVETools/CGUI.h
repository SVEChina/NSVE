//
//  CGUI.h
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSViewController.h>
#import <AppKit/NSWindow.h>
#import "CGState.h"

//@class WinCtrl;
//@class WinCtrlGift;
//@class WinCtrlBeauty;
//@class WinCtrlFilter;
//@class WinCtrlGame;
//@class CGMenuMain;
//@class CGUIFrameGL;

@interface CGUI : NSObject

+ (instancetype) getInst;

-(void)cgInit:(int)_mode;

-(void)cgDestroy;
//
//-(void)setEditMode:(int)_mode;
//
//-(void)refreshUI:(NSRect)_rc;
//
//-(void*)getFrameRoot;
//
//-(void)setPropVis:(bool)_vis;
//
//-(void)setAniVis:(bool)_vis;
//
//-(void)setToolbarVis:(bool)_vis;
//
////定时器刷新
//-(void)updateTimer;

////窗口ctrl
//@property(nonatomic,strong) WinCtrl* m_pWinCtrl;
//@property(nonatomic,strong) WinCtrlGift* m_pWinCtrlGift;
//@property(nonatomic,strong) WinCtrlBeauty* m_pWinCtrlBeauty;
//@property(nonatomic,strong) WinCtrlFilter* m_pWinCtrlFilter;
//@property(nonatomic,strong) WinCtrlGame* m_pWinCtrlGame;
//
////主菜单
//@property(nonatomic,strong) CGMenuMain* m_pMainMenu;
////framegl
//@property(nonatomic,strong) CGUIFrameGL *frameGL;


@end
