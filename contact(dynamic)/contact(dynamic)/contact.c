#include "contact.h"

//判断通讯录满了吗
void check_contact(contact* pc)
{
	assert(pc);
	//判断通讯录满了吗
	if (pc->count == pc->capacity)
	{
		pc->data = (peo*)realloc(pc->data, (pc->capacity + ADD_SIZE) * sizeof(peo));
		if (pc->data == NULL)
		{
			printf("Add::%s\n", strerror(errno));
			return;
		}
		else
		{
			pc->capacity += ADD_SIZE;
		}
	}
}


//读取文件
void readFile(contact* pc)
{
	FILE* file1 = fopen("contact.txt", "rb");
	if (file1 == NULL)
		return;
	peo tmp = { 0 };
	while (fread(&tmp, sizeof(peo), 1, file1) == 1)
	{
		if ((pc->count) >= 3 && (pc->count % 2) == 1)
			check_contact(pc);
		pc->data[pc->count] = tmp;
		pc->count++;
	}	
	fclose(file1);
	file1 = NULL;
}


//初始化通讯录(动态版本)
void Init(contact* pc)
{
	assert(pc); //指针不能为空
	pc->count = 0;
	//申请内存
	pc->data = (peo*)calloc(INIT_SIZE, sizeof(peo));
	//判断指针是否为空
	if (pc->data == NULL)
	{
		printf("Init::%s\n", strerror(errno));
	}
	//读入文件
	readFile(pc);
}



//添加联系人
void Add(contact* pc)
{
	assert(pc);
	check_contact(pc);
	printf("请输入名字：");
	//[pc->count]为data的下标，在已有联系人后面添加，data为数组,数组名为地址，不用“&”
	scanf("%s", pc->data[pc->count].name);
	printf("请输入年龄：");
	scanf("%d", &(pc->data[pc->count].age));
	printf("请输入性别(选择数字> 1:男 0:女)：");
	scanf("%d", &(pc->data[pc->count].gender));
	printf("请输入电话：");
	scanf("%s", pc->data[pc->count].tel);
	printf("请输入地址：");
	scanf("%s", pc->data[pc->count].address);

	pc->count++;
	printf("添加成功!\n");
}


//展示通讯录
void Show(const contact* pc)
{
	assert(pc);
	printf("   %-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");	//%3d--占三位数字空间
	for (int i = 0; i < pc->count; i++)
	{
		printf(" %d ", i + 1);
		printf("%-20s\t%-3d\t%-1d\t%-12s\t%-30s\n", pc->data[i].name,
			pc->data[i].age,
			pc->data[i].gender,
			pc->data[i].tel,
			pc->data[i].address);
	}

}


//查找联系人
int FindName(char* name, const contact* pc)
{
	for (int i = 0; i < pc->count; i++)
	{
		if (strcmp(name, pc->data[i].name) == 0)
			return i;
	}
	return -1;
}


//打印要查找联系人
void Search(const contact* pc)
{
	assert(pc);
	printf("输入要查找人的姓名：");
	char name[20];
	scanf("%s", name);
	int i = FindName(name, pc);
	if (i > -1)
	{
		printf("   %-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");
		printf("   %-20s\t%-3d\t%-1d\t%-12s\t%-30s\n", pc->data[i].name,
			pc->data[i].age,
			pc->data[i].gender,
			pc->data[i].tel,
			pc->data[i].address);
	}
	else
	{
		printf("没有找到！\n");
	}
	return;
}


//删除联系人
void Del(contact* pc)
{
	assert(pc);
	printf("输入要删除人的姓名：");
	char name[20];
	scanf("%s", name);
	int i = FindName(name, pc);
	if (i > -1)
	{
		for (int j = i; j < pc->count - 1; j++)
		{
			pc->data[j] = pc->data[j + 1];
		}
		pc->count--;
		printf("删除成功!\n");
	}
	else
	{
		printf("没有找到！\n");
	}
}



//修改菜单
void menu1()
{
	printf("*********************************************\n");
	printf("*****  1. 修改姓名         2. 修改年龄    *****\n");
	printf("*****  3. 修改性别          4. 修改电话    *****\n");
	printf("*****  5. 修改地址         ********************\n");
	printf("*********************************************\n");
}
//修改联系人
void Modify(contact* pc)
{
	assert(pc);
	printf("输入要修改人的姓名：");
	char name[20];
	int input = 0;
	scanf("%s", name);
	int i = FindName(name, pc);
	do
	{
		menu1();
		printf("请选择:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("请输入修改后的名字：");
			scanf("%s", pc->data[i].name);
			break;
		case 2:
			printf("请输入修改后的年龄：");
			scanf("%d", &(pc->data[i].age));
			break;
		case 3:
			printf("请输入修改后的性别(选择数字> 1:男 0:女)：");
			scanf("%d", &(pc->data[i].gender));
			break;
		case 4:
			printf("请输入修改后的电话：");
			scanf("%s", pc->data[i].tel);
			break;
		case 5:
			printf("请输入修改后的地址：");
			scanf("%s", pc->data[i].address);
			break;
		case 0:
			printf("退出程序！");
			break;
		default:
			printf("输入错误，请重新输入!");
			break;
		}
		printf("修改成功!\n");
		if (input != 0)
		{
			printf("是否还有修改? 1:是  0:不是\n");
			printf("请选择:");
			scanf("%d", &input);
		}
	} while (input);
}


int compareName(const void* pc0, const void* pc1)
{
	int i = strcmp(((peo*)pc0)->name, ((peo*)pc1)->name);
	return i;
}

//排序
void Sort(contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->count, sizeof(peo), compareName);
	Show(pc);
	return;
}


//保存通讯录
void SaveConcat(contact* pc)
{
	assert(pc);
	FILE* file = fopen("contact.txt", "wb");
	if (file == NULL)
	{
		perror("SaveConcat");
		return;
	}
	for (int i = 0; i < pc->count; i++)
	{
		fwrite(pc->data+i, sizeof(peo), 1, file);
	}
	fclose(file);
	file = NULL;
	free(pc->data);
	pc->data = NULL;
}