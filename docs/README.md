﻿# All-In-One-Toolbox

GooglePlay: https://play.google.com/store/apps/details?id=imoblife.toolbox.full
Background: http://naotu.baidu.com/file/484dfc7d182509c049491858c20ef87b?token=d7bc58785b6f68ef

---------------------------------------------------------------------------------------------------
# 功能模块

*	base 基础类
    * base_titlebar标题栏
	* base_statusbar状态栏
	* base_toolbar工具栏

*	splash 欢迎界面
    * Admob预加载 （AdHelper.getInstance(ASplash.this);）
    * 定时提醒检查 （NotifierRemind.getInstance(this).check();）
    * 桌面快捷方式检查 （ShortcutUtil.checkShortcut(getApplicationContext());）
    * 通知栏检查 （Notifier.getInstance(getApplicationContext()).checkNotifier();）
    * 初始化白名单检查 （WhitelistHelper.getInstance(getApplicationContext()).check();）
    * LuckAd预加载 （LuckAdNew.get(getContext(), this).checkAd();）
    * 强制清除友盟配置 （clearUmeng();）
    * 扫描结果重置 （ScanManage.getInstance(this).reset();）
    * 友盟后台统计检查 （countManager.checkUpdateAlartRotation();）

*	main 主界面

*	clean 清理模块
	* cache 缓存
	* leftover 卸载残留
	    filepath.db中存在路径记录，类型为0会清理时会自动打勾，卸载时会有清理弹窗提醒；类型大于0，勾选时警告，卸载时无清理弹窗。
	* apk 安装包清理
	* trash 存储卡清理
		* temp 临时文件
		* thumb 缩略图
	* recycle 回收站
	    * 大于1MB的图片文件

*	privacy 隐私
	* history历史
	    * clipboard 剪切板
	    * browser 浏览器历史记录
	    * Gmail搜索记录
	    * GoogleEarth搜索记录
	    * Google Maps搜索记录
	* StorageAnalysis 磁盘分析
	* cmct通信清理
		* call通话
		* sms短信
    * Chrome
    * Youtube
    * QuickSearch
    * Downloads
    * Wifi
    * 预置列表中数据大于零的应用
        * com.alibaba.android.babylon
        * com.alibaba.mobileim
        * com.facebook.orca
        * com.facebook.katana
        * com.google.android.apps.plus
        * com.igg.android.im
        * com.immomo.momo
        * com.linkedin.android
        * com.snapchat.android
        * com.skype.raider
        * com.tencent.mm
        * com.tencent.mobileqq
        * com.twitter.android
        * com.whatsapp
        * jp.naver.line.android
        * kik.android
        * org.buffer.android
        * com.opera.mini.android
        * com.opera.browser

*	boost 加速模块
	* process进程
	* startup启动项

*   boost+ 超级加速
    * 支持4.4及以上系统

*   cooling 冷却机制
    * boost & boost+
          * 完整扫描，完整查杀则冷却
          * 超过五分钟则不冷却
          * 未扫描完全则不冷却
          * 未全选查杀则不冷却
          * 由主界面退出则不冷却
          * 由欢迎界面进入则不冷却

*	QuickBoost 快速优化
	* process目前只包括进程清理

*	toolbox 工具箱
	* install安装
	* uninstall卸载
	* slimming系统精简
		* slimming_bin回收站
	* bakrst备份还原
		* backup备份
		* restore还原
	* app2sd
	* file文件管理
	* startup_add启动项添加
	* plugin插件

*	prokey 专业版

*	info 系统信息

*	setting 设置界面

*	whitelist 进程白名单

*	ignorelist 清理白名单

*	feedback 反馈

*	share 分享弹窗

*	rate 评论弹窗

*	about 关于

*	notifier 通知栏
	* 每10分钟刷新一次，解锁时立即刷新

*	widget 小部件
	* widget_custom自定义小部件
	* widget_expand扩展页面

*	shortcut 快捷方式
	* shortcut_boost加速动画页面

*	schedule 定时检测

*	track 数据跟踪
	* GoogleAnalytics谷歌分析
	* UmengCount友盟统计

*	LauncheMessage 推送消息

