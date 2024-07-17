#include "player.h"

void Player::init(string name) {
    Player::name = name;

    fstream in;
    File::openUserFStream(in, ios::in, Player::name);

    Player::rank = File::findByPrefix(
        Player::name,
        Variables::rankPrefix,
        in
    );
    Player::elo = stoi(File::findByPrefix(
        Player::name,
        Variables::eloPrefix,
        in
    ));
    Player::balance = stol(File::findByPrefix(
        Player::name,
        Variables::balancePrefix,
        in
    ));
    Player::wins = stoi(File::findByPrefix(
        Player::name,
        Variables::winsPrefix,
        in
    ));
    Player::losses = stoi(File::findByPrefix(
        Player::name,
        Variables::lossesPrefix,
        in
    ));
    Player::gamesPlayed = stoi(File::findByPrefix(
        Player::name,
        Variables::gamesPlayedPrefix,
        in
    ));
}