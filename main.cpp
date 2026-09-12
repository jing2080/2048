#include<bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
bool should_break=false;
int block[4][4]={
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}};		//初始化二维数组，存储数字块对应的数字 
int block_temporary[4][4]={
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}};		//临时二维数组 
int random_num()	//生成随机数以抽取新生成的数字块为2或4
{
	int i=rand() % 10;
	if 	(i<=4)
	{
		return 2;
	}
	else return 4;
} 
int random_block()		//随机选择区块生成数字 
{
	int i=rand() % 4;
	return i;
}

void print()	//打印数字块 
{	
	for (int i=0;i<=3;i++) 
	{
		for (int j=0;j<=3;j++) 
		{ 
			cout << " " << setw(6) << block[i][j] << " ";	//格式化输出 
		}
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
	}
}
void genarate()		//生成数字块 
{
	int a=random_num();
	int x,y;
	while (true)
	{
		x=random_block();
		y=random_block();
		if (block[x][y]==0)
		{
			break;
		}
	}
	block[x][y]=a;
}
int plus_up()		//滑动相加(向上)
{
	int cl=0;//检测是否一个数字块都没动 
	for (int j=0;j<=3;j++) 
	{
		should_break=false;
		for (int i=0;i<=3 && should_break!=true;i++) 
		{ 
			if (block[i][j]==0 && i!=3) //若数字为0，且不是第四个数，整体向上移 
			{
				int offset=0;
				int m=i;
				while (block[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}
				if (m>=3) //若从某位到最后一位均为0，跳出内层for循环 
				{
					should_break=true;
				}
				for (int n=i;n<=3-offset && should_break!=true;n++)//移位 
				{
					block[n][j]=block[n+offset][j];
					block[n+offset][j]=0;
					cl++; 
				}
				i-=1;
			}
			else if (i!=3) 
			{
				int offset=0;
				int m=i+1;
				while (block[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}	
				if (block[i][j]==block[m][j])
				{
					block[i][j]=block[i][j]+block[m][j];
					block[m][j]=0;
					cl++;
				}
			}	 
		}	
	}
	return cl;	
}
int plus_left()		//滑动相加(向左)
{
	int cl=0;//检测是否一个数字块都没动 
	for (int i=0;i<=3;i++) 
	{
		should_break=false;
		for (int j=0;j<=3 && should_break!=true;j++) 
		{ 
			if (block[i][j]==0 && j!=3) //若数字为0，且不是第四个数，整体向左移 
			{
				int offset=0;
				int m=j;
				while (block[i][m]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}
				if (m>=3) //若从某位到最后一位均为0，跳出内层for循环 
				{
					should_break=true;
				}
				for (int n=j;n<=3-offset && should_break!=true;n++)//移位 
				{
					block[i][n]=block[i][n+offset];
					block[i][n+offset]=0;
					cl++; 
				}
				j-=1;
			}
			else if (j!=3) 
			{
				int offset=0;
				int m=j+1;
				while (block[i][m]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}	
				if (block[i][j]==block[i][m])
				{
					block[i][j]=block[i][j]+block[i][m];
					block[i][m]=0;
					cl++;
				}
			}	 
		}	
	}
	return cl;	
}
int plus_right()		//滑动相加(向右)
{
	int cl=0;//检测是否一个数字块都没动 
	for (int i=3;i>=0;i--) 
	{
		should_break=false;
		for (int j=3;j>=0 && should_break!=true;j--) 
		{ 
			if (block[i][j]==0 && j!=0) //若数字为0，且不是第1个数，整体向右移 
			{
				int offset=0;
				int m=j;
				while (block[i][m]==0 && m>=0)//检测到下一个非0数前有几个0 
				{
					offset--;
					m--;
				}
				if (m<=0) //若从某位到最后一位均为0，跳出内层for循环 
				{
					should_break=true;
				}
				for (int n=j;n>=0-offset && should_break!=true;n--)//移位 
				{
					block[i][n]=block[i][n+offset];
					block[i][n+offset]=0;
					cl++; 
				}
				j+=1;
			}
			else if (j!=0) 
			{
				int offset=0;
				int m=j-1;
				while (block[i][m]==0 && m>=0)//检测到下一个非0数前有几个0 
				{
					offset--;
					m--;
				}	
				if (block[i][j]==block[i][m])
				{
					block[i][j]=block[i][j]+block[i][m];
					block[i][m]=0;
					cl++;
				}
			}	 
		}	
	}
	return cl;	
}
int plus_down()		//滑动相加(向下)
{
	int cl=0;//检测是否一个数字块都没动 
	for (int j=3;j>=0;j--) 
	{
		should_break=false;
		for (int i=3;i>=0 && should_break!=true;i--) 
		{ 
			if (block[i][j]==0 && i!=0) //若数字为0，且不是第四个数，整体向下移 
			{
				int offset=0;
				int m=i;
				while (block[m][j]==0 && m>=0)//检测到下一个非0数前有几个0 
				{
					offset--;
					m--;
				}
				if (m<=0) //若从某位到最后一位均为0，跳出内层for循环 
				{
					should_break=true;
				}
				for (int n=i;n>=0-offset && should_break!=true;n--)//移位 
				{
					block[n][j]=block[n+offset][j];
					block[n+offset][j]=0;
					cl++; 
				}
				i+=1;
			}
			else if (i!=0) 
			{
				int offset=0;
				int m=i-1;
				while (block[m][j]==0 && m>=0)//检测到下一个非0数前有几个0 
				{
					offset--;
					m--;
				}	
				if (block[i][j]==block[m][j])
				{
					block[i][j]=block[i][j]+block[m][j];
					block[m][j]=0;
					cl++;
				}
			}	 
		}	
	}
	return cl;	
}
int main()
{
	genarate();
	genarate();
	print();
	int a=0;
	while (true)
	{
		if (_kbhit()) 
		{
            int ch = _getch(); 
	
			if(ch==119)
				a=plus_up();
			else if(ch==97)
				a=plus_left();
			else if(ch==115)
				a=plus_down();
			else if(ch==100)
				a=plus_right();
			if (a!=0)
			{
				genarate();
				system("cls");
				print();
			}
		}
	}
} 

