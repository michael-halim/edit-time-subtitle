#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool is_contain(char num, char arr[10]) {
	for (int i = 0; i < 10; i++)
		if (num == arr[i]) return true;

	return false;
}
bool is_number(string& s)
{
	char numbers[10] = {'1','2','3','4','5','6','7','8','9','0'};
	for (int i = 0; i < s.length(); i++)	
		if ( ! is_contain(s[i], numbers)) 
			return false;	
	return true;
}
int to_milisecond(string time) {
	int result = 0;
	string piece = "";
	int co = 0;
	for (int i = 0; i < time.length() + 1; i++)
	{
		if (time[i] == ':' || time[i] == ',' || time[i] == '\0') {
			if (co == 0) {
				result = result + (stoi(piece) * 3600000);
			}
			else if (co == 1) {
				result = result + (stoi(piece) * 60000);
			}
			else if (co == 2) {
				result = result + (stoi(piece) * 1000);
			}
			else if (co == 3) {
				result = result + stoi(piece);
			}
			piece = "";
			co++;
		}
		else {
			piece += time[i];
		}
	}
	return result;
}
string to_hour(int time) {
	string result = "";
	string zero = "0";

	if (time / 3600000 < 10) {
		result = result + zero + to_string(time / 3600000); result += ":"; //jam
	}
	else {
		result = result + to_string(time / 3600000); result += ":"; //jam
	}
	time %= 3600000;

	if (time / 60000 < 10) {
		result = result + zero + to_string(time / 60000); result += ":"; //menit
	}
	else {
		result = result + to_string(time / 60000); result += ":"; //menit
	}
	time %= 60000;

	if (time / 1000 < 10) {
		result = result + zero + to_string(time / 1000); result += ","; //menit
	}
	else {
		result = result  + to_string(time / 1000); result += ","; //menit
	}
	time %= 1000;

	if (time < 100) {
		result = result + zero + to_string(time);
	}
	else {
		result = result + to_string(time);
	}

	return result;  // return result += milisecond
}
string manipulation(string time, int num, int kecepatan) {
	int milisecond = 0;
	if (kecepatan == 0) {
		milisecond = to_milisecond(time) + num;
	}
	else if (kecepatan == 1) {
		milisecond = to_milisecond(time) - num;
	}
	return to_hour(milisecond);
}


int main() {
	
	int kecepatan,howFast;
	string num,first,second,arrow;
	string text[50];
	string cache = "";
	int secondChange = 1;
	string inputFileName,outputFileName;
	cout << "Masukkan Nama File \n";
	getline(cin, inputFileName);
	cout << "Tuliskan Output File Mau Dinamai Apa ?\n";
	getline(cin, outputFileName);
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	do {
		cout << "Mau Mempercepat atau Memperlambat Subtitle ? (0.Memperlambat) (1. Mempercepat) \n";
		cin >> kecepatan;
	} while (kecepatan > 1 && kecepatan < 0);

	cout << "Seberapa cepat ? (dalam Milisecond)\n";
	cin >> howFast;

	/*while (!inputFile.eof()) {
		int co = 0;
		inputFile >> num;
		inputFile >> first;
		inputFile >> arrow;
		inputFile >> second;
		cout << num << endl;
		cout << manipulation(first,howFast,kecepatan) << " " << arrow << " " << manipulation(second,howFast,kecepatan) << endl;

		getline(inputFile, text[co]);
		
		do {
			if (is_number(text[co]) && text[co] != "") {
				break;
			}
			if (!(text[co] == cache)) {
				cout << text[co];
			}
			co++;
			getline(inputFile, text[co]);
			if (! (text[co] == cache)) {
				cout << text[co] << endl;
			}
			cache = text[co];
		} while (!is_number(text[co]));
		
	}*/
	while (!inputFile.eof()) {
		int co = 0;
		inputFile >> num;
		inputFile >> first;
		inputFile >> arrow;
		inputFile >> second;
		outputFile << num << endl;
		outputFile << manipulation(first, howFast, kecepatan) << " " << arrow << " " << manipulation(second, howFast, kecepatan) << endl;

		getline(inputFile, text[co]);

		do {
			if (is_number(text[co]) && text[co] != "") {
				break;
			}
			if (!(text[co] == cache)) {
				outputFile << text[co];
			}
			co++;
			getline(inputFile, text[co]);
			if (!(text[co] == cache)) {
				outputFile << text[co] << endl;
			}
			cache = text[co];
		} while (!is_number(text[co]));

	}
	
}