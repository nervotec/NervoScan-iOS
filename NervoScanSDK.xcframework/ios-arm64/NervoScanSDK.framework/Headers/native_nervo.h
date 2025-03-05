#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface NervoScanWrapper : NSObject
- (instancetype) initWithWindow:(NSNumber *)window_time andFloat:(NSNumber *)scan_time;
- (NSNumber *)calculateFPS: (UIImage *) image;
- (NSNumber *)queueFrameTimes:(UIImage *)image time:(NSNumber *)time;
- (NSNumber *)startProcessingThread;
- (NSNumber *)stopProcessingThread;
- (NSNumber *)getStatus;
- (NSNumber *)getProcessingStatus;
- (NSNumber *)isResultsReady;
- (NSNumber *)isMinuteResultsReady;
- (NSArray<NSArray<NSNumber *>*> *)getResults;
- (NSArray<NSArray<NSNumber *>*> *)getMinuteResults;
@end
