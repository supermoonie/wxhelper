# wxhelper
wechat hook 。PC端微信逆向学习。支持3.8.0.41，3.8.1.26版本。
#### 免责声明:
本仓库发布的内容，仅用于学习研究，请勿用于非法用途和商业用途！如因此产生任何法律纠纷，均与作者无关！

#### 项目说明：
本项目是个人学习学习逆向的项目，主要参考   https://github.com/ljc545w/ComWeChatRobot ，在此基础上实现了微信的的其它版本的部分内容。

#### 使用说明：
支持的版本3.8.0.41，3.8.1.26。
src:主要的dll代码
tool：简单的注入工具，一个是控制台，一个是图形界面。
python: 简单的服务器，用以接收消息内容。
release：编译好的dll。

0.首先安装对应的微信版本，主分支是3.8.0.41版本，3.8.1.26分支对应3.8.1.26版本。  
1.通过cmake构建成功后，将wxhelper.dll注入到微信，本地启动tcp server，监听19088端口。  
2.通过http协议与dll通信，方便客户端操作。  
3.接口的url为http://127.0.0.1:19088，注入成功后，直接进行调用即可。  
4.特别注意数据库查询接口需要先调用获取到句柄之后，才能进行查询。  
5.相关功能只在win11环境下进行简单测试，其他环境无法保证。  
6.注意个别接口在3.8.0.41版本没有实现，具体参考源码。  
7.对应分支接口文档都是支持指定版本的，其他版本不支持，请特别注意版本。

#### 编译环境

Visual Studio 2022(x86)  

Visual Studio code   

cmake  

vcpkg
#### 构建步骤
以下是在vscode中操作，vs中的操作类似。  
1.安装vcpkg，cmake，vscode  

2.安装相应的库，如果安装的版本不同，则根据vcpkg安装成功后提示的find_package修改CMakeLists.txt内容即可。或者自己编译。
```
    vcpkg  install mongoose  
    vcpkg  install nlohmann-json
```
3.vscode 配置CMakePresets.json,主要设置CMAKE_C_COMPILER 和CMAKE_CXX_COMPILER 为cl.exe.参考如下
```
 {
            "name": "x86-release",
            "displayName": "x86-release",
            "description": "Sets Ninja generator, build and install directory",
            "generator": "Ninja",
            "binaryDir": "${sourceDir}/out/build/${presetName}",
            "architecture":{
                "value": "x86",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_C_COMPILER": "cl.exe",
                "CMAKE_CXX_COMPILER": "cl.exe",
                "CMAKE_BUILD_TYPE": "Release",
                "CMAKE_INSTALL_PREFIX": "${sourceDir}/out/install/${presetName}",
                "CMAKE_TOOLCHAIN_FILE": {
                    "value": "C:/soft/vcpkg/scripts/buildsystems/vcpkg.cmake",
                     "type": "FILEPATH"
                  }
            },
            "environment": {

            }
          
        }
```
4.vscode中右键configure all  projects,在Terminal中点击Run Task，如没有先配置build任务，然后运行即可   

5.命令行注入工具，注入命令 
``` javascript
    //-i  注入程序名   -p 注入dll路径   
    // -u 卸载程序名   -d 卸载dll名称
    //注入  
    ConsoleInject.exe  -i demo.exe -p E:\testInject.dll
    //卸载 
    ConsoleInject.exe  -u demo.exe -d  testInject.dll
```

#### 更新说明
2022-12-26 ： 增加3.8.1.26版本支持。  

2022-12-29 ： 新增提取文字功能。  

2023-01-02 ： 退出微信登录。  

2023-01-31 ： 新增修改群昵称（仅支持3.8.1.26）。  

2023-02-01 ： 新增拍一拍（仅支持3.8.1.26）。  

2023-02-04 ： 新增群消息置顶和取消置顶。  

2023-02-06 ： 新增确认收款。  

2023-02-08 ： 新增朋友圈消息。

