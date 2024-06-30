#include "file.h"

void File::test() {
	fstream in, out;

	out.open(
		Variables::txtFileBasePath + "helloworld.txt",
		ios::out
	);

	if (out.is_open()) {
		cout << "works?";
		out << "REPLACES EXISTING TXT sasdasdwda";
	}
	else {
		Screens::errorScreen("Could not open file");
	}

	out.close();

	in.open(
		Variables::txtFileBasePath + "helloworld.txt",
		ios::in
	);

	if (in.is_open()) {
		string line;
		while(getline(in, line)) {
			cout << line << '\n';
		}
	} else {
		Screens::errorScreen("Could not open file");
	}

	in.close();
}

string File::extractLineData(
	string line,
	string prefix
) {
	return line.substr(prefix.length());
}

bool File::existingUser(string username) {
	fstream in;
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);
	return in.is_open();
}

string File::getUserPasswordLine(string username) {
	fstream in;
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);

	if (in.is_open()) {
		string line;
		while(getline(in, line)) {
			if (line.find(Variables::passwordPrefix) != string::npos) {
				return line;
			}
		}
	}

	return Variables::falsyString;
}

bool File::createUser(
	string username,
	string password,
	string key
) {
	fstream out;

	out.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::out
	);

	if (out.is_open()) {
		string encryptedPassword = Auth::crypt(
			password,
			key,
			Enums::ENCRYPT
		);

		out << Variables::passwordPrefix + encryptedPassword;
		return true;
	}

	return false;
}

void File::updateLeaderboard() {
}

void File::updateOptions() {
}
