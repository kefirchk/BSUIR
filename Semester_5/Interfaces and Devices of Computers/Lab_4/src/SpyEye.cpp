#include "SpyEye.h"

// ====================================================================
// ����������� �� ���������
// --------------------------------------------------------------------
SpyEye::SpyEye()
{
	isActive = false;   // ��������� �������� ��������� ������
}

// ====================================================================
// ����������
// --------------------------------------------------------------------
SpyEye::~SpyEye()
{
	camera.release();   // ����������� ������
}

// ====================================================================
// ����� �������� ���������
// --------------------------------------------------------------------
void SpyEye::printLogo()
{
	cout << "_______  _____  __\   __     _______ __\   __ _______    _ _____" << endl
		 << "|______ |_____]   \\_/   ___ |______   \\_/   |______   /| |   |" << endl
		 << "______| |          \|        |______    \|    |______    |.|___|" << endl << endl;
}

// ====================================================================
// ����� ��������� ��������� ������
// --------------------------------------------------------------------
void SpyEye::help()
{
	cout << "'help' - Show all commands" << endl
		 << "'photo' - Photo mode, press '1' to ON/OFF mode" << endl
		 << "'video' - Video mode, press '2' to ON/OFF mode" << endl
		 << "[3] - Press '3' to hide/show console"
		 << "'info' - Show information about webcamera" << endl
		 << "'mirror' - Mirror mode, press ESC to exit from mode" << endl
		 << "'exit' - Exit" << endl;
}

// ====================================================================
// ��������� ������� �����
// --------------------------------------------------------------------
string SpyEye::generateFileName(string folderPath, string fileName, string fileFormat)
{
	bool isFounded = false;    // ������� ���������� �����
	for (int index = 1; index < 1000; ++index)  // 1000 ������� ���� ������ �����, ����� ����� ����������
	{
		// ����� �����
		for (const auto& entry : experimental::filesystem::directory_iterator(folderPath)) {
			if (entry.path().filename() == fileName + fileFormat) {
				isFounded = true; // ���� ������
				break;
			}
		}
		if (isFounded)            // ���� ���� ������
		{
			fileName = fileName.substr(0, 5) + "(" + to_string(index) + ")"; // ��������� ����� ��� �����
			isFounded = false;
		}
		else
			break;
	}
	return fileName;
}

// ====================================================================
// ������� ����
// --------------------------------------------------------------------
void SpyEye::startSpyPhoto()
{
	Mat image;          // ������� ������ Mat ��� �������� �����������
	camera.open(0);     // ������� ������
	if (!camera.isOpened()) {
		cout << "Error: failed to open webcam" << endl;
		exit(EXIT_FAILURE);
	}
	isActive = true;    // ���������� ������� ������� ������
	//while (isActive)
	//{
	//	Sleep(PHOTO_DELAY);           // ������ �������� ����� ����
		camera >> image;              // ��������� �����������
		imwrite(PHOTO_FOLDER_NAME + generateFileName(PHOTO_FOLDER_NAME, photoName, PHOTO_FORMAT) + PHOTO_FORMAT, image); // ��������� ����������� � ����
	//	if ((char)waitKey(100) == 49) // ���� ������ '1'
	//		break;
	//}
	camera.release();   // ����������� ������
	isActive = false;   // ���������� ������� ����������� ������
}

// ====================================================================
// ������ �����
// --------------------------------------------------------------------
void SpyEye::startSpyVideo()
{
	Mat frame;           // ������� ������ Mat ��� �������� ����� �����
	camera.open(0);      // ������� ������
	int width = camera.get(CAP_PROP_FRAME_WIDTH);
	int height = camera.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter video(VIDEO_FOLDER_NAME + generateFileName(VIDEO_FOLDER_NAME, videoName, VIDEO_FORMAT) + VIDEO_FORMAT,
		VideoWriter::fourcc('M', 'J', 'P', 'G'),
		24,
		Size(width, height));
	if (!camera.isOpened()) 
	{
		cout << "Error: failed to open webcam" << endl;
		exit(EXIT_FAILURE);
	}
	isActive = true;     // ���������� ������� ������
	while (isActive)
	{
		camera >> frame;              // �������� ���� � ���-������
		video.write(frame);           // ���������� ���� � ���������
		if ((char)waitKey(25) == 50)  // ���� ������ '2'
			break;
	}
	camera.release();   // ����������� ������
	video.release();    // ��������� ���������
	isActive = false;   // ������������� ������� ����������� ������
}

