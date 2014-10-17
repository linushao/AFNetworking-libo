// 会话

#import <Foundation/Foundation.h>

#import "AFURLResponseSerialization.h"
#import "AFURLRequestSerialization.h"
#import "AFNetworkReachabilityManager.h"



#if (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 70000) || (defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 1090)

@interface AFURLSessionManager : NSObject <NSURLSessionDelegate,
                                           NSURLSessionTaskDelegate,
                                           NSURLSessionDataDelegate,
                                           NSURLSessionDownloadDelegate,
                                           NSCoding,
                                           NSCopying>

/* The managed session */
@property (readonly, nonatomic, strong) NSURLSession *session;

/* The operation queue on which delegate callbacks are run */
@property (readonly, nonatomic, strong) NSOperationQueue *operationQueue;

@property (nonatomic, strong) id <AFURLResponseSerialization> responseSerializer;



///--------------------------------------
/// @name Monitoring Network Reachability
///--------------------------------------

/* The network reachability manager. `AFURLSessionManager` uses the `sharedManager` by default. */
@property (readwrite, nonatomic, strong) AFNetworkReachabilityManager *reachabilityManager;

///----------------------------
/// @name Getting Session Tasks
///----------------------------

/* The data, upload, and download tasks currently run by the managed session */
@property (readonly, nonatomic, strong) NSArray *tasks;

/* The data tasks currently run by the managed session */
@property (readonly, nonatomic, strong) NSArray *dataTasks;

/* The upload tasks currently run by the managed session */
@property (readonly, nonatomic, strong) NSArray *uploadTasks;

/* The download tasks currently run by the managed session */
@property (readonly, nonatomic, strong) NSArray *downloadTasks;

///---------------------------------
/// @name Managing Callback Queues
///---------------------------------

@property (nonatomic, strong) dispatch_queue_t completionQueue;

@property (nonatomic, strong) dispatch_group_t completionGroup;

@property (nonatomic, assign) BOOL attemptsToRecreateUploadTasksForBackgroundSessions;

///---------------------
/// @name Initialization
///---------------------

/* Creates and returns a manager for a session created with the specified configuration. This is the designated initializer */
- (instancetype)initWithSessionConfiguration:(NSURLSessionConfiguration *)configuration;

/**
 Invalidates the managed session, optionally canceling pending tasks.
 
 @param cancelPendingTasks Whether or not to cancel pending tasks.
 */
- (void)invalidateSessionCancelingTasks:(BOOL)cancelPendingTasks;

///-------------------------
/// @name Running Data Tasks
///-------------------------


- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request
                            completionHandler:(void (^)(NSURLResponse *response, id responseObject, NSError *error))completionHandler;

///---------------------------
/// @name Running Upload Tasks
///---------------------------

- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request
                                         fromFile:(NSURL *)fileURL
                                         progress:(NSProgress * __autoreleasing *)progress
                                completionHandler:(void (^)(NSURLResponse *response, id responseObject, NSError *error))completionHandler;

- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request
                                         fromData:(NSData *)bodyData
                                         progress:(NSProgress * __autoreleasing *)progress
                                completionHandler:(void (^)(NSURLResponse *response, id responseObject, NSError *error))completionHandler;

/* Creates an `NSURLSessionUploadTask` with the specified streaming request */
- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request
                                                 progress:(NSProgress * __autoreleasing *)progress
                                        completionHandler:(void (^)(NSURLResponse *response, id responseObject, NSError *error))completionHandler;

///-----------------------------
/// @name Running Download Tasks
///-----------------------------

