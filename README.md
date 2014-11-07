# Beacapp SDK for iOS Version 1.0.0
## Intoroduction
Beacappで登録したコンテンツをiOSで利用するためのSDKです。

## OverView


## Requirements
* Xcode6 and later
* iOS7 and later

## Installation Using [CocoaPods](http://cocoapods.org)
**Podfile**　に下記の一行を追加するだけでインストール可能です:

    pod "BeacappSDKforiOS"

## Getting Started
1. ヘッダーをインポートします

		#import ＜BeacappSDKforiOS/JBCPCore.h>

2. JBCPMangaerを生成してください

		JBCPManager *manager = [JBCPMangaer sharedManager];

3. SDKのアクティベートを実行してください

		NSError *activateError = nil;
		BOOL activateResult = [manager initializeWithRequestToken:@"yourRequestToken" secretKey:@"yourSecretKey" options:nil error:&activateError]
		
4. 最新のイベントデータをCMSから取得します

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

4. ビーコンの監視を開始します。

		NSError *scanError = nil;
		BOOL result = [manager startScan:&scanError];
		
5. CMSで設定したイベントが検知されると下記のデリゲートが呼ばれます。

		- (void)manager:(JBCPManager *)manager fireEvent:(NSDictionary *)event{
			// do anything
		}


## More Info
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

## Documents
See above [documents](Documents/ios-api-reference.md)

## Author

Beacapp Dev Team
- jena co. ltd.
- JMAS Systems Corp,.

## License

BeacappSDKforiOS is available under xxxx






