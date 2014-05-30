
#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <Availability.h>

#if __IPHONE_OS_VERSION_MIN_REQUIRED
#import <MobileCoreServices/MobileCoreServices.h>
#else
#import <CoreServices/CoreServices.h>
#endif

#import "AFHTTPRequestOperation.h"
#import "AFURLResponseSerialization.h"
#import "AFURLRequestSerialization.h"
#import "AFSecurityPolicy.h"
#import "AFNetworkReachabilityManager.h"

@interface AFHTTPRequestOperationManager : NSObject <NSCoding, NSCopying>


@property (readonly, nonatomic, strong) NSURL *baseURL;

@property (nonatomic, strong) AFHTTPRequestSerializer <AFURLRequestSerialization> * requestSerializer;//序列化

@property (nonatomic, strong) AFHTTPResponseSerializer <AFURLResponseSerialization> * responseSerializer;

/**
 The operation queue on which request operations are scheduled and run.
 */
@property (nonatomic, strong) NSOperationQueue *operationQueue;

@property (nonatomic, assign) BOOL shouldUseCredentialStorage; //凭证存储
@property (nonatomic, strong) NSURLCredential *credential;


@property (nonatomic, strong) AFSecurityPolicy *securityPolicy; //安全政策

@property (readwrite, nonatomic, strong) AFNetworkReachabilityManager *reachabilityManager;//可达性


+ (instancetype)manager;

- (instancetype)initWithBaseURL:(NSURL *)url;

///---------------------------------------
/// @name Managing HTTP Request Operations
///---------------------------------------

/**
 创建一个`AFHTTPRequestOperation`，并将响应序列化到HTTP客户端的
 */
- (AFHTTPRequestOperation *)HTTPRequestOperationWithRequest:(NSURLRequest *)request
                                                    success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                                                    failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;


- (AFHTTPRequestOperation *)GET:(NSString *)URLString
                     parameters:(id)parameters
                        success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;



- (AFHTTPRequestOperation *)HEAD:(NSString *)URLString
                      parameters:(id)parameters
                         success:(void (^)(AFHTTPRequestOperation *operation))success
                         failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;

- (AFHTTPRequestOperation *)POST:(NSString *)URLString
                      parameters:(id)parameters
                         success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;

/**
 @param block A block that takes a single argument and appends data to the HTTP body. The block argument is an object adopting the `AFMultipartFormData` protocol.
 */
- (AFHTTPRequestOperation *)POST:(NSString *)URLString
                      parameters:(id)parameters
       constructingBodyWithBlock:(void (^)(id <AFMultipartFormData> formData))block
                         success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;


- (AFHTTPRequestOperation *)PUT:(NSString *)URLString
                     parameters:(id)parameters
                        success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;


- (AFHTTPRequestOperation *)PATCH:(NSString *)URLString
                       parameters:(id)parameters
                          success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                          failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;


- (AFHTTPRequestOperation *)DELETE:(NSString *)URLString
                        parameters:(id)parameters
                           success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                           failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;

@end