*	CPU Cooler

	* 1 开启CPU监测

	* 2.1 电池温度小于43

	* 2.1.1 一天监测两次

	* 2.2 电池温度大于43

	* 2.2.1 每分钟检测一次

	* 3 某个进程CPU占用率超过40%

	* 4 某个进程电池使用量大于1%

	* 5 非当前运行进程

	* 6 提示CPU占用过高

*	RateDialog 评论弹窗
	* http://naotu.baidu.com/file/0d0e678983395dd6ed8cc7957db3ccb8?token=4d98ecc27c61b475

*  Immerse 沉浸模式
    * 支持Android 4.4及以上(sdk>=19)

*	Drawable（保留资源，请勿删除以下模块图片）

	* tools_install.png
	* tools_uninstall.png
	* tools_backuprestore.png
	* system_lose.png
	* tools_tranfer.png
	* tools_startupmanager.png
	* tools_startupadd.png
	* tools_file.png

*	NativeAd 广告页面

*	InterstitialAd 全屏广告
	* 说明：未安装谷歌市场(com.android.vending, market.android.com)，点击礼物盒子打开全屏广告。
	* 时机：1.点击礼物盒子时才加载。
	* 位置：Main、Clean、Boost标题栏礼物盒子图标。
	* 用户：未安装Google Play的用户。
	* 机制：

*	FacebookAd
	* 说明：Clean、Boost结果页面列表嵌入广告条目。
	* 时机：1.首次出现结果页面时加载一次。2.解锁屏幕後广告被置空，再次显示结果页时重新加载一次。 3.点击广告后后台加载一条新广告 4.退出主程序根据频率更新陈旧广告
	* 位置：Clean、Boost结果页面。
	* 用户：所有用户（MotoX，S5测试与是否安装Facebook或是否登陆Facebook无关）
	* 机制：
		*	1.广告缓存在AIO系统缓存中，AIO系统缓存清除后图片需要重新加载。
		*	2.每次加载一条广告


*	LuckAd 原生广告（目前计划尝试使用42，然后调优更新广告时间）

	* 实现机制I：   YeahMobi的SDK调用，请求15个广告，点击礼物盒子显示广告，依次循环显示。
	* 实现机制II：  Yeahmobi的API机制，每次加载5个，并在后台提前转换5个GP链接
	* 实现机制III： Glispa的API机制，每次加载5个广告，并在后台提前转换5个GP链接
	* 实现机制IV：  Yeahmobi的API和Glispa的API合并机制，实现机制II和机制III
	* 实现机制V：   Yeahmobi的API和Glispa的API混合机制，每次进入程序，两者交替调用，但不同时出现。
	* 实现机制VI：  Glispa的API机制，每次只加载5个广告，但只在后台提前转换1个GP链接，剩余的在每次点击礼物盒子的时候加载，点击一下加载下一个。
	* 实现机制VII： Glispa的API机制，每次只加载5个广告，但只在后台不提前转换任何GP链接，点击才加载。
	* 实现机制VIII：Glispa的API机制，每次加载5个广告，首次进入或者进入广告列表为空时，在后台提前转换5个GP链接。以后在进入程序，根据时间限制，重新加载5个新广告，但只在后台提前转换1个GP链接。用户点击礼物盒子时，加载下一个GP链接。
	* 实现机制IX：与机制VII相似，但引入缓存机制，减少不必要的重复加载。

*	GoogleAnalytics(4.0)
    * 欢迎界面100%统计
    * 其他界面关联设置中的‘软件改进’，勾选则统计，否则不统计。

*   锁屏充电界面(LockScreenActivity)
    * 文档http://aypdar.axshare.com

---------------------------------------------------------------------------------------------------
# 代码规范补充：

* 自定义方法不要和系统方法同名
* ModernAsyncTask主要用作主功能，AsyncTaskEx主要用作网络操作
* 建议把颜色等资源复制到别的库后， 加一个前缀。  现在资源有些id对应多个res文件
* 新加代码尽量置于原有代码之后
* 防御式编程，过滤掉空指针等错误。对没有把握的功能，可以try catch暂时加以保护
* 提高代码可读性，提交可读性。尽量每个任务相关文件整理为单词提交，便于review。
* 新模块统一定一个内部模块名



---------------------------------------------------------------------------------------------------
# 谷歌分析对应页面统计名称