/**
 @param destination A block object to be executed in order to determine the destination of the downloaded file. This block takes two arguments, the target path & the server response, and returns the desired file URL of the resulting download. The temporary file used during the download will be automatically deleted after being moved to the returned URL.
 */
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request
                                             progress:(NSProgress * __autoreleasing *)progress
                                          destination:(NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
                                    completionHandler:(void (^)(NSURLResponse *response, NSURL *filePath, NSError *error))completionHandler;

/**
 @param resumeData The data used to resume downloading.
 @param progress A progress object monitoring the current download progress.
 @param destination A block object to be executed in order to determine the destination of the downloaded file. This block takes two arguments, the target path & the server response, and returns the desired file URL of the resulting download. The temporary file used during the download will be automatically deleted after being moved to the returned URL.
 */
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData
                                                progress:(NSProgress * __autoreleasing *)progress
                                             destination:(NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
                                       completionHandler:(void (^)(NSURLResponse *response, NSURL *filePath, NSError *error))completionHandler;

///---------------------------------
/// @name Getting Progress for Tasks
///---------------------------------

- (NSProgress *)uploadProgressForTask:(NSURLSessionUploadTask *)uploadTask;


- (NSProgress *)downloadProgressForTask:(NSURLSessionDownloadTask *)downloadTask;

///-----------------------------------------
/// @name Setting Session Delegate Callbacks
///-----------------------------------------


- (void)setSessionDidBecomeInvalidBlock:(void (^)(NSURLSession *session, NSError *error))block;



///--------------------------------------
/// @name Setting Task Delegate Callbacks
///--------------------------------------


- (void)setTaskDidSendBodyDataBlock:(void (^)(NSURLSession *session, NSURLSessionTask *task, int64_t bytesSent, int64_t totalBytesSent, int64_t totalBytesExpectedToSend))block;


- (void)setTaskDidCompleteBlock:(void (^)(NSURLSession *session, NSURLSessionTask *task, NSError *error))block;

///-------------------------------------------
/// @name Setting Data Task Delegate Callbacks
///-------------------------------------------


- (void)setDataTaskDidReceiveResponseBlock:(NSURLSessionResponseDisposition (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSURLResponse *response))block;


- (void)setDataTaskDidBecomeDownloadTaskBlock:(void (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSURLSessionDownloadTask *downloadTask))block;


- (void)setDataTaskDidReceiveDataBlock:(void (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSData *data))block;


- (void)setDataTaskWillCacheResponseBlock:(NSCachedURLResponse * (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSCachedURLResponse *proposedResponse))block;


- (void)setDidFinishEventsForBackgroundURLSessionBlock:(void (^)(NSURLSession *session))block;

///-----------------------------------------------
/// @name Setting Download Task Delegate Callbacks
///-----------------------------------------------


- (void)setDownloadTaskDidFinishDownloadingBlock:(NSURL * (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, NSURL *location))block;


- (void)setDownloadTaskDidWriteDataBlock:(void (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite))block;


- (void)setDownloadTaskDidResumeBlock:(void (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, int64_t fileOffset, int64_t expectedTotalBytes))block;

@end

#endif

///--------------------
/// @name Notifications
///--------------------


extern NSString * const AFNetworkingTaskDidStartNotification DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidResumeNotification;
extern NSString * const AFNetworkingTaskDidFinishNotification DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteNotification;
extern NSString * const AFNetworkingTaskDidSuspendNotification;
extern NSString * const AFURLSessionDidInvalidateNotification;
extern NSString * const AFURLSessionDownloadTaskDidFailToMoveFileNotification;
extern NSString * const AFNetworkingTaskDidFinishResponseDataKey DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteResponseDataKey;
extern NSString * const AFNetworkingTaskDidFinishSerializedResponseKey DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteSerializedResponseKey;
extern NSString * const AFNetworkingTaskDidFinishResponseSerializerKey DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteResponseSerializerKey;
extern NSString * const AFNetworkingTaskDidFinishAssetPathKey DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteAssetPathKey;
extern NSString * const AFNetworkingTaskDidFinishErrorKey DEPRECATED_ATTRIBUTE;
extern NSString * const AFNetworkingTaskDidCompleteErrorKey;
