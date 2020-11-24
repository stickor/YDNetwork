
Pod::Spec.new do |s|
  s.name             = 'YDNetwork'
  s.version          = '0.0.1'
  s.summary          = 'YDNetwork. is prvite kit'

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/stickor/YDNetwork.git'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { '895148635@qq.com' => 'yangyinyin@yd.com.cn' }
  s.source           = { :git => 'https://github.com/stickor/YDNetwork.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'

  s.source_files = 'YDNetwork/Classes/**/*'
  
  # s.resource_bundles = {
  #   'YDNetwork' => ['YDNetwork/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
