##	IS32U512A-SM2 MODULE DRIDER AND TEST CASE.
AUTHOR:QINXD
TIME:2022/7/20


ADD SM2 KDF AND POINTER DECOMPRESS.
2022/7/25

1.8.8.4-02
COS VERSION 1.8.8.4
SOC VERISON V2
更正了密钥衍生部分的说明文档和注释。
KE和KS是同一个流程
完整密钥或者是一个流程。

修改后的名字是：
ISTECC512A_SM2EncryptSignKeyKDF     生成衍生的签名或者加密密钥
ISTECC512A_SM2CompleteKDF           生成完整私钥Si.


1.8.8.4-03
COS VERSION 1.8.8.4
SOC VERISON 第三版
加入完整的秘钥衍生例程


1.8.8.5-01
为了保持格式兼容，将logic_level的所有int型变量转为unsigned long
char转换为unsinged char

1.8.8.6
add mod add api.
INS: 0X3B

1.8.8.7 
The test routine of SM4CCM is added.
Added a separate SM2 encryption and decryption routine.
Added separate mod_ Add interface.

1.8.9.1
add e+rs verify mode. and test data.


1.8.9.2
新的COS更正了HSM模块的点解压的问题。
新的测试例程更正了点解压的测试例程。分别进行MODE2,MODE3的测试。
修改了hex_dump()程序。只进行简单的打印信息输出。界面更加清晰。
将DownloadFile.c 和DownloadFile.h更新为1.8.9.2版本。
更正了导入私钥函数中错误的长度(64+6).更正为32+6.
ImportSM2Prikey
更正了导出私钥函数中错误的长度。


1.8.9.4
增加了E值签名的功能和测试DEMO.
修改了APP update 流程。支持在线升级

1.8.9.5
增加了直接获取sij的功能。将导入秘钥和导出秘钥等操作包含在内。只用调用一次即可。


verison: 1.8.9.6
updated based  on verison 1.8.9.5  
The original verison is 1.8.9.5. ccm.c ccm.h sm4.c sm4.h files were removed on this basis.
and the gpio.c gpio.h was rewritten.The gpio control structure has beed redefiend. 
Removed some test code.  unsigned long ISTECCSm4CcmTest(void)
Removed the  include "ccm.h"  and  include "sm4.h"
MIT's license description was added at the beginning of each file.
