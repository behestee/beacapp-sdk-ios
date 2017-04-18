# Beacapp SDK for iOS Version 2.0.0
## はじめに
[Beacapp](http://www.beacapp.com)で登録したコンテンツをiOSで利用するためのSDKです。

## 概要
BeacappSDKforiOSは、iOSアプリケーションにBeacappの機能を組み込むためのSDK（ソフトウェア開発キット）です。
既存のiOSアプリケーション、これから製造するiOSアプリケーションにBeacappSDKforiOSを組み込み、必要な処理を実行するだけで ビーコンを検知して様々なアクションを実行することができます。

BeacappSDKforiOSの主な機能は以下の通りです。

- BeacappSDKのアクティベーション
	BeacappSDKforiOSを実行するためにはアプリ起動毎にアクティベーションが必要となります。アクティベーションとは、Beacapp Web管理コンソール（以下、CMS)にアクセスし、BeacappSDKforiOSが組み込まれているアプリケーションがCMSで登録されているアプリケーションかを判定します。CMSで登録されているアプリケーションではない、もしくはCMSで発行されている認証情報がBeacappSDKに正しく設定されていない場合はエラーと判断されます。また、アクティベーション時に端末の電波状態が著しく悪い場合、機内モード・圏外などの場合もエラーとなる場合があります。

- CMSで設定された各種情報のダウンロード
	CMSで設定された各種情報（ビーコンの情報、イベントの発火条件の情報など）をCMSからダウンロードします。この情報のダウンロードは後のビーコンの検知、イベントの発火に必要となります。

- ビーコンの検知・検知停止
	ビーコンの検知・検知停止を実行します。BeacappSDKforiOSでは、ビーコンの検知を行うために位置情報サービスの利用とBluetoothの状態確認を行います。

- イベントのハンドリングと発火
	BeacappSDKforiOSではビーコンを検知した際に、CMSで設定されたイベントの条件と合致するかを自動で判定します。イベントの条件と合致する場合は、BeacappSDKforiOSを組み込んでいるアプリケーションに通知を行います。


## 実行環境
* Xcode6 and later
* iOS7 and later

## SDKの導入　（ [CocoaPods](http://cocoapods.org)　を利用する）
**Podfile**　に下記の一行を追加するだけでインストール可能です:

バージョン1.3.0からは、cocoapods 0.39.0 以上の利用をお願い致します。

    pod "BeacappSDKforiOS"

- 注意：BeacappSDKforiOSはBitcode非対応です。Xcode のターゲット設定を変更してください。
		
	[Your App Target] - [Build Settings] - [Build Options] - "Enable Bitcode" -> No

## SDKの使い方
1. ヘッダーをインポートします

		#import <BeacappSDKforiOS/JBCPCore.h>

2. Delegateを採用します（以下は、UIViewControllerに設定する場合の例）

		@interface ViewController : UIViewController<JBCPManagerDelegate>


3. JBCPMangaerを生成してください

		JBCPManager *manager = [JBCPManager sharedManager];
		manager.delegate = self;

4. SDKのアクティベートを実行してください

		NSError *activateError = nil;
		BOOL activateResult = [manager initializeWithRequestToken:@"yourRequestToken" secretKey:@"yourSecretKey" options:nil error:&activateError];

5. 最新のイベントデータをCMSから取得します

		NSError *eventError = nil;
		BOOL result = [manager startUpdateEvents:&eventError];

	イベントの取得を開始時に以下のデリゲートが呼ばれます。
	YESを返すと、イベントデータの取得を実行します。NOを返すとイベントデータの取得を行わず処理を終了します。

		- (BOOL)manager:(JBCPManager *)manager shouldUpdateEvents:(NSDictionary *)info{
			if (![info[@"alreadyNewest"]boolValue]) {
        		return YES;
    		}else{
				// YESを返すことによって、強制的にイベントデータの更新を実行することも可能です。
				// NOを返しても、didFinishUpdateEventsは呼ばれます。
        		return NO;
    		}
		}

		最後に下記のデリゲートが呼ばれます。
		- (void)manager:(JBCPManager *)manager didFinishUpdateEvents:(NSError *)error{
			if(error){
				// your error handling
			}else{
				// do anything
			}
		}

6. ビーコンの監視を開始します。

		NSError *scanError = nil;
		BOOL result = [manager startScan:&scanError];

7. CMSで設定したイベントが検知されると下記のデリゲートが呼ばれます。

		- (void)manager:(JBCPManager *)manager fireEvent:(NSDictionary *)event{
			// do anything
		}


