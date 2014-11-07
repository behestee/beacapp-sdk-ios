#JBCPManager クラスリファレンス

## 概要
このクラスはビーコンデバイス、アプリ情報などを管理するクラスである。
主に以下の機能を提供する。

- SDKの初期化処理

- イベントデータ更新処理
  ビーコンリスト、 イベント、トリガー、アクションの更新

- ビーコン受信処理開始／終了

- コールバックの登録

- デバイス固有の識別子取得

### プロパティ
----

    delegate
	verboseMode
	isNeedActivation

### メソッド
-----

	+ sharedMangaer
    -initializeWithRequestToken: secretKey: options: error:
    - startUpdateEvents:
    - startScan:
    - stopScan:
    - getDeviceIdentifier:

## プロパティ

### delegate

		id<JBCPManagerDelegate> delegate

デリゲートオブジェクトを登録する。
nil をセットするとデリゲートが無効となり、デリゲートプロトコル（JBCPManagerDelegate)で定義されているメソッドは機能しなくなる。

### verboseMode

		BOOL verboseMode

YESに設定すると、SDK内の詳細のログをデバッグログとして出力できる。

### isNeedActivation (readOnly)

		BOOL isNeedActivation

SDKのアクティベートが必要な場合、YESに設定される

## メソッド

### +sharedManager;

		+(JBCPManager*)sharedManager;

SDKのインスタンスを生成する。SDKはアプリ起動毎にシングルトンオブジェクトとして生成される。

### -initializeWithRequestToken: secretKey: options: error:

		-(BOOL)initializeWithRequestToken:(NSString*)requestToken secretKey:(NSString*)secretKey options:(NSDictionary*)options error:(NSError**)error;

SDKの初期化をおこなう。未アクティベート時にはアクティベート処理を開始する。本関数は同期型であり、アクティベート処理が完了するまでブロックする。SDKを利用するアプリケーションは、本関数を使用する必要がある。引数 options にはオプションパラメータを指定する。  

##### requestToken パラメーター

Beacapp Web管理コンソールで登録したアプリケーションのリクエストトークンを指定する

##### secretKey パラメーター

 Beacapp Web管理コンソールで登録したアプリケーションのシークレットキーを指定する

##### options パラメータ

キーに文字列、値は任意のオブジェクトを格納する。省略(nil)可能
現状未使用。

##### error パラメータ

エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

#### 戻り値
成功した場合は YESを返します。
エラーの場合は、NOを返します。

------

### - startUpdateEvents:

		- (BOOL)startUpdateEvents:(NSError **)error

イベントデータの更新を開始する。 イベントデータとは、Beacapp Web管理コンソールで登録した情報を指す。アクティベートが必要な場合、もしくはdelegate がセットされていない場合エラー終了する。 更新処理の進捗と完了通知は delegate にセットされた JBCPManagerDelegate を実装したクラスへコールバックされる。
完了コールバック関数は JBCPManagerDelegate の didFinishUpdateEvents がコールされる。
エラー発生時には didFinishUpdateEvents の error に詳細情報が格納される。 また、SDK利用者は JBCPManagerDelegate の shouldUpdateEvents を定義する事で、強制的に更新するかどうかを選択する事も可能である。
サーバから成りすまし防止の位置情報認証を利用するかどうかも取得する。位置情報を利用する場合はOSの位置情報取得処理を開始する。
既にstartScanが成功していた場合、startUpdateEventsを呼ぶとSDK内部で強制的にstopScanを実行する。startUpdateEventsおよびこれに係る処理全てが完了した場合、再度startScanを呼び出す必要がある。

##### 成りすまし防止の位置情報認証について
ビーコンデバイスの成りすまし防止に、OSの位置情報を利用した認証機能を利用できます。 ビーコンを検出した際に、現在地とBeacapp Web管理コンソールで登録した位置情報が大きくかけ離れている場合は不正と見なす機能である。 Beacapp Web管理コンソールで位置登録することで利用可能である。

#### パラメータ
- error  
 エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

#### 戻り値
YES:成功 NO:失敗

-----

### - startScan:

		- (BOOL)startScan:(NSError **)error

iBeacon デバイスのスキャンを開始する。スキャンはバックグラウンドで行われ、イベント発生などの通知は delegate に登録されたコールバッククラスへコールバックされる。
iBeaconの監視は、UUIDごとに実行される。iOSの制約上、監視すべきUUIDが20個以上の場合はこれを実行することができない。
アクティベートが必要な場合、エラーとなる。

#### パラメータ
- error  
 エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

#### 戻り値
YES:成功 NO:失敗

-----

### - stopScan:

			- (BOOL)stopScan:(NSError **)error

iBeacon デバイスのスキャンを停止する。
アクティベートが必要な場合、エラーとなる。


#### パラメータ
- error  
 エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

#### 戻り値
YES:成功 NO:失敗

------

### - getDeviceIdentifier:

			- (NSString *)getDeviceIdentifier:(NSError **)error

デバイス固有の識別子を取得する。
識別子は初回SDK利用時に生成するユニークなIDとなる。
アクティベートが必要な場合、エラーとなる。


#### パラメータ
- error  
 エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

#### 戻り値  
デバイス固有の識別子を返す。

