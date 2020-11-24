//
//  YDNetworkHelper.h
//  YDNetworking
//
//  Created by mac on 2020/11/26.
//  Copyright © 2020 . All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "YDNetworkCache.h"

#ifdef DEBUG
#define YLog(...) printf("[%s] %s [第%d行]: %s\n", __TIME__ ,__PRETTY_FUNCTION__ ,__LINE__, [[NSString stringWithFormat:__VA_ARGS__] UTF8String])
#else
#define YLog(...)
#endif

#define NSStringFormat(format,...) [NSString stringWithFormat:format,##__VA_ARGS__]

#ifndef kIsNetwork
#define kIsNetwork     [YDNetworkHelper isNetwork]  // 一次性判断是否有网的宏
#endif

#ifndef kIsWWANNetwork
#define kIsWWANNetwork [YDNetworkHelper isWWANNetwork]  // 一次性判断是否为手机网络的宏
#endif

#ifndef kIsWiFiNetwork
#define kIsWiFiNetwork [YDNetworkHelper isWiFiNetwork]  // 一次性判断是否为WiFi网络的宏
#endif

typedef NS_ENUM(NSUInteger, YDNetworkStatusType) {
    /// 未知网络
    YDNetworkStatusUnknown,
    /// 无网络
    YDNetworkStatusNotReachable,
    /// 手机网络
    YDNetworkStatusReachableViaWWAN,
    /// WIFI网络
    YDNetworkStatusReachableViaWiFi
};
typedef NS_ENUM(NSUInteger, YDRequestType) {
    /// 设置请求数据GET
    YDRequestTypeGET = 0,
    YDRequestTypePOST,
    YDRequestTypePUT,
    YDRequestTypePATCH,
    YDRequestTypeDELETE,
};
typedef NS_ENUM(NSUInteger, YDRequestSerializer) {
    /// 设置请求数据为JSON格式
    YDRequestSerializerJSON,
    /// 设置请求数据为二进制格式
    YDRequestSerializerHTTP,
};

typedef NS_ENUM(NSUInteger, YDResponseSerializer) {
    /// 设置响应数据为JSON格式
    YDResponseSerializerJSON,
    /// 设置响应数据为二进制格式
    YDResponseSerializerHTTP,
};
/// 完成的回调
typedef void(^YDHandlerBlock)(id _Nullable aResponseObject, NSError* _Nullable anError);

/// 请求成功的Block
typedef void(^YDHttpRequestSuccess)(id _Nullable responseObject);

/// 请求失败的Block
typedef void(^YDHttpRequestFailed)(NSError * _Nullable error);

/// 缓存的Block
typedef void(^YDHttpRequestCache)(id _Nullable responseCache);

/// 上传或者下载的进度, Progress.completedUnitCount:当前大小 - Progress.totalUnitCount:总大小
typedef void (^YDHttpProgress)(NSProgress * _Nullable progress);

/// 网络状态的Block
typedef void(^YDNetworkStatus)(YDNetworkStatusType status);

@class AFHTTPSessionManager;
@interface YDNetworkHelper : NSObject

/// 有网YES, 无网:NO
+ (BOOL)isNetwork;

/// 手机网络:YES, 反之:NO
+ (BOOL)isWWANNetwork;

/// WiFi网络:YES, 反之:NO
+ (BOOL)isWiFiNetwork;

/// 取消所有HTTP请求
+ (void)cancelAllRequest;

/// 实时获取网络状态,通过Block回调实时获取(此方法可多次调用)
+ (void)networkStatusWithBlock:(YDNetworkStatus _Nonnull)networkStatus;

/// 取消指定URL的HTTP请求
+ (void)cancelRequestWithURL:(NSString *_Nonnull)URL;

/// 开启日志打印 (Debug级别)
+ (void)openLog;

/// 关闭日志打印,默认关闭
+ (void)closeLog;