## 補足
1. JBCPManagerはアクティベーションやDBの生成に失敗するとstartUpdateEvents: やstartScan: などが実行できなくなります。
2. イベントデータの実際の取得は非同期処理で行われます。
イベントデータの取得のAPIでのBOOL値は、CMSからイベントデータ取得を実行する準備が完了した場合にYESを返します。イベントデータの取得は完了していないことに注意してください。

3. ビーコンの監視を開始するときは、イベントデータの取得処理が完了した後に行うことを推奨します。
ビーコン監視中にイベントデータの取得処理を実行すると、SDK内部でビーコンの監視を強制的に停止します。イベントデータの取得処理およびそれに係るすべての処理が完了してもビーコンの監視は自動で再開致しません。

4. JBCPManagerDelegateはメインスレッドではない場合があります。
デリゲートメソッド内にてメインスレッドで処理を行う必要がある場合は、メインスレッドかどうかの判定を行う必要があります。

		if ([NSThread isMainThread]){
			// main thread
		}else{
			// not main thread
			dispatch_sync (
                       dispatch_get_main_queue(),^{
                           // do anything
                       	}
                       );
		}

5. バックグランドでもビーコンを検知したい場合は、JBCPManager,JBCPMangerDelegateをAppDelege内もしくはRoot ViewControllerに実装するようにしてください。

6. BeacappSDKforiOSではビーコンの検知を行う為、内部でCLLocatinManager, CBPeripheralManagerを使用しています.

