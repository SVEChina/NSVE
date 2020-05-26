//
//  CGState.h
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>

enum EDITSTATE {
    E_EDIT_T_FREE,
    E_EDIT_T_EDIT,
    E_EDIT_T_PLAY
};

//编辑器模式
enum EDITMODE {
    E_EDIT_M_NULL = 0,
    E_EDIT_M_BASE,
    E_EDIT_M_GIFT,
    E_EDIT_M_BEAUTY,
    E_EDIT_M_FILTER,
    E_EDIT_M_GAME
};

@interface CGState : NSObject

+ (instancetype) getInst;

@end
