//宏定义
#define uchar unsigned char 
#define uint unsigned int
sbit rs = P2^6;
sbit en = P2^7;
uchar num=0;
void delay1602(uint x)
{
  uint i,j;
  for(i=x;i>0;i--)
     for(j=110;j>0;j--);
}
void write_com(uchar com)
{
	rs=0;//命令
	P0=com;
	delay1602(5);
	en=1;
	delay1602(5);
	en=0;
}
void write_date(uchar date)
{
	rs=1;//数据
	P0=date;
	delay1602(5);
	en=1;
	delay1602(5);
	en=0;
}
void init1602()
{
	write_com(0x38);	//设置工作方式
	write_com(0x0c);	//设置光标
	write_com(0x06);	//设置输入方式
	write_com(0x01);	//清屏
	write_com(0x80);

}	
void write_num(uchar add, uchar date, uchar row)
{
    uchar shi,ge;
    shi = date / 10;
    ge = date % 10;
    if(row == 1) {
        write_com(0x80 + add); // 第一行的显示位置
    } else if(row == 2) {
        write_com(0x80 + 0x40 + add); // 第二行的显示位置
    }
    write_date(0x30 + shi);
    write_date(0x30 + ge);
}
/********************************************************
函数名称:lcd1602_write_character(uchar x,uchar y,uchar *p)
函数作用:LCD1602显示一个字符
参数说明:在横坐标x（0~7），纵坐标y（1~2）开始显示字符串*p
lcd1602_write_character(0,1,"Intelligent car");	   //初始化显示的文字
********************************************************/
void lcd1602_write_character(uchar x,uchar y,uchar *p) 
{ 
	uchar add; 
	if(y==1) 
		add=0x80+x; 
	else 
		add=0xc0+x;
	write_com(add); 
	while (*p!='\0') 
	{ 
		write_date(*p++);
	} 
}