模块名	GA名字
欢迎界面	v6_splash
主页	v6_homepage
普通清理界面	v6_clean
高级清理	v6_advanced_clean
清理设置界面	v6_clean_settings
清理白名单	v6_clean_whitelist
清理还原中心	v6_clean_restore_center
清理结果界面	v6_clean_result
占用分析	v6_storage_analysis
加速界面	v6_boost
超级加速	v6_boost_plus
加速白名单	v6_boost_whitelist
加速结果界面	v6_boost_result
插件list view	v6_plugins_list
插件grid	v6_plugins_grid
工具界面-list view	v6_tools_list
工具界面-grid	v6_tools_grid
CPU降温	v6_cpu_cooler
批量安装	v6_install
批量卸载	v6_uninstall
备份	v6_backup
还原	v6_restore
系统应用卸载	v6_preinstalled_app
系统应用卸载还原中心	v6_preinstalled_restore
软件搬家手机界面	v6_app2sd_phone
软件搬家SD卡界面	v6_app2sd_sd
开机加速用户应用	v6_boot_speedup_user
开机加速系统应用	v6_boot_speedup_system
添加启动项主界面	v6_add_startup_main
添加启动项用户应用界面	v6_add_startup_user
添加启动项系统应用界面	v6_add_startup_system
文件管理器	v6_file_manager
文件管理器-多选	v6_file_manager_multiselect
备份弹窗	v6_backup_window
设置界面	v6_settings
暗色通知栏	v6_custom_notification_dark
亮色通知栏	v6_custom_notification_light
自定义通知栏	v6_custom_notification
卸载残留提醒	v6_leftover_dialogue
1X1小部件	v6_1x1_widget
4x1小部件自定义界面	v6_4x1_widget_custom
快捷方式选择界面	v6_pick_shortcut
clean快捷方式	v6_clean_shortcut
boost快捷方式	v6_boost_shortcut
通知栏ram	v6_notificationbar_ram
系统信息	v6_system_info
自定义主页	v6_diy_homepage
关于	v6_about
关于（用户手册）	v6_about_user_manual
关于（FAQ）	v6_about_faq
关于（权限）	v6_about_permission
关于（翻译）	v6_about_translator


---------------------------------------------------------------------------------------------------
# android.os.Build.java

1   BASE	                    October 2008: The original, first, version of Android.
2   BASE_1_1	                February 2009: First Android update, officially called 1.1.
3   CUPCAKE	                    May 2009: Android 1.5.
5   DONUT	                    September 2009: Android 1.6. / ECLAIR	November 2009: Android 2.0
6   ECLAIR_0_1	                December 2009: Android 2.0.1
7   ECLAIR_MR1	                January 2010: Android 2.1
8   FROYO	                    June 2010: Android 2.2
9   GINGERBREAD	                November 2010: Android 2.3
10  GINGERBREAD_MR1	            February 2011: Android 2.3.3.
11  HONEYCOMB	                February 2011: Android 3.0.
12  HONEYCOMB_MR1	            May 2011: Android 3.1.
13  HONEYCOMB_MR2	            June 2011: Android 3.2.
14  ICE_CREAM_SANDWICH	        October 2011: Android 4.0.
15  ICE_CREAM_SANDWICH_MR1	    December 2011: Android 4.0.3.
16  JELLY_BEAN	                Android 4.1.
17  JELLY_BEAN_MR1              November 2012: Android 4.2, Moar jelly beans!
18  JELLY_BEAN_MR2              July 2013: Android 4.3, the revenge of the beans.
19  KITKAT                      October 2013: Android 4.4, KitKat, another tasty treat.
20  KITKAT_WATCH                Android 4.4W: KitKat for watches, snacks on the run.
21  LOLLIPOP                    Android 5.0 Lollipop, 2014/6/25                                     https://zh.wikipedia.org/wiki/Android_Lollipop
22  LOLLIPOP_MR1                Lollipop with an extra sugar coating on the outside!
23  Marshmallow                 Android 6.0 Marshmallow, 2015/10                                    https://zh.wikipedia.org/wiki/Android_Marshmallow
24  Nougat                      Android 7.0 Nougat, 2016/3/9                                        https://zh.wikipedia.org/wiki/Android_Nougat



