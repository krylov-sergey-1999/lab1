#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define ERROR_FILE_OPEN -3
FILE *mf = NULL;

typedef struct student // ������ ���������
{
	char surname[40];
	int group_number;
	int assessment[6];
	int debt;
} Student;

Student student[1000]; // ������ ��������
int nw;

int Menu(); // ����
void CreateNewFile(); // �������� ����� c ����
void Enter(int); // ���� ������ �� ��������
void ViewFile(); // �������� ����������� �����
void Edit(); // �������������� ������
void Exit(); // ����� �� ���������
void DeleteZapis(); // �������� ������
void FileToStructEdit(); // ������ ����� � ���������
void RecordChange(); // ��������� ������
void NewRecord(); // ���������� ����� ������
void TaskPerformance(); // ���������� ������
void Task1(); // ���������� ������ ������
void Task2(); // ���������� ������ ������

void main()
{
	setlocale(LC_CTYPE, "Russian");

	do
	{
		system("cls");
		int choice = Menu();
		switch (choice)
		{
		case 1: CreateNewFile(); break;
		case 2: ViewFile(); break;
		case 3: Edit(); break;
		case 4: TaskPerformance(); break;
		case 5: Exit(); break;
		}

		_getch();
	} while (1);
}

int Menu()
{
	int n;
	do
	{
		printf("������� �������� ����� ��������");
		printf("\n1 - ������� ����");
		printf("\n2 - ���������� ����");
		printf("\n3 - ������������� ������");
		printf("\n4 - ���������� ���������");
		printf("\n5 - �����");

		printf("\n\n������� ����� ��������: ");
		scanf_s("%d", &n);
		fflush(stdin);
		system("cls");
	} while (n < 1 || n > 5);

	return n;
}

void CreateNewFile()
{
	fopen_s(&mf, "test.bin", "wb");

	// �������� �������� �����
	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}
	else printf("���� ������.\n");
	printf("_________________________________________\n");
	int number;
	printf("������� ���-�� ���������: ");
	scanf_s("%d", &number);

	for (int i = 0; i < number; i++) {
		Enter(i);
		nw = i + 1;
		fwrite(&(student[i]), sizeof(Student), 1, mf);
		printf("_________________________________________\n");
	}
	printf("������ � ���� ���������\n");
	fclose(mf);
	printf("������ ���������. ������� ����� �������.\n");
}

void Enter(int i)
{
	char surname[40];
	int group_number;
	int assessment[6];

	printf("\n������� �������: ");
	scanf_s("%s", &surname, _countof(surname));
	fflush(stdin);
	strcpy_s(student[i].surname, 40, surname);

	printf("\n������� ����� ������: ");
	scanf_s("%d", &group_number);
	fflush(stdin);
	student[i].group_number = group_number;

	printf("\n������� 4 ������ ����� ������ �� ��������: ");
	scanf_s("%d %d %d %d", &(assessment[0]), &(assessment[1]), &(assessment[2]), &(assessment[3]));
	fflush(stdin);
	student[i].assessment[0] = assessment[0];
	student[i].assessment[1] = assessment[1];
	student[i].assessment[2] = assessment[2];
	student[i].assessment[3] = assessment[3];

	printf("\n������� ���������� � �������(1 - �����, 0 - �������), ����� ������ ����� ������ 2 �����: ");
	scanf_s("%d %d", &(assessment[4]), &(assessment[5]));
	fflush(stdin);
	student[i].assessment[4] = assessment[4];
	student[i].assessment[5] = assessment[5];
}

void ViewFile()
{
	fopen_s(&mf, "test.bin", "rb");

	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}
	printf("������ ������:");
	printf("\n������� | ����� ������ | �������� | ������");
	printf("\n");

	int i = 0;
	Student studentRead;
	while (fread(&studentRead, sizeof(Student), 1, mf))
	{
		if (feof(mf))
		{
			break;
		}

		student[i] = studentRead;

		printf("\n������� �%d\n������� - %s \n����� ������: %d\n�������� : %d, %d, %d, %d.\n������: %d, %d",
			i + 1,
			student[i].surname,
			student[i].group_number,
			student[i].assessment[0],
			student[i].assessment[1],
			student[i].assessment[2],
			student[i].assessment[3],
			student[i].assessment[4],
			student[i].assessment[5]);
		printf("\n");
		i++;
	}
	fclose(mf);

	printf("\n������� ����� ������.");
}

void Exit()
{
	exit(0);
}

void Edit()
{
	int actionNumber;

	do
	{
		printf("1 - ������� ������");
		printf("\n2 - ������������� ������");
		printf("\n3 - �������� ����� ������");
		printf("\n4 - ������");

		printf("\n\n������� ����� ��������: ");
		scanf_s("%d", &actionNumber);
		fflush(stdin);

		if (actionNumber < 1 || actionNumber > 4)
		{
			printf("���������� ������� ����� �� 1 �� 4.\n\n");
		}
	} while (actionNumber < 1 || actionNumber > 4);

	switch (actionNumber)
	{
	case 1: DeleteZapis();
	case 2: RecordChange();
	case 3: NewRecord();
	case 4:
		return;
		break;
	}
	printf("\n\n������� enter.");
}

