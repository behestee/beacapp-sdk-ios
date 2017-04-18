//
//  JBCPManagerDelegate.h
//  BeacappSDKforiOS version2.0.0
//
//  Created by Akira Hayakawa on 2014/11/11.
//  Update by Akira Hayakawa on 2017/04
//  Copyright (c) 2017年 JMA Systems Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
@class JBCPManager;
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>

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
- (BOOL)manager:(JBCPManager * _Nonnull)manager shouldUpdateEvents:(NSDictionary * _Nullable)info;

@required
/**
 *  イベント更新が完了すると、このコールバック関数がコールされる。 エラー発生時にもコールされ、その場合は error に詳細情報が格納される。このコールバック関数はメインスレッドで呼ばれない場合があるため、メインスレッドでその後の動作を行う場合は注意すること。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param error   エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 */
- (void)manager:(JBCPManager * _Nonnull)manager didFinishUpdateEvents:(NSError * _Nullable)error;

/**
 *  ビーコンを受信し、条件に合致すると、このコールバック関数がコールされる。event に受信したビーコン情報、トリガーの条件、実行すべきアクションを辞書形式で格納する。
 *
 *  @param manager JBCPManager のインスタンス
 *  @param event   イベントデータを辞書形式で格納する。
 */
- (void)manager:(JBCPManager * _Nonnull)manager fireEvent:(NSDictionary * _Nonnull)event;

@optional
/**
 *  位置情報サービスの許可状態、端末Bluetooth状態を検知し場合、このコールバック関数がコールされる。
 *
 *  @param manager            JBCPManagerのインスタンス
 *  @param authrizationStatus 位置情報サービスの利用許可ステータス
 *  @param centralState    Bluetoothのステータス
 */
-(void)manager:(JBCPManager * _Nonnull)manager didUpdateMonitoringStatus:(CLAuthorizationStatus)authrizationStatus centralState:(CBCentralManagerState)centralState;

/**
*  位置情報サービスの許可状態、端末Bluetooth状態を検知し場合、このコールバック関数がコールされる。
*
*  @param manager            JBCPManagerのインスタンス
*  @param authrizationStatus 位置情報サービスの利用許可ステータス
*  @param peripheralState    Bluetoothのステータス
*/
-(void)manager:(JBCPManager * _Nonnull)manager didUpdateMonitoringStatus:(CLAuthorizationStatus)authrizationStatus peripheralState:(CBPeripheralManagerState)peripheralState __attribute__((availability(ios, unavailable,message="manager:didUpdateMonitoringStatus:peripheralState: is unavailable in This Version. Use manager:didUpdateMonitoringStatus:centralState: .")));


/**
 *  CLLocationManagerを利用した位置情報サービスの利用、Beaconの検知実行時にエラーが発生した場合に、コールバック関数がコールされる。
 *
 *  @param manager JBCPManagerのインスタンス
 *  @param error   エラーが発生した場合、詳細情報のNSErrorオブジェクトを格納する。(CLErrorをサポートしてください）
 */
-(void)manager:(JBCPManager * _Nonnull)manager didFailWithError:(NSError * _Nullable)error;

/**
 *  iBeaconのエリア内でのiBeaconの検知状況をおおよそ1秒毎に通知する。この関数は、iOSの標準のiBeacon検知時のときと同様の動きをする。
 *
 *  @param manager JBCPManagerのインスタンス
 *  @param beacons 検知しているiBeaconの配列オブジェクトを格納する。
 */
-(void)manager:(JBCPManager * _Nonnull)manager didRangedBeacon:(NSArray<CLBeacon *> * _Nullable)beacons;

@end