/**
 *  GET请求,无缓存
 *
 *  @param URL        请求地址
 *  @param parameters 请求参数
 *  @param success    请求成功的回调
 *  @param failure    请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask * _Nonnull)GET:(NSString * _Nonnull)URL
                        parameters:(id _Nullable)parameters
                           success:(YDHttpRequestSuccess _Nullable)success
                           failure:(YDHttpRequestFailed _Nullable)failure;


/**
 通用请求
 
 @param method 请求方式
 @param url 请求的url
 @param parameters 请求参数
 @param handlerBlock 回调
 @return 返回的对象可取消请求,调用cancel方法
 */
+(NSURLSessionTask * _Nonnull)requestTypeMethod:(YDRequestType)method url:(NSString * _Nonnull)url
                            parameters:(id _Nullable)parameters
                               handler:(YDHandlerBlock _Nonnull)handlerBlock;

/**
 *  GET请求,自动缓存
 *
 *  @param URL           请求地址
 *  @param parameters    请求参数
 *  @param responseCache 缓存数据的回调
 *  @param success       请求成功的回调
 *  @param failure       请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask *_Nonnull)GET:(NSString *_Nonnull)URL
                        parameters:(id _Nullable)parameters
                     responseCache:(YDHttpRequestCache _Nullable)responseCache
                           success:(YDHttpRequestSuccess _Nullable)success
                           failure:(YDHttpRequestFailed _Nullable)failure;

/**
 *  POST请求,无缓存
 *
 *  @param URL        请求地址
 *  @param parameters 请求参数
 *  @param success    请求成功的回调
 *  @param failure    请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask *_Nonnull)POST:(NSString *_Nonnull)URL
                         parameters:(id _Nullable)parameters
                            success:(YDHttpRequestSuccess _Nullable)success
                            failure:(YDHttpRequestFailed _Nullable)failure;

/**
 *  POST请求,自动缓存
 *
 *  @param URL           请求地址
 *  @param parameters    请求参数
 *  @param responseCache 缓存数据的回调
 *  @param success       请求成功的回调
 *  @param failure       请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask *_Nonnull)POST:(NSString *_Nonnull)URL
                         parameters:(id _Nullable)parameters
                      responseCache:(YDHttpRequestCache _Nullable)responseCache
                            success:(YDHttpRequestSuccess _Nullable)success
                            failure:(YDHttpRequestFailed _Nullable)failure;

/**
 *  上传文件
 *
 *  @param URL        请求地址
 *  @param parameters 请求参数
 *  @param name       文件对应服务器上的字段
 *  @param filePath   文件本地的沙盒路径
 *  @param progress   上传进度信息
 *  @param success    请求成功的回调
 *  @param failure    请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask *_Nonnull)uploadFileWithURL:(NSString *_Nonnull)URL
                                      parameters:(id _Nullable)parameters
                                            name:(NSString * _Nullable)name
                                        filePath:(NSString * _Nonnull)filePath
                                        progress:(YDHttpProgress _Nullable)progress
                                         success:(YDHttpRequestSuccess _Nullable)success
                                         failure:(YDHttpRequestFailed _Nullable)failure;

/**
 *  上传单/多张图片
 *
 *  @param URL        请求地址
 *  @param parameters 请求参数
 *  @param name       图片对应服务器上的字段
 *  @param images     图片数组
 *  @param fileNames  图片文件名数组, 可以为nil, 数组内的文件名默认为当前日期时间"yyyyMMddHHmmss"
 *  @param imageScale 图片文件压缩比 范围 (0.f ~ 1.f)
 *  @param imageType  图片文件的类型,例:png、jpg(默认类型)....
 *  @param progress   上传进度信息
 *  @param success    请求成功的回调
 *  @param failure    请求失败的回调
 *
 *  @return 返回的对象可取消请求,调用cancel方法
 */
