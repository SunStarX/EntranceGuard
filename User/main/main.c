#include "main.h"

/*全局变量*/
char cStr [ 30 ];
uint8_t ucArray_ID [ 5 ];  /*先后存放IC卡的类型和UID(IC卡序列号)*/ 
uint8_t ucIC_Card1[4];
uint8_t ucStatusReturn;    /*返回状态*/                                                                                         
static u8 ucLineCount = 2; 
uint8_t Memory_ID[40]; //用于存储ID卡的数据
static uint8_t testCNT = 0;
char dispBuff[100];
uint8_t Count=4,i; //用于循环变量
uint8_t Change=1; //用于菜单切换的标志位
uint8_t Flag1=1;  

extern uint8_t Flag2;
uint8_t Flag3;

extern uint8_t Key;  //按键值

/*键盘输入数字用到的中间变量*/
static uint8_t KEY=0;
static uint8_t count=1;

/*指纹ID*/
uint32_t  ID=0;

/*存储密码*/
char PassWord[10];
uint8_t Pass_Buff[10]={0,0,0,0,0,0};
uint8_t Place_pass,Place_Flag;


//extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
//extern uint8_t aDST_Buffer[BUFFER_SIZE];


/*延时函数*/
void Delay(uint32_t Count)
{
	for(;Count!=0;Count--);
}

/*******硬件初始化******/
void Hard_Init(void)
{
	Beep_GPIO_Config();  //蜂鸣器初始化
	//Matrix_Key_Config();   //矩阵按键初始化
	//RC522_Init();  		 //RC522模块所需外设的初始化配置
	ILI9341_Init();      //LCD显示屏初始化
	ILI9341_Clear(0,0, 240, 320,BACKGROUND);
	//PcdReset ();         //复位RC522
	//M500PcdConfigISOType ( 'A' );  /*设置工作方式*/
	LED_GPIO_Config();  //LED灯初始化
	/*初始化环形缓冲区*/
	rx_queue_init();
   
	/*初始化指纹模块配置*/
	AS608_Config();
	USART_Config();
	/*测试STM32与指纹模块的通信*/
    //Connect_Test();

	ee_Test();//初始化E2PROM

	
}


