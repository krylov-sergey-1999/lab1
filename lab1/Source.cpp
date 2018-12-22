#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define ERROR_FILE_OPEN -3
FILE *mf = NULL;

typedef struct student // Шаблон структуры
{
	char surname[40];
	int group_number;
	int assessment[6];
	int debt;
} Student;

Student student[1000]; // Массив структур
int nw;

int Menu(); // Меню
void CreateNewFile(); // Создание файла c нуля
void Enter(int); // Ввод данных на студента
void ViewFile(); // Просмотр содержимого файла
void Edit(); // Редактирование данных
void Exit(); // Выход из программы
void DeleteZapis(); // Удаление записи
void FileToStructEdit(); // Запись файла в структуру
void RecordChange(); // Изменение записи
void NewRecord(); // Добавление новой записи
void TaskPerformance(); // Выполнение задачи
void Task1(); // Выполнение первой задачи
void Task2(); // Выполнение первой задачи

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
		printf("Введите желаемый номер действия");
		printf("\n1 - Создать файл");
		printf("\n2 - Посмотреть файл");
		printf("\n3 - Редактировать записи");
		printf("\n4 - Посмотреть результат");
		printf("\n5 - Выход");

		printf("\n\nВведите номер действия: ");
		scanf_s("%d", &n);
		fflush(stdin);
		system("cls");
	} while (n < 1 || n > 5);

	return n;
}

