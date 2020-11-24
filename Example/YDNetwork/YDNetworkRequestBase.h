//
//  YDNetworkRequestBase.h
//  YDNetworking_Example
//
//  Created by 杨引 on 2020/11/20.
//  Copyright © 2020 895148635@qq.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YDNetworkRequest.h"
NS_ASSUME_NONNULL_BEGIN


@interface YDNetworkRequestBase : NSObject

+(void)requestUrl:(NSString *)url requestMethod:(YDRequestType)method param:(NSDictionary *)aParam andhandler:(YDHandlerBlock)handlerBlock;

@end

NS_ASSUME_NONNULL_END
