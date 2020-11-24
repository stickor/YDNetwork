//
//  YDNetworkRequestBase.m
//  YDNetworking_Example
//
//  Created by 杨引 on 2020/11/20.
//  Copyright © 2020 895148635@qq.com. All rights reserved.
//

#import "YDNetworkRequestBase.h"
#import <YDNetworking/YDNetworkHelper.h>
#import "YDURL.h"

@implementation YDNetworkRequestBase


/// 请求相关设置 请求头、 请求格式、返回数据格式、请求超时时长
+ (void)initialize {
    [YDNetworkHelper setHTTPHeaders:[YDNetworkRequestBase requestHeaders]];
    [YDNetworkHelper setRequestSerializer:YDRequestSerializerJSON];
    [YDNetworkHelper setRequestSerializer:YDRequestSerializerJSON];
    [YDNetworkHelper setRequestTimeoutInterval:30];
}

+(void)requestUrl:(NSString *)url requestMethod:(YDRequestType)method param:(NSDictionary *)aParam andhandler:(YDHandlerBlock)handlerBlock
{
    YDNetworkRequest *request = [YDNetworkRequest new];
    [request requestTypeMethod:method url:[NSString stringWithFormat:@"%@%@",kBaseUrl,url] parameters:aParam handler:^(id  _Nullable aResponseObject, NSError * _Nullable anError) {
        if (anError == nil && aResponseObject != nil) {
            handlerBlock(aResponseObject,anError);
        }else{
            [YDNetworkRequestBase errorActionWithErrror:anError andhandler:^(id  _Nullable aResponseObject, NSError * _Nullable anError) {
                handlerBlock(nil,anError);
            }];
        }
    }];
    
}

+(void)errorActionWithErrror:(NSError *)error andhandler:(YDHandlerBlock)handlerBlock
{
    /// 和后台约定的指定code码比如：-99 token失效
    if (error.code == -99) {
        NSLog(@"跳转到登录");
        return;
    }else{
        handlerBlock(nil,error);
    }
    
}

+ (NSDictionary *)requestHeaders {
    return @{@"appName":@"yuetao",
             @"brand":@"Apple",
             @"brand":@"APP",
             @"codepushVersion":@"--",
             @"model":@"iPhone,0",
             @"systemType":@"ios",
             @"systemVersion":@"14.2",
             @"uuid": @"--------------------",
             @"version": @"3.9.96"};
}
@end