int main(void)
{
	uint16_t  i,j,sure,ID;
	Hard_Init();
	 
	while(1)
	{
		
		if(Change==1)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			LCD_SetFont(&Font8x16);
			LCD_SetColors(RED, BACKGROUND); 
			ILI9341_DispString_EN_CH(50,0,"智能门禁系统");
			ILI9341_DispString_EN_CH(0,300,"设置");
			
			//ILI9341_DispString_EN_CH(10,100,"请按指纹解锁");
		}
		/*菜单一*/
		while(Change==1)
		{
			//RCC_Iden();   //识别门禁卡
			//Compare_FR();
			//Matrix_Test();
			Compare_FR();
		}
		
		
		
		if(Change==2)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			LCD_SetFont(&Font8x16);
			//Flag1 =1;
		}
		/*菜单二*/
		while(Change==2)
		{
			Matrix_Test();
			switch(Flag1)
			{
				case 1:	
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");
				        ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
				        ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
				        ILI9341_DispString_EN_CH(0,80,"5.修改密码    ");
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页    ");
						break;
				case 2:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");						
				        ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
				        ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
				        ILI9341_DispString_EN_CH(0,80,"5.修改密码    ");
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页    ");
						break;
				
				case 3:                         
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");				        
				        ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
				        ILI9341_DispString_EN_CH(0,80,"5.修改密码      ");
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页    ");
						break;
						
						
				case 4: 
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");
				        ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
				        ILI9341_DispString_EN_CH(0,80,"5.修改密码      ");
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页   ");
						break;
				case 5:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,80,"5.修改密码      ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");
				        ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
				        ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页     ");
				        break;
				
				case 6:
					
					    LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,100,"6.返回上一页    ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.增加IC卡用户  ");
						ILI9341_DispString_EN_CH(0,20,"2.删除IC卡用户  ");
				        ILI9341_DispString_EN_CH(0,40,"3.增加指纹用户  ");
				        ILI9341_DispString_EN_CH(0,60,"4.删除指纹用户  ");
				        ILI9341_DispString_EN_CH(0,80,"5.修改密码      ");
						break;

						
				case 7:
									
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.确认添加  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND);
						ILI9341_DispString_EN_CH(0,20,"2.返回上一页");
						ILI9341_Clear(0, 40, 200, 20 ,BACKGROUND);
						
						break;
				
				case 8:	
					
				        LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.确认添加  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW);
						ILI9341_DispString_EN_CH(0,20,"2.返回上一页");
						ILI9341_Clear(0, 40, 200, 20 ,BACKGROUND);

						break;
						
				case 9:
                         					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"请输入录入的序号");
						
				
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,300,"确定");
				
				
							/*显示用户序号变量*/
						LCD_SetFont(&Font8x16); /*设置英文字体类型*/
						LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/

						testCNT = Count_KEY(Key);
						/*使用c标准库把变量转化成字符串*/
						sprintf(dispBuff,"%d ",testCNT);
						
						/*然后显示该字符串即可，其它变量也是这样处理*/
						ILI9341_DispString_EN_CH(150,0,dispBuff);
						
						Key = 10;					
						break;
						
				case 10:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.删除指定用户  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND);
						ILI9341_DispString_EN_CH(0,20,"2.清空指纹库  ");
						break;
						
				case 11:
					
						LCD_SetFont(&Font8x16);             
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.删除指定用户  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW);
						ILI9341_DispString_EN_CH(0,20,"2.清空指纹库  ");
						break;
						
						
				case 12:
						ee_Erase();
						ILI9341_DispString_EN_CH(0,0,"已经删除所有IC卡号");
						Delay_1ms(100000);
						ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
						Flag1=2;  //返回上一级
						break;
				
				case 13:
						
						
						ILI9341_DispString_EN_CH(0,20,"删除指定用户ID");
						LCD_SetFont(&Font8x16); /*设置英文字体类型*/
						LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
						ID = Count_KEY(Key);
						sprintf(dispBuff,"%d ",ID);
						ILI9341_DispString_EN_CH(150,20,dispBuff);
						Key = 10;
						break;
				
				case 14 : 
						Pass();
					    break;
						
				
			}//switch(Flag1)
		
		}
		 
		if(Change==3)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			LCD_SetFont(&Font8x16);
			LCD_SetColors(RED, BACKGROUND); 
			ILI9341_DispString_EN_CH(0,0,"正在添加，请放入卡片。。。");
		}
		
		
		/*用于录入IC卡用户数据*/
		while(Change==3)
		{
			RCC_Iden();
				
		}/*while(Change==3)*/
		
		
		/*若录入成功，则显示号码以及其他*/
		if(Change==4)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			ILI9341_DispString_EN_CH(0,0,"录入成功");
			ILI9341_DispString_EN_CH(0,40,cStr);
			
			ILI9341_DispString_EN_CH(0,300,"继续录入"); 
			ILI9341_DispString_EN_CH(150,300,"回到主界面"); 
		}
		
		
		/****按下按键*继续录入******/
		/****按下按键#回到主界面****/
		while(Change==4)
		{
			Matrix_Test();
		}
		
		
		/*用于显示识别成功*/
		while(Change==5)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			ILI9341_DispString_EN_CH(40,100,"识别成功,卡号:");
			LCD_SetFont(&Font8x16); /*设置英文字体类型*/
			LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
			sprintf(dispBuff,"%d",Memory_ID [4]);
			ILI9341_DispString_EN_CH(170,100,dispBuff);
			Beep_ON;
			Delay_1ms(50000);
			Beep_OFF;
			Change=1;
		}
		
		/*添加指纹*/
		while(Change == 6)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
			Add_FR();                                    /*添加指纹*/
			Change =7;
		}
		/*判断是否继续录入指纹*/
		if(Change == 7)
		{
			ILI9341_DispString_EN_CH(0,300,"继续录入"); 
			ILI9341_DispString_EN_CH(150,300,"回到主界面");
		}
		while(Change == 7)
		{
			Matrix_Test();
		}
		
		
	}/*while(1)*/
}/*main()*/