---------------------------------------------------------------------------------------------------
# IconFont

*   FontCreator打开ttf文件，右键新建，粘贴图标
*   右键属性，修改映射值为上一图标的映射值+1
*   Toolbox.java文件中Icon类中新增一条枚举：AIO_ICON_NAME('\uE907')
*   Xml中，引用IconicsTextView,IconicsImageView,IconicsButton等组件（推荐使用IconicsTextView，兼容性好，占用内存小），
    其中IconicsTextView的text属性指定"{AIO_ICON_NAME}"，IconicsImageView的iiv_icon属性指定图标 AIO_ICON_NAME，iiv_color指定颜色。
*   代码中，IconFontDrawable drawable = new IconFontDrawable(context)
                                        .icon(Toolbox.Icon.AIO_ICON_NAME)
                                        .colorRes(colorRes)
                                        .contentRatio(1 / 1.7f)
                                        .sizeDp(40);


---------------------------------------------------------------------------------------------------
# 插件确认自身是否为注册版流程

0.AIO:ProkeyHelper.java:

        //Prokey设置项和广播定义
        public static final String PROKEY_PREFERENCE_KEY =  "isPro";
        public static final String PLUGIN_ACTION_PROKEY_QUERY =  "com.pro.provider";
        public static final String PLUGIN_ACTION_PROKEY_RESULT =  "com.pro.provider.result";

1.Applock:Splash.java:

        //若插件非PRO版本，则发送广播询问AIO状态
        public void checkPro() {
            if (!PreferenceHelper.isPro(this)) {
                sendBroadcast(new Intent(PLUGIN_ACTION_PROKEY_QUERY));
            }
        }

2.AIO:CommandReceiver.java:

        //若AIO为PRO版本，则发送广播通知所有插件
        else if (action.equals(PLUGIN_ACTION_PROKEY_QUERY)) {
            if (PreferenceHelper.isPro(context)) {
                Intent i = new Intent(PLUGIN_ACTION_PROKEY_RESULT);
                context.sendBroadcast(i);
            }
        }

3.Applock:KeepAliveReceiver.java:

        //若插件确认AIO为PRO版，则将自身注册为PRO版。
        if (action.equals(PLUGIN_ACTION_PROKEY_RESULT)) {
			PreferenceHelper.setBoolean(context, PROKEY_PREFERENCE_KEY, true);
		}


---------------------------------------------------------------------------------------------------
# SkinManager

1   XML中
    1.1 增加属性(在相应布局的RootView)：
    xmlns:skin="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    tools:ignore="missingPrefix"

    1.2 增加颜色(res/value/skin_colors.xml)：
    <color name="boost_plus_anim_window_color">@color/white</color>

    1.3 替换颜色
    skin:enable="true"
    android:background="@color/boost_plus_anim_window_color"

    1.4 增加相应颜色(Toolbox_skin_dark/res/values/colors.xml)：
    <color name="boost_plus_anim_window_color">#FF102031</color>是ss

    1.5 Toolbox_skin中build apk并复制到Toolbox/assets/skin/skin_dark_[versioncode]

    1.6 卸载重新运行Toolbox验证

2   代码中

    2.1 base.util.ViewUtil.setBackgroundDrawable([VIEW], SkinManager.getInstance().getDrawable(R.drawable.[X]));

*   用style里面的background 和 textcolor，xml+skin：enable的方式不识别


---------------------------------------------------------------------------------------------------
# filepath.db修改

*   数据修改：1.在Web端修改，导出filepath.import.txt给Android端 2.Android端导入并替换/assets/leftover/filepath.db
    *   1 Web(filepath.db)  -->  2 filepath.import.txt  -->   3 Android(filepath.encrypted.db)

