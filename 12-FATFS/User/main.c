#include "stm32f10x.h" 
#include "ff.h"
#include <stdio.h>
#include "string.h"

#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"


FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL fnew;													/* �ļ����� */
FRESULT res_flash;                /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
BYTE WriteBuffer[] =              /* д������*/
"��ӭʹ��Ұ��STM32������,����FatFs�����������\r\n";
char fpath[100];                  /* ���浱ǰɨ��·�� */
char readbuffer[512];  


static FRESULT miscellaneous(void);
static FRESULT file_check(void);
static FRESULT scan_files (char* path);

int main(void)
{
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE    
	LED_RGB_Init();
	LED_BLUE;

	printf("\r \n ����һ�� SPI FLASH �ļ�ϵͳʵ�� \r \n");
	res_flash = f_mount(&fs,"1:",1);
	
	/*----------------------- ��ʽ������-----------------*/
	if(res_flash == FR_NO_FILESYSTEM)
	{
		printf("��FLASH��û���ļ�ϵͳ���������и�ʽ��...\r\n");
		res_flash=f_mkfs("1:",0,0); // ��ʽ��
		
		if(res_flash == FR_OK)
		{
			printf("��FLASH�ѳɹ���ʽ���ļ�ϵͳ��\r\n");
			res_flash = f_mount(NULL,"1:",1);
			res_flash = f_mount(&fs,"1:",1);
		}
		else
		{
			LED_RED;
			printf("<<.......��ʽ��ʧ��......>>\r\n");
			while(1);
		}
	}
	else if (res_flash != FR_OK)
	{
		printf("!!�ⲿFlash �����ļ�ϵͳʧ�ܡ�(%d)\r\n",res_flash);
		printf("!!����ԭ��SPI Flash ��ʼ�����ɹ���\r\n");
		while (1);
	}
	else
	{
		printf("���ļ�ϵͳ���سɹ������Խ��ж�д����\r\n");
	}
	
	/*----------------------- �ļ�ϵͳ���ԣ�д����-------------------*/
	printf("\r\n****** ���������ļ�д�����... ******\r\n");
	res_flash = f_open(&fnew, "1:FatFs ��д�ļ�����.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if (res_flash == FR_OK)
	{
		printf("������/����FatFs��д�����ļ�.txt �ļ��ɹ��� ���ļ�д������\r\n");
		
		res_flash = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
		
		if(res_flash == FR_OK)
		{
			printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\n",fnum);
			printf("�����ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
		}
		else
		{
			printf("�����ļ�д��ʧ�ܣ�(%d)\n",res_flash);
		}
		
		f_close(&fnew);
	}
	else
	{
		LED_RED;
		printf("!!��/�����ļ�ʧ��\r\n");
	}
	
	
	/*------------------- �ļ�ϵͳ���ԣ�������--------------------------*/
	printf("******* ���������ļ���ȡ����**********\r\n");
	res_flash = f_open(&fnew, "1:FatFs ��д�ļ�����.txt",FA_OPEN_EXISTING | FA_READ);
	
	if(res_flash == FR_OK)
	{
		LED_GREEN;
		printf("�� ���ļ��ɹ���\r\n");
		res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
		
		if(res_flash == FR_OK)
		{
			printf("���ļ���ȡ�ɹ��� ��ȡ���ֽ����ݣ�%d \r\n", fnum);
			printf("����ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);
		}
		
		else
		{
				printf("!!�ļ���ȡʧ�ܡ�\r\n");
		}		
	}
	else
	{
		LED_RED;
		printf("�����ļ���ȡʧ�ܡ� \r\n");
	}
	
	f_close(&fnew);
	
	 /* FatFs����ܲ��� */
  res_flash = miscellaneous();

  
  printf("\n*************** �ļ���Ϣ��ȡ���� **************\r\n");
  res_flash = file_check();

  
  printf("***************** �ļ�ɨ����� ****************\r\n");
  strcpy(fpath,"1:");
  scan_files(fpath);
	
	f_mount(NULL,"1:",1);
	
	while(1){}
}

static FRESULT miscellaneous(void)
{
	DIR dir;
	FATFS *pfs;
	DWORD fre_clust, fre_sect, tot_sect;
	
	printf("\n**********�豸��Ϣ��ȡ**************\r\n");

	// ��ȡ�豸��Ϣ�Ϳմش�С
	res_flash = f_getfree("1:", &fre_clust, &pfs);
	
	// ����õ��ܵ����������Ϳ������ĸ���
	tot_sect = (pfs->n_fatent -2) * pfs->csize;  // cluster * sector
	fre_sect = fre_clust * pfs->csize;  // free cluster * sector
	
	printf("���豸�ܿռ䣺%10lu KB��\n�����ÿռ䣺  %10lu KB��\n", tot_sect *4, fre_sect *4);
	
	printf("\n******** �ļ���λ�͸�ʽ��д�빦�ܲ��� ********\r\n");
  res_flash = f_open(&fnew, "1:FatFs��д�����ļ�.txt", FA_OPEN_ALWAYS|FA_WRITE|FA_READ );
	if ( res_flash == FR_OK )
	{
    /*  �ļ���λ */
    res_flash = f_lseek(&fnew,f_size(&fnew));
    if (res_flash == FR_OK)
    {
      /* ��ʽ��д�룬������ʽ����printf���� */
      f_printf(&fnew,"\n��ԭ���ļ������һ������\n");
      f_printf(&fnew,"�豸�ܿռ䣺%10lu KB��\n ���ÿռ䣺  %10lu KB��\n", tot_sect *4, fre_sect *4);
      /*  �ļ���λ���ļ���ʼλ�� */
      res_flash = f_lseek(&fnew,0);
      /* ��ȡ�ļ��������ݵ������� */
      res_flash = f_read(&fnew,readbuffer,f_size(&fnew),&fnum);
      if(res_flash == FR_OK)
      {
        printf("���ļ����ݣ�\n%s\n",readbuffer);
      }
			else
			{
				printf("!!��ȡ�ļ�����ʧ�� \r\n");
			}
    }
    f_close(&fnew);    
    
    printf("\n********** Ŀ¼���������������ܲ��� **********\r\n");
    /* ���Դ�Ŀ¼ */
    res_flash=f_opendir(&dir,"1:TestDir");
    if(res_flash!=FR_OK)
    {
      /* ��Ŀ¼ʧ�ܣ��ʹ���Ŀ¼ */
      res_flash=f_mkdir("1:TestDir");
    }
    else
    {
      /* ���Ŀ¼�Ѿ����ڣ��ر��� */
      res_flash=f_closedir(&dir);
      /* ɾ���ļ� */
      f_unlink("1:TestDir/testdir.txt");
    }
    if(res_flash==FR_OK)
    {
      /* ���������ƶ��ļ� */
      res_flash=f_rename("1:FatFs��д�����ļ�.txt","1:TestDir/testdir.txt");
			printf("      ���������ƶ��ļ��ɹ���\r\n");
    } 
	}
  else
  {
    printf("!! ���ļ�ʧ�ܣ�%d\n",res_flash);
    printf("!! ������Ҫ�ٴ����С�FatFs��ֲ���д���ԡ�����\n");
  }
  return res_flash;
	
}


FILINFO fno;
/**
  * �ļ���Ϣ��ȡ
  */
static FRESULT file_check(void)
{

  
  /* ��ȡ�ļ���Ϣ */
  res_flash=f_stat("1:TestDir/testdir.txt",&fno);
  if(res_flash==FR_OK)
  {
    printf("��testdir.txt���ļ���Ϣ��\n");
    printf("���ļ���С: %ld(�ֽ�)\n", fno.fsize);
    printf("��ʱ���: %u/%02u/%02u, %02u:%02u\n",
           (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,fno.ftime >> 11, fno.ftime >> 5 & 63);
    printf("������: %c%c%c%c%c\n\n",
           (fno.fattrib & AM_DIR) ? 'D' : '-',      // ��һ��Ŀ¼
           (fno.fattrib & AM_RDO) ? 'R' : '-',      // ֻ���ļ�
           (fno.fattrib & AM_HID) ? 'H' : '-',      // �����ļ�
           (fno.fattrib & AM_SYS) ? 'S' : '-',      // ϵͳ�ļ�
           (fno.fattrib & AM_ARC) ? 'A' : '-');     // �����ļ�
		printf("file data output: %d\r\n", fno.fattrib);
					 
	
	if(res_flash == FR_OK)
	 {
		res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
		if(res_flash == FR_OK)
		{
			printf("����ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);
		}	
		else
		{
				printf("!!�ļ���ȡʧ�ܡ�\r\n");
		}		
	 }
	}
  return res_flash;
}

/**
  * @brief  scan_files �ݹ�ɨ��FatFs�ڵ��ļ�
  * @param  path:��ʼɨ��·��
  * @retval result:�ļ�ϵͳ�ķ���ֵ
  */
static FRESULT scan_files (char* path) 
{ 
  FRESULT res; 		//�����ڵݹ���̱��޸ĵı���������ȫ�ֱ���	
  FILINFO fno; 
  DIR dir; 
  int i;            
  char *fn;        // �ļ���	
	
#if _USE_LFN 
  /* ���ļ���֧�� */
  /* ����������Ҫ2���ֽڱ���һ�����֡�*/
  static char lfn[_MAX_LFN*2 + 1]; 	
  fno.lfname = lfn; 
  fno.lfsize = sizeof(lfn); 
#endif 
  //��Ŀ¼
  res = f_opendir(&dir, path); 
  if (res == FR_OK) 
	{ 
    i = strlen(path); 
    for (;;) 
		{ 
      //��ȡĿ¼�µ����ݣ��ٶ����Զ�����һ���ļ�
      res = f_readdir(&dir, &fno); 								
      //Ϊ��ʱ��ʾ������Ŀ��ȡ��ϣ�����
      if (res != FR_OK || fno.fname[0] == 0) break; 	
#if _USE_LFN 
      fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
      fn = fno.fname; 
#endif 
      //���ʾ��ǰĿ¼������			
      if (*fn == '.') continue; 	
      //Ŀ¼���ݹ��ȡ      
      if (fno.fattrib & AM_DIR)         
			{ 			
        //�ϳ�����Ŀ¼��        
        sprintf(&path[i], "/%s", fn); 		
        //�ݹ����         
        res = scan_files(path);	
        path[i] = 0;         
        //��ʧ�ܣ�����ѭ��        
        if (res != FR_OK) 
					break; 
      } 
			else 
			{ 
				printf("%s/%s\r\n", path, fn);								//����ļ���	
        /* ������������ȡ�ض���ʽ���ļ�·�� */        
      }//else
    } //for
  } 
  return res; 
}
