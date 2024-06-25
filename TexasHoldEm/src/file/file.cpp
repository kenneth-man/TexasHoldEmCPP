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

// credentials.txt, leaderboard.txt and options.txt,
// if they don't already exist
void File::createBaseFiles() {
	
}

void File::getPassword() {
}

void File::setCredentials() {
}

void File::updateCredentials(){
}

void File::updateLeaderboard(){
}

void File::updateOptions(){
}
