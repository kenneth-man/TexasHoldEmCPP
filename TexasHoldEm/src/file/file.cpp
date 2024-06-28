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

bool File::existingUser(string username) {
	fstream in;
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);
	return in.is_open();
}

void File::getUser() {
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
		string output = "Password: ";
		string encryptedPassword = Auth::crypt(
			password,
			key,
			Enums::ENCRYPT
		);

		out << output + encryptedPassword;
		return true;
	}

	return false;
}

void File::updateLeaderboard() {
}

void File::updateOptions() {
}
