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
		printf("��ѡ��");
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
			printf("�˳�����");
			break;
		default:
			printf("�����������������!");
			break;
		}
	} while (input);
	return 0;
}