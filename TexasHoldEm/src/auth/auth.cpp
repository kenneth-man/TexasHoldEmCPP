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

void Auth::loginUser(
    Enums::GameState &gameState
) {

}

void Auth::registerUser(
    Enums::GameState &gameState
) {
    vector<string> inputs; // = {username, password, key};

    for(int i = 0; i < Variables::registerInstructions.size(); ++i) {
        const string input = Screens::infoScreen(
            Variables::registerInstructions[i].first,
            Variables::registerInstructions[i].second
        );

        const string error = registerUserValidation(input, i);

        if (error != Variables::falsyString) {
            Screens::errorScreen(error);
            gameState = Enums::AUTH;
            return;
        }

        inputs.push_back(input);
    }

    const bool created = File::createUser(inputs[0], inputs[1], inputs[2]);

    if (!created) {
        Screens::errorScreen("Could not create user");
        gameState = Enums::AUTH;
        return;
    }

    gameState = Enums::TITLE;
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