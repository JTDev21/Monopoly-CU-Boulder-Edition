#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;


//PLAYER CLASS IS FINISHED
//IS IT?
class Player
{
    private:
        string playerName;
        string playerChar;
        int balance;
        int playerPos_x;
        int playerPos_y;
        bool bankrupt;
        
    public:
        Player();
        
        void setName(string playerName_); // Set player name
        void setPlayerChar(string playerChar_);
        // NOTE: We can only set the balance and not update it(ADD/SUBTRACT)
        void setBalance(int balance_); 
        void setPlayerPos(int x, int y);
        
        
        //We must only use this function when we have determined that the player is bankrupted or has decided to quit
        void setBankruptStatusTrue();
        
        string getName() const; //Get player name
        string getPlayerChar() const;
        int getBalance() const; //Get balance
        int getPlayerPos_x() const;
        int getPlayerPos_y() const;
        bool getStatus() const; // We must use this function to check if the player can play
};
#endif