void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

/*RC522检测*/
void RCC_Iden(void)
{
		
	/*寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  
      /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                                 

		if ( ucStatusReturn == MI_OK  )
		{
			
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",
                  ucArray_ID [ 0 ], 
                  ucArray_ID [ 1 ], 
                  ucArray_ID [ 2 ], 
                  ucArray_ID [ 3 ]);
			
				
				if(Change==1)
				{

					
					for(i=0;i<40;i++)
					{
						ee_ReadBytes(Memory_ID, i*5, 5);
						   if(Memory_ID[0]==ucArray_ID[0]
							&&Memory_ID[1]==ucArray_ID[1]
							&&Memory_ID[2]==ucArray_ID[2]
							&&Memory_ID[3]==ucArray_ID[3])
						   {
								Change=5;
							    break;
						   }
						   
						   
						   
					}
				}
				
				/*如果在Change==3时存储数据*/
				if(Change==3)
				{
					
					ucArray_ID [ 4 ] = testCNT;  //用来存放地址号
					if (ee_WriteBytes(ucArray_ID, testCNT*5, 5) == 0)
					{
						//printf("写eeprom出错！\r\n");
					}
					else
					{		
						//printf("写eeprom成功！\r\n");
					}
					
						
 
					Change=4;	
				}		
				
			}		
		}
}



