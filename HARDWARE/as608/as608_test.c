/**
  ******************************************************************************
  * @file    bsp_as608.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ָ��ʶ��ģ��ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����STM32 F103-�Ե� ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "as608_test.h"
#include "bsp_as608.h"
#include "bsp_ili9341_lcd.h"
#include "bsp.key.h"
#include "main.h"

uint32_t ch=1;
extern uint8_t TouchOut_int_flag;
extern uint32_t  ID;
uint8_t Key=10;  //����ֵ
uint8_t Flag2;
 /**
  * @brief  ָ�����
  * @param  ��
  * @retval ��
  */
void Show_Message(void)
{
  AS608_INFO("   ������ָ�����ָ����������봰�ڰ��س������ٷ���ָ�����\r\n");
  AS608_INFO("   ָ��   ------      ���� \r\n");
  AS608_INFO("    1     ------    ���ָ�� \r\n");
  AS608_INFO("    2     ------    �Ա�ָ�� \r\n");
  AS608_INFO("    3     ------    ɾ��ָ���û�ָ��\r\n");
  AS608_INFO("    4     ------    ���ָ�ƿ�\r\n");  
}






/**
  * @brief  �����ָ��ģ���ͨ��
  * @param  ��
  * @retval ��
  */
void  Connect_Test(void)
{   
  Usart_SendString( DEBUG_USARTx,"����һ��ָ��ģ��ʵ��\r\n");
    
  if(PS_Connect(&AS608_Addr))                      /*��AS608����ͨ��*/
  { 
    AS608_INFO("δ��⵽ָ��ģ�飬�������ӣ�����\r\n");             
  }
  else
  {
    AS608_INFO("ͨѶ�ɹ�\r\n");
    Show_Message();
  }
}


/**
  * @brief  ¼ָ��
  * @param  ��
  * @retval ��
  */
void  Add_FR(void)
{
  uint16_t  i,j,sure,ID;
  char ID_Buff[10];
  i=j=0;
    
  while(1)
  {
    switch (j)
    {
      case 0:                            /*ִ�е�1��*/
        
        i++;
        LCD_SetFont(&Font8x16);
        LCD_SetColors(RED, BACKGROUND); 
        ILI9341_DispString_EN_CH(0,0,"********����밴��ָ********");
       
        
        sure=PS_GetImage();              /*¼��ͼ��*/      
        if(sure == 0x00)
        {
          sure=PS_GenChar(CHAR_BUFFER1);  /*��������1*/
          if(sure==0x00)
          { 
                    ILI9341_DispString_EN_CH(0,20,"����ָ��1����������");
        
            
            sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
            if(sure==0x00)
            {

                ILI9341_DispString_EN_CH(0,40,"ָ���Ѵ��ڣ�ָ��ID��");
                LCD_SetFont(&Font8x16); /*����Ӣ����������*/
                LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
                sprintf(ID_Buff,"%d ",ID);
                ILI9341_DispString_EN_CH(180,40,ID_Buff);
             return ;
            }              
            else 
            {
              i=0;
              j=1;                   /*��ת����2��*/
             }
           }
                 else
                 {
                     ShowErrMessage(sure);         
                 }
        }
              else 
              {
                  ShowErrMessage(sure); 
              }
      break;


      case 1:
        
        i++;
      

        ILI9341_DispString_EN_CH(0,60,"***������ٰ�һ����ָ***");
        sure=PS_GetImage();
        if(sure==0x00)
        { 
          sure=PS_GenChar(CHAR_BUFFER2);  /*��������2*/
          if(sure==0x00)
          { 
        
                    ILI9341_DispString_EN_CH(0,80,"����ָ��2����");
            i=0;
            j=2;                   /*��ת����3��*/
          }
                  else 
                  {
                      ShowErrMessage(sure);
                  }

         }
               else 
               {
               ShowErrMessage(sure);
         }              
       break;

            
       case 2:
         

         ILI9341_DispString_EN_CH(0,100,"���ڶԱ����������ָ��");
       
         sure=PS_Match();                /*��ȷ�ȶ���öָ������*/
         if(sure==0x00) 
         {
                
                    ILI9341_DispString_EN_CH(0,120,"����ָ�ƶԱȳɹ�");
           
           j=3;                         /*��ת����4��*/
         }
         else
         {
             
             ILI9341_DispString_EN_CH(0,140,"�Ա�ʧ�ܣ�������¼��ָ��");
             ShowErrMessage(sure);
           i=0;
           j=0;
         }
        
       break;
         
         
       case 3:
         

            ILI9341_DispString_EN_CH(0,160,"��������ָ��ģ��");
       
         sure=PS_RegModel();            /*�ϲ�����������ģ�壩*/
         if(sure==0x00)     
         {

             ILI9341_DispString_EN_CH(0,180,"����ָ��ģ��ɹ�");
           j=4;                        /*��ת����5��*/
         } 
         else 
        {
         j =0;
         ShowErrMessage(sure);
        }
        
       break;
        

       case 4:

       Flag2 =1;
        while(Flag2)
        {
            Matrix_Test();
            LCD_SetTextColor(RED); /*����LCD��ǰ��(����)��ɫ,RGB565*/
            ILI9341_DispString_EN_CH(0,200,"������ID����ΧΪ0��299:");
            /*��ʾ�û���ű���*/
            LCD_SetFont(&Font8x16); /*����Ӣ����������*/
            LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
            
            ID =Count_KEY(Key);
            
            sprintf(ID_Buff,"%d ",ID);
            ILI9341_DispString_EN_CH(200,200,ID_Buff);
            Key = 10;
        }
        
         sure=PS_StoreChar(CHAR_BUFFER2,ID);  /*����ģ��*/
         if(sure==0x00)     
         {
           ILI9341_DispString_EN_CH(0,240,"¼��ָ��ģ��ɹ�������");
           return ;
         } 
         else 
         {
           j =0;
           ShowErrMessage(sure);
         }
       break;
      }
    
      SysTick_Delay_ms(1000);
      
      if(i==6)                       /*����6��û�а���ָ���˳�*/
      { 
        ILI9341_DispString_EN_CH(0,260,"¼ָ��ʧ�ܣ�");
        break;
      }
  }
}

