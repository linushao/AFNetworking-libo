

#import <Foundation/Foundation.h>

#import <Availability.h>
#import "AFSecurityPolicy.h"



@interface AFURLConnectionOperation : NSOperation <NSURLConnectionDelegate, NSURLConnectionDataDelegate, NSCoding, NSCopying>


@property (nonatomic, strong) NSSet *runLoopModes;



@property (readonly, nonatomic, strong) NSURLRequest *request;
@property (readonly, nonatomic, strong) NSURLResponse *response;
@property (readonly, nonatomic, strong) NSError *error;


@property (readonly, nonatomic, strong) NSData *responseData;
@property (readonly, nonatomic, copy) NSString *responseString;
@property (readonly, nonatomic, assign) NSStringEncoding responseStringEncoding;


@property (nonatomic, assign) BOOL shouldUseCredentialStorage;
@property (nonatomic, strong) NSURLCredential *credential;


@property (nonatomic, strong) AFSecurityPolicy *securityPolicy;

@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, strong) NSOutputStream *outputStream;


@property (nonatomic, strong) dispatch_queue_t completionQueue;//队列
@property (nonatomic, strong) dispatch_group_t completionGroup;//组


@property (nonatomic, strong) NSDictionary *userInfo;


- (instancetype)initWithRequest:(NSURLRequest *)urlRequest;


- (void)pause;
- (BOOL)isPaused;
- (void)resume;

///----------------------------------------------
/// @name Configuring Backgrounding Task Behavior 配置后台运行
///----------------------------------------------

/**
 Specifies that the operation should continue execution after the app has entered the background, and the expiration handler for that background task.

 @param handler A handler to be called shortly before the application’s remaining background time reaches 0. The handler is wrapped in a block that cancels the operation, and cleans up and marks the end of execution, unlike the `handler` parameter in `UIApplication -beginBackgroundTaskWithExpirationHandler:`, which expects this to be done in the handler itself. The handler is called synchronously on the main thread, thus blocking the application’s suspension momentarily while the application is notified.
 */
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
- (void)setShouldExecuteAsBackgroundTaskWithExpirationHandler:(void (^)(void))handler;
#endif

///---------------------------------
/// @name Setting Progress Callbacks  进度回调
///---------------------------------

/**
 Sets a callback to be called when an undetermined number of bytes have been uploaded to the server.

 @param block A block object to be called when an undetermined number of bytes have been uploaded to the server. This block has no return value and takes three arguments: the number of bytes written since the last time the upload progress block was called, the total bytes written, and the total bytes expected to be written during the request, as initially determined by the length of the HTTP body. This block may be called multiple times, and will execute on the main thread.
 */
- (void)setUploadProgressBlock:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))block;

/**
 Sets a callback to be called when an undetermined number of bytes have been downloaded from the server.

 @param block A block object to be called when an undetermined number of bytes have been downloaded from the server. This block has no return value and takes three arguments: the number of bytes read since the last time the download progress block was called, the total bytes read, and the total bytes expected to be read during the request, as initially determined by the expected content size of the `NSHTTPURLResponse` object. This block may be called multiple times, and will execute on the main thread.
 */
- (void)setDownloadProgressBlock:(void (^)(NSUInteger bytesRead, long long totalBytesRead, long long totalBytesExpectedToRead))block;

///-------------------------------------------------
/// @name Setting NSURLConnection Delegate Callbacks
///-------------------------------------------------

/**
 Sets a block to be executed when the connection will authenticate a challenge in order to download its request, as handled by the `NSURLConnectionDelegate` method `connection:willSendRequestForAuthenticationChallenge:`.
 
 @param block A block object to be executed when the connection will authenticate a challenge in order to download its request. The block has no return type and takes two arguments: the URL connection object, and the challenge that must be authenticated. This block must invoke one of the challenge-responder methods (NSURLAuthenticationChallengeSender protocol).
 
 If `allowsInvalidSSLCertificate` is set to YES, `connection:willSendRequestForAuthenticationChallenge:` will attempt to have the challenge sender use credentials with invalid SSL certificates.
 */
- (void)setWillSendRequestForAuthenticationChallengeBlock:(void (^)(NSURLConnection *connection, NSURLAuthenticationChallenge *challenge))block;

/**
 Sets a block to be executed when the server redirects the request from one URL to another URL, or when the request URL changed by the `NSURLProtocol` subclass handling the request in order to standardize its format, as handled by the `NSURLConnectionDataDelegate` method `connection:willSendRequest:redirectResponse:`.

 @param block A block object to be executed when the request URL was changed. The block returns an `NSURLRequest` object, the URL request to redirect, and takes three arguments: the URL connection object, the the proposed redirected request, and the URL response that caused the redirect.
 */
- (void)setRedirectResponseBlock:(NSURLRequest * (^)(NSURLConnection *connection, NSURLRequest *request, NSURLResponse *redirectResponse))block;


/**
 Sets a block to be executed to modify the response a connection will cache, if any, as handled by the `NSURLConnectionDelegate` method `connection:willCacheResponse:`.

 @param block A block object to be executed to determine what response a connection will cache, if any. The block returns an `NSCachedURLResponse` object, the cached response to store in memory or `nil` to prevent the response from being cached, and takes two arguments: the URL connection object, and the cached response provided for the request.
 */
- (void)setCacheResponseBlock:(NSCachedURLResponse * (^)(NSURLConnection *connection, NSCachedURLResponse *cachedResponse))block;

///

/**

 */
+ (NSArray *)batchOfRequestOperations:(NSArray *)operations
                        progressBlock:(void (^)(NSUInteger numberOfFinishedOperations, NSUInteger totalNumberOfOperations))progressBlock
                      completionBlock:(void (^)(NSArray *operations))completionBlock;

@end

///----------------
/// @name Constants
///----------------

extern NSString * const AFNetworkingErrorDomain;
extern NSString * const AFNetworkingOperationFailingURLRequestErrorKey;
extern NSString * const AFNetworkingOperationFailingURLResponseErrorKey;

///--------------------
/// @name Notifications
///--------------------

/**
 Posted when an operation begins executing.
 */
extern NSString * const AFNetworkingOperationDidStartNotification;

/**
 Posted when an operation finishes.
 */
extern NSString * const AFNetworkingOperationDidFinishNotification;
