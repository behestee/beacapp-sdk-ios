//
//  JBCPManagerDelegate.h
//  BeacappSDKforiOS version1.2.0
//
//  Created by Akira Hayakawa on 2014/11/11.
//  Update by Akira Hayakawa on 2016/02/05
//  Copyright (c) 2015年 JMA Systems Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
@class JBCPManager;
@import CoreLocation;
@import CoreBluetooth;

@protocol JBCPManagerDelegate <NSObject>
@optional

/**
 *  イベント更新するかどうかをSDK利用者に問い合わせるためのコールバック。JBCPManager#startUpdateEvents がコールされると本関数がコールバックされる。利用者は戻り値 YES or NO を返却することでイベントを更新するかどうかを選択可能とする。また、本関数を定義しない場合はデフォルトの動作を行う。引数 info には、イベント更新するかどうかの情報が辞書形式で格納される。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param info    イベント更新するかどうかの情報が格納される。キーに文字列、値は任意のオブジェクトを格納する。info の alreadyNewest が 1 の場合は更新をおこなわない。 0 の場合のみ更新をおこなう。
 *
 *  @return NO の場合は更新しない。YES の場合はイベントの更新をおこなう。 デフォルトの動作ではinfo の alreadyNewest が 1 の場合でも YES を返却することで強制的にイベント更新を行うことができる。
 */
- (BOOL)manager:(JBCPManager *)manager shouldUpdateEvents:(NSDictionary *)info;


/**
 *  !!! version1.2では利用不可 !!!
 *  イベント更新の進捗コールバック。 このコールバックは JBCPManager の startUpdateEvents が呼ばれるとコールされる。 プログレスバーの表示などをおこないたい場合に本関数を使用する。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param current 現在の進捗値。%で表す場合は 100 * current / total で計算できる。
 *  @param total   進捗値の最大値
 */
- (void)manager:(JBCPManager *)manager didProgressUpdateEvents:(NSNumber *)current total:(NSNumber *)total __attribute__((unavailable("manager:didProgressUpdateEvents:total: is unavailable in Version 1.2")));

@required
/**
 *  イベント更新が完了すると、このコールバック関数がコールされる。 エラー発生時にもコールされ、その場合は error に詳細情報が格納される。このコールバック関数はメインスレッドで呼ばれない場合があるため、メインスレッドでその後の動作を行う場合は注意すること。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param error   エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 */
- (void)manager:(JBCPManager *)manager didFinishUpdateEvents:(NSError *)error;


/**
 *  !!! version1.2では利用不可 !!!
 *  コンテンツ更新するかどうかをSDK利用者に問い合わせるためのコールバック。JBCPManager#startUpdateContents がコールされると本関数がコールバックされる。利用者は戻り値 YES or NO を返却することでコンテンツを更新するかどうかを選択可能とする。また、本関数を定義しない場合はデフォルトの動作を行う。引数 info には、コンテンツ更新するかどうかの情報が辞書形式で格納される。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param info    コンテンツ更新するかどうかの情報が格納される。キーに文字列、値は任意のオブジェクトを格納する。info の alreadyNewest が 1 の場合は更新をおこなわない。 0 の場合のみ更新をおこなう。
 *
 *  @return NO の場合は更新しない。YES の場合はコンテンツの更新をおこなう。 デフォルトの動作ではinfo の alreadyNewest が 1 の場合でも YES を返却することで強制的にコンテンツ更新を行うことができる。
 */
@optional
- (BOOL)manager:(JBCPManager *)manager shouldUpdateContents:(NSDictionary *)info __attribute__((unavailable("manager:shouldUpdateContents: is unavailable in Version 1.2")));


/**
 *  !!! version1.2では利用不可 !!!
 *  コンテンツ更新の進捗コールバック。 このコールバックは JBCPManager の startUpdateContents が呼ばれるとコールされる。 プログレスバーの表示などをおこないたい場合に本関数を使用する。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param current 現在の進捗値。%で表す場合は 100 * current / total で計算できる。
 *  @param total   進捗値の最大値
 */
- (void)manager:(JBCPManager *)manager didProgressUpdateContents:(NSNumber *)current total:(NSNumber *)total __attribute__((unavailable("manager:didProgressUpdateContents:total: is unavailable in Version 1.2")));


/**
 *  !!! version1.2では利用不可 !!!
 *  コンテンツ更新が完了すると、このコールバック関数がコールされる。 エラー発生時にもコールされ、その場合は error に詳細情報が格納される。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param error   エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 */
- (void)manager:(JBCPManager *)manager didFinishUpdateContents:(NSError *)error __attribute__((unavailable("manager:didFinishUpdateContents: is unavailable in Version 1.2")));

@required
/**
 *  ビーコンを受信し、条件に合致すると、このコールバック関数がコールされる。event に受信したビーコン情報、トリガーの条件、実行すべきアクションを辞書形式で格納する。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param event   イベントデータを辞書形式で格納する。
 */
- (void)manager:(JBCPManager *)manager fireEvent:(NSDictionary *)event;

@optional
/**
 *  位置情報サービスの許可状態、端末Bluetooth状態を検知し場合、このコールバック関数がコールされる。
 *
 *  @param manager            JBCPManagerのインスタンス
 *  @param authrizationStatus 位置情報サービスの利用許可ステータス
 *  @param peripheralState    Bluetoothのステータス
 */
-(void)manager:(JBCPManager*)manager didUpdateMonitoringStatus:(CLAuthorizationStatus)authrizationStatus peripheralState:(CBPeripheralManagerState)peripheralState;

/**
 *  CLLocationManagerを利用した位置情報サービスの利用、Beaconの検知実行時にエラーが発生した場合に、コールバック関数がコールされる。
 *
 *  @param manager JBCPManagerのインスタンス
 *  @param error   エラーが発生した場合、詳細情報のNSErrorオブジェクトを格納する。(CLErrorをサポートしてください）
 */
-(void)manager:(JBCPManager*)manager didFailWithError:(NSError*)error;

@end