#### 功能预览：
0.检查是否登录  
1.获取登录微信信息  
2.发送文本  
5.发送图片  
6.发送文件  
9.hook消息  
10.取消hook消息  
11.hook图片  
12.取消hook图片    
17.删除好友    
25.获取群成员  
27.删除群成员  
28.增加群成员  
31.修改群昵称  
32.获取数据库句柄  
34.查询数据库  
40.转发消息  
44.退出登录  
45.确认收款  
46.联系人列表  
47.获取群详情  
48.获取解密图片  
49.图片提取文字ocr  
50.拍一拍  
51.群消息置顶消息  
52.群消息取消置顶  
53.朋友圈首页
54.朋友圈下一页
### 接口文档：


#### 0.检查微信登录**
###### 接口功能
> 检查微信是否登录

###### 接口地址
> [/api/?type=0](/api/?type=0)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1 成功, 0失败|
|result|string|成功提示|
|data|string|响应内容|

###### 接口示例
入参：
``` javascript
```
响应：
``` javascript
{
    "code": 1,
    "result": "ok"
}
```

#### 1.获取登录用户信息**
###### 接口功能
> 获取登录用户信息

###### 接口地址
> [/api/?type=1](/api/?type=1)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1 成功, 0失败|
|result|string|成功提示|
|data|object|响应内容|
|account|string|账号|
|bigImage|string|头像大图|
|city|string|城市|
|country|string|国家|
|currentDataPath|string|当前数据目录|
|dataRootPath|string|根目录|
|dataSavePath|string|保存目录|
|mobile|string|手机|
|name|string|昵称|
|province|string|省|
|smallImage|string|小头像|
|wxid|string|wxid|

###### 接口示例
入参：
``` javascript
```
响应：
``` javascript
{"code":1,"data":{"account":"xx","bigImage":"https://wx.qlogo.cn/mmhead/ver_1xx","city":"xx","country":"CN","currentDataPath":"xxx","dataRootPath":"C:\\xx","dataSavePath":"C:\\xx","mobie":"13949175447","name":"xx","province":"xx","smallImage":"xx","wxid":"xx"},"result":"OK"}
```




#### 2.发送文本消息**
###### 接口功能
> 发送文本消息

###### 接口地址
> [/api/?type=2](/api/?type=2)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 接收人wxid |
|msg|true |string|消息文本内容|

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,不为0成功, 0失败|
|result|string|成功提示|


###### 接口示例

入参：
``` javascript
{
    "wxid": "filehelper",
    "msg": "1112222"
}
```
响应：
``` javascript
{"code":345686720,"result":"OK"}
```



#### 5.发送图片消息**
###### 接口功能
> 发送图片消息

###### 接口地址
> [/api/?type=5](/api/?type=5)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 接收人wxid |
|imagePath|true |string|图片路径|

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,不为0成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "wxid": "filehelper",
    "imagePath": "C:/Users/123.png"
}
```
响应：
``` javascript
{"code":345686724,"result":"OK"}
```



#### 6.发送文件消息**
###### 接口功能
> 发送文件

###### 接口地址
> [/api/?type=6](/api/?type=6)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 接收人wxid |
|filePath|true |string|文件路径|

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "wxid": "filehelper",
    "filePath": "C:/Users/123.txt"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```


#### 9.hook消息**
###### 接口功能
> hook接收文本消息，图片消息，群消息.该接口将hook的消息通过tcp回传给本地的端口

###### 接口地址
> [/api/?type=9](/api/?type=9)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|port |ture |string| 本地服务端端口，用来接收消息内容 |
|ip |ture |string| 服务端ip地址，用来接收消息内容，可以是任意ip,即tcp客户端连接的服务端的ip (3.8.1.26版本)|

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "port": "19099"
    "ip":"127.0.0.1"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```


#### 10.取消hook消息**
###### 接口功能
> 取消hook消息

###### 接口地址
> [/api/?type=10](/api/?type=10)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|



###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript

```
响应：
``` javascript
{"code":1,"result":"OK"}
```

