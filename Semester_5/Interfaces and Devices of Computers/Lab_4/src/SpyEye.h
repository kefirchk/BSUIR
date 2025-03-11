#pragma once
#include "Libs.h"
#include "Webcam.h"
#include "Console.h"

// ====================================================================
// ���������� ��������
// --------------------------------------------------------------------
#define VIDEO_FOLDER_NAME "./Video/"  // ����� ��� �����
#define PHOTO_FOLDER_NAME "./Photo/"  // ����� ��� ����
#define VIDEO_FORMAT ".avi"           // ���������� �����
#define PHOTO_FORMAT ".jpg"           // ���������� ����
#define PHOTO_DELAY 5000              // �������� ����� ����

// ====================================================================
// ����� SpyEye
// --------------------------------------------------------------------
class SpyEye
{
public:
	bool isActive = false;                // ������� ������� ������

	SpyEye();                             // ����������� �� ���������
	~SpyEye();                            // ����������
	void help();                          // ��������� ��������� ������
	bool executeCommand(string command);  // ��������� �������
	void printLogo();                     // ���������� ������� ���������
	void startSpyVideo();                 // ������ ������ �����
	void startSpyPhoto();                 // ������� ����
	void mirror();                        // �������� ����� �������
	void aboutCamera();                   // ������� ���������� � ���-������
	Console& getConsole();				  // �������� ���� console
	string generateFileName(string, string, string); // ��������� ����� ����� � ��������

private:
	const string videoName = "video";     // ��� ����� ��� �����
	const string photoName = "photo";     // ��� ����� ��� ����
	set<string> commands = {              // ��������� �������
		"mirror",
		"photo",
		"video",
		"info",
		"help",
		"exit"
	};
	VideoCapture camera;                  // ������ ������
	Console console;                      // �������
};

