#include "contact.h"

//�ж�ͨѶ¼������
void check_contact(contact* pc)
{
	assert(pc);
	//�ж�ͨѶ¼������
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


//��ȡ�ļ�
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


//��ʼ��ͨѶ¼(��̬�汾)
void Init(contact* pc)
{
	assert(pc); //ָ�벻��Ϊ��
	pc->count = 0;
	//�����ڴ�
	pc->data = (peo*)calloc(INIT_SIZE, sizeof(peo));
	//�ж�ָ���Ƿ�Ϊ��
	if (pc->data == NULL)
	{
		printf("Init::%s\n", strerror(errno));
	}
	//�����ļ�
	readFile(pc);
}



//�����ϵ��
void Add(contact* pc)
{
	assert(pc);
	check_contact(pc);
	printf("���������֣�");
	//[pc->count]Ϊdata���±꣬��������ϵ�˺�����ӣ�dataΪ����,������Ϊ��ַ�����á�&��
	scanf("%s", pc->data[pc->count].name);
	printf("���������䣺");
	scanf("%d", &(pc->data[pc->count].age));
	printf("�������Ա�(ѡ������> 1:�� 0:Ů)��");
	scanf("%d", &(pc->data[pc->count].gender));
	printf("������绰��");
	scanf("%s", pc->data[pc->count].tel);
	printf("�������ַ��");
	scanf("%s", pc->data[pc->count].address);

	pc->count++;
	printf("��ӳɹ�!\n");
}


//չʾͨѶ¼
void Show(const contact* pc)
{
	assert(pc);
	printf("   %-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");	//%3d--ռ��λ���ֿռ�
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


//������ϵ��
int FindName(char* name, const contact* pc)
{
	for (int i = 0; i < pc->count; i++)
	{
		if (strcmp(name, pc->data[i].name) == 0)
			return i;
	}
	return -1;
}


//��ӡҪ������ϵ��
void Search(const contact* pc)
{
	assert(pc);
	printf("����Ҫ�����˵�������");
	char name[20];
	scanf("%s", name);
	int i = FindName(name, pc);
	if (i > -1)
	{
		printf("   %-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		printf("   %-20s\t%-3d\t%-1d\t%-12s\t%-30s\n", pc->data[i].name,
			pc->data[i].age,
			pc->data[i].gender,
			pc->data[i].tel,
			pc->data[i].address);
	}
	else
	{
		printf("û���ҵ���\n");
	}
	return;
}


//ɾ����ϵ��
void Del(contact* pc)
{
	assert(pc);
	printf("����Ҫɾ���˵�������");
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
		printf("ɾ���ɹ�!\n");
	}
	else
	{
		printf("û���ҵ���\n");
	}
}



//�޸Ĳ˵�
void menu1()
{
	printf("*********************************************\n");
	printf("*****  1. �޸�����         2. �޸�����    *****\n");
	printf("*****  3. �޸��Ա�          4. �޸ĵ绰    *****\n");
	printf("*****  5. �޸ĵ�ַ         ********************\n");
	printf("*********************************************\n");
}
//�޸���ϵ��
void Modify(contact* pc)
{
	assert(pc);
	printf("����Ҫ�޸��˵�������");
	char name[20];
	int input = 0;
	scanf("%s", name);
	int i = FindName(name, pc);
	do
	{
		menu1();
		printf("��ѡ��:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("�������޸ĺ�����֣�");
			scanf("%s", pc->data[i].name);
			break;
		case 2:
			printf("�������޸ĺ�����䣺");
			scanf("%d", &(pc->data[i].age));
			break;
		case 3:
			printf("�������޸ĺ���Ա�(ѡ������> 1:�� 0:Ů)��");
			scanf("%d", &(pc->data[i].gender));
			break;
		case 4:
			printf("�������޸ĺ�ĵ绰��");
			scanf("%s", pc->data[i].tel);
			break;
		case 5:
			printf("�������޸ĺ�ĵ�ַ��");
			scanf("%s", pc->data[i].address);
			break;
		case 0:
			printf("�˳�����");
			break;
		default:
			printf("�����������������!");
			break;
		}
		printf("�޸ĳɹ�!\n");
		if (input != 0)
		{
			printf("�Ƿ����޸�? 1:��  0:����\n");
			printf("��ѡ��:");
			scanf("%d", &input);
		}
	} while (input);
}


int compareName(const void* pc0, const void* pc1)
{
	int i = strcmp(((peo*)pc0)->name, ((peo*)pc1)->name);
	return i;
}

//����
void Sort(contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->count, sizeof(peo), compareName);
	Show(pc);
	return;
}


//����ͨѶ¼
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