#### 11.hook图片**
###### 接口功能
> hook图片原始内容，不推荐该接口，可以使用图片查询接口

###### 接口地址
> [/api/?type=11](/api/?type=11)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|imgDir |ture |string| 图片保存的目录 |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "imgDir":"C:\\other"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```


#### 12.取消hook图片**
###### 接口功能
> 取消hook图片

###### 接口地址
> [/api/?type=12](/api/?type=12)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|



###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript

```
响应：
``` javascript
{"code":1,"result":"OK"}
```

#### 17.删除好友**
###### 接口功能
> 删除好友

###### 接口地址
> [/api/?type=17](/api/?type=17)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 好友wxid |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "wxid":"wxid_o"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```



#### 25.获取群成员**
###### 接口功能
> 获取群成员

###### 接口地址
> [/api/?type=25](/api/?type=25)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 群id |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|
|data|object|返回内容|
|admin|string|群主id|
|chatRoomId|string|群id|
|members|string|群成员id以^分隔|


###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"123@chatroom"
}
```
响应：
``` javascript
{"code":1,"data":{"admin":"wxid","chatRoomId":"123@chatroom","members":"wxid_123^Gwxid_456^Gwxid_45677"},"result":"OK"}
```



#### 27.删除群成员**
###### 接口功能
> 删除群成员

###### 接口地址
> [/api/?type=27](/api/?type=27)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 群id |
|memberIds |ture |string| 成员id，以,分割 |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"34932563384@chatroom",
    "memberIds":"wxid_oyb662qhop4422"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```



#### 28.增加群成员**
###### 接口功能
> 增加群成员

###### 接口地址
> [/api/?type=28](/api/?type=28)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 群id |
|memberIds |ture |string| 成员id，以,分割 |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"34932563384@chatroom",
    "memberIds":"wxid_oyb662qhop4422"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```


#### 31.修改自身群昵称**
###### 接口功能
> 修改群名片

###### 接口地址
> [/api/?type=31](/api/?type=31)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 群id |
|wxid |ture |string| 自己的id，只能修改自己的群名片 |
|nickName |ture |string| 修改的昵称 |

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"34932563384@chatroom",
    "wxid":"wxid_272211111121112",
    "nickName":"昵称test"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```



#### 32.获取数据库句柄**
###### 接口功能
> 获取sqlite3数据库句柄

###### 接口地址
> [/api/?type=32](/api/?type=32)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|



###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|
|data|array|返回数据|
|databaseName|string|数据库名称|
|handle|int|数据库句柄|
|tables|array|表信息|
|name|string|表名|
|rootpage|string|rootpage|
|sql|string|sql|
|tableName|string|tableName|


###### 接口示例
入参：
``` javascript

