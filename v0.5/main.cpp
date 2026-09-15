#include <iostream>
#include <cmath>
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
	{0,0,0,0}};		//临时二维数组，用于翻转数组
int block_detect[4][4]={
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}};		//临时二维数组，用于检测游戏结束与否
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
void flip(int a,int (&arr)[4][4],int (&arr2)[4][4])		//翻转数组，使各种方向都成为向上，配合plus()操作方法
{
	for (int i=0;i<=3;i++)
	{
		for (int j=0;j<=3;j++)
		{
			if (a==0)//up
			{
				arr[i][j]=arr2[i][j];
			}
			else if (a==1)//left
			{
				arr[i][j]=arr2[3-j][i];
			}
			else if (a==2)//right
			{
				arr[i][j]=arr2[j][3-i];
			}
			else if (a==3)//down
			{
				arr[i][j]=arr2[3-i][j];
			}
		}
	}
}
	

void flip_back(int b,int (&arr)[4][4],int (&arr2)[4][4])	//临时数组写回原数组，反向翻转 
{
	
	
	for (int i=0;i<=3;i++)
	{
		for (int j=0;j<=3;j++)
		{
			if (b==0)//up
			{
				arr[i][j]=arr2[i][j];
			}
			else if (b==1)//left
			{
				arr[i][j]=arr2[j][3-i];
			}
			else if (b==2)//right
			{
				arr[i][j]=arr2[3-j][i];
			}
			else if (b==3)//down
			{
				arr[i][j]=arr2[3-i][j];
			}
		}
	}	
}
void reset_temporary_array(int (&arr)[4][4])	//重置临时数组
{
	for (int i=0;i<=3;i++)
		{
			for (int j=0;j<=3;j++)
			{
				arr[i][j]=0;
			}
		}	
}

int plus_all(int n,int (&arr)[4][4],int (&arr2)[4][4],bool b)		//滑动相加 0->up 1->left 2->down 3->right 
{																	//b用于判断是真实移动还是模拟移动
	flip(n,arr,arr2);
	int cl=0;//检测是否一个数字块都没动 
	for (int j=0;j<=3;j++) 
	{
		should_break=false;
		for (int i=0;i<=3 && should_break!=true;i++) 
		{ 
			if (arr[i][j]==0 && i!=3) //若数字为0，且不是第四个数，整体向上移 
			{
				int offset=0;
				int m=i;
				while (arr[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
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
					arr[n][j]=arr[n+offset][j];
					arr[n+offset][j]=0;
					cl++; 
				}
				i-=1;
			}
			else if (i!=3) 
			{
				int offset=0;
				int m=i+1;
				while (arr[m][j]==0 && m<=3)//检测到下一个非0数前有几个0 
				{
					offset++;
					m++;
				}	
				if (arr[i][j]==arr[m][j])
				{
					arr[i][j]=arr[i][j]+arr[m][j];
					arr[m][j]=0;
					cl++;
				}
			}	 
		}	
	}
	if (b==true)
	{
		flip_back(n,arr2,arr);//写回原数组
	}
	reset_temporary_array(arr);//重置临时数组
	return cl;	
}
bool game_over_detect()		//检测游戏是否结束
{
	if (plus_all(0,block_detect,block,false)+plus_all(1,block_detect,block,false)+plus_all(2,block_detect,block,false)+plus_all(3,block_detect,block,false)==0)
	{
		reset_temporary_array(block_detect);
		return true;
	}
	else
	{
		reset_temporary_array(block_detect);	
		return false;
	}
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
				a=plus_all(0,block_temporary,block,true);
			else if(ch==97)//a
				a=plus_all(1,block_temporary,block,true);
			else if(ch==100)//d
				a=plus_all(2,block_temporary,block,true);
			else if(ch==115)//s
				a=plus_all(3,block_temporary,block,true);
			
			if (a!=0)
			{
				genarate();
				system("cls");
				print();
				if (game_over_detect()==true)
				{
					cout<<"Game Over!";
					//此处去除break，因为有使用者按太快导致控制台关闭
				}
			}
			a=0;
		}
	}
	return 0;
} 

