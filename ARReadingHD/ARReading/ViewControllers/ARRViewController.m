//
//  ARRViewController.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "ARRViewController.h"

#import "CameraController.h"
#import "ARRCamera.h"

@interface ARRViewController ()

@end

@implementation ARRViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    camera = [[ARRCamera alloc] initWithFrameRect:self.view.bounds];
    [self.view.layer addSublayer:camera.previewLayer];
    [camera start];
    
    [self.view addSubview:camera.glView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// ARC 不需要 且不能显式 release及dealloc
//- (void)dealloc {
//	[camera release];
//	[super dealloc];
//}

@end