```
响应：
``` javascript
{
  "data": [
    {
      "databaseName": "MicroMsg.db",
      "handle": 119561688,
      "tables": [
        {
          "name": "Contact",
          "rootpage": "2",
          "sql": "CREATE TABLE Contact(UserName TEXT PRIMARY KEY ,Alias TEXT,EncryptUserName TEXT,DelFlag INTEGER DEFAULT 0,Type INTEGER DEFAULT 0,VerifyFlag INTEGER DEFAULT 0,Reserved1 INTEGER DEFAULT 0,Reserved2 INTEGER DEFAULT 0,Reserved3 TEXT,Reserved4 TEXT,Remark TEXT,NickName TEXT,LabelIDList TEXT,DomainList TEXT,ChatRoomType int,PYInitial TEXT,QuanPin TEXT,RemarkPYInitial TEXT,RemarkQuanPin TEXT,BigHeadImgUrl TEXT,SmallHeadImgUrl TEXT,HeadImgMd5 TEXT,ChatRoomNotify INTEGER DEFAULT 0,Reserved5 INTEGER DEFAULT 0,Reserved6 TEXT,Reserved7 TEXT,ExtraBuf BLOB,Reserved8 INTEGER DEFAULT 0,Reserved9 INTEGER DEFAULT 0,Reserved10 TEXT,Reserved11 TEXT)",
          "tableName": "Contact"
        }
      ]
    }
  ],
  "result": "OK"
}
```



#### 34.查询数据库**
###### 接口功能
> 查询数据库

###### 接口地址
> [/api/?type=34](/api/?type=34)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|dbHandle |ture |int| 句柄 |
|sql |ture |string| sql语句 |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|
|data|array|返回数据|



###### 接口示例
入参：
``` javascript
{
    "dbHandle": 219277920,
    "sql":"select * from MSG where MsgSvrID=8985035417589024392"
}
```
响应：
``` javascript
{"code":1,"data":[["localId","TalkerId","MsgSvrID","Type","SubType","IsSender","CreateTime","Sequence","StatusEx","FlagEx","Status","MsgServerSeq","MsgSequence","StrTalker","StrContent","DisplayContent","Reserved0","Reserved1","Reserved2","Reserved3","Reserved4","Reserved5","Reserved6","CompressContent","BytesExtra","BytesTrans"],["6346","24","8985035417589024392","1","0","0","1670897832","1670897832000","0","0","2","1","778715089","wxid_1222","112","","0","2","","","","","","","CgQIEBAAGkEIBxI9PG1zZ3NvdXJjZT4KCTxzaWduYXR1cmU+djFfSFFyeVAwZTE8L3NpZ25hdHVyZT4KPC9tc2dzb3VyY2U+ChokCAISIDU5NjI1NjUxNWE0YzU2ZDQxZDJlOWMyYmIxMjFhNmZl",""]],"result":"OK"}
```


#### 40.转发消息**
###### 接口功能
> 直接转发消息

###### 接口地址
> [/api/?type=40](/api/?type=40)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 消息接收人wxid |
|msgid |ture |number| 消息id，hook消息接口中返回的消息id |


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,非0成功|
|result|string|成功提示|


###### 接口示例
入参：
``` javascript
{
    "wxid": "filehelper",
    "msgid":7215505498606506901
}
```
响应：
``` javascript
{"code":4344,"result":"OK"}
```


#### 44.退出登录**
###### 接口功能
> 退出登录微信，相当于直接退出微信，跟手动退出比，少了重新打开登录的一步，dll注入后也会随微信关闭而关闭。调用后不能再继续操作dll。

###### 接口地址
> [/api/?type=44](/api/?type=44)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|



###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,非0成功|
|result|string|成功提示|




###### 接口示例
入参：
``` javascript

```
响应：
``` javascript
{"code":4344,"result":"OK"}
```


#### 45.确认收款**
###### 接口功能
> 收到转账消息后，自动收款确认。type=49 即是转账消息。

###### 接口地址
> [/api/?type=45](/api/?type=45)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid|string|转账人微信id，从hook的消息中获取|
|transcationId|string|从hook的消息中获取对应的字段内容。|
|transferId|string|从hook的消息中获取对应的字段内容。|

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功|
|result|string|成功提示|




###### 接口示例
入参：
``` javascript
{
    "wxid":"wxid_agz5q76f11112",
    "transcationId":"10000500012302060002831233124719620",
    "transferId":"10000500012023020619112332136412"
}
```
响应：
``` javascript
{"code":1,"result":"OK"}
```

#### 46.联系人列表**
###### 接口功能
> 联系人列表

###### 接口地址
> [/api/?type=46](/api/?type=46)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|


###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|
|data|array|返回内容|
|customAccount|string|自定义账号|
|delFlag|int|删除标志|
|type|int|好友类型|
|userName|string|用户名称|
|verifyFlag|int|验证|
|wxid|string|wxid|



###### 接口示例
入参：
``` javascript
{
    "wxid": "filehelper",
    "msgid":7215505498606506901
}
```
响应：
``` javascript
{"code":1,"data":[{"customAccount":"custom","delFlag":0,"type":8388611,"userName":"昵称","verifyFlag":0,"wxid":"wxid_123pcqm22"}]}
```


#### 47.群详情**
###### 接口功能
> 获取群详情

###### 接口地址
> [/api/?type=47](/api/?type=47)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 群id |

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|
|data|object|返回内容|
|admin|string|群主id|
|chatRoomId|int|群id|
|notice|int|通知|
|xml|string|xml|



###### 接口示例
入参：
``` javascript
{
    "wxid": "filehelper",
    "msgid":7215505498606506901
}
```
响应：
``` javascript
{"code":1,"data":{"admin":"123","chatRoomId":"123@chatroom","notice":"1222","xml":""},"result":"OK"}
```



#### 48.获取解密图片**
###### 接口功能
> 获取解密图片

###### 接口地址
> [/api/?type=48](/api/?type=48)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|imagePath |ture |string| 图片路径 |
|savePath |ture |string| 保存路径 |

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, 0失败|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript
{
    "imagePath":"C:\\3a610d7bc1cf5a15d12225a64b8962.dat",
    "savePath":"C:\\other"
}

```
响应：
``` javascript
{"code":1,"result":"OK"}
```



