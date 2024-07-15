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
	//TODO: Possible refactor to prevent repeating??
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);
	return in.is_open();
}

string File::updateLineValue(
	string username,
	string prefix,
	string value
) {
	fstream in, out;
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);
	
	if (in.is_open()) {
		vector<string> lines;
		string line;

		while (getline(in, line)) {
			lines.push_back(line);
		}

		if (lines.size() == 0) {
			return Variables::falsyString;
		}

		auto it = find_if(
			lines.begin(),
			lines.end(),
			[prefix](string current) {
				return current.find(prefix) != string::npos;
			}
		);

		out.open(
			Variables::txtFileBasePath + username + ".txt",
			ios::out
		);

		if (it != lines.end() && out.is_open()) {
			string updatedLine = prefix + value;
			*it = updatedLine;

			for (string s : lines) {
				out << s << endl;
			}

			return value;
		}
	}

	return Variables::falsyString;
}

string File::getLineValue(
	string username,
	string prefix
) {
	fstream in;
	in.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::in
	);

	if (in.is_open()) {
		string value = findByPrefix(
			username,
			prefix,
			in
		);

		if (value != Variables::falsyString) {
			return value;
		}
	}

	return Variables::falsyString;
}

string File::findByPrefix(
	string username,
	string prefix,
	fstream &in
) {
	// set position back to top of file, in the case of using `getline`
		// multiple times on the same fstream
	in.seekg(0);

	string line;

	while (getline(in, line)) {
		if (line.find(prefix) != string::npos) {
			return line.substr(prefix.length());
		}
	}

	return Variables::falsyString;
}

bool File::resetUser(string username) {
	string encryptedPassword = getLineValue(username, Variables::passwordPrefix);
	bool removed = filesystem::remove(Variables::txtFileBasePath + username + ".txt");
	bool created = createUser(username, encryptedPassword, Variables::falsyString, true);

	if (!removed || !created) {
		return false;
	}

	return true;
}

bool File::createUser(
	string username,
	string password,
	string key,
	bool passwordAlreadyEncrypted
) {
	fstream out;
	out.open(
		Variables::txtFileBasePath + username + ".txt",
		ios::out
	);

	if (out.is_open()) {
		string encryptedPassword = passwordAlreadyEncrypted ?
			password :
			Auth::crypt(
				password,
				key,
				Enums::ENCRYPT
			);

		for (auto &it : Variables::newUserDefault) {
			if (it.first != Variables::passwordPrefix) {
				out << it.first + it.second << endl;
				continue;
			}
			out << Variables::passwordPrefix + encryptedPassword << endl;
		}

		return true;
	}

	return false;
}

void File::updateLeaderboard() {
}

void File::updateOptions() {
}
