
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
#import "AFNetworkReachabilityManager.h"

@interface AFHTTPRequestOperationManager : NSObject <NSCoding, NSCopying>


@property (readonly, nonatomic, strong) NSURL *baseURL;

@property (nonatomic, strong) AFHTTPRequestSerializer <AFURLRequestSerialization> * requestSerializer;//序列化

@property (nonatomic, strong) AFHTTPResponseSerializer <AFURLResponseSerialization> * responseSerializer;

/**
 The operation queue on which request operations are scheduled and run.
 */
@property (nonatomic, strong) NSOperationQueue *operationQueue;


@property (readwrite, nonatomic, strong) AFNetworkReachabilityManager *reachabilityManager;//可达性


+ (instancetype)manager;







- (AFHTTPRequestOperation *)GET:(NSString *)URLString
                     parameters:(id)parameters
                        success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;



- (AFHTTPRequestOperation *)POST:(NSString *)URLString
                      parameters:(id)parameters
                         success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;









@end

