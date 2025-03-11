#include "Functions.h"

LPCTSTR PORT_NAME_1 = L"COM1";
LPCTSTR PORT_NAME_2 = L"COM2";
#define MAX_STRING_LEN 80

int main()
{
    setlocale(LC_ALL, "Rus");
    HANDLE COM_Port_1 = CreateFile(PORT_NAME_1, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //�������� ������
    HANDLE COM_Port_2 = CreateFile(PORT_NAME_2, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    char inBuff[MAX_STRING_LEN + 1] = "";     //����� ���������� ������
    char outBuff[MAX_STRING_LEN + 1] = "";    //����� ���������� ������
    try
    {
        if (COM_Port_1 == INVALID_HANDLE_VALUE || COM_Port_2 == INVALID_HANDLE_VALUE)
            throw Exception(-1, "������ �������� �����!");  //����� ����� ������������ GetLastError()

        DCB Parametres = { 0 };
        Parametres.DCBlength = sizeof(Parametres);
        if (!GetCommState(COM_Port_1, &Parametres))
            throw Exception(-1, "������ ������������� �����!");
        Parametres.BaudRate = CBR_115200;
        Parametres.ByteSize = 8;
        Parametres.StopBits = ONESTOPBIT;
        Parametres.Parity = NOPARITY;
        if (!SetCommState(COM_Port_1, &Parametres))
            throw Exception(-1, "������ ������������� �����!");
        if (!SetCommState(COM_Port_2, &Parametres))
            throw Exception(-1, "������ ������������� �����!");

        cout << "������� ��������� (�� " << MAX_STRING_LEN << " ��������):\n";
        cin.getline(inBuff, MAX_STRING_LEN + 1);

        DWORD willWrittenBytes = strlen(inBuff);  //������� ����� �������� ���� ����������
        DWORD writtenBytes;                       //������� ������� �������� ����
        DWORD readBytes;                          //����� ����������� ����

        if (!WriteFile(COM_Port_1, &inBuff, willWrittenBytes, &writtenBytes, NULL))
            throw Exception(-3, "������ ������! �� ������� ��������� ������.");
        cout << "�������� ����: " << writtenBytes << endl;
        if (!ReadFile(COM_Port_2, &outBuff, strlen(inBuff), &readBytes, 0))
            throw Exception(-4, "\n������ ������! �� ������� �������� ������.");
        cout << "�������� ����: " << readBytes << endl;
        cout << "���������� ������:" << endl << outBuff << endl;

        CloseHandle(COM_Port_1);
        CloseHandle(COM_Port_2);
    }
    catch (Exception& err)
    {
        err.what();
        return err.getErrorCode();
    }
    return 0;
}