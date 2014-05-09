

#import <Foundation/Foundation.h>
#import "AFURLConnectionOperation.h"
#import "AFURLResponseSerialization.h"


@interface AFHTTPRequestOperation : AFURLConnectionOperation


@property (readonly, nonatomic, strong) NSHTTPURLResponse *response;


@property (nonatomic, strong) AFHTTPResponseSerializer <AFURLResponseSerialization> * responseSerializer;


@property (readonly, nonatomic, strong) id responseObject;


- (void)setCompletionBlockWithSuccess:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                              failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure;

@end
