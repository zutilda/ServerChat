#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
    //������ ������� �����
    system("chcp 1251 > null");
    HANDLE hNamePipe; //���������� ����������� ������
    LPSTR lpstPipeName = L"\\\\.\\pipe\\MyPipe"; // ����������, ���������� ��� ������   
    LPWSTR buffer = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR)); // ��������� ���������, � ������� ����� ������� �����
    char message[SIZE_BUFFER]; // ������ ���������
    BOOL Connected;
    DWORD actual_readen; // ������� �� ����� ���� ���� ��������� ����
    //������ �� ������
    LPWSTR b = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    LPWSTR zero = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    while (TRUE)
    {
        HANDLE hNamePipe = CreateNamedPipe( // �������� ������
            lpstPipeName, // ��� ������ - ����
            // � ��������� � ����������
            PIPE_ACCESS_DUPLEX, // ���� ������� � ������ (�������������/������������)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // ����� ������ ������: ���������� ���������| ������ �������� | �����
            PIPE_UNLIMITED_INSTANCES, // �������� �� ������� ���������� � ������, � ������ ������ �����.
            SIZE_BUFFER, // ����� ������ ��� ������ (����)
            SIZE_BUFFER, // ����� ������ ��� ������ (����)
            INFINITE, // ������������ ����� �������� ��������� - ����� �� �����
            NULL // ��������� �� ��������� ������������
        );
        Connected = ConnectNamedPipe(hNamePipe, NULL); // ��������� � ��������� ������� � �������
        if (Connected) // ���� ������ �����������
        {
            printf("\n������ ������� ���������\n");
           
            if (ReadFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL))
            {
                // ����� �����������
                printf("\n������ �����: ");
                printf(buffer);

                printf("\n���������: ");
                gets(message);
                buffer = &message;
                WriteFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);

                // ���������� � �������
                //printf("\n������ �����: \n");
                //printf(buffer);// ����� �� ����� ������������ ���������
                //printf("\n");
                //float a = atof(buffer);// ����������� ������ � �������� ���� double
                //float aa = a * a; // � �������
                //sprintf(message, "%g", aa); // �����
                //zero = L"0";
                //sprintf(b, "%s", buffer);
                //if (aa == 0 && strcmp(b, zero) != 0)
                //{
                //    sprintf(message, "�� ��������� ������� ������");
                //}
                //buffer = &message;
                //WriteFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
            }


        }
        else
        {
            printf("\n������ ���������� �� �������\n");
        }
        CloseHandle(hNamePipe); // ��������� �����

    }
}