#### 49.提取文字**
###### 接口功能
> 提取图片中的文字

###### 接口地址
> [/api/?type=49](/api/?type=49)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|imagePath |ture |string| 图片路径 |

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,0成功, -1失败，1 2 则是缓存或者正在进行中需再调用一次|
|result|string|成功提示|
|text|string|提取的相应文字|


#### 50.拍一拍**
###### 接口功能
> 群里拍一拍用户

###### 接口地址
> [/api/?type=50](/api/?type=50)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 微信群聊id |  
|wxid |ture |string| 要拍的用户wxid，如果使用用户自定义的微信号，则不会显示群内昵称 |
###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, -1失败|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"123331@chatroom",
    "wxid":"wxid_123456"
}

```
响应：
``` javascript
{"code":1,"result":"OK"}
```


#### 51.群内消息置顶**
###### 接口功能
> 在群聊里置顶某条消息,可以置顶文字和图片消息，其他消息未测试，部分低版本移动端置顶消息点击后会直接取消，高版本会一直置顶，其他未测试。

###### 接口地址
> [/api/?type=51](/api/?type=51)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|wxid |ture |string| 置顶消息的发送人wxid |
|msgid |ture |string| 消息id |
###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,0成功, -1失败，-2 未查到该消息|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript
{
    "wxid":"wxid_oy11111p4422",
    "msgid":3334956046278903121
}

```
响应：
``` javascript
{"code":0,"result":"OK"}
```


#### 52.取消群内消息置顶**
###### 接口功能
> 取消置顶的消息。部分低版本移动端会不显示移除消息，但是会正常移除。

###### 接口地址
> [/api/?type=52](/api/?type=52)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|chatRoomId |ture |string| 微信群聊id |  
|msgid |ture |string| 消息id |
###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,0成功, -1失败|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript
{
    "chatRoomId":"2136311004@chatroom",
    "msgid":3374951233278903120
}

```
响应：
``` javascript
{"code":0,"result":"OK"}
```   



#### 53.朋友圈首页消息**
###### 接口功能
> 获取朋友圈最新消息，调用之后，会在tcpserver服务中收到朋友圈的消息。格式如下：
``` javascript
{
  'data': [
    {
      'content': '朋友圈[玫瑰][玫瑰]',
      'createTime': 1675827480,
      'senderId': 'wxid_12333',
      'snsId': 14057859804711563695,
      'xml': '<TimelineObject><id><![CDATA[1405712322563695]]></id><username><![CDATA[wxid_12333]]></username><createTime><![CDATA[1675827480]]></createTime><contentDescShowType>0</contentDescShowType><contentDescScene>0</contentDescScene><private><![CDATA[0]]></private><contentDesc><![CDATA[朋友圈[玫瑰][玫瑰]]]></contentDesc><contentattr><![CDATA[0]]></contentattr><sourceUserName></sourceUserName><sourceNickName></sourceNickName><statisticsData></statisticsData><weappInfo><appUserName></appUserName><pagePath></pagePath><version><![CDATA[0]]></version><debugMode><![CDATA[0]]></debugMode><shareActionId></shareActionId><isGame><![CDATA[0]]></isGame><messageExtraData></messageExtraData><subType><![CDATA[0]]></subType><preloadResources></preloadResources></weappInfo><canvasInfoXml></canvasInfoXml><ContentObject><contentStyle><![CDATA[2]]></contentStyle><contentSubStyle><![CDATA[0]]></contentSubStyle><title></title><description></description><contentUrl></contentUrl></ContentObject><actionInfo><appMsg><mediaTagName></mediaTagName><messageExt></messageExt><messageAction></messageAction></appMsg></actionInfo><appInfo><id></id></appInfo><location poiClassifyId="" poiName="" poiAddress="" poiClassifyType="0" city=""></location><publicUserName></publicUserName><streamvideo><streamvideourl></streamvideourl><streamvideothumburl></streamvideothumburl><streamvideoweburl></streamvideoweburl></streamvideo></TimelineObject>'
    }]
}

