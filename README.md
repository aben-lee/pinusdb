# 松果时序数据库(pinusdb)

松果时序数据库是一款针对中小规模（设备数少于10万台，每天产生的数据量少于10亿条）场景设计的时序数据库。以简单、易用、高性能为设计目标。使用SQL语句进行交互，拥有极低的学习、使用成本。虽然代码量少但也提供了丰富的功能、较高的性能。

# 文档
[松果时序数据库用户手册](http://www.pinusdb.cn/doc/manual_v3/index.html "用户手册")

# 性能
在i3-7100， 8G 内存，1TB HDD windows server 2016 环境下，每条数据8个字段，达到每秒20万条数据写入。
最高数据扫描、统计达到5000万条每秒。
历史数据整理后压缩，每个设备的数据顺序存放，极大提供数据查询性能。

# 压缩
松果时序数据库先将整数、浮点数按照差值压缩，然后将数据块以zlib压缩，极大提高压缩率。
不仅如此，我们还提供将浮点数按倍数放大后存储为整数，从而提高浮点数的压缩率。用户使用时以浮点数使用即可。  
real2 -> 倍数100，     取值范围[-999,999,999.99     ~ +999,999,999.99]   
real3 -> 倍数1000，    取值范围[-999,999,999.999    ~ +999,999,999.999]  
real4 -> 倍数10000，   取值范围[-999,999,999.9999   ~ +999,999,999.9999]  
real6 -> 倍数1000000， 取值范围[-999,999,999.999999 ~ +999,999,999.999999]

# 容量
在松果时序数据库中，每个表每天的数据存储为一个文件，超过写入时间窗口的文件会被压缩。
所以，数据容量仅限于服务器存储的容量，并且在大容量下还能保持极高的数据读取性能。  
并且，用户可以对数据文件进行管理（分离、附加、删除）等操作，方便对数据进行备份。

# 数据安全性
数据写入松果时序数据库中，首先会写commit日志，commit日志每3秒或写满64KB会刷一次磁盘，所以意外宕机，或服务器断电后只会丢失较少的数据。
松果时序数据库写数据文件时使用doublewrite，保证写入数据页时发送断电数据文件和数据页也不会损坏。

# 编译
松果时序数据库支持Windows以及Linux，代码中包含CMake文件，下载后需要配置boost库的包含目录和库目录、zlib的库目录即可编译成功。
若您需要已编译好的程序，请在 http://www.pinusdb.cn 网站相应的链接下载。

# 运行
松果时序数据库以windows服务的方式运行，运行前请先配置好服务配置文件config.ini 具体运行配置细节请参考文档： http://www.pinusdb.cn/doc/pdb_windows_install.html

# 二次开发
提供c/c++ SDK, .Net SDK, jdbc 驱动，未来还会支持restful及更多的二次开发接口。  
[c/c++ SDK](http://www.pinusdb.cn/doc/c_sdk/c_sdk_demo.html "c/c++ SDK")  
[.net SDK](http://www.pinusdb.cn/doc/dotnet_sdk/index.html ".net SDK")  
[jdbc](http://www.pinusdb.cn/doc/jdbc/index.html "jdbc")  
更多细节请参考：http://www.pinusdb.cn

# 交流
若您需要帮助或希望给我们反馈信息，请提交Issue、给我们发邮件：zhangquan@pinusdb.cn, 或者加QQ：445560747

# 赞助  
松果时序数据库所有功能都开源，您可以免费使用。由于产品的更新、升级也需要资金，所以我们提供如下的收费服务，若您有需要可以联系我们：  
1. 如果您有需要使用时序数据库产品的项目，我们可以给您提供技术方案的咨询等。  
2. 如果您正在使用松果时序数据库的产品，我们可以给您提供技术支持、维护、升级等。  
3. 如果您想了解我们数据库内部的实现原理，我们可以给您提供对应的培训。  
4. 如果您的需求比较特别，我们可以为您提供数据库的定制服务。  

当然，如果您觉得我们的产品不错，想鼓励一下，希望我们继续更新、升级，也可以通过微信扫码打赏来支持一下，就当请我们喝杯咖啡 : )  

![image](http://www.pinusdb.cn/upload/webimg/rewardme.png)   

