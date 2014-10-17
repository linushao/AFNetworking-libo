

#import <Foundation/Foundation.h>

#import <Availability.h>

///----------------
/// @name Constants
///----------------

extern NSString * const AFNetworkingErrorDomain;
extern NSString * const AFNetworkingOperationFailingURLRequestErrorKey;
extern NSString * const AFNetworkingOperationFailingURLResponseErrorKey;

///--------------------
/// @name Notifications
///--------------------

extern NSString * const AFNetworkingOperationDidStartNotification;
extern NSString * const AFNetworkingOperationDidFinishNotification;




#pragma mark ------

@interface AFURLConnectionOperation : NSOperation <NSURLConnectionDelegate,
                                                   NSURLConnectionDataDelegate,
                                                   NSCoding,
                                                   NSCopying>


@property (nonatomic, strong) NSSet *runLoopModes;



@property (readonly, nonatomic, strong) NSURLRequest *request;
@property (readonly, nonatomic, strong) NSURLResponse *response;
@property (readonly, nonatomic, strong) NSError *error;


@property (readonly, nonatomic, strong) NSData *responseData;
@property (readonly, nonatomic, copy) NSString *responseString;
@property (readonly, nonatomic, assign) NSStringEncoding responseStringEncoding;



@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, strong) NSOutputStream *outputStream;


@property (nonatomic, strong) dispatch_queue_t completionQueue;//队列
@property (nonatomic, strong) dispatch_group_t completionGroup;//组


@property (nonatomic, strong) NSDictionary *userInfo;


- (instancetype)initWithRequest:(NSURLRequest *)urlRequest;


- (void)pause;
- (BOOL)isPaused;
- (void)resume;


#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
- (void)setShouldExecuteAsBackgroundTaskWithExpirationHandler:(void (^)(void))handler;
#endif

///---------------------------------
/// @name Setting Progress Callbacks  进度回调
///---------------------------------


/* 定义好typedefy BLOCK ；此处显示BLOCK的元素，可在调用时显示元素 */
- (void)setUploadProgressBlock:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))block;

- (void)setDownloadProgressBlock:(void (^)(NSUInteger bytesRead, long long totalBytesRead, long long totalBytesExpectedToRead))block;

///-------------------------------------------------
/// @name Setting NSURLConnection Delegate Callbacks  验证
///-------------------------------------------------

- (void)setWillSendRequestForAuthenticationChallengeBlock:(void (^)(NSURLConnection *connection, NSURLAuthenticationChallenge *challenge))block;

//重定向
- (void)setRedirectResponseBlock:(NSURLRequest * (^)(NSURLConnection *connection, NSURLRequest *request, NSURLResponse *redirectResponse))block;



- (void)setCacheResponseBlock:(NSCachedURLResponse * (^)(NSURLConnection *connection, NSCachedURLResponse *cachedResponse))block;


//批量
+ (NSArray *)batchOfRequestOperations:(NSArray *)operations
                        progressBlock:(void (^)(NSUInteger numberOfFinishedOperations, NSUInteger totalNumberOfOperations))progressBlock
                      completionBlock:(void (^)(NSArray *operations))completionBlock;

@end