*   文件规范 filepath.import.txt:

    *   采用txt（uft-8）格式同步数据
    *   _filePath, _pkgName的值需要trim以规避重复问题
    *   _filePath为相对路径,且以/开头
    *   _filePath(_id), pkgName(id)顺序和之前版本保持一致
    *   filePath(_id)最大值应该与belongTo(filePathId_)最大值相等
    *   pkgName(_id)最大值应该与belongTo(pkgNameId_)最大值相等

    *   示例v2
        filePath,_id,_filePath,_categoryId,_filePathDesc,1,"/test_filepath_1",0,"test file path's desc"
        pkgName,_id,_pkgName,1,"com.test.package.name1"
        pkgName,_id,_pkgName,2,"com.test.package.name2"
        belongTo,filePathId_,pkgNameId_,1,1
        belongTo,filePathId_,pkgNameId_,1,2

    *   示例v1
        INSERT INTO filePath(_filePath, _categoryId, _filePathDesc) VALUES('/capsanotes',      0, 'Capsa Notes');
        INSERT INTO pkgName(_pkgName) values('com.handmark.tweetcaster.premium');
        INSERT INTO belongTo(filePathId_, pkgNameId_) values(   1,   566);

    *   示例v3
        {filePath: {_filePath: '/capsanotes', _categoryId: 0, _filePathDesc: 'Capsa Notes'}}
        {pkgName: { _pkgName: 'com.handmark.tweetcaster.premium'}}
        {belongTo: {filePathId_: 1, pkgNameId_: 566}}

*   辅助方法验证原始数据
    *   debug版本
    *   设置 - 软件改进 - 启用
    *   关于界面 - 长按Logo三次
    *   长按分享选项
    *   查看当前数据库txt版本文件：/sdcard/filepath.export.txt


*   附录说明：
    * 问号开头的路径或包名，是有待进一步处理的存疑数据，程序中会忽略。
    * Android手机中文件夹如果只是大小写差异，会被当作一个路径。
    * Web与Android端AES加密方式不匹配，所以加密未能直接在Web端实现。
    * filepath.db发布前建议执行SqliteSpy的Execute - Vacuum Database优化体积


---------------------------------------------------------------------------------------------------
# SVG替换资源

*   Toolbox_BaseLibrary\svg_a 下替换相应资源

*   运行脚本：aio_gradle -> Tasks -> svg -> svgAssemble

*   预览后删除此文件夹：Toolbox_BaseLibrary\res\drawable-svg


---------------------------------------------------------------------------------------------------
# 打正式包注意事项

*   修改打包签名文件位置：Toolbox\build.gradle\signingConfigs\release\storeFile file("X:/.../imoblife.keystore")

*   修改打包签名文件位置：Toolbox_skin\aio_skin_dark\build.gradle\signingConfigs\release\storeFile file("X:/.../imoblife.keystore")

*   如果version_code +1，修改/Toolbox/assets/skin/skin_dark_[version_code]

*   运行 Gradle/aio_gradle/Tasks/andresguard/resguard/task/resguardGooglePlayRelease编译

*   复制apk：Toolbox/build/outputs/apk/AndResGuard_Toolbox-GooglePlay-release/Toolbox-GooglePlay-release_signed_7zip_aligned.apk

*   复制mapping: Toolbox/output/mapping/mapping.txt

*   如果打包Toolbox_skin重复上面步骤

---------------------------------------------------------------------------------------------------
# 语言资源提交检查要点

*   100% 中的%替换为\u0025

*   需要空格的地方替换为\u0020

*   ' 确保替换为\'

*   确保values-xx中的语言在values中存在（即values是全集,values-xx是子集）

*   阅读xml语法规则 http://www.w3school.com.cn/xml/xml_syntax.asp

*   提交的res中只保留string.xml string-array-xml用户改动的，剔除诸如style.xml dimens.xml values-21等用户未改动的

*   %1$s %1s等改动后确保界面中检查后提交（这个语法有多种形式，目前没有一劳永逸的排查方法。例如  %1$s, %1s, %s, %1...$s, %1...s (...为类阿拉伯语)）

---------------------------------------------------------------------------------------------------
# 多语言打包

*   打开项目All-In-One-Toolbox/Toolbox_Remote_Res
*   覆盖values下相应语言strings.xml，strings-arrays.xml，strings-filemanager.xml
*   覆盖values下public.xml为最新版，注释掉报错项
*   确保build.gradle文件compileSdkVersion，buildToolsVersion，versionCode，versionName与AIO一致
*   确保setting.xml，strings_notfortranslate.xml中string在public中存在
*   修改All-In-One-Toolbox/Toolbox/assets/lang_config.json中相应语言的update_time