void Matrix_Test(void)
{
	uint16_t Temp;
	
	
/*****************第一列检测********************************/
	Write_Date(KEY_GPIO_PORT,0x1FC0); //向GPIO写入值

	Temp = Matrix_Scan(KEY_GPIO_PORT);
	
	Temp = Temp & 0x1FE0;
	
	Temp = Temp & 0x1E00; 
	
	while(Temp != 0x1E00)
	{
		SysTick_Delay_ms(5);
		Temp = Matrix_Scan(KEY_GPIO_PORT);
		Temp = Temp & 0x1FE0;
		switch(Temp)
		{
			case 0x1DC0:           //"1"
				Key = 1;break;
			case 0x1BC0:           //"4"
				Key = 4;break;
			case 0x17C0:           //"7"
				Key = 7;break;
			
			case 0x0FC0:           //"*"
				if(1 == Change)
				{
					Change=2;
					break;
				}
				
				
				if(2 == Change) 
				{
					switch(Flag1)
					{
						case 1:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//进入增加IC卡用户
								Flag1=7;
								break;
						case 2:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//进入删除IC卡用户
								Flag1=12;
								break;
						case 3:
								Change=6;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//进入指纹用户
								break;
						case 4:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//删除指纹用户
								Flag1=10;
								break;
						case 5: 
							
								Flag1 = 14;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
								break;/*修改密码*/
						case 6:
								Change=1;
								break;
						
						case 7:  
								Flag1=9;        //进入确认添加卡片
								ILI9341_Clear(0, 20, 200, 20 ,BACKGROUND);
								break;
						case 8: 
								Flag1= 1;    
								ILI9341_Clear(0, 20, 200, 20 ,BACKGROUND);
								break;
						
						case 9:            //继续添加
								Change =3;
								count =1;
								KEY = 0;
								break;
						
						case 10:  
								//进入ID选择
								Flag1 = 13;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
								break;
						
						
						case 11:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
								Clean_FR();  //清空指纹库
								Flag1=4;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //清屏
								break;
						
						case 13:
								Del_FR();      //进入删除指定指纹
								break;
						
						case 14:
								if(Flag3==1) Flag3=2;
								if(Flag3==3) Flag3=4;
					}
					
				}//if(2 == Change) 
				
				if(Change == 4)
				{
					Flag1 =9;
					Change = 2;
					ILI9341_Clear(0,0, 240, 320,BACKGROUND);
				}
				
				
				if(Change == 6)
				Flag2 = 0;
				
				if(Change == 7)
				Change = 6;
				break;
				
				
		}
		
		while(Temp!=0x1E00)								//松手检测
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
		
///*****************第二列检测********************************/	

	
Write_Date(KEY_GPIO_PORT,0x1FA0); //向GPIO写入值

	Temp = Matrix_Scan(KEY_GPIO_PORT);
	
	Temp = Temp & 0x1FE0;
	
	Temp = Temp & 0x1E00; 
	
	while(Temp != 0x1E00)
	{
		SysTick_Delay_ms(5);
		Temp = Matrix_Scan(KEY_GPIO_PORT);
		Temp = Temp & 0x1FE0;
		switch(Temp)
		{
			case 0x1DA0:           //"2"
				Key = 2;break;
			case 0x1BA0:           //"5"
				Key = 5;break;
			case 0x17A0:           //"8"
				Key = 8;break;;
			
			case 0x0FA0:           //"0"
				Key = 0;break;
		}
		
		while(Temp!=0x1E00)								//松手检测
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
///*****************第三排检测********************************/	

Write_Date(KEY_GPIO_PORT,0x1F60); //向GPIO写入值

	Temp = Matrix_Scan(KEY_GPIO_PORT);
	
	Temp = Temp & 0x1FE0;
	
	Temp = Temp & 0x1E00; 
	
	while(Temp != 0x1E00)
	{
		SysTick_Delay_ms(5);
		Temp = Matrix_Scan(KEY_GPIO_PORT);
		Temp = Temp & 0x1FE0;
		switch(Temp)
		{
			case 0x1D60:           //"3"
				Key = 3;break;
			case 0x1B60:           //"6"
				Key = 6;break;
			case 0x1760:           //"9"
				Key = 9;break;
			
			case 0x0F60:           //"#"
				Change = 1;
				Flag1=1;
				break; //防止退到主界面后再进入没有菜单
		}
		
		while(Temp!=0x1E00)								//松手检测
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
///*****************第四排检测********************************/	

Write_Date(KEY_GPIO_PORT,0x1EE0); //向GPIO写入值

	Temp = Matrix_Scan(KEY_GPIO_PORT);
	
	Temp = Temp & 0x1FE0;
	
	Temp = Temp & 0x1E00; 
	
	while(Temp != 0x1E00)
	{
		SysTick_Delay_ms(5);
		Temp = Matrix_Scan(KEY_GPIO_PORT);
		Temp = Temp & 0x1FE0;
		switch(Temp)
		{
			case 0x1CE0:           //"A"
				if(2 == Change && Flag1<7)
				{
					Flag1--;
					if(Flag1 <= 0) Flag1 =6;
					break;
				}
				
				if(2 == Change && Flag1>=7)
				{
					switch(Flag1)
					{
						case 7:      //1.确认添加 2.返回上一页
								Flag1=7; 
								break;
						case 8:
								Flag1=7;
								break;
						
						case 10 :
								Flag1=10;   //切换到删除指定用户
								break;
						case 11:
								Flag1=10;   //切换到删除指定用户//切换到清空指纹库
								break;
						
					}//switch(Flag1)	
					
				}//if(2 == Change)
				
				break;

				
			case 0x1AE0:           //"B"
				if(2 == Change && Flag1<7)
				{
					Flag1++;
					if(Flag1 > 6) Flag1 =1;
					break;
				}
				
				if(2 == Change && Flag1>=7)
				{
					switch(Flag1)
					{
						case 7:            //1.确认添加 2.返回上一页
								Flag1=8; 
								break;
						
						case 8:
								Flag1=8;
								break;
						case 10: 
								Flag1=11;   //切换到清空指纹库
								break;
						case 11:
								Flag1=11;   //切换到清空指纹库
								break;

					}
					
					
				}
				break;

			case 0x16E0:           //"C"
				 KEY =0;
				 count=1;break;
			
			case 0x0EE0:           //"D"
				switch(Flag3)
				{
					case 1:
							if(Place_pass != 0)
							Place_pass--;
							ILI9341_DispString_EN_CH(140+Place_pass*10,0," ");
							break;
					case 3:
							if(Place_pass != 0)
							Place_pass--;
							ILI9341_DispString_EN_CH(140+Place_pass*10,20," ");
							break;
					case 5:
							if(Place_pass != 0)
							Place_pass--;
							ILI9341_DispString_EN_CH(140+Place_pass*10,40," ");
							break;
						
				}
				break;
		}
		
		while(Temp!=0x1E00)								//松手检测
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}


}


uint8_t Count_KEY(uint8_t Key)
{	
	
	
	if(Key != 10)
	{
		
		if(count == 2)
		{
			KEY = KEY*10+Key;
			count = 0;
		}
		
		if(count == 1 && Key!=0)
		{
			KEY = Key;
			count ++;
		}
		
		
	}
	
	
	

	return KEY;		
}



void PASSWORD(uint8_t Key)
{
	uint8_t PassWord[6],PW_bit;
	if(Key!=10)
	{
		PassWord[PW_bit] = Key;
		PW_bit++;
		if(PW_bit == 7)
		{
			PW_bit = 0;
		}
	}

}

void Pass()
{
	uint16_t  i=0,j=0;
	uint8_t KEY22;
	
	while(1)
	{
		switch(Flag3)
		{
			case 0:
				LCD_SetFont(&Font8x16);
				LCD_SetColors(RED, BACKGROUND); 
				ILI9341_DispString_EN_CH(0,0,"请输入原密码：");
				Flag3++;
				break;
			case 1:
				
				Matrix_Test();
				KEY22 =Key;
				LCD_SetFont(&Font8x16); /*设置英文字体类型*/
				LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
				
				if(KEY22 != 10 && Place_pass<6)
				{
					Pass_Buff[Place_pass]=KEY22;
					sprintf(PassWord,"%d",  
					Pass_Buff[Place_pass]);
					ILI9341_DispString_EN_CH(140+Place_pass*10,0,PassWord);
					Place_pass++;
				}
				
				
				Key = 10;
					
				break;
				
			case 2:
					for(i=0;i<6;i++)
					{
						Pass_Buff[i]=0;
						sprintf(PassWord,"%d",  
						Pass_Buff[i]);					
					}
					Place_pass = 0;
					LCD_SetFont(&Font8x16);
					LCD_SetColors(RED, BACKGROUND); 
					ILI9341_DispString_EN_CH(0,20,"请输入新密码：");
					Flag3++;
					break;
			
			case 3:
					Matrix_Test();
					KEY22 =Key;
					LCD_SetFont(&Font8x16); /*设置英文字体类型*/
					LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
					
					if(KEY22 != 10 && Place_pass<6)
					{
						Pass_Buff[Place_pass]=KEY22;
						sprintf(PassWord,"%d",  
						Pass_Buff[Place_pass]);
						ILI9341_DispString_EN_CH(140+Place_pass*10,20,PassWord);
						Place_pass++;
					}
					
					
					Key = 10;
						
					break;
					
			case 4:
					LCD_SetFont(&Font8x16);
					LCD_SetColors(RED, BACKGROUND); 
					  Place_pass = 0;
					ILI9341_DispString_EN_CH(0,40,"再输入一次密码：");
					Flag3++;
					break;
			
			case 5:
					Matrix_Test();
					KEY22 =Key;
					LCD_SetFont(&Font8x16); /*设置英文字体类型*/
					LCD_SetTextColor(WHITE); /*设置LCD的前景(字体)颜色,RGB565*/
					
					if(KEY22 != 10 && Place_pass<6)
					{
						Pass_Buff[Place_pass]=KEY22;
						sprintf(PassWord,"%d",  
						Pass_Buff[Place_pass]);
						ILI9341_DispString_EN_CH(140+Place_pass*10,40,PassWord);
						Place_pass++;
					}
					
					
					Key = 10;
						
					break;
						
					
		}//switch(Flag3)
	}

}
