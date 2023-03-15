/*
 * @Author: your name
 * @Date: 2021-04-19 15:08:39
 * @LastEditTime: 2022-11-24 15:09:39
 * @LastEditors: qinxd qinxd@istecc.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \SKF-IMX8-IS32U512A\spidev_test.c
 */
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <sys/time.h>

#include "hsm_test_task.h"

#define READ_VERISON   			0x00
#define ALL_FUN_TEST    		0X01
#define APP_ERASE       		0X02
#define APP_UPDATE      		0X03
#define POINTER_DECOMPRESS 		0X04
#define KEY_DERIVE              0X05	
#define SM4_CCM		            0X06
#define SM2_ENCRYPT_DECRYPT     0X07
#define SM4_STRESS     			0X08
#define SM2_VERIFY_ONE_CORE     0X09  /*original verify*/
#define SM2_VERIFY_E_RS			0x0A  /*10 e value sign*/
#define SM2_SIGN_E_VALUE		0x0B  /*11 E value sign*
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
static void pabort(const char *s)
{
	perror(s);
	abort();
}

extern const unsigned char UserID00_UserInfo[];
/*Print log with English*/
static void print_usage_English(void)
{
	printf("  istecc's is32u512a test code for linux\n");
	printf("  author: Qinxd\n");
	printf("  func 0: Read moudle verison(maybe 1.8.7)\n");
	printf("  func 1: All function test\n");
	printf("  func 2: App Erase test\n");
	printf("  func 3: App Update\n");
	printf("  func 4: Pointer Descompress\n");
	printf("  func 5: KEY_DERIVE\n");
	printf("  func 10: E+RS verify mode\n");
	printf("  input parameter with the test number\n");
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int time = 0;
	
	int x = 100;
	if (argc != 2)
	{
		printf("Abnormal parameter Number!\n");
		print_usage_English();
		return 1;
	}
	x = atoi(argv[1]);
	print_usage_English();
	switch (x)
	{
	case READ_VERISON:
		IS32U512AReadVerisonTest();
		break;
	case ALL_FUN_TEST:
		IS32U512AFunctionTest();
		break;
	case APP_ERASE:
		printf("Please Input 1234 to make sure what you want to do.\n");
		scanf("%d",&ret);
		if(ret==1234){
			printf("APP erase!\n");
			//ISTECCEraseAPPTest();
			ISTECCEraseAPPTest2();
		}
		break;
	case APP_UPDATE:
		printf("Please Input 1234 to make sure what you want to do.\n");
		scanf("%d",&ret);
		printf("update vserison 1.8.8\n");
		if(ret==1234){
			printf("APP Update!\n");
			ISTECCUpdateTest();
		}
		break;
	case POINTER_DECOMPRESS:
		printf("ISTECCSPointerDecompressTest TEST.");
		ISTECCSPointerDecompressTest();
		break;
	case KEY_DERIVE:
		ISTECCKeyDeriveTest();
		break;
	case SM4_CCM:
		ISTECCSm4CcmTest();
		break;
	case SM2_ENCRYPT_DECRYPT:
		IS32U512ASM2EncyprtDecryptTest();
		break;
	case SM2_VERIFY_E_RS:
		IS32U512ASm2VerifyEvalueWithPubKeyIndex();
	case SM2_SIGN_E_VALUE:
		IS32U512ASm2SignEvalueAndVerifyEvalueWithPubKeyIndex();	
	default:
		printf("not support!\n");
		break;
	}
	printf("TestTask end:\n");
	return 0;
}