+ (__kindof NSURLSessionTask * _Nonnull)uploadImagesWithURL:(NSString *_Nonnull)URL
                                        parameters:(id _Nullable)parameters
                                              name:(NSString *_Nullable)name
                                            images:(NSArray<UIImage *> *_Nonnull)images
                                         fileNames:(NSArray<NSString *> *_Nullable)fileNames
                                        imageScale:(CGFloat)imageScale
                                         imageType:(NSString *_Nullable)imageType
                                          progress:(YDHttpProgress _Nullable)progress
                                           success:(YDHttpRequestSuccess _Nullable)success
                                           failure:(YDHttpRequestFailed _Nullable)failure;

/**
 *  下载文件
 *
 *  @param URL      请求地址
 *  @param fileDir  文件存储目录(默认存储目录为Download)
 *  @param progress 文件下载的进度信息
 *  @param success  下载成功的回调(回调参数filePath:文件的路径)
 *  @param failure  下载失败的回调
 *
 *  @return 返回NSURLSessionDownloadTask实例，可用于暂停继续，暂停调用suspend方法，开始下载调用resume方法
 */
+ (__kindof NSURLSessionTask *_Nonnull)downloadWithURL:(NSString *_Nonnull)URL
                                       fileDir:(NSString *_Nullable)fileDir
                                      progress:(YDHttpProgress _Nullable)progress
                                               success:(void(^_Nullable)(NSString *_Nullable filePath))success
                                       failure:(YDHttpRequestFailed _Nullable)failure;




#pragma mark - 设置AFHTTPSessionManager相关属性
#pragma mark 注意: 因为全局只有一个AFHTTPSessionManager实例,所以以下设置方式全局生效
/**
 在开发中,如果以下的设置方式不满足项目的需求,就调用此方法获取AFHTTPSessionManager实例进行自定义设置
 (注意: 调用此方法时在要导入AFNetworking.h头文件,否则可能会报找不到AFHTTPSessionManager的❌)
 @param sessionManager AFHTTPSessionManager的实例
 */
+ (void)setAFHTTPSessionManagerProperty:(void(^_Nullable)(AFHTTPSessionManager *_Nullable sessionManager))sessionManager;

/**
 *  设置网络请求参数的格式:默认为二进制格式
 *
 *  @param requestSerializer YDRequestSerializerJSON(JSON格式),YDRequestSerializerHTTP(二进制格式),
 */
+ (void)setRequestSerializer:(YDRequestSerializer)requestSerializer;

/**
 *  设置服务器响应数据格式:默认为JSON格式
 *
 *  @param responseSerializer YDResponseSerializerJSON(JSON格式),YDResponseSerializerHTTP(二进制格式)
 */
+ (void)setResponseSerializer:(YDResponseSerializer)responseSerializer;

/**
 *  设置请求超时时间:默认为30S
 *
 *  @param time 时长
 */
+ (void)setRequestTimeoutInterval:(NSTimeInterval)time;

/// 设置请求头
+ (void)setValue:(NSString *_Nonnull)value forHTTPHeaderField:(NSString *_Nonnull)field;
+ (void)setHTTPHeaders:(NSDictionary *_Nonnull)headers;

/**
 *  是否打开网络状态转圈菊花:默认关闭
 *
 *  @param open YES(打开), NO(关闭)
 */
+ (void)openNetworkActivityIndicator:(BOOL)open;

/**
 配置自建证书的Https请求, 参考链接: http://blog.csdn.net/syg90178aw/article/details/52839103
 
 @param cerPath 自建Https证书的路径
 @param validatesDomainName 是否需要验证域名，默认为YES. 如果证书的域名与请求的域名不一致，需设置为NO; 即服务器使用其他可信任机构颁发
 的证书，也可以建立连接，这个非常危险, 建议打开.validatesDomainName=NO, 主要用于这种情况:客户端请求的是子域名, 而证书上的是另外
 一个域名。因为SSL证书上的域名是独立的,假如证书上注册的域名是www.google.com, 那么mail.google.com是无法验证通过的.
 */
+ (void)setSecurityPolicyWithCerPath:(NSString *_Nonnull)cerPath validatesDomainName:(BOOL)validatesDomainName;

@end

