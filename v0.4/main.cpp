#include<bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include"color.h"
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
	int basecolor[100]={4,5,3,2,1,162,6,7,8,48,226,167,96,56,202,144,130,63,213,52,111};   	         
	for (int i=0;i<=3;i++) 
	{
		for (int j=0;j<=3;j++) 
		{ 
			int n=0;
			while (pow(2,n)!=block[i][j] && block[i][j]!=0)
			{
				n++;
			}
			int color=basecolor[n];
			setFG(color);
			cout << " " << setw(6) << block[i][j] << " ";//格式化输出 
			reset();	
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
void flip(int a)		//翻转数组，使各种方向都成为向上，配合plus()操作方法
{
	if (a==0)//up
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block_temporary[i][j]=block[i][j];
			}
		}
	}
	else if (a==1)//left
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block_temporary[i][j]=block[3-j][i];
			}
		}
	}
	else if (a==2)//right
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block_temporary[i][j]=block[j][3-i];
			}
		}
	}
	else if (a==3)//down
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block_temporary[i][j]=block[3-i][j];
			}
		}
	}
}
void flip_back(int b)	//临时数组写回原数组，反向翻转 
{
	if (b==0)//up
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block[i][j]=block_temporary[i][j];
			}
		}
	}
	if (b==1)//left
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block[i][j]=block_temporary[j][3-i];
			}
		}
	}
	if (b==2)//right
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block[i][j]=block_temporary[3-j][i];
			}
		}
	}
	if (b==3)//down
	{
		for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block[i][j]=block_temporary[3-i][j];
			}
		}
	}
}
void reset_temporary_array()	//重置临时数组
{
	for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				block_temporary[i][j]=0;
			}
		}	
}

int plus_all(int n)		//滑动相加 0->up 1->left 2->down 3->right
{
	flip(n);
	int cl=0;//检测是否一个数字块都没动 
	for (int j=0;j<=3;j++) 
	{
		should_break=false;
		for (int i=0;i<=3 && should_break!=true;i++) 
		{ 
			if (block_temporary[i][j]==0 && i!=3) //若数字为0，且不是第四个数，整体向上移 
			{
				int offset=0;
				int m=i;
				while (block_temporary[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}
				if (m>3) //若从某位到最后一位均为0，跳出内层for循环 
				{
					should_break=true;
				}
				for (int n=i;n<=3-offset && should_break!=true;n++)//移位 
				{
					block_temporary[n][j]=block_temporary[n+offset][j];
					block_temporary[n+offset][j]=0;
					cl++; 
				}
				i-=1;
			}
			else if (i!=3) 
			{
				int offset=0;
				int m=i+1;
				while (block_temporary[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}	
				if (block_temporary[i][j]==block_temporary[m][j])
				{
					block_temporary[i][j]=block_temporary[i][j]+block_temporary[m][j];
					block_temporary[m][j]=0;
					cl++;
				}
			}	 
		}	
	}
	flip_back(n);//写回原数组
	reset_temporary_array();//重置临时数组
	return cl;	
}

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	genarate();
	genarate();
	print();
	int a=0;
	while (true)
	{
		if (_kbhit()) 
		{
            int ch = _getch(); 
	
			if(ch==119)//w
				a=plus_all(0);
			else if(ch==97)//a
				a=plus_all(1);
			else if(ch==100)//d
				a=plus_all(2);
			else if(ch==115)//s
				a=plus_all(3);
			
			if (a!=0)
			{
				genarate();
				system("cls");
				print();
			}
			a=0;
		}
	}
	return 0;
} 