void CreateNewFile()
{
	fopen_s(&mf, "test.bin", "wb");

	// Проверка открытия файла
	if (mf == NULL) {
		printf("Ошибка\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}
	else printf("Файл открыт.\n");
	printf("_________________________________________\n");
	int number;
	printf("Введите кол-во студентов: ");
	scanf_s("%d", &number);

	for (int i = 0; i < number; i++) {
		Enter(i);
		nw = i + 1;
		fwrite(&(student[i]), sizeof(Student), 1, mf);
		printf("_________________________________________\n");
	}
	printf("Запись в файл выполнена\n");
	fclose(mf);
	printf("Запись сохранена. Нажмите любую клавишу.\n");
}

void Enter(int i)
{
	char surname[40];
	int group_number;
	int assessment[6];

	printf("\nВведите фамилию: ");
	scanf_s("%s", &surname, _countof(surname));
	fflush(stdin);
	strcpy_s(student[i].surname, 40, surname);

	printf("\nВведите номер группы: ");
	scanf_s("%d", &group_number);
	fflush(stdin);
	student[i].group_number = group_number;

	printf("\nВведите 4 оценки через пробел за экзамены: ");
	scanf_s("%d %d %d %d", &(assessment[0]), &(assessment[1]), &(assessment[2]), &(assessment[3]));
	fflush(stdin);
	student[i].assessment[0] = assessment[0];
	student[i].assessment[1] = assessment[1];
	student[i].assessment[2] = assessment[2];
	student[i].assessment[3] = assessment[3];

	printf("\nВведите информацию о зачетах(1 - зачет, 0 - незачет), нужно ввести через пробел 2 числа: ");
	scanf_s("%d %d", &(assessment[4]), &(assessment[5]));
	fflush(stdin);
	student[i].assessment[4] = assessment[4];
	student[i].assessment[5] = assessment[5];
}

void ViewFile()
{
	fopen_s(&mf, "test.bin", "rb");

	if (mf == NULL) {
		printf("Ошибка\n");
		_getch();
		exit(ERROR_FILE_OPEN);
	}
	printf("Формат записи:");
	printf("\nФамилия | Номер группы | Экзамены | Зачеты");
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

		printf("\nСтудент №%d\nФамилия - %s \nНомер группы: %d\nЭкзамены : %d, %d, %d, %d.\nЗачеты: %d, %d",
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

	printf("\nНажмите любую кнопку.");
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
		printf("1 - Удалить запись");
		printf("\n2 - Редактировать запись");
		printf("\n3 - Добавить новую запись");
		printf("\n4 - Отмена");

		printf("\n\nВведите номер действия: ");
		scanf_s("%d", &actionNumber);
		fflush(stdin);

		if (actionNumber < 1 || actionNumber > 4)
		{
			printf("Пожалуйста введите номер от 1 до 4.\n\n");
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
	printf("\n\nНажмите enter.");
}

void DeleteZapis() {
	int recordNumber;
	FileToStructEdit();
	system("cls");
	printf("Удаление записи");
	printf("Формат записи");
	printf("\nФамилия | Номер группы | Экзамены | Зачеты");
	printf("\n");

	for (int i = 0; i < nw; i++)
	{
		printf("\nСтудент №%d\nФамилия - %s \nНомер группы: %d\nЭкзамены : %d, %d, %d, %d.\nЗачеты: %d, %d",
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
		printf("Введите номер удаляемого студента: ");
		scanf_s("%d", &recordNumber);
		fflush(stdin);
	} while (recordNumber < 1 || recordNumber > nw);

	fopen_s(&mf, "test.bin", "wb");
	if (mf == NULL) {
		printf("Ошибка\n");
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
	printf("Удаление прошло успешно.");
}

void FileToStructEdit()
{
	Student studentEdit;
	int i = 0;
	fopen_s(&mf, "test.bin", "rb");
	if (mf == NULL) {
		printf("Ошибка\n");
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
	printf("Редактирование записи\n");
	printf("Формат записи:");
	printf("\nФамилия | Номер группы | Экзамены | Зачеты");
	printf("\n");


	for (int i = 0; i < nw; i++) {
		printf("\nСтудент №%d\nФамилия - %s \nНомер группы: %d\nЭкзамены : %d, %d, %d, %d.\nЗачеты: %d, %d",
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
		printf("Введите номер заказа для редактирования: ");
		scanf_s("%d", &recordNumber);
		fflush(stdin);
	} while (recordNumber < 1 || recordNumber > nw);

	fopen_s(&mf, "test.bin", "wb");

	if (mf == NULL) {
		printf("Ошибка\n");
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
	printf("Изменение прошло успешно.");
}

void NewRecord() {
	FileToStructEdit();

	system("cls");
	printf("Добавим новую запись.\n");

	fopen_s(&mf, "test.bin", "wb");
	if (mf == NULL) {
		printf("Ошибка\n");
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
	printf("Добавление новой записи прошло успешно.");
}

void TaskPerformance() {
	int actionNumber;

	do
	{
		printf("1 - Вывести всех(отсортированных по кол-ву задолжностей)");
		printf("\n2 - Вывести всех студентов по номеру групы(с указанным средним баллом)");
		printf("\n3 - Отмена");
		printf("\n\nВведите номер действия: ");
		scanf_s("%d", &actionNumber);
		fflush(stdin);

		if (actionNumber < 1 || actionNumber > 3)
		{
			printf("Пожалуйста введите номер от 1 до 3.\n\n");
		}
	} while (actionNumber < 1 || actionNumber > 3);

	switch (actionNumber)
	{
	case 1: Task1(); break;
	case 2: Task2(); break;
	case 3:
		printf("\nНажмите enter.");
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
	printf("Формат записи:");
	printf("\nФамилия | Номер группы | Экзамены | Зачеты");
	printf("\n");

	for (int i = 0; i < nw; i++) {
		printf("\nСтудент №%d\nФамилия - %s \nНомер группы: %d\nЭкзамены : %d, %d, %d, %d.\nЗачеты: %d, %d",
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
	float s = 0; // сумма баллов в группе
	int kol = 0; // кол-во людей в группе
	printf("\nВведите номер интересующей вас группы: ");
	scanf_s("%d", &number);
	for (int i = 0; i < nw; i++) {
		float sum = 0;
		if (student[i].group_number == number) {
			sum += student[i].assessment[0] + student[i].assessment[1] + student[i].assessment[2] + student[i].assessment[3];
			kol++;
			sum = sum / 4;
			printf("\nСредний балл студента #%d(%s) равен = %f", i + 1, student[i].surname, sum);
			s += sum;
		}
	}
	s = s / kol;
	printf("\nСредний балл группы равен = %f", s);

}