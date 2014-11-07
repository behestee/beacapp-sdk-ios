# NSError クラスリファレンス

## 概要

NSError クラスに、エラー発生時の詳細情報を格納するクラスである。

-------
#### domain について

Beacapp では NSError の domain に以下の値を使用する。
**BeacappDomain**

-------

#### code について

Beacapp では以下のコードを使用する。
コード一覧表

|値    |define                            |意味                                  |
|------|----------------------------------|--------------------------------------|
|0     |JBCPCodeSuccess                   |成功                                  |
|1000  |JBCPCodeInvalidActivationKey      |アクティベーションキーが不正          |
|1001  |JBCPCodeNotInitializeYet          |SDK未初期化エラー                     |
|1002  |JBCPCodeDBError                   |DB関連のエラー                        |
|1003  |JBCPCodeNetworkError              |ネットワークラー                      |
|1004  |JBCPCodeAccessTokenExpired        |アクセストークンの有効期限切れ        |
|1005  |JBCPCodeNotSupportedBlutooth      |Bluetoothデバイスをサポートしていない |
|1006 | JBCPCodeInvalidSDKVersion         |SDKバージョン違い|
|1007 | JBCPCodeNeedsDelegateSet          |デリゲート未定義|
|1008 | JBCPCodeInvalidBackgroundRunning  | バックグランド実行は出来ない|

JBCPCodeInvalidBackgroundRunning = 1008 //バックグラウンド実行はできない
define で定義された値は JBCPError.h に定義されている。

--------

#### localizedDescription について

メソッド localizedDescription を使用することでローカライズされたエラー文言が取得可能である。
