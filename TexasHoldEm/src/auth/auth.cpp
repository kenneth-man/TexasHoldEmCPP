#include "auth.h"

string Auth::crypt(
    string password,
    string key,
    Enums::Crypt type
) {
    string encrypted = password;
    uint32_t k = stoi(key);

    for (uint32_t i = 0; i < password.length(); ++i) {
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
    string (*validation)(string, uint8_t)
) {
    for (uint8_t i = 0; i < instructions.size(); ++i) {
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
    Enums::GameState &gameState,
    Player &player
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

    const string password = File::getLineValue(
        inputs[0],
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

    player.init(inputs[0]);

    gameState = Enums::TITLE;
}

void Auth::registerUser(
    Enums::GameState &gameState,
    Player &player
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

    player.init(inputs[0]);

    gameState = Enums::TITLE;
}

string Auth::loginUserValidation(
    string input,
    uint8_t index
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
        case 1: {
            break;
        }
        // key
        case 2:{
            const string errorMsg = Calc::checkInputIsValidUInt(input);

            if (errorMsg != Variables::falsyString) {
                return errorMsg;
            }

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
    uint8_t index
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
            const string errorMsg = Calc::checkInputIsValidUInt(input);

            if (errorMsg != Variables::falsyString) {
                return errorMsg;
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