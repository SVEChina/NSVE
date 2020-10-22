//
//  ViewController.m
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "ViewController.h"
#import "CGDef.h"
#import "CGBaseSys.h"
#import "CMetalView.h"
#import "CGLView.h"
#import "CGInst.h"

@interface ViewController () {
    CMetalView* metalview;
    CGLView* glview;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [[CGBaseSys getInst] initSys];
    // Do any additional setup after loading the view.
    [[CGInst getInst] cgInit];
    //
    if(SVE_CORE == SVE_GLES) {
        glview = [[CGLView alloc] initWithFrame:self.view.bounds];
        [self.view addSubview:glview];
    }else if(SVE_CORE == SVE_METAL){
        metalview = [[CMetalView alloc] initWithFrame:self.view.bounds];
        [self.view addSubview:metalview];
    }
}


@end
