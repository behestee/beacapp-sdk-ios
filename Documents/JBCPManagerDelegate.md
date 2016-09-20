# JBCPManagerDelegate プロトコルリファレンス

## 概要
このプロトコルは、JBCPManager からDelegateされる以下の関数を定義する。

- イベント更新問い合わせ
- イベント更新コールバック
- ビーコンイベントの発火
- 位置情報サービスの利用許可状況、Bluetoothの状態通知
- 位置情報の取得、ビーコンの監視・レンジング時等のエラー通知
- ビーコンレンジングイベントのコールバック(BETA)

### メソッド

    - manager:shouldUpdateEvents:
    - manager:didFinishUpdateEvents:
    - manager:fireEvent:
    - manager:didUpdateMonitoringStatus:peripheralState:
    - manager:didFailWithError:
    - manager:didRangedBeacon:

## メソッド

### (Optional) - manager:shouldUpdateEvents:

		- (BOOL)manager:(JBCPManager * _Nonnull)manager shouldUpdateEvents:(NSDictionary * _Nullable)info

イベント更新するかどうかをSDK利用者に問い合わせるためのdelegateメソッド。  
JBCPManager#startUpdateEvents がコールされると本関数がデリゲートされる。  
利用者は戻り値 YES or NO を返却することでイベントを更新するかどうかを選択可能とする。  
また、本関数を定義しない場合はデフォルトの動作を行う。  
引数 info には、イベント更新するかどうかの情報が辞書形式で格納される。  

##### info パラメータ
キーに文字列、値は任意のオブジェクトを格納する。  

|キー               |値の型   |値の説明                                  |
|-------------------|---------|------------------------------------------|
|lastUpdatedAt      |NSDate   |最後に更新した日時                        |
|alreadyNewest      |NSNumber |1:既に最新版  0:サーバに新イベントあり  |


##### デフォルトの動作

info の alreadyNewest が 1 の場合は更新をおこなわない。 0 の場合のみ更新をおこなう。



#### パラメータ
- manager
JBCPManager のインスタンス

- info
イベント更新するかどうかの情報が格納される


#### 戻り値
NO の場合は更新しない。
YES の場合はイベントの更新をおこなう。
info の alreadyNewest が 1 の場合でも YES を返却することで強制的にイベント更新を行うことができる。

-----

### (Required) - manager:didFinishUpdateEvents:

		- (void)manager:(JBCPManager * _Nonnull)manager didFinishUpdateEvents:(NSError * _Nullable)error

イベント更新が完了すると、このdelegateメソッドがコールされる。
エラー発生時にもコールされ、その場合は error に詳細情報が格納される。
このdelegateメソッドはメインスレッドで呼ばれない場合があるため、メインスレッドでその後の動作を行う場合は注意すること。

#### パラメータ
- manager
JBCPManager のインスタンス

- error
エラーが発生した場合、詳細情報の NSError オブジェクトを格納する。成功した場合は nil が格納される。

-----

### (Required) - manager:fireEvent:


		- (void)manager:(JBCPManager * _Nonnull)manager fireEvent:(NSDictionary * _Nonnull)event

ビーコンを受信し、条件に合致すると、このdelegateメソッドがコールされる。
event に受信したビーコン情報、トリガーの条件、実行すべきアクションを辞書形式で格納する。
event に格納されるデータのうち、Beacapp Web管理コンソールで登録した**連携させるコンテンツ**をJSON形式で表すと以下のイメージである。

- action_data
 実行すべきアクション（連携させるコンテンツ）の情報を格納する。
 key, value 形式の辞書型とする。
 key には必ず "action" キーが存在し、その値にアクションの種別を格納する。

  - action の値

  |値           |説明                  |
  |-------------|----------------------|
  |jbcp_open_image |画像がコンテンツとして設定されている          |
  |jbcp_open_url     |Web URLがコンテンツとして設定されている       |
  |jbco_open_text   |テキスト情報がコンテンツとして設定されている       |
  |jbcp_custom_key_value       |カスタムデータが設定されている  |

  - jbcp_open_image の場合

    キー url の値に表示する画像が格納される

	    "action_data" : {
    	  "action" : "jbcp_open_image",
      	"url" : "http://some-server/some-path/some.png"
    	}

  - jbcp_open_url の場合

    キー url の値に Web ページに表示するURLを格納

	    "action_data" : {
    	  "action" : "jbcp_open_url",
      	"url" : "http://some-server/some-path/?some-query=foo"
    	}

  - jbco_open_text の場合

    キー text の値に テキスト情報 を文字列で定義

	    "action_data" : {
    	  "action" : "jbco_open_text",
      	"text" : "hello beacapp world"
   	 }

  - jbcp_custom_key_value の場合

  	Beacapp Web管理コンソールで登録した任意のキー、値で構成される
	Beacapp Web管理コンソールで登録した任意のキー、値は**key_values**キー内に格納されている

	    "action_data" : {
    	  "action" : "jbcp_custom_key_value",
		  "key_values" : {
		  	"some_key" : "some_value",
			  "some_key2" : "some_value2"
		  }
   	 }


#### パラメータ
- manager
JBCPManager のインスタンス

- event
イベントデータを辞書形式で格納する。上記のとおり。

-------

### (Optional) - manager:didUpdateMonitoringStatus:peripheralState:

		-(void)manager:(JBCPManager * _Nonnull)manager didUpdateMonitoringStatus:(CLAuthorizationStatus)authrizationStatus peripheralState:(CBPeripheralManagerState)peripheralState

位置情報サービスの許可状態、端末Bluetooth状態を検知し場合、このdelegateメソッドがコールされる。

#### パラメータ
- manager
JBCPManagerのインスタンス

- authrizationStatus
位置情報サービスの利用許可ステータス

- peripheralState
Bluetoothのステータス

------

### (Optional) - manager:didFailWithError:

		-(void)manager:(JBCPManager * _Nonnull)manager didFailWithError:(NSError * _Nullable)error

CLLocationManagerを利用した位置情報サービスの利用、Beaconの監視・レンジング実行時にエラーが発生した場合に、このdelegateメソッドがコールされる。

#### パラメータ
- manager
JBCPManagerのインスタンス

- error
エラーが発生した場合、詳細情報のNSErrorオブジェクトを格納する。(CLError）

-------

### (Optional) - manager:didRangedBeacon:

      -(void)manager:(JBCPManager * _Nonnull)manager didRangedBeacon:(NSArray<CLBeacon *> * _Nullable)beacons

iBeaconのエリア内でのiBeaconの検知状況をおおよそ1秒毎に通知する。この関数は、iOSの標準のiBeacon検知時のときと同様の動きをする。

#### パラメータ
- manager
JBCPManagerのインスタンス

- beacons
検知しているiBeaconの配列オブジェクトを格納する。
