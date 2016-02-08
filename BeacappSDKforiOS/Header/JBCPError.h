//
//  JBCPError.h
//  BeacappSDKforiOS version1.0.0
//
//  Created by Akira Hayakawa on 2014/11/11.
//  Copyright (c) 2014年 JMA Systems Corp. All rights reserved.
//

#ifndef BeacappSDK_JPCPError_h
#define BeacappSDK_JPCPError_h

typedef NS_ENUM(NSUInteger, JBCPCode) {
    JBCPCodeSuccess = 0,    // 成功
    JBCPCodeInvalidActivationKey = 1000,    // アクティベーションキーが不正
    JBCPCodeNotInitializeYet = 1001,    // SDK未初期化エラー
    JBCPCodeDBError = 1002, // DB関連のエラー
    JBCPCodeNetworkError = 1003,    // ネットワークエラー
    JBCPCodeAccessCodeExpired = 1004,   // アクセストークンの有効期限切れ
    JBCPCodeNotSupportedBlutooth = 1005, // デバイスをサポートしていない
    JBCPCodeInvalidSDKVersion = 1006, //バージョン違い
    JBCPCodeNeedsDelegateSet = 1007, // デリゲート未定義
    JBCPCodeInvalidBackgroundRunning = 1008, //バックグラウンド実行はできない
    JBCPCodeInvalidData = 1009, // データ不整合
    JBCPCodeCannotStartLocation = 1010, // 位置情報サービスが開始できない
    JBCPCodeAWSError = 1011, // AWSでエラーが発生した
    JBCPCodeUnKnownError = 9999 // UnknownError
};



#endif
