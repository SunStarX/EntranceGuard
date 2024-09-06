#include "main.h"

/*ȫ�ֱ���*/
char cStr [ 30 ];
uint8_t ucArray_ID [ 5 ];  /*�Ⱥ���IC�������ͺ�UID(IC�����к�)*/ 
uint8_t ucIC_Card1[4];
uint8_t ucStatusReturn;    /*����״̬*/                                                                                         
static u8 ucLineCount = 2; 
uint8_t Memory_ID[40]; //���ڴ洢ID��������
static uint8_t testCNT = 0;
char dispBuff[100];
uint8_t Count=4,i; //����ѭ������
uint8_t Change=1; //���ڲ˵��л��ı�־λ
uint8_t Flag1=1;  

extern uint8_t Flag2;
uint8_t Flag3;

extern uint8_t Key;  //����ֵ

/*�������������õ����м����*/
static uint8_t KEY=0;
static uint8_t count=1;

/*ָ��ID*/
uint32_t  ID=0;

/*�洢����*/
char PassWord[10];
uint8_t Pass_Buff[10]={0,0,0,0,0,0};
uint8_t Place_pass,Place_Flag;


//extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
//extern uint8_t aDST_Buffer[BUFFER_SIZE];


/*��ʱ����*/
void Delay(uint32_t Count)
{
	for(;Count!=0;Count--);
}

