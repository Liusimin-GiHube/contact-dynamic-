#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


#define ADD_SIZE 2	//每次增容个数
#define INIT_SIZE 3	//初始化个数

//联系人信息
typedef	struct peo
{
	char name[20];
	int age;
	int gender; //男--1； 女--0
	long tel[12];
	char address[30];
}peo;


//建立通讯录结构（动态版本）
typedef struct contact
{
	peo* data;//联系人信息
	int count;//当前联系人个数
	int capacity;	//通讯录容量
}contact;

//初始化通讯录
void Init(contact* pc);

//添加联系人
void Add(contact* pc);

//展示通讯录
void Show(const contact* pc);

//删除联系人
void Del(contact* pc);

//查找联系人
void Search(const contact* pc);

//修改联系人
void Modify(contact* pc);

//排序
void Sort(contact* pc);

//保存通讯录
void SaveConcat(contact* pc);