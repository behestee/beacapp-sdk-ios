//
//  JBCPManager.h
//  BeacappSDKforiOS version1.0.0
//
//  Created by Akira Hayakawa on 2014/11/11.
//  Copyright (c) 2014年 JMA Systems Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JBCPManagerDelegate.h"
#import "JBCPError.h"

@class BFTask;

@interface JBCPManager : NSObject

/**
 *  @property delegate
 *
 *  @discussion デリゲートオブジェクトを設定すると、JBCPManagerDelegateプロトコルのイベントをコールバックします.
 */
@property (weak, nonatomic) id <JBCPManagerDelegate> delegate;
/**
 *  @property verboseMode
 *
 *  @discussion SDK内の詳細なデバッグログを出力したい場合、このプロパティをYESに設定してください.
 */
@property (assign, nonatomic) BOOL verboseMode;

/**
 *  @property isNeedActivation
 *
 *  @discussion SDKのアクティベートが必要な場合、YESとなります.
 */
@property (assign, nonatomic, readonly) BOOL isNeedActivation;

/**
 *  シングルトンクラスを生成します.
 *
 *  @return 生成に成功した場合はシングルトンオブジェクトを返す.
 */
+(JBCPManager*)sharedManager;

/**
 *  SDKの初期化をおこなう。
 *  未アクティベート時にはアクティベート処理を開始する。
 *  本関数は同期型であり、アクティベート処理が完了するまでブロックする。
 *  SDKを利用するアプリケーションは、本関数を使用する必要がある。
 *  引数 options にはオプションパラメータを指定する。
 *
 *  @param requestToken Beacapp Web管理コンソールで登録したアプリケーションのリクエストトークンを指定する
 *  @param secretKey    Beacapp Web管理コンソールで登録したアプリケーションのシークレットキーを指定する
 *  @param options      オプションパラメータ キーに文字列、値は任意のオブジェクトを格納する。version1.0では未使用。
 *  @param error        エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return 成功した場合は YESを返す。
 */
-(BOOL)initializeWithRequestToken:(NSString*)requestToken secretKey:(NSString*)secretKey options:(NSDictionary*)options error:(NSError**)error;



/**
 *  イベントデータの更新を開始する。 イベントデータには、ビーコンリスト、 イベント、トリガー、アクションなど Beacapp を動作するさせるために必要な情報である。delegate がセットされていない場合エラー終了する。 更新処理の進捗と完了通知は delegate にセットされた JBCPManagerDelegate を実装したクラスへコールバックされる。
 *  進捗コールバック関数は JBCPManagerDelegate の didProgressEvents がコールされる。(version1.0では利用不可）
 *  完了コールバック関数は JBCPManagerDelegate の didFinishUpdateEvents がコールされる。
 *  エラー発生時には didFinishUpdateEvents の error に詳細情報が格納される。 また、SDK利用者は JBCPManagerDelegate の shouldUpdateEvents を定義する事で、強制的に更新するかどうかを選択する事も可能である。
 *  サーバから成りすまし防止の位置情報認証を利用するかどうかも取得する。位置情報を利用する場合はOSの位置情報取得処理を開始する。
 *  成りすまし防止の位置情報認証について
 *  ビーコンデバイスの成りすまし防止に、OSの位置情報を利用した認証機能を利用できます。 ビーコンを検出した際に、現在地とBeacapp Web管理コンソールで登録した位置情報が大きくかけ離れている場合は不正と見なす機能である。 Beacapp Web管理コンソールで位置登録することで利用可能である。
 *  すでにstartScanが成功していた場合、startUpdateEventsを呼ぶとSDK内部で強制的にstopScanを実行する。startUpdateEventsおよびこれに係る処理全てが完了した場合、再度startScanを呼び出す必要がある。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)startUpdateEvents:(NSError **)error;


/**
 *  !!! version 1.0では利用不可 !!!
 *  コンテンツデータの更新を開始する。
 *  コンテンツデータには、SDKで利用する画像、動画などが格納される。
 *  delegate がセットされていない場合エラー終了する。 更新処理の進捗と完了通知は delegate にセットされた JBCPManagerDelegate を実装したクラスへコールバックされる。
 *  進捗コールバック関数は JBCPManagerDelegate の didProgressContents がコールされる。
 *  完了コールバック関数は JBCPManagerDelegate の didFinishUpdateContents がコールされる。
 *  エラー発生時には didFinishUpdateContents の error に詳細情報が格納される。 また、SDK利用者は JBCPManagerDelegate の shouldUpdateContents を定義する事で、強制的に更新するかどうかを選択する事も可能である。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)startUpdateContents:(NSError **)error __attribute__((unavailable("startUpdateContents: is unavailable in Version 1.0")));


/**
 *  iBeacon デバイスのスキャンを開始する。スキャンはバックグラウンドで行われ、イベント発生などの通知は delegate に登録されたコールバッククラスへコールバックされる。
 *  iBeaconの監視は、UUIDごとに実行される。iOSの制約上、監視すべきUUIDが20個以上の場合はこれを実行することができない。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)startScan:(NSError **)error;


/**
 *  iBeacon デバイスのスキャンを停止する。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)stopScan:(NSError **)error;


/**
 *  デバイス固有の識別子を取得する。識別子は初回SDK利用時に生成するユニークなIDとなる。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return デバイス固有の識別子を返す。
 */
- (NSString *)getDeviceIdentifier:(NSError **)error;

@end
