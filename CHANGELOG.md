# BeacappSDKforiOS CHANGELOG
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
