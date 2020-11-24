
Pod::Spec.new do |s|
  s.name             = 'YDNetwork'                    #名称
  s.version          = '0.0.2'                           #版本号
  s.summary          = 'YDNetwork. 基于AFNetworking封装网络请求'

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/stickor/YDNetwork.git'    #主页,这里要填写可以访问到的地址，不然验证不通过
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'    #截图
  s.license          = { :type => 'MIT', :file => 'LICENSE' }                               #开源协议
  s.author           = { '895148635@qq.com' => 'yangyinyin@yd.com.cn' }                     #作者信息
  s.source           = { :git => 'https://github.com/stickor/YDNetwork.git', :tag => s.version.to_s }    #项目地址，这里不支持ssh的地址，验证不通过，只支持HTTP和HTTPS，最好使用HTTPS
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'       #多媒体介绍地址

  s.ios.deployment_target = '9.0'               #支持的平台及版本
  s.source_files = 'YDNetwork/Classes/**/*.{h,m}'          #代码源文件地址，**/*表示Classes目录及其子目录下所有文件，如果有多个目录下则用逗号分开，如果需要在项目中分组显示，这里也要做相应的设置
  
    #s.resource_bundles = {
     #   'YDNetwork' => ['YDNetwork/Assets/*.png']
    #}                  #

   # s.public_header_files = 'YDNetwork/Classes/**/*.h'  #公开头文件地址
   s.frameworks = 'UIKit', 'MapKit'     #所需的framework，多个用逗号隔开
    s.dependency 'AFNetworking'         #依赖关系，该项目所依赖的其他库，如果有多个需要填写多个s.dependency
    s.dependency 'YYCache'
end


