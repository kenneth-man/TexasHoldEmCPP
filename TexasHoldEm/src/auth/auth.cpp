#include "auth.h"

string Auth::crypt(
    string password,
    string key,
    Enums::Crypt type
) {
    string encrypted = password;
    int k = stoi(key);

    for (int i = 0; i < password.length(); ++i) {
        char c = password[i];

        if (type == Enums::ENCRYPT) {
            c += k;
        } else {
            c -= k;
        }

        encrypted[i] = c;
    }

    return encrypted;
}

string Auth::handleInput(
    vector<string> &inputs,
    const authUserInstructions &instructions,
    string (*validation)(string, int)
) {
    for (int i = 0; i < instructions.size(); ++i) {
        const string input = Screens::infoScreen(
            instructions[i].first,
            instructions[i].second
        );

        const string error = validation(input, i);

        if (error != Variables::falsyString) {
            return error;
        }

        inputs.push_back(input);
    }

    return Variables::falsyString;
}

void Auth::loginUser(
    Enums::GameState &gameState
) {
    vector<string> inputs; // = {username, password, key};

    const string error = handleInput(
        inputs,
        Variables::loginInstructions,
        &loginUserValidation
    );

    if (error != Variables::falsyString) {
        failure(error, gameState);
        return;
    }

    const string line = File::getUserPasswordLine(inputs[0]);
    const string password = File::extractLineData(
        line,
        Variables::passwordPrefix
    );

    if (password == Variables::falsyString) {
        failure("Couldn't open User file", gameState);
        return;
    }

    const string decryptedPassword = crypt(
        password,
        inputs[2],
        Enums::DECRYPT
    );

    if (decryptedPassword != inputs[1]) {
        failure("Invalid Password or Key provided", gameState);
        return;
    }

    gameState = Enums::TITLE;
}

void Auth::registerUser(
    Enums::GameState &gameState
) {
    vector<string> inputs; // = {username, password, key};

    const string error = handleInput(
        inputs,
        Variables::registerInstructions,
        &registerUserValidation
    );

    if (error != Variables::falsyString) {
        failure(error, gameState);
        return;
    }

    const bool created = File::createUser(inputs[0], inputs[1], inputs[2]);

    if (!created) {
        failure("Could not create user", gameState);
        return;
    }

    gameState = Enums::TITLE;
}

string Auth::loginUserValidation(
    string input,
    int index
) {
    switch (index) {
        // username
        case 0: {
            const bool exists = File::existingUser(input);

            if (!exists) {
                return "User doesn't exist";
            }

            break;
        }
        case 1:
        case 2: {
            break;
        }
        default: {
            return "Too many inputs...";
        }
    }

    return Variables::falsyString;
}

string Auth::registerUserValidation(
    string input,
    int index
) {
    switch (index) {
        // username
        case 0: {
            const bool exists = File::existingUser(input);

            if (exists) {
                return "User already exists";
            }

            break;
        }
        // password
        case 1: {
            if (input.length() < Variables::minPasswordLen) {
                return "Passwords must be at least " +
                    to_string(Variables::minPasswordLen) +
                    " characters long";
            }

            break;
        }
        // key
        case 2: {
            try {
                const int i = stoi(input);

                if (i < 0) {
                    return "Key must be an unsigned integer; it cannot be negative";
                }
            } catch (const invalid_argument &_) {
                return "Key must be an unsigned integer; it cannot contain letters or symbols";
            } catch (const out_of_range &_) {
                return "Key exceeds the max number of a 4 byte integer";
            }

            break;
        }
        default: {
            return "Too many inputs...";
        }
    }

    return Variables::falsyString;
}

void Auth::failure(
    string error,
    Enums::GameState &gameState
) {
    Screens::errorScreen(error);
    gameState = Enums::AUTH;
}