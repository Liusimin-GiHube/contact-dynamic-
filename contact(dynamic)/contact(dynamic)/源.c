#include "contact.h"

void menu()
{
	printf("*********************************************\n");
	printf("******  1. add             2. del     *******\n");
	printf("******  3. search          4. modify  *******\n");
	printf("******  5. show            6. sort    *******\n");
	printf("******  0. exit                       *******\n");
	printf("*********************************************\n");
}

int main()
{
	contact con;
	Init(&con);
	int input = 0;
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			Add(&con);
			break;
		case 2:
			Del(&con);
			break;
		case 3:
			Search(&con);
			break;
		case 4:
			Modify(&con);
			break;
		case 5:
			Show(&con);
			break;
		case 6:
			Sort(&con);
			break;
		case 0:
			SaveConcat(&con);
			printf("退出程序！");
			break;
		default:
			printf("输入错误，请重新输入!");
			break;
		}
	} while (input);
	return 0;
}