```

###### 接口地址
> [/api/?type=53](/api/?type=53)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|


   

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, -1失败|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript


```
响应：
``` javascript
{"code":1,"result":"OK"}
```   


#### 54.朋友圈下一页**
###### 接口功能
> 朋友圈下一页，会在tcpserver服务中收到朋友圈的消息。格式如下：
``` javascript
{
  'data': [
    {
      'content': '朋友圈[玫瑰][玫瑰]',
      'createTime': 1675827480,
      'senderId': 'wxid_12333',
      'snsId': 14057859804711563695,
      'xml': '<TimelineObject><id><![CDATA[1405712322563695]]></id><username><![CDATA[wxid_12333]]></username><createTime><![CDATA[1675827480]]></createTime><contentDescShowType>0</contentDescShowType><contentDescScene>0</contentDescScene><private><![CDATA[0]]></private><contentDesc><![CDATA[朋友圈[玫瑰][玫瑰]]]></contentDesc><contentattr><![CDATA[0]]></contentattr><sourceUserName></sourceUserName><sourceNickName></sourceNickName><statisticsData></statisticsData><weappInfo><appUserName></appUserName><pagePath></pagePath><version><![CDATA[0]]></version><debugMode><![CDATA[0]]></debugMode><shareActionId></shareActionId><isGame><![CDATA[0]]></isGame><messageExtraData></messageExtraData><subType><![CDATA[0]]></subType><preloadResources></preloadResources></weappInfo><canvasInfoXml></canvasInfoXml><ContentObject><contentStyle><![CDATA[2]]></contentStyle><contentSubStyle><![CDATA[0]]></contentSubStyle><title></title><description></description><contentUrl></contentUrl></ContentObject><actionInfo><appMsg><mediaTagName></mediaTagName><messageExt></messageExt><messageAction></messageAction></appMsg></actionInfo><appInfo><id></id></appInfo><location poiClassifyId="" poiName="" poiAddress="" poiClassifyType="0" city=""></location><publicUserName></publicUserName><streamvideo><streamvideourl></streamvideourl><streamvideothumburl></streamvideothumburl><streamvideoweburl></streamvideoweburl></streamvideo></TimelineObject>'
    }]
}

```

###### 接口地址
> [/api/?type=54](/api/?type=54)

###### HTTP请求方式
> POST  JSON

###### 请求参数
|参数|必选|类型|说明|
|---|---|---|---|
|snsId |ture |string| 朋友圈的snsId |

   

###### 返回字段
|返回字段|字段类型|说明                              |
|---|---|---|
|code|int|返回状态,1成功, -1失败|
|result|string|成功提示|



###### 接口示例
入参：
``` javascript
{
    "snsId":"14056334227327177401"
   
}

```
响应：
``` javascript
{"code":1,"result":"OK"}
```

#### 感谢
https://github.com/ljc545w/ComWeChatRobot  

https://github.com/NationalSecurityAgency/ghidra  

https://github.com/x64dbg/x64dbg  
