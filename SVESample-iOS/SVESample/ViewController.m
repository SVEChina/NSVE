//
//  ViewController.m
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "ViewController.h"
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
    // Do any additional setup after loading the view.
    [[CGInst getInst] cgInit];
    //
    if(false) {
        metalview = [[CMetalView alloc] initWithFrame:self.view.bounds];
        [self.view addSubview:metalview];
    }else{
        glview = [[CGLView alloc] initWithFrame:self.view.bounds];
        [self.view addSubview:glview];
    }
}


@end