void DeleteZapis() {
	int recordNumber;
	FileToStructEdit();
	system("cls");
	printf("�������� ������");
	printf("������ ������");
	printf("\n������� | ����� ������ | �������� | ������");
	printf("\n");

	for (int i = 0; i < nw; i++)
	{
		printf("\n������� �%d\n������� - %s \n����� ������: %d\n�������� : %d, %d, %d, %d.\n������: %d, %d",
			i + 1,
			student[i].surname,
			student[i].group_number,
			student[i].assessment[0],
			student[i].assessment[1],
			student[i].assessment[2],
			student[i].assessment[3],
			student[i].assessment[4],
			student[i].assessment[5]);
		printf("\n");
	}

	printf("\n\n");
	do
	{
		printf("������� ����� ���������� ��������: ");
		scanf_s("%d", &recordNumber);
		fflush(stdin);
	} while (recordNumber < 1 || recordNumber > nw);

	fopen_s(&mf, "test.bin", "wb");
	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}

	for (int i = 0; i < nw - 1; i++)
	{
		if (i > recordNumber - 2)
		{
			student[i] = student[i + 1];
		}

		fwrite(&(student[i]), sizeof(Student), 1, mf);
	}
	fclose(mf);
	printf("�������� ������ �������.");
}

void FileToStructEdit()
{
	Student studentEdit;
	int i = 0;
	fopen_s(&mf, "test.bin", "rb");
	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}

	nw = 0;
	while (fread(&studentEdit, sizeof(Student), 1, mf))
	{
		if (feof(mf))
		{
			break;
		}

		student[i] = studentEdit;

		i++;
		nw++;
	}
	fclose(mf);
}

void RecordChange() {
	FileToStructEdit();
	int recordNumber;
	system("cls");
	printf("�������������� ������\n");
	printf("������ ������:");
	printf("\n������� | ����� ������ | �������� | ������");
	printf("\n");


	for (int i = 0; i < nw; i++) {
		printf("\n������� �%d\n������� - %s \n����� ������: %d\n�������� : %d, %d, %d, %d.\n������: %d, %d",
			i + 1,
			student[i].surname,
			student[i].group_number,
			student[i].assessment[0],
			student[i].assessment[1],
			student[i].assessment[2],
			student[i].assessment[3],
			student[i].assessment[4],
			student[i].assessment[5]);
		printf("\n");
	}

	do
	{
		printf("������� ����� ������ ��� ��������������: ");
		scanf_s("%d", &recordNumber);
		fflush(stdin);
	} while (recordNumber < 1 || recordNumber > nw);

	fopen_s(&mf, "test.bin", "wb");

	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}

	for (int i = 0; i < nw; i++)
	{
		if (i == recordNumber - 1)
		{
			Enter(i);
		}

		fwrite(&student[i], sizeof(Student), 1, mf);
	}

	fclose(mf);
	printf("��������� ������ �������.");
}

void NewRecord() {
	FileToStructEdit();

	system("cls");
	printf("������� ����� ������.\n");

	fopen_s(&mf, "test.bin", "wb");
	if (mf == NULL) {
		printf("������\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}

	for (int i = 0; i < nw + 1; i++)
	{
		if (i == nw)
		{
			Enter(i);
		}

		fwrite(&student[i], sizeof(Student), 1, mf);
	}

	nw++;
	fclose(mf);
	printf("���������� ����� ������ ������ �������.");
}

void TaskPerformance() {
	int actionNumber;

	do
	{
		printf("1 - ������� ����(��������������� �� ���-�� ������������)");
		printf("\n2 - ������� ���� ��������� �� ������ �����(� ��������� ������� ������)");
		printf("\n3 - ������");
		printf("\n\n������� ����� ��������: ");
		scanf_s("%d", &actionNumber);
		fflush(stdin);

		if (actionNumber < 1 || actionNumber > 3)
		{
			printf("���������� ������� ����� �� 1 �� 3.\n\n");
		}
	} while (actionNumber < 1 || actionNumber > 3);

	switch (actionNumber)
	{
	case 1: Task1(); break;
	case 2: Task2(); break;
	case 3:
		printf("\n������� enter.");
		return;
		break;
	}

}

void Task1() {
	FileToStructEdit();

	for (int i = 0; i < nw; i++) {
		int debt = 0;
		if (student[i].assessment[0] < 3)
			debt++;
		if (student[i].assessment[1] < 3)
			debt++;
		if (student[i].assessment[2] < 3)
			debt++;
		if (student[i].assessment[3] < 3)
			debt++;
		if (student[i].assessment[4] == 0)
			debt++;
		if (student[i].assessment[5] == 0)
			debt++;
		student[i].debt = debt;
	}

	printf("\n");

	for (int i = nw - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (student[j].debt < student[j + 1].debt)
			{
				Student tmp = student[j];
				student[j] = student[j + 1];
				student[j + 1] = tmp;
			}
		}
	}
	printf("������ ������:");
	printf("\n������� | ����� ������ | �������� | ������");
	printf("\n");

	for (int i = 0; i < nw; i++) {
		printf("\n������� �%d\n������� - %s \n����� ������: %d\n�������� : %d, %d, %d, %d.\n������: %d, %d",
			i + 1,
			student[i].surname,
			student[i].group_number,
			student[i].assessment[0],
			student[i].assessment[1],
			student[i].assessment[2],
			student[i].assessment[3],
			student[i].assessment[4],
			student[i].assessment[5]);
		printf("\n");
	}
}

void Task2() {
	FileToStructEdit();
	system("cls");
	int number = 0;
	float s = 0; // ����� ������ � ������
	int kol = 0; // ���-�� ����� � ������
	printf("\n������� ����� ������������ ��� ������: ");
	scanf_s("%d", &number);
	for (int i = 0; i < nw; i++) {
		float sum = 0;
		if (student[i].group_number == number) {
			sum += student[i].assessment[0] + student[i].assessment[1] + student[i].assessment[2] + student[i].assessment[3];
			kol++;
			sum = sum / 4;
			printf("\n������� ���� �������� #%d(%s) ����� = %f", i + 1, student[i].surname, sum);
			s += sum;
		}
	}
	s = s / kol;
	printf("\n������� ���� ������ ����� = %f", s);

}