/*******Ӳ����ʼ��******/
void Hard_Init(void)
{
	Beep_GPIO_Config();  //��������ʼ��
	//Matrix_Key_Config();   //���󰴼���ʼ��
	//RC522_Init();  		 //RC522ģ����������ĳ�ʼ������
	ILI9341_Init();      //LCD��ʾ����ʼ��
	ILI9341_Clear(0,0, 240, 320,BACKGROUND);
	//PcdReset ();         //��λRC522
	//M500PcdConfigISOType ( 'A' );  /*���ù�����ʽ*/
	LED_GPIO_Config();  //LED�Ƴ�ʼ��
	/*��ʼ�����λ�����*/
	rx_queue_init();
   
	/*��ʼ��ָ��ģ������*/
	AS608_Config();
	USART_Config();
	/*����STM32��ָ��ģ���ͨ��*/
    //Connect_Test();

	ee_Test();//��ʼ��E2PROM

	
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
			ILI9341_DispString_EN_CH(50,0,"�����Ž�ϵͳ");
			ILI9341_DispString_EN_CH(0,300,"����");
			
			//ILI9341_DispString_EN_CH(10,100,"�밴ָ�ƽ���");
		}
		/*�˵�һ*/
		while(Change==1)
		{
			//RCC_Iden();   //ʶ���Ž���
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
		/*�˵���*/
		while(Change==2)
		{
			Matrix_Test();
			switch(Flag1)
			{
				case 1:	
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");
				        ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,80,"5.�޸�����    ");
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ    ");
						break;
				case 2:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");						
				        ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,80,"5.�޸�����    ");
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ    ");
						break;
				
				case 3:                         
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");				        
				        ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,80,"5.�޸�����      ");
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ    ");
						break;
						
						
				case 4: 
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");
				        ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,80,"5.�޸�����      ");
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ   ");
						break;
				case 5:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,80,"5.�޸�����      ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");
				        ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ     ");
				        break;
				
				case 6:
					
					    LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,100,"6.������һҳ    ");
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.����IC���û�  ");
						ILI9341_DispString_EN_CH(0,20,"2.ɾ��IC���û�  ");
				        ILI9341_DispString_EN_CH(0,40,"3.����ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,60,"4.ɾ��ָ���û�  ");
				        ILI9341_DispString_EN_CH(0,80,"5.�޸�����      ");
						break;

						
				case 7:
									
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.ȷ�����  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND);
						ILI9341_DispString_EN_CH(0,20,"2.������һҳ");
						ILI9341_Clear(0, 40, 200, 20 ,BACKGROUND);
						
						break;
				
				case 8:	
					
				        LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.ȷ�����  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW);
						ILI9341_DispString_EN_CH(0,20,"2.������һҳ");
						ILI9341_Clear(0, 40, 200, 20 ,BACKGROUND);

						break;
						
				case 9:
                         					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"������¼������");
						
				
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,300,"ȷ��");
				
				
							/*��ʾ�û���ű���*/
						LCD_SetFont(&Font8x16); /*����Ӣ����������*/
						LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/

						testCNT = Count_KEY(Key);
						/*ʹ��c��׼��ѱ���ת�����ַ���*/
						sprintf(dispBuff,"%d ",testCNT);
						
						/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
						ILI9341_DispString_EN_CH(150,0,dispBuff);
						
						Key = 10;					
						break;
						
				case 10:
					
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW); 
						ILI9341_DispString_EN_CH(0,0,"1.ɾ��ָ���û�  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, BACKGROUND);
						ILI9341_DispString_EN_CH(0,20,"2.���ָ�ƿ�  ");
						break;
						
				case 11:
					
						LCD_SetFont(&Font8x16);             
						LCD_SetColors(RED, BACKGROUND); 
						ILI9341_DispString_EN_CH(0,0,"1.ɾ��ָ���û�  ");
						LCD_SetFont(&Font8x16);
						LCD_SetColors(RED, YELLOW);
						ILI9341_DispString_EN_CH(0,20,"2.���ָ�ƿ�  ");
						break;
						
						
				case 12:
						ee_Erase();
						ILI9341_DispString_EN_CH(0,0,"�Ѿ�ɾ������IC����");
						Delay_1ms(100000);
						ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
						Flag1=2;  //������һ��
						break;
				
				case 13:
						
						
						ILI9341_DispString_EN_CH(0,20,"ɾ��ָ���û�ID");
						LCD_SetFont(&Font8x16); /*����Ӣ����������*/
						LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
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
			ILI9341_DispString_EN_CH(0,0,"������ӣ�����뿨Ƭ������");
		}
		
		
		/*����¼��IC���û�����*/
		while(Change==3)
		{
			RCC_Iden();
				
		}/*while(Change==3)*/
		
		
		/*��¼��ɹ�������ʾ�����Լ�����*/
		if(Change==4)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			ILI9341_DispString_EN_CH(0,0,"¼��ɹ�");
			ILI9341_DispString_EN_CH(0,40,cStr);
			
			ILI9341_DispString_EN_CH(0,300,"����¼��"); 
			ILI9341_DispString_EN_CH(150,300,"�ص�������"); 
		}
		
		
		/****���°���*����¼��******/
		/****���°���#�ص�������****/
		while(Change==4)
		{
			Matrix_Test();
		}
		
		
		/*������ʾʶ��ɹ�*/
		while(Change==5)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);
			ILI9341_DispString_EN_CH(40,100,"ʶ��ɹ�,����:");
			LCD_SetFont(&Font8x16); /*����Ӣ����������*/
			LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
			sprintf(dispBuff,"%d",Memory_ID [4]);
			ILI9341_DispString_EN_CH(170,100,dispBuff);
			Beep_ON;
			Delay_1ms(50000);
			Beep_OFF;
			Change=1;
		}
		
		/*���ָ��*/
		while(Change == 6)
		{
			ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
			Add_FR();                                    /*���ָ��*/
			Change =7;
		}
		/*�ж��Ƿ����¼��ָ��*/
		if(Change == 7)
		{
			ILI9341_DispString_EN_CH(0,300,"����¼��"); 
			ILI9341_DispString_EN_CH(150,300,"�ص�������");
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

/*RC522���*/
void RCC_Iden(void)
{
		
	/*Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  
      /*��ʧ���ٴ�Ѱ��*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                                 

		if ( ucStatusReturn == MI_OK  )
		{
			
      /*����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			
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
				
				/*�����Change==3ʱ�洢����*/
				if(Change==3)
				{
					
					ucArray_ID [ 4 ] = testCNT;  //������ŵ�ַ��
					if (ee_WriteBytes(ucArray_ID, testCNT*5, 5) == 0)
					{
						//printf("дeeprom����\r\n");
					}
					else
					{		
						//printf("дeeprom�ɹ���\r\n");
					}
					
						
 
					Change=4;	
				}		
				
			}		
		}
}