bool DisplayString(int X,int Y, char* str, bool IsClear)
{
	static char preStr[50];

	if(strcmp(preStr, str) == 0)
	{
		return FALSE;
	}
	memset(preStr, 0, sizeof(preStr));
	memcpy(preStr, str, strlen(str));
    if(IsClear == TRUE)
    {
        ILI9341_Clear(0,0, 240, 320,BACKGROUND);
    }
    
    ILI9341_DispString_EN_CH(50,100,str);
	return TRUE;
}

/**
  * @brief  �ȶ�ָ�ƣ�ʶ��ָ�ƣ�
  * @param  ��
  * @retval ��
  */
bool Compare_FR(void)  
{  
  uint16_t  ID=0;                    /*��ʼ��IDֵ*/  
  uint16_t  sure;
  char ID_Buff[10];


    //ILI9341_DispString_EN_CH(50,100,"�밴��ָ���н���");

    DisplayString(50,100, "�밴��ָ���н���", TRUE);

    //ʶ����ָ�ư���
    if(GPIO_ReadInputDataBit(AS608_TouchOut_INT_GPIO_PORT, AS608_TouchOut_INT_GPIO_PIN) == TRUE)
    {
        DisplayString(50,100, "����ʶ���У��뱣����ָ������", TRUE);
        sure=PS_GetImage();
        if(sure == 0x00)
        {
            sure=PS_GenChar(CHAR_BUFFER1);    /*��������1*/
            if(sure==0x00)
            {  
				/*��������ָ�ƿ�*/
                sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
                if(sure==0x00)
                {
					DisplayString(0,200, "ָ����ȷ,�����ɹ�", TRUE);
					//ILI9341_DispString_EN_CH(0,200,"�Ա�ָ�Ƴɹ���ָ��ID��");
                    LCD_SetFont(&Font8x16); /*����Ӣ����������*/
                    LCD_SetTextColor(RED); /*����LCD��ǰ��(����)��ɫ,RGB565*/
                    //sprintf(ID_Buff,"%d ",ID);
					//DisplayString(170,200, ID_Buff, FALSE);
                    //ILI9341_DispString_EN_CH(170,200,ID_Buff);
                    Beep_ON;
                    Delay_1ms(300000);
					Beep_OFF;
                    return true;
				}
				else 
				{
					ShowErrMessage(sure);
					Delay_1ms(300000);
					return false;
				}
            }
            else 
            {   
              ShowErrMessage(sure); 
              return false;
            }
        }
		else  
		{
			ShowErrMessage(sure);
			return false;
		}
    }
}



/**
  * @brief  ���ָ�ƿ�
  * @param  ��
  * @retval ��
  */
void Clean_FR(void) 
{
  uint16_t  sure;
    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BACKGROUND); 
    ILI9341_DispString_EN_CH(0,0,"���ָ�ƿ�");

    
    sure=PS_Empty();     
    if(sure == 0x00)
    {
        
        ILI9341_DispString_EN_CH(0,20,"���ָ�ƿ�ɹ�������");
        SysTick_Delay_ms(1000);
    }
    else 
    {
        ShowErrMessage(sure);
    }

}


/**
  * @brief  ɾ��ָ���û�ָ��
  * @param  ��
  * @retval ��
  */
void Del_FR(void)
{ 
    
    uint16_t  sure;

    
    sure=PS_DeletChar(ID,1);         /*ɾ��ָ���û���ָ��ģ��*/
    
    if(sure == 0x00)                
    {

        ILI9341_DispString_EN_CH(0,60,"ɾ��ָ���û�ָ�Ƴɹ�������");
    }
    else 
    {
        ShowErrMessage(sure);
    }
}


/*********************************************END OF FILE**********************/
