/*
 * 	Copyright (c) 2023 qinxd
 *  qinxd
 *  email:qinxd@istecc.com
 *  Licensed under MIT License.
 * 
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
#define SM2_SIGN_E_VALUE		0x0B  /*11 E value sign*/
#define SELF_TEST				0X0C  
#define SELF_TEST_WITH_MUTEX	0X0D  //TEST MUL PTHREAD.
#define SELF_TEST_MUL_PROCESS	0X0E  //TEST MUL PROCESS.
#define HSM_ONE_KEY_RESOTRE		0X0F  //TEST ONE KEY ERSTORE.
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
	printf("  func 12: HSM Self test\n");
	printf("  input parameter with the test number\n");
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int time = 0;
	int test_loop = 100;

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
	case SELF_TEST:
		if(HSMSelfTest(test_loop))
		{
			printf("HSMSelfTest failed!\n");
		}
		break;
	case SELF_TEST_WITH_MUTEX:
		if(HSMSelfTestWithMultithreading())
		{
			printf("HSMSelfTestWithMultithreading failed!\n");
		}
		break;
	case SELF_TEST_MUL_PROCESS:
		if(HSMSelfTestWithMulProcess())
		{
			printf("HSMSelfTestWithMulProcess failed!\n");
		}
		break;
	case HSM_ONE_KEY_RESOTRE:
		if(HSMOneKeyRestore())
		{
			printf("HSMOneKeyRestore failed!\n");
		}
		break;
	default:
		printf("not support!\n");
		break;
	}
	printf("TestTask end:\n");
	return 0;
}
