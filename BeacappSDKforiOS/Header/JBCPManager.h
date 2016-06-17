//
//  JBCPManager.h
//  BeacappSDKforiOS version1.3.2
//
//  Created by Akira Hayakawa on 2014/11/11.
//  Update by Akira Hayakawa on 2016/06/17
//  Copyright (c) 2016年 JMA Systems Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JBCPManagerDelegate.h"
#import "JBCPError.h"
@class AWSTask;

/**
 *  !!! BETA !!!
 *  ビーコンイベント検知間隔の設定
 */
typedef NS_ENUM(NSUInteger, JBCPEventSchedule) {
    /**
     *  おおよそ2秒間隔でイベントの検知を実行する
     */
    JBCPEventScheduleFast,
    /**
     *  おおよそ5秒間隔でイベントの検知を実行する
     */
    JBCPEventScheduleDefault,
    /**
     *  おおよそ10秒間隔でイベントの検知を実行する
     */
    JBCPEventScheduleLong,
};

@interface JBCPManager : NSObject

/**
 *  @property delegate
 *
 *  @discussion デリゲートオブジェクトを設定すると、JBCPManagerDelegateプロトコルのイベントをコールバックします.
 */
@property (weak, nonatomic) _Nullable id <JBCPManagerDelegate> delegate;
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
+(JBCPManager * _Nonnull)sharedManager;

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
-(BOOL)initializeWithRequestToken:(NSString * _Nonnull)requestToken secretKey:(NSString * _Nonnull)secretKey options:(NSDictionary * _Nullable)options error:(NSError * _Nullable __autoreleasing * _Nullable)error;



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
- (BOOL)startUpdateEvents:(NSError * _Nullable __autoreleasing * _Nullable)error;


/**
 *  !!! version 1.3では利用不可 !!!
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
- (BOOL)startUpdateContents:(NSError * _Nullable __autoreleasing * _Nullable)error __attribute__((unavailable("startUpdateContents: is unavailable in This Version")));


/**
 *  iBeacon デバイスのスキャンを開始する。スキャンはバックグラウンドスレッドで行われ、イベント発生などの通知は delegate に登録されたコールバッククラスへコールバックされる。
 *  iBeaconの監視は、UUIDごとに実行される。iOSの制約上、監視すべきUUIDが20個以上の場合はこれを実行することができない。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)startScan:(NSError * _Nullable __autoreleasing * _Nullable)error;

/**
 *  !!! BETA !!!
 *  iBeacon デバイスのスキャンを開始する。スキャンはバックグラウンドスレッドで行われ、イベント発生などの通知は delegate に登録されたコールバッククラスへコールバックされる。
 *  iBeaconの監視は、UUIDごとに実行される。iOSの制約上、監視すべきUUIDが20個以上の場合はこれを実行することができない。
 *  すでにスキャンが開始されている場合は”スキャンとイベント発生確認の間隔”の変更は実行されない。変更する場合は一度 - (BOOL)stopScan:(NSError * _Nullable __autoreleasing * _Nullable)error を成功させる必要がある。
 *
 *  @param schedule スキャンとイベント発生確認の間隔
 *  @param error    エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)startScanWithSchedule:(JBCPEventSchedule)schedule error:(NSError * _Nullable __autoreleasing * _Nullable)error;


/**
 *  iBeacon デバイスのスキャンを停止する。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)stopScan:(NSError * _Nullable __autoreleasing * _Nullable)error;


/**
 *  デバイス固有の識別子を取得する。識別子は初回SDK利用時に生成するユニークなIDとなる。
 *
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return デバイス固有の識別子を返す。
 */
- (NSString * _Nullable)getDeviceIdentifier:(NSError * _Nullable __autoreleasing * _Nullable)error;

/**
 *  アプリケーション・端末に保存しているBeacappSDKで必要なアクティベーション情報を消去する。
 *  このメソッドは、Debug実行時のみ実行することを推奨する。
 *  このメソッドを呼び出した後にBeacappSDKの機能を利用したい場合、再度アクティベーションする必要が有る。
 *  なお、Beacappのアクティベーション数を増やすことになるため本メソッドの呼び出しを多用することは推奨しない。
 *  本メソッドを呼び出すことによるアクティベーション数の増加のいかなる責任をBeacappは一切負わないこととする。
 *
 *  @return 消去の成功可否
 */
-(BOOL)clearActivationData;

/**
 *  ログのカスタム領域に追加する文字列を設定する。
 *  valueには下記のチェックを行う。
 *  文字列がSJISの範囲内であること。 
 *  制御文字(=<>/!"#$%&'()-^~|[]{}`@*:;_/?><)が使用されていないこと。
 *  また、UTF8エンコードにおいて1000バイト以内であること。
 *  エラーの場合はerror変数にNSErrorオブジェクトを格納する。
 *
 *  @param value カスタム領域に追加する文字列を指定する。
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)setAdditionalLog:(NSString * _Nullable)value error:(NSError * _Nullable __autoreleasing * _Nullable)error;

/**
 *  ログのカスタム領域に追加する文字列を設定しログ出力を行う。
 *  ログのtypeは256で出力する。
 *  valueには下記のチェックを行う。
 *  文字列がSJISの範囲内であること。
 *  制御文字(<>!"#$%&'()-^~|[]{}`@*:;\_?)が使用されていないこと。
 *  また、UTF8エンコードにおいて1000バイト以内であること。
 *  エラーの場合はerror変数にNSErrorオブジェクトを格納する。
 *  前回customLogが呼び出されてから1秒以上経過していること。
 *
 *  @param value カスタム領域に追加する文字列を指定する。
 *  @param error エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。
 *
 *  @return YES:成功 NO:失敗
 */
- (BOOL)customLog:(NSString * _Nonnull)value error:(NSError * _Nullable __autoreleasing * _Nullable)error;

@end