void Matrix_Test(void)
{
	uint16_t Temp;
	
	
/*****************��һ�м��********************************/
	Write_Date(KEY_GPIO_PORT,0x1FC0); //��GPIOд��ֵ

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
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//��������IC���û�
								Flag1=7;
								break;
						case 2:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//����ɾ��IC���û�
								Flag1=12;
								break;
						case 3:
								Change=6;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//����ָ���û�
								break;
						case 4:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);//ɾ��ָ���û�
								Flag1=10;
								break;
						case 5: 
							
								Flag1 = 14;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
								break;/*�޸�����*/
						case 6:
								Change=1;
								break;
						
						case 7:  
								Flag1=9;        //����ȷ����ӿ�Ƭ
								ILI9341_Clear(0, 20, 200, 20 ,BACKGROUND);
								break;
						case 8: 
								Flag1= 1;    
								ILI9341_Clear(0, 20, 200, 20 ,BACKGROUND);
								break;
						
						case 9:            //�������
								Change =3;
								count =1;
								KEY = 0;
								break;
						
						case 10:  
								//����IDѡ��
								Flag1 = 13;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
								break;
						
						
						case 11:
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
								Clean_FR();  //���ָ�ƿ�
								Flag1=4;
								ILI9341_Clear(0,0, 240, 320,BACKGROUND);  //����
								break;
						
						case 13:
								Del_FR();      //����ɾ��ָ��ָ��
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
		
		while(Temp!=0x1E00)								//���ּ��
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
		
///*****************�ڶ��м��********************************/	

	
Write_Date(KEY_GPIO_PORT,0x1FA0); //��GPIOд��ֵ

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
		
		while(Temp!=0x1E00)								//���ּ��
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
///*****************�����ż��********************************/	

Write_Date(KEY_GPIO_PORT,0x1F60); //��GPIOд��ֵ

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
				break; //��ֹ�˵���������ٽ���û�в˵�
		}
		
		while(Temp!=0x1E00)								//���ּ��
		{
			Temp = Matrix_Scan(KEY_GPIO_PORT);
			Temp = Temp & 0x1FE0;
			Temp = Temp&0x1E00;
		}
	
	}
///*****************�����ż��********************************/	

Write_Date(KEY_GPIO_PORT,0x1EE0); //��GPIOд��ֵ

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
						case 7:      //1.ȷ����� 2.������һҳ
								Flag1=7; 
								break;
						case 8:
								Flag1=7;
								break;
						
						case 10 :
								Flag1=10;   //�л���ɾ��ָ���û�
								break;
						case 11:
								Flag1=10;   //�л���ɾ��ָ���û�//�л������ָ�ƿ�
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
						case 7:            //1.ȷ����� 2.������һҳ
								Flag1=8; 
								break;
						
						case 8:
								Flag1=8;
								break;
						case 10: 
								Flag1=11;   //�л������ָ�ƿ�
								break;
						case 11:
								Flag1=11;   //�л������ָ�ƿ�
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
		
		while(Temp!=0x1E00)								//���ּ��
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
				ILI9341_DispString_EN_CH(0,0,"������ԭ���룺");
				Flag3++;
				break;
			case 1:
				
				Matrix_Test();
				KEY22 =Key;
				LCD_SetFont(&Font8x16); /*����Ӣ����������*/
				LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
				
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
					ILI9341_DispString_EN_CH(0,20,"�����������룺");
					Flag3++;
					break;
			
			case 3:
					Matrix_Test();
					KEY22 =Key;
					LCD_SetFont(&Font8x16); /*����Ӣ����������*/
					LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
					
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
					ILI9341_DispString_EN_CH(0,40,"������һ�����룺");
					Flag3++;
					break;
			
			case 5:
					Matrix_Test();
					KEY22 =Key;
					LCD_SetFont(&Font8x16); /*����Ӣ����������*/
					LCD_SetTextColor(WHITE); /*����LCD��ǰ��(����)��ɫ,RGB565*/
					
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
