// 序列化

#import <Foundation/Foundation.h>
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#import <UIKit/UIKit.h>
#endif

#pragma mark -------------- AFURLRequestSerialization ---------------
//设置相应的 HTTP 格式
@protocol AFURLRequestSerialization <NSObject, NSCoding, NSCopying>

- (NSURLRequest *)requestBySerializingRequest:(NSURLRequest *)request
                               withParameters:(id)parameters
                                        error:(NSError * __autoreleasing *)error;
@end



typedef NS_ENUM(NSUInteger, AFHTTPRequestQueryStringSerializationStyle) {
    AFHTTPRequestQueryStringDefaultStyle = 0,
};

#pragma mark -------------- AFMultipartFormData ------------
@protocol AFMultipartFormData;//多部件的


///---------------------------------------
/// AFHTTPRequestSerializer
///---------------------------------------


//提供的查询字符串/ URL格式编码的参数序列化和默认的请求报头，以及响应状态代码和内容类型验证一个具体的基实现。
@interface AFHTTPRequestSerializer : NSObject <AFURLRequestSerialization>

@property (nonatomic, assign) NSStringEncoding stringEncoding;

@property (nonatomic, assign) BOOL allowsCellularAccess;//可以使用蜂窝无线电

@property (nonatomic, assign) NSURLRequestCachePolicy cachePolicy;

@property (nonatomic, assign) BOOL HTTPShouldHandleCookies;

@property (nonatomic, assign) BOOL HTTPShouldUsePipelining;//接受先前数据

@property (nonatomic, assign) NSURLRequestNetworkServiceType networkServiceType;//libo

@property (nonatomic, assign) NSTimeInterval timeoutInterval;



///---------------------------------------
/// @name Configuring HTTP Request Headers
///---------------------------------------

@property (readonly, nonatomic, strong) NSDictionary *HTTPRequestHeaders;

+ (instancetype)serializer;

- (void)setValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

- (void)setAuthorizationHeaderFieldWithUsername:(NSString *)username
                                       password:(NSString *)password;

/**
 @deprecated This method has been deprecated. Use -setValue:forHTTPHeaderField: instead.
 */
- (void)setAuthorizationHeaderFieldWithToken:(NSString *)token DEPRECATED_ATTRIBUTE;

- (void)clearAuthorizationHeader;


///-------------------------------------------------------
/// @name Configuring Query String Parameter Serialization
///-------------------------------------------------------


@property (nonatomic, strong) NSSet *HTTPMethodsEncodingParametersInURI;


- (void)setQueryStringSerializationWithStyle:(AFHTTPRequestQueryStringSerializationStyle)style;

- (void)setQueryStringSerializationWithBlock:(NSString * (^)(NSURLRequest *request, NSDictionary *parameters, NSError * __autoreleasing *error))block;

///-------------------------------
/// @name Creating Request Objects
///-------------------------------

/**
 @deprecated This method has been deprecated. Use -requestWithMethod:URLString:parameters:error: instead.
 */
- (NSMutableURLRequest *)requestWithMethod:(NSString *)method
                                 URLString:(NSString *)URLString
                                parameters:(id)parameters DEPRECATED_ATTRIBUTE;


- (NSMutableURLRequest *)requestWithMethod:(NSString *)method
                                 URLString:(NSString *)URLString
                                parameters:(id)parameters
                                     error:(NSError * __autoreleasing *)error;

/**
 @deprecated This method has been deprecated. Use -multipartFormRequestWithMethod:URLString:parameters:constructingBodyWithBlock:error: instead.
 */
- (NSMutableURLRequest *)multipartFormRequestWithMethod:(NSString *)method
                                              URLString:(NSString *)URLString
                                             parameters:(NSDictionary *)parameters
                              constructingBodyWithBlock:(void (^)(id <AFMultipartFormData> formData))block DEPRECATED_ATTRIBUTE;


- (NSMutableURLRequest *)multipartFormRequestWithMethod:(NSString *)method
                                              URLString:(NSString *)URLString
                                             parameters:(NSDictionary *)parameters
                              constructingBodyWithBlock:(void (^)(id <AFMultipartFormData> formData))block
                                                  error:(NSError * __autoreleasing *)error;


- (NSMutableURLRequest *)requestWithMultipartFormRequest:(NSURLRequest *)request
                             writingStreamContentsToFile:(NSURL *)fileURL
                                       completionHandler:(void (^)(NSError *error))handler;

@end

#pragma mark -

extern NSUInteger const kAFUploadStream3GSuggestedPacketSize;
extern NSTimeInterval const kAFUploadStream3GSuggestedDelay;


@protocol AFMultipartFormData


- (BOOL)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                        error:(NSError * __autoreleasing *)error;

- (BOOL)appendPartWithFileURL:(NSURL *)fileURL
                         name:(NSString *)name
                     fileName:(NSString *)fileName
                     mimeType:(NSString *)mimeType
                        error:(NSError * __autoreleasing *)error;


- (void)appendPartWithInputStream:(NSInputStream *)inputStream
                             name:(NSString *)name
                         fileName:(NSString *)fileName
                           length:(int64_t)length
                         mimeType:(NSString *)mimeType;


- (void)appendPartWithFileData:(NSData *)data
                          name:(NSString *)name
                      fileName:(NSString *)fileName
                      mimeType:(NSString *)mimeType;


- (void)appendPartWithFormData:(NSData *)data
                          name:(NSString *)name;


- (void)appendPartWithHeaders:(NSDictionary *)headers
                         body:(NSData *)body;


- (void)throttleBandwidthWithPacketSize:(NSUInteger)numberOfBytes
                                  delay:(NSTimeInterval)delay;

@end


///---------------------------------------
/// AFJSONRequestSerializer
///---------------------------------------



@interface AFJSONRequestSerializer : AFHTTPRequestSerializer


@property (nonatomic, assign) NSJSONWritingOptions writingOptions;

+ (instancetype)serializerWithWritingOptions:(NSJSONWritingOptions)writingOptions;


@end


///---------------------------------------
/// AFPropertyListRequestSerializer
///---------------------------------------


@interface AFPropertyListRequestSerializer : AFHTTPRequestSerializer


@property (nonatomic, assign) NSPropertyListFormat format;

@property (nonatomic, assign) NSPropertyListWriteOptions writeOptions;

+ (instancetype)serializerWithFormat:(NSPropertyListFormat)format
                        writeOptions:(NSPropertyListWriteOptions)writeOptions;





@end
