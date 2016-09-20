# BeacappSDKforiOS CHANGELOG
## 1.4.0 (Sep 21, 2016)
Features:
- JBCPEventSchedule、JBCPManager / - startScanWithSchedule: error:　APIを正式提供にしました。
- JBCPManagerDelegate / - manager:didRangedBeacon:　デリゲートメソッドを正式提供にしました。
- BETA提供用のAPIを公開
  - イベント発火確認のための検知開始APIにおいて、iBeaconのスキャン開始と同時にレンジングも行うかどうかを設定可能なAPI
  - BeacappAPIのURLを設定/取得可能にするAPI

Bugfix:
- Beacappサーバーとの通信処理や認証処理の不具合を修正しました。
- 多くのイベント情報が登録された際にアップデートイベントができない不具合を修正しました。
- ネットワーク接続ができない状態の際にログデータの送信を見送るように修正しました。

## 1.3.2 (June 17, 2016)
Features:
- アプリケーションの位置情報サービス利用許可タイプがWhenInUseの場合に対応。ただし、WhenInUseの場合はiBeaconのEnterRegion, ExitRegionは検知できなくなります。

Bugfix:
- Beacapp管理画面において、iBeaconの登録でUUIDが小文字の場合にイベントが発火しないことを修正しました。
- アプリケーション側で本SDKとは別にCLCircleRegionによるリージョン監視を行っている場合にExceptionが発生することを修正しました。
  ただし、アプリケーション側で本SDKとは別にリージョン監視を行う場合、CLLocationManagerの仕様によりCLLocationManagerDelegateの関連メソッドに対して本SDKで監視しているiBeaconのリージョン情報も通知される可能性があります。
  また、iOSのアプリケーション内で観測できるリージョンの数には制限があります。（最大20個）
  本SDKではBeacapp管理画面において登録・設定されたアプリケーションと関連するiBeaconのUUIDのパターン数を観測するようにしています。
  （iBeaconのUUIDが３種類必要なときは3つを観測対象として登録します。）
  アプリケーション側で観測するリージョンの数と本SDK側で観測するiBeaconのリージョンの数に注意してください。

## 1.3.1 (May 12, 2016)
Features:
- アプリケーションがバックグランド状態でビーコンのエリアイン／アウトイベントがiOSから通知された際のイベント発火確認のための処理を向上

## 1.3.0 (May 11, 2016)
Features:
- [AWS SDK iOS Version 2.3.6](https://github.com/aws/aws-sdk-ios/tree/2.3.6)への対応
これにより、CocoaPods 0.39.0での利用が可能
- ログ情報に現在位置情報が取得できている場合をこれを定常的に付与
- BETA提供用のAPIを公開
  - ビーコンのレンジングコールバック
  - イベント発火確認のための検知間隔の設定
- Swiftからの利用のための[_Nullable syntax](https://developer.apple.com/swift/blog/?id=25)の適用

## 1.2.0 (February 5, 2016)
Features:
- カスタムログ送信機能
- ログへの任意情報付与機能
- 以下の不具合修正
  - 成り済まし検知オフ設定時に、位置情報を送信していなかった問題を修正

## 1.1.0 (April 28, 2015)
Features:
- AWS SDK 2.1.1対応
- ログ情報保存・アップロード処理修正
- アクティベーション情報の初期化メソッド追加

## 1.0.0 (November 11, 2014)
Features:
- SDKの初期化
- SDKのアクティベート
- CMSで設定したイベント情報の取得
- ビーコンの監視とレンジング
- ビーコンの監視の停止
- CMSで設定したイベントの発火通知
