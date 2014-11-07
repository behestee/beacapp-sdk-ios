Pod::Spec.new do |s|
  s.name         = "BeacappSDKforiOS"
  s.version      = "0.9.1"
  s.summary      = "iOS Library for Beacapp"

  s.homepage     = "http://www.beacapp.com"

  s.license      = {
    :type => 'Copyright',
    :text => <<-LICENSE
      Copyright 2014 JMA Systems Corp., All Rights Reserved.
      LICENSE
  }

  s.author       = { "JMA Systems Corp.," => "Akira_Hayakawa@jmas.co.jp" }
  s.platform     = :ios, "7.0"

  s.source       = { :git => "https://github.com/JMASystems/beacapp-sdk-ios.git", :tag => "0.9.1" }
  s.public_header_files = "BeacappSDKforiOS/Header/*.h"
  s.source_files =  'BeacappSDKforiOS/Header/*.h'

  s.preserve_paths = "BeacappSDKforiOS/staticLib/libBeacappSDKforiOS.a"
  s.vendored_libraries = "BeacappSDKforiOS/staticLib/libBeacappSDKforiOS.a"

  s.frameworks = "CoreLocation", "CoreBluetooth","SystemConfiguration"
  s.library   = "BeacappSDKforiOS"
  
  s.requires_arc = true

  s.xcconfig =  { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/BeacappSDKforiOS/BeacappSDKforiOS/staticLib"', 'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/Headers/BeacappSDKforiOS"'}

  s.dependency "AWSiOSSDKv2/Kinesis", '2.0.12'
  s.dependency "AWSiOSSDKv2/DynamoDB", '2.0.12'
  s.dependency "AWSiOSSDKv2/S3", '2.0.12'
  s.dependency "FMDB", '2.4'

end