// ====================================================================
// ����� "�������"
// --------------------------------------------------------------------
void SpyEye::mirror()
{
	Mat image;			           // ������� ������ Mat ��� �������� �����������
	camera.open(0);
	namedWindow("Mirror window");  // ���������� ����
	if (!camera.isOpened()) {
		cout << "Error: failed to open webcam" << endl;
		exit(EXIT_FAILURE);
	}
	isActive = true;     // ���������� ������� ������
	while (isActive)
	{
		camera >> image;           // ������ ������
		imshow("Mirror window", image); // ������� �����������
		if (waitKey(25) == 27)     // ���� ����� ESC
			break;
	}
	isActive = false;   // ������������� ������� ����������� ������
	camera.release();              // ����������� ������
	destroyAllWindows();           // ������� ��� ����
}

// ====================================================================
// ������� ���������� � ���-������
// --------------------------------------------------------------------
void SpyEye::aboutCamera()
{
	Webcam webcam;
	// ������ ������ �������
	cout << ' ';
	for (int i = 0; i < 81; ++i)
		cout << '_';
	cout << endl;

	// ������� ������
	cout << setw(32) << left << "| Driver name: " << "| " << setw(48) << webcam.getDriverName() << '|' << endl
		 << setw(32) << left << "| Driver version: " << "| " << setw(48) << webcam.getDriverVersion().substr(10) << '|' << endl
		 << setw(32) << left << "| Webcam name: " << "| " << setw(48) << webcam.getData(SPDRP_FRIENDLYNAME) << '|' << endl
		 << setw(32) << left << "| Producer: " << "| " << setw(48) << webcam.getData(SPDRP_MFG) << '|' << endl
		 << setw(32) << left << "| Class: " << "| " << setw(48) << webcam.getData(SPDRP_CLASS) << '|' << endl
		 << setw(32) << left << "| Class GUID: " << "| " << setw(48) << webcam.getData(SPDRP_CLASSGUID) << '|' << endl
		 << setw(32) << left << "| Compatibleids: " << "| " << setw(48) << webcam.getData(SPDRP_COMPATIBLEIDS) << '|' << endl
		 << setw(32) << left << "| Device description: " << "| " << setw(48) << webcam.getData(SPDRP_DEVICEDESC) << '|' << endl
		 << setw(32) << left << "| Enumerator name: " << "| " << setw(48) << webcam.getData(SPDRP_ENUMERATOR_NAME) << '|' << endl
		 << setw(32) << left << "| Hardware ID: " << "| " << setw(48) << webcam.getData(SPDRP_HARDWAREID) << '|' << endl
		 << setw(32) << left << "| Location information: " << "| " << setw(48) << webcam.getData(SPDRP_LOCATION_INFORMATION) << '|' << endl
		 << setw(32) << left << "| Location paths: " << "| " << setw(48) << webcam.getData(SPDRP_LOCATION_PATHS) << '|' << endl
		 << setw(32) << left << "| Lower filters: " << "| " << setw(48) << webcam.getData(SPDRP_LOWERFILTERS) << '|' << endl
		 << setw(32) << left << "| Physical device object name: " << "| " << setw(48) << webcam.getData(SPDRP_PHYSICAL_DEVICE_OBJECT_NAME) << '|' << endl
		 << setw(32) << left << "| Service: " << "| " << setw(48) << webcam.getData(SPDRP_SERVICE) << '|' << endl << '|';
	
	// ������ ����� �������
	for (int i = 0; i < 81; ++i)
		if (i == 31) cout << '|';
		else cout << '_';
	cout << '|' << endl << endl;
}

// ====================================================================
// ��������� �������
// --------------------------------------------------------------------
bool SpyEye::executeCommand(string command)
{
	if (command == "") return false;
	if (commands.find(command) == commands.end())
		cout << "Error: invalid command" << endl;

	if (command == "mirror")
		this->mirror();
	if (command == "photo")
	{
		console.hide();
		this->startSpyPhoto();
		//console.show();
	}
	if (command == "video") 
	{
		console.hide();
		this->startSpyVideo();
		console.show();
	}
	if (command == "info")
		this->aboutCamera();
	if (command == "help")
		this->help();
	if (command == "exit")
		return true;
	return false;
}

// ====================================================================
// GETTER ��� ���� console
// --------------------------------------------------------------------
Console& SpyEye::getConsole()
{
	return console;
}
