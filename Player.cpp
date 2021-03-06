#include "Player.h"
#include <iostream>

using namespace std;

//PLAYER CLASS IS FINISHED

Player::Player()
{
    balance = 1500;
    boardlocation = 0;
    previousBoardLocation = 0;
    playerPos_x = 0;
    playerPos_y = 0;
    bankrupt = false;
    inJail = false;
    turnsinjail = 0;
    resetLocation = false;
    displayStatus = true;
}


void Player::setDisplayStatus(bool updateStatus)
{
    displayStatus = updateStatus;
}

void Player::setResetLocation_TRUE()
{
    resetLocation = true;
}

void Player::setName(string playerName_)
{
    playerName = playerName_;
    // cout << "playerName: " << playerName << endl;
}

void Player::setJailStatus(bool status)
{
    inJail = status;
}

void Player::setJailCounter(int counter)
{
    turnsinjail = counter;
}

void Player::setBalance(int balance_)
{
    balance = balance_;
    // cout << "balance: " << balance << endl;
}

void Player::setBoardLocation(int boardlocation_)
{
    previousBoardLocation = boardlocation;
    boardlocation = boardlocation_ % 39;
    
}

void Player::setPlayerPos(int x, int y)
{
    playerPos_x = x;
    playerPos_y = y;
    // cout << "playerPos_x: " << playerPos_x << endl;
    // cout << "playerPos_y: " << playerPos_y << endl;
}

void Player::setPlayerChar(string playerChar_)
{
    playerChar = playerChar_;
    // cout << "playerChar: " << playerChar << endl;
}

void Player::setBankruptStatusTrue()
{
    bankrupt = true;
}

string Player::getName() const
{
    return playerName;
}

int Player::getBoardLocation()
{
    return boardlocation;
}

int Player::getJailCounter()
{
    return turnsinjail;
}

string Player::getPlayerChar() const
{
    return playerChar;
}

bool Player::getJailStatus()
{
    return inJail;
}

int Player::getBalance() const
{
    return balance;
}

int Player::getPlayerPos_x() const
{
    return playerPos_x;
}

int Player::getPlayerPos_y() const
{
    return playerPos_y;
}

bool Player::getBankruptStatus() const
{
    return bankrupt;
}

int Player::getPreviousBoardLocation()
{
    return previousBoardLocation;
}

bool Player::getDisplayStatus() const
{
    return displayStatus;
}

bool Player::getResetLocation_Status()
{
    return resetLocation;
}