7. iOS8でBeacappSDKforiOSを利用する場合
	iOS8から位置情報サービスを利用するための実行許可の方式が変更となります。
	iOSアプリケーションのinfo.plistに以下のキーを追加し、アプリケーションとして必要な説明文を追記してください。

	| キー名　　|
	|---------------|
	|NSLocationAlwaysUsageDescription|

	**BeacappSDKfoiOSでは 位置情報サービスの利用許可種類としてAlwaysUseを推奨しています**

	**v1.4.0現在では、WhenInUseの場合、Beacappでは位置情報サービス利用許可申請アラートを自動で表示いたします**

	また、CMSと通信を行うため、AWS SDKが説明する以下を適用してください。
	 - [ATS(Apple Transport Security)の設定](https://github.com/aws/aws-sdk-ios/tree/2.3.6#preparing-your-apps-for-ios-9)

8. manager:fireEvent: のイベント情報ハンドリング方法サンプル
	イベントが発火した際に、BeacappSDKforiOSからアプリケーション側に通知されるデリゲートメソッドにおけるイベント情報のハンドリング方法のサンプルを示します。
	デリゲートのパラメーターとして渡されるfireEventのNSDictionary中にCMSで設定したコンテンツ情報が含まれています。

	(NSDictionary*)eventから　コンテンツ情報を取得する方法

		NSDictionary *actionContentDic = event[@"action_data"];

	もしくは

		NSDictionary *actionContentDic = [event objectForKey:@"action_data"];

	これでCMSで設定されたコンテンツの種類とその内容が含まれているNSDictionaryオブジェクトを取得することができます。
	actionContentDicオブジェクトからさらにCMSで設定されているコンテンツの種類と、内容をそれぞれ取得する方法は下記のようになります。

		NSString *type = actionContentDic[@"action"];

		// type　が URLもしくはimageの場合は、urlキーでコンテンツの内容を取得することができます。
		if ([type isEqualToString:@"jbcp_open_url"] || [type isEqualToString:@"jbcp_open_image"]){
			NSString *contentUrl = actionContentDic[@"url"];
		}
		// typeがtextの場合は、textキーでコンテンツの内容を取得することができます。
		else if([type isEqualToString:@"jbcp_open_text"]){
			NSString *contentText = actionContentDic[@"text"];
		}
		// typeがカスタムの場合は、key_valuesキーでCMSで設定したカスタムキーとバリューを取得することができます。
		else if([type isEqualToString:@"jbcp_custom_key_value"]){
			// Your Custom KeyValue can get Key => key_values
			NSDictionary *customKeyVaules = actionContentDic[@"key_values"];
		}

9. サンプルコード
	BeacappSDKforiOSの一般的な処理の流れとしてのサンプルコードです。

		@interface ViewController ()
		<JBCPManagerDelegate>
		@property (nonatomic, weak) JBCPManager *jbcpmanager;
		@end
		@implementation ViewController

		-(void)viewDidLoad{
			[super viewDidLoad];
			// YourCode
		}

		-(void)viewWillAppear:(BOOL)animated{
    		[super viewWillAppear:animated];

	    	NSError *error = nil;
    		self.jbcpmanager = [JBCPManager sharedManager];
			self.jbcpmanager.delegate = self;

			BOOL initRet = [self.jbcpmanager initializeWithRequestToken:@"yourRequestToken" secretKey:@"yourSecretKey" options:nil error:&error];
    		if (initRet) {
        		BOOL updateEventRet = [self.jbcpmanager startUpdateEvents:&error];
        		if (updateEventRet) {
         		   // OK update start
        		}else{
         	   	   // NG update can't start
        		}
    		}
		}

		#pragma mark JBCPManagerDelegate
		-(BOOL)manager:(JBCPManager *)manager shouldUpdateEvents:(NSDictionary *)info{
    		   if (![info[@"alreadyNewest"]boolValue]) {
       		      return YES;
    		   }else{
    		      return NO;
    		   }
    		   return YES;
		}

		-(void)manager:(JBCPManager *)manager didFinishUpdateEvents:(NSError *)error{
		    if (!error) {
        		NSError *startError = nil;
        		if ([self.jbcpmanager startScan:&startError]) {
        		}else{
         		   NSLog(@"error %@",startError);
        		}
    		   }else{
       		      NSLog(@"error %@",error);
    		   }
		}

		-(void)manager:(JBCPManager *)manager fireEvent:(NSDictionary *)event
		{
	           if ([NSThread isMainThread]) {
    	    	      // 処理
        	      [self myBeaconEventUIShow:event[@"action_data"]];
    	    	   } else {
	            	dispatch_sync (
                	           	dispatch_get_main_queue(),
                    	       	^{
                        		       // 処理
                        	    	   [self myBeaconEventUIShow:event[@"action_data"]];
	                	           }
    	        	               );
        	   }
		}

		-(void)myBeaconEventUIShow:(NSDictionary*)action_data{
				// Your Code
		}

10. アプリケーション側でCoreLocationを利用する場合

 アプリケーション側で本SDKとは別にCLCircleRegionによるリージョン監視を行っている場合は以下にに注意してください。

 アプリケーション側で本SDKとは別にリージョン監視を行う場合、CLLocationManagerの仕様によりCLLocationManagerDelegateの関連メソッドに対して本SDKで監視しているiBeaconのリージョン情報も通知される可能性があります。

 また、iOSのアプリケーション内で観測できるリージョンの数には制限があります。（最大20個）

 本SDKではBeacapp管理画面において登録・設定されたアプリケーションと関連するiBeaconのUUIDのパターン数を観測するようにしています。（iBeaconのUUIDが３種類必要なときは3つを観測対象として登録します。）

 アプリケーション側で観測するリージョンの数と本SDK側で観測するiBeaconのリージョンの数に注意してください。


## ドキュメント
各種APIのドキュメントなどは[こちら](Documents/ios-api-reference.md)です。

## 製作者

- [jena co. ltd.](http://www.jena.ne.jp)
- [JMAS Systems Corp,.](https://www.jmas.co.jp)

## ライセンス

BeacappSDKforiOSを利用するためには、Beacappの利用規約に同意する必要があります。
BeacappSDKforiOSをいかなる方法を以ってダウンロードした場合、Beacappの利用規約に同意しているものとみなします。
Beacappのご利用申し込みおよび利用規約の同意は[こちら](https://cms.beacapp.com/signup/index/)から可能です。

## その他

- BeacappSDKforiOSでは、[Version2 of AWS SDK for iOS](https://github.com/aws/aws-sdk-ios)が必要となります。

    Version2 of AWS SDK for iOSは　Apache 2.0ライセンスとなります。
	Version2 of AWS SDK for iOS
    Copyright 2014 Amazon.com, Inc. or its affiliates. All Rights Reserved.
    [https://github.com/aws/aws-sdk-ios/blob/master/LICENSE](https://github.com/aws/aws-sdk-ios/blob/master/LICENSE)

- BeacappSDKforiOSでは、[FMDB](https://github.com/ccgus/fmdb)が必要となります。

    FMDB
	Copyright (c) 2008-2014 Flying Meat Inc.
    [https://github.com/ccgus/fmdb/blob/master/LICENSE.txt](https://github.com/ccgus/fmdb/blob/master/LICENSE.txt)
(https://github.com/ccgus/fmdb/blob/master/LICENSE.txt)
