/**
  ******************************************************************************
  * @file    bsp_as608.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   指纹识别模块实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火STM32 F103-霸道 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
uint8_t Key=10;  //按键值
uint8_t Flag2;
 /**
  * @brief  指令解析
  * @param  无
  * @retval 无
  */
void Show_Message(void)
{
  AS608_INFO("   请输入指令，输入指令后请在输入窗口按回车键后再发送指令！！！\r\n");
  AS608_INFO("   指令   ------      功能 \r\n");
  AS608_INFO("    1     ------    添加指纹 \r\n");
  AS608_INFO("    2     ------    对比指纹 \r\n");
  AS608_INFO("    3     ------    删除指定用户指纹\r\n");
  AS608_INFO("    4     ------    清空指纹库\r\n");  
}






/**
  * @brief  检测与指纹模块的通信
  * @param  无
  * @retval 无
  */
void  Connect_Test(void)
{   
  Usart_SendString( DEBUG_USARTx,"这是一个指纹模块实验\r\n");
    
  if(PS_Connect(&AS608_Addr))                      /*与AS608串口通信*/
  { 
    AS608_INFO("未检测到指纹模块，请检查连接！！！\r\n");             
  }
  else
  {
    AS608_INFO("通讯成功\r\n");
    Show_Message();
  }
}


/**
  * @brief  录指纹
  * @param  无
  * @retval 无
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
      case 0:                            /*执行第1步*/
        
        i++;
        LCD_SetFont(&Font8x16);
        LCD_SetColors(RED, BACKGROUND); 
        ILI9341_DispString_EN_CH(0,0,"********命令：请按手指********");
       
        
        sure=PS_GetImage();              /*录入图像*/      
        if(sure == 0x00)
        {
          sure=PS_GenChar(CHAR_BUFFER1);  /*生成特征1*/
          if(sure==0x00)
          { 
                    ILI9341_DispString_EN_CH(0,20,"输入指纹1正常！！！");
        
            
            sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
            if(sure==0x00)
            {

                ILI9341_DispString_EN_CH(0,40,"指纹已存在，指纹ID：");
                LCD_SetFont(&Font8x16); /*设置英文字体类型*/
                LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
                sprintf(ID_Buff,"%d ",ID);
                ILI9341_DispString_EN_CH(180,40,ID_Buff);
             return ;
            }              
            else 
            {
              i=0;
              j=1;                   /*跳转到第2步*/
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
      

        ILI9341_DispString_EN_CH(0,60,"***命令：请再按一次手指***");
        sure=PS_GetImage();
        if(sure==0x00)
        { 
          sure=PS_GenChar(CHAR_BUFFER2);  /*生成特征2*/
          if(sure==0x00)
          { 
        
                    ILI9341_DispString_EN_CH(0,80,"输入指纹2正常");
            i=0;
            j=2;                   /*跳转到第3步*/
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
         

         ILI9341_DispString_EN_CH(0,100,"正在对比两次输入的指纹");
       
         sure=PS_Match();                /*精确比对两枚指纹特征*/
         if(sure==0x00) 
         {
                
                    ILI9341_DispString_EN_CH(0,120,"输入指纹对比成功");
           
           j=3;                         /*跳转到第4步*/
         }
         else
         {
             
             ILI9341_DispString_EN_CH(0,140,"对比失败，请重新录入指纹");
             ShowErrMessage(sure);
           i=0;
           j=0;
         }
        
       break;
         
         
       case 3:
         

            ILI9341_DispString_EN_CH(0,160,"正在生成指纹模块");
       
         sure=PS_RegModel();            /*合并特征（生成模板）*/
         if(sure==0x00)     
         {

             ILI9341_DispString_EN_CH(0,180,"生成指纹模块成功");
           j=4;                        /*跳转到第5步*/
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
            LCD_SetTextColor(RED); /*设置LCD的前景(字体)颜色,RGB565*/
            ILI9341_DispString_EN_CH(0,200,"请输入ID，范围为0—299:");
            /*显示用户序号变量*/
            LCD_SetFont(&Font8x16); /*设置英文字体类型*/
            LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
            
            ID =Count_KEY(Key);
            
            sprintf(ID_Buff,"%d ",ID);
            ILI9341_DispString_EN_CH(200,200,ID_Buff);
            Key = 10;
        }
        
         sure=PS_StoreChar(CHAR_BUFFER2,ID);  /*储存模板*/
         if(sure==0x00)     
         {
           ILI9341_DispString_EN_CH(0,240,"录入指纹模块成功！！！");
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
      
      if(i==6)                       /*超过6次没有按手指则退出*/
      { 
        ILI9341_DispString_EN_CH(0,260,"录指纹失败！");
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
  * @brief  比对指纹（识别指纹）
  * @param  无
  * @retval 无
  */
bool Compare_FR(void)  
{  
  uint16_t  ID=0;                    /*初始化ID值*/  
  uint16_t  sure;
  char ID_Buff[10];


    //ILI9341_DispString_EN_CH(50,100,"请按手指进行解锁");

    DisplayString(50,100, "请按手指进行解锁", TRUE);

    //识别到有指纹按下
    if(GPIO_ReadInputDataBit(AS608_TouchOut_INT_GPIO_PORT, AS608_TouchOut_INT_GPIO_PIN) == TRUE)
    {
        DisplayString(50,100, "正在识别中，请保持手指。。。", TRUE);
        sure=PS_GetImage();
        if(sure == 0x00)
        {
            sure=PS_GenChar(CHAR_BUFFER1);    /*生成特征1*/
            if(sure==0x00)
            {  
				/*高速搜索指纹库*/
                sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
                if(sure==0x00)
                {
					DisplayString(0,200, "指纹正确,解锁成功", TRUE);
					//ILI9341_DispString_EN_CH(0,200,"对比指纹成功，指纹ID：");
                    LCD_SetFont(&Font8x16); /*设置英文字体类型*/
                    LCD_SetTextColor(RED); /*设置LCD的前景(字体)颜色,RGB565*/
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
  * @brief  清空指纹库
  * @param  无
  * @retval 无
  */
void Clean_FR(void) 
{
  uint16_t  sure;
    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BACKGROUND); 
    ILI9341_DispString_EN_CH(0,0,"清空指纹库");

    
    sure=PS_Empty();     
    if(sure == 0x00)
    {
        
        ILI9341_DispString_EN_CH(0,20,"清空指纹库成功！！！");
        SysTick_Delay_ms(1000);
    }
    else 
    {
        ShowErrMessage(sure);
    }

}


/**
  * @brief  删除指定用户指纹
  * @param  无
  * @retval 无
  */
void Del_FR(void)
{ 
    
    uint16_t  sure;

    
    sure=PS_DeletChar(ID,1);         /*删除指定用户的指纹模板*/
    
    if(sure == 0x00)                
    {

        ILI9341_DispString_EN_CH(0,60,"删除指定用户指纹成功！！！");
    }
    else 
    {
        ShowErrMessage(sure);
    }
}


/*********************************************END OF FILE**********************/
