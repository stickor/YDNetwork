//
//  YDNetworkRequest.m
//  YDNetworking
//
//  Created by mac on 2020/11/26.
//  Copyright © 2002 . All rights reserved.
//

#import "YDNetworkRequest.h"
#import "AFNetworking.h"
@implementation YDNetworkRequest


-(instancetype)init
{
    self = [super init];
    if (self) {
#if DEBUG
        self.retryTimes = 0;
        self.intervalInSeconds = 0;
        self.showLog = YES;
#else
        self.retryTimes = 1;
        self.intervalInSeconds = 2;
        self.showLog = NO;
#endif
    }
    return self;
}

-(void)requestTypeMethod:(YDRequestType)method url:(NSString *)url parameters:(id)parameters handler:(YDHandlerBlock)handlerBlock
{
    __weak __typeof(self)weakSelf = self;
    if (![NSURL URLWithString:url]) {
        YLog(@"url is nil");
        return ;
    }
    if (self.showLog) {
        YLog(@"Request URL is: %@",url);
        NSArray *methodArr = @[@"GET",@"POST",@"PUT",@"PATCH",@"DELETE"];
        YLog(@"Request Method: %@", methodArr[method]);
        if (parameters) {
            if ([NSJSONSerialization isValidJSONObject:parameters]) {
                NSData* jsonData = [NSJSONSerialization dataWithJSONObject:parameters options:NSJSONWritingPrettyPrinted error:nil];
                NSString *jsonStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
                YLog(@"Parameter is: %@",jsonStr);
            }
        }
    }
    
    [YDNetworkHelper requestTypeMethod:method url:url parameters:parameters handler:^(id  _Nullable aResponseObject, NSError * _Nullable anError) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        if (strongSelf.showLog) {
            NSData* jsonData = [NSJSONSerialization dataWithJSONObject:aResponseObject options:NSJSONWritingPrettyPrinted error:nil];
            NSString *jsonStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            YLog(@"aResponseObject is: %@",jsonStr);
        }
        if (anError == nil && aResponseObject != nil) {
            // aResponseObject not dictionary
            if (![aResponseObject isKindOfClass:[NSDictionary class]]) {
                NSError *err = [NSError errorWithDomain:NSURLErrorDomain code:NSURLErrorUnknown userInfo:@{NSLocalizedDescriptionKey:@"数据格式返回错误!"}];
                handlerBlock(nil, err);
                return;
            }else{
                handlerBlock(aResponseObject,anError);
            }
        }else{
            if (anError.code == NSURLErrorNotConnectedToInternet) {
                if (strongSelf.retryTimes > 0) {
                    strongSelf.retryTimes -= 1;
                    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(strongSelf.intervalInSeconds * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                        __strong __typeof(weakSelf)strongSelf = weakSelf;
                        [strongSelf requestTypeMethod:method url:url parameters:parameters handler:nil];
                    });
                }else{
                    handlerBlock(aResponseObject,anError);
                    return;
                }
            }else{
                handlerBlock(aResponseObject,anError);
                return;
            }
            
        }
    }];
}

- (__kindof NSURLSessionTask *)uploadImagesWithURL:(NSString *)URL parameters:(id)parameters name:(NSString *)name images:(NSArray<UIImage *> *)images fileNames:(NSArray<NSString *> *)fileNames imageScale:(CGFloat)imageScale imageType:(NSString *)imageType progress:(YDHttpProgress)progress handler:(YDHandlerBlock)handlerBlock
{
    return [YDNetworkHelper uploadImagesWithURL:URL parameters:parameters name:name images:images fileNames:fileNames imageScale:imageScale imageType:imageType progress:^(NSProgress *progres) {
        progress(progres);
    } success:^(id responseObject) {
        handlerBlock(responseObject,nil);
    } failure:^(NSError *error) {
        handlerBlock(nil,error);
    }];
    
}

- (__kindof NSURLSessionTask *)downloadWithURL:(NSString *)URL fileDir:(NSString *)fileDir progress:(YDHttpProgress)progress handler:(YDHandlerBlock)handlerBlock
{
    return [YDNetworkHelper downloadWithURL:URL fileDir:fileDir progress:^(NSProgress *progres) {
        progress(progres);
    } success:^(NSString *filePath) {
        handlerBlock(filePath,nil);
    } failure:^(NSError *error) {
        handlerBlock(nil,error);
    }];
}



@end
