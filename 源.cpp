#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void gne(int* arr, int len);
void gotoxy(int x, int y) //将光标移动到坐标为(x,y)的地方
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void menu()
{
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t欢迎使用PCM计算器\n");
	printf("\t\t\t--------------------------------------\n\n");
	printf("\t\t\t1.抽样值编码并计算量化值及误差\n\n");
	printf("\t\t\t2.PCM编码转量化值\n\n\n\n\n\n\n");
	printf("\t\t\t你的选择:\n\n");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	//system("color 0a");
	printf("\t\t\t\t\t\t\t\t版本-V1.0.2\n");
	printf("\t\t\t\t\t\t\t\t鱼汤！ 制作\n");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(33,15);                                    //移动光标
}
void error1()
{
	system("cls");
	printf("\n\n\n\t\t\t\tERROR\n\n");
	printf("\t\t\t请从1、2中选择一个\n\n");
	printf("\t\t\t将在3s后返回选择界面");
	Sleep(3000);
}
void sr()
{
	int b = 0,b1;
	char z[13];
	int a[8];
	//int *p1;
	//p1 = (int*)malloc(sizeof(int) * 8);
	do
	{
		b = 0;
		do
		{
			system("cls");
			printf("\n\n\n");
			printf("输入--8位--PCM编码:");
			scanf("%s", z);
			if (strlen(z) != 8)
			{
				printf("\n\n\n你输入的有问题！！！\n\n你输入了：%d位！！！\n\n请你输入8位！！！\n\n3秒后重输！！！\n\n\n", strlen(z));
				Sleep(3000);
			}

		} while (strlen(z) != 8);
		while (b < 8)
		{
			b1 = 0;
			a[b] = z[b] - 48;
			//p1[b] = a[b];
			if (a[b] != 0 && a[b] != 1)
			{
				printf("\n\n你的输入真的有问题，只能输0、1\n\n3秒后重输！！！\n\n\n");
				Sleep(3000);
				b = 8;
				//break;
				b1 = 1;
			}
			b++;
		}
	}while(b1);
	printf("\n\n你的输入的码是：");
	b = 0;
	while (b<8)
	{
		printf("%d", a[b]);
		b++;
	}
	gne(a, 8);
}
void gny()                   //抽样值编码
{
	int a,a1,b[8],c1,d1,d2,d3=0;
	system("cls");
	printf("\n\n\n");
	printf("输入需要转化的值");
	scanf("%d",&a);
	do
	{
		if (a < -2048 && a>2048)
			printf("你输入的数真的有问题！！！");
	} while (a < -2048 && a>2048);
	if (a > 0)
	{
		b[0] = 1;
	}
	else
	{
		b[0] = 0;
		a = a*(-1);
	}
	if (a >= 0 && a < 16)
	{
		b[1] = 0;
		b[2] = 0;
		b[3] = 0;
	}
	else
	{
		if (a < 32)
		{
			b[1] = 0;
			b[2] = 0;
			b[3] = 1;
		}
		else
		{
			if (a < 64)
			{
				b[1] = 0;
				b[2] = 1;
				b[3] = 0;
			}
			else
			{
				if (a < 128)
				{
					b[1] = 0;
					b[2] = 1;
					b[3] = 1;
				}
				else
				{
					if (a < 256)
					{
						b[1] = 1;
						b[2] = 0;
						b[3] = 0;
					}
					else
					{
						if (a < 512)
						{
							b[1] = 1;
							b[2] = 0;
							b[3] = 1;
						}
						else
						{
							if (a < 1024)
							{
								b[1] = 1;
								b[2] = 1;
								b[3] = 0;
							}
							else
							{
								b[1] = 1;
								b[2] = 1;
								b[3] = 1;
							}
						}
					}
				}
			}
		}
	}
	c1 = b[1] * 4 + b[2] * 2 + b[3];
	switch (c1)
	{
	case 0:d1 = 0; break;
	case 1:d1 = 16; break;
	case 2:d1 = 32; break;
	case 3:d1 = 64; break;
	case 4:d1 = 128; break;
	case 5:d1 = 256; break;
	case 6:d1 = 512; break;
	case 7:d1 = 1024; break;
	}
	a1 = a - d1+1;       //判断要大于等于，用加以不改大于号
	switch (c1)
	{
	case 0:d2 = 1; break;
	case 1:d2 = 1; break;
	case 2:d2 = 2; break;
	case 3:d2 = 4; break;
	case 4:d2 = 8; break;
	case 5:d2 = 16; break;
	case 6:d2 = 32; break;
	case 7:d2 = 64; break;
	}
	if (a1 > (d2 * 8))
	{
		b[4] = 1;
		if (a1 > (d2 * (8 + 4)))
		{
			b[5] = 1;
			if (a1 > (d2 * (8 + 4 + 2)))
			{
				b[6] = 1;
				if (a1 > (d2 * (8 + 4 + 2 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
			else
			{
				b[6] = 0;
				if (a1 > (d2 * (8 + 4 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
		}
		else
		{
			b[5] = 0;
			if (a1 > (d2 * (8 + 2)))
			{
				b[6] = 1;
				if (a1 > (d2 * (8 + 2 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
			else
			{
				b[6] = 0;
				if (a1 > (d2 * (8 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
		}
	}
	else
	{
		b[4] = 0;
		if (a1 > (d2 * 4))
		{
			b[5] = 1;
			if (a1 > (d2 * (4 + 2)))
			{
				b[6] = 1;
				if (a1 > (d2 * (4 + 2 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
			else
			{
				b[6] = 0;
				if (a1 > (d2 * (4 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
		}
		else
		{
			b[5] = 0;
			if (a1 > (d2 * 2))
			{
				b[6] = 1;
				if (a1 > (d2 * (2 + 1)))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
			else
			{
				b[6] = 0;
				if (a1 > (d2 * 1))
				{
					b[7] = 1;
				}
				else
				{
					b[7] = 0;
				}
			}
		}
	}
	printf("\n\n%d编好的8位码是：",a);
	while (d3<8)
	{
		printf("%d", b[d3]);
		d3++;
	}
	

	gne(b,8);
}

void gne(int* arr,int len)                  //PCM编码转量化值
{
	
	int	a1,a[8],b = 0, c1, c2, d1, d2,d3=1;
	double d;
	char z[9];
	while(b<8)
	{
		a[b] = arr[b];
		b++;
	}
		/*system("cls");
		printf("\n\n\n");
		printf("输入--8位--PCM编码:");
		scanf("%s", z);
		while (b < 8)
		{
			a[b] = z[b] - 48;
			if (a[b] != 0 && a[b] != 1)
			{
				printf("\n\n你的输入真的有问题，只能输0、1");
				b--;
			}
			else
				b++;
		}
		printf("\n\n你的输入的码是：");
		b = 0;
		while (b<8)
		{
			printf("%d", a[b]);
			b++;
		}*/
	
	c1 = a[3] + a[2] * 2 + a[1] * 4;
	switch (c1)
	{
	case 0:d1 = 0; break;
	case 1:d1 = 16; break;
	case 2:d1 = 32; break;
	case 3:d1 = 64; break;
	case 4:d1 = 128; break;
	case 5:d1 = 256; break;
	case 6:d1 = 512; break;
	case 7:d1 = 1024; break;
	}

	c2 = a[7] + a[6] * 2 + a[5] * 4 + a[4] * 8;
	switch (c1)
	{
	case 0:d2 = 1; break;
	case 1:d2 = 1; break;
	case 2:d2 = 2; break;
	case 3:d2 = 4; break;
	case 4:d2 = 8; break;
	case 5:d2 = 16; break;
	case 6:d2 = 32; break;
	case 7:d2 = 64; break;
	}
	if (a[0] == 0)
	{
		d3 = -1;
	}
	d =( d1 + d2*c2 + double(d2) / 2)*d3;
	printf("\n\n量化编码是：%.1lf\n\n\n\n", d);
}
//void gns(int a,int b)                  //误差
//{
//	int c;
//	c = a - b;
//	printf("\n\n量化误差是：%d\n\n\n\n",c);
//	
//}



int main()
{
	int a;
	menu();
	do                              //选择大方向
	{
		scanf("%d", &a);
		if (a != 1 && a != 2)
		{
			error1();
			menu();
		}
	} while (a != 1 && a != 2);

	if (a == 1)
	{
		gny();
		//gne();
	}
	else
	{
		sr();
	   //gne();
	}
	
	
	
	
	system("pause");
	return 0;
	
}