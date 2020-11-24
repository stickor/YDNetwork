//
//  YDViewController.m
//  YDNetworking
//
//  Created by 895148635@qq.com on 11/20/2020.
//  Copyright (c) 2020 895148635@qq.com. All rights reserved.
//

#import "YDViewController.h"
#import "YDNetworkRequestBase.h"
#import "YDURL.h"
#import "YDLog.h"
@interface YDViewController ()

@end

@implementation YDViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [YDLog testRun];
    for (int i = 0 ; i<20; i++) {
        [YDNetworkRequestBase requestUrl:kUrl1 requestMethod:YDRequestTypePOST param:@{} andhandler:^(id  _Nullable aResponseObject, NSError * _Nullable anError) {
            if (aResponseObject) {
                NSLog(@" 成功第%d次====>\n %@",i,aResponseObject);
            }
            if (anError) {
                NSLog(@" 失败第%d次====>\n %@",i,anError);
            }
        }];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
