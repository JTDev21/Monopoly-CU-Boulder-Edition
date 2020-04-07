#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
//01001110 01101001 01100011 01100101 00100001 00100001 00100000 01000101 01100001 01110011 01110100 01100101 01110010 00100000 01000101 01100111 01100111 00101100 00100000 01101000 01110101 01101000 00111111 00001101 00001010 00100000 00100000 00100000 01011111 00001101 00001010 00100000 00100111 00100000 00100000 00100000 00100111 00001101 00001010 00100111 00100000 00100000 00100000 00100000 00100000 00100111 00001101 00001010 00100000 00100111 00100000 01011111 00100000 00100111 00001101 00001010 00100000
using namespace std; 

string toupper(string name) //A function to turn the string entered into all capital leters
{
    int length = name.length(); //Obtains the length of the string
    string newname;
    for(int i = 0; i < length; i++) //Cycles through all of the characters of the entered string.
    {
        if(name[i] >= 97 && name[i] <= 122) //Checks if characher is a lowercase letter using ascii values.
        {
            char newchar = name[i] - 32; //Obtains its capital leter equivalent.
            newname = newname + newchar;
        }
        else
        {
            newname = newname + name[i];
        }
    }
    return newname;
}

Game::Game()
{
    dice_1 = 0;
    dice_2 = 0;
    currentTurn = 0;
    inJail = false;
    numPlayers = 0;
    
    //Initialized Tabula Rasa Board
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
                    {
                        map[i][j][k][l] = '#';
                    }
                    else
                    {
                        map[i][j][k][l] = ' ';
                    }
                    if(((l % 2) != 0) && !((1 <= i && i <= 9) && (1 <= j && j <= 9)) || (j == 9 && l == 1))
                    {
                        map[i][j][k][l] += " |";
                    }
                    else
                    {
                        map[i][j][k][l] += "  ";
                    }
                    map[i][j][k][l] += ' ';
                }
            }
        }
    }
}

void Game::move(int currentTurn)
{
    //This is where we will update players position
    int i = 10;
    int j = 10;
    int k = player[currentTurn - 1].getPlayerPos_x();
    int l = player[currentTurn - 1].getPlayerPos_y();
    string playerPiece = player[currentTurn - 1].getPlayerChar();
    // cout << "K:" << k << endl;
    // cout << "l:" << l << endl;
    // cout << "playerPiece:" << playerPiece << endl;
    // int k = 0;
    // int l = 0;
    // string playerPiece = "$";
    
    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
    {
        map[i][j][k][l] = playerPiece;
    }
    else
    {
        map[i][j][k][l] = ' ';
    }
    if(((l % 2) != 0) && !((1 <= i && i <= 9) && (1 <= j && j <= 9)) && j != 10)
    {
        map[i][j][k][l] += "|";
    }
    else
    {
        map[i][j][k][l] += " ";
    }
    map[i][j][k][l] += " ";
}

void Game::display_MapAndPlayer() const
{
    //4d array - This allows for fixed position of character while knowing which player is on which square
        /*arr[i][j][k][l] <-- I and J represent the number of squares in a monopoly board (11 by 11)
            //k and l are the position of each player. This will not be change under any circumstance to change the player position use i and j
        */
    //This is where the map will be displayed
    string firstRowConcatOfK, secondRowConcatOfK;
    int topLinecounter = 20;
    int leftLineCounter = 20;
    int rightLineCounter = 30;
    for(int oneLine = 0; oneLine < 11; oneLine++)
    {
        cout << "      " << topLinecounter; 
        topLinecounter++;
    }
    cout << endl;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    // cout << "i: " << i << " j: " << j  << " k: " << k << " l: " << l << endl;
                    if(k == 0) //OMG I forgot the other = and it kept on going to inf
                    {
                        firstRowConcatOfK += map[i][j][k][l];
                        //cout << firstRowConcatOfK << endl;
                    }
                    else
                    {
                        secondRowConcatOfK += map[i][j][k][l];
                    }
                    
                }
                
            }
        }
        if(rightLineCounter == 40)
        {
            rightLineCounter = 0;
        }
        cout << leftLineCounter << " | " << firstRowConcatOfK << endl << "   | " << secondRowConcatOfK << rightLineCounter << endl;
        leftLineCounter--;
        rightLineCounter++;
        if(0 <= i && i < 10)
        {
            cout << "   ---------" << setw(80) << "---------" << endl;
        }
        firstRowConcatOfK = "";
        secondRowConcatOfK = "";
    }
    
    int bottomLinecounter = 10;
    for(int oneLine = 0; oneLine < 11; oneLine++)
    {
        cout << "      " << bottomLinecounter << " "; 
        bottomLinecounter--;
    }
    cout << endl;
}

bool Game::readPlayers()
{
    cout << "How many players? (2-4): " << endl;
    cin >> numPlayers;
    ifstream readPlayerFile;
    string line, x_pos, y_pos, playerChar_, playerName;
    readPlayerFile.open("player.csv");
    if(readPlayerFile.fail())
    {
        cout << "Error. Could not read player file." << endl;
        return false;
    }
    else
    {
        if(!(2 <= numPlayers && numPlayers <= 4))
        {
            cout << "Invalid Range of players" << endl << endl;
            return false;
        }
        else
        {
            for(int i = 0; i <= numPlayers; i++)
            {
                getline(readPlayerFile, line);
                istringstream strm;
                strm.str(line);
                getline(strm, x_pos, ',');
                getline(strm, y_pos, ',');
                getline(strm, playerChar_, ',');
                if(i != 0)
                {
                    cout << "\n(" << i << ") Enter a player name: " << endl;
                    cin >> playerName;
                    
                    player[i - 1].setName(playerName);
                    player[i - 1].setPlayerChar(playerChar_);
                    cout << "Player Character: " << player[i - 1].getPlayerChar() << endl;
                    player[i - 1].setPlayerPos(stoi(x_pos), stoi(y_pos));
                }
            }
            // for(int i = 0; i < numPlayers; i++)
            // {
            //     cout << setw(20) << player[i].getName() << " (" << player[i].getPlayerChar() << ')' << endl;
            //     cout << setw(20) << "Balance: " << player[i].getBalance() << endl;
            //     cout << setw(20) << '(' << player[i].getPlayerPos_x() << ", " << player[i].getPlayerPos_y() << ')' << endl;
            // }
            readPlayerFile.close();
            return true;
        }
        
    }
}

//Will intialize the property of the board after reading the file
void Game::readProperty()
{
    string line, propertyLocation_str;
    ifstream readPropertyFile;
    readPropertyFile.open("property.csv");
    if(readPropertyFile.fail())
    {
        cout << "Boi you failed somewhere cause you got an error for readProperty file." << endl;
        cout << "The file probably doesn't exist." << endl;
        exit(-1);
    }
    for(int i = 0; i <= (40 + 1); i++) //<-- The number 23 represents how many buildings, the extra +1 comes from the 2nd header()
    {
        getline(readPropertyFile, line);
        if(i != 0 && i!= 1) //Will skip the first line
        {
            istringstream strm;
            strm.str(line);
            getline(strm, propertyLocation_str, ',');

            int propertyLocation_int = stoi(propertyLocation_str);
            
            switch(propertyLocation_int)
            {
                //All these cases 
                // Note that cases 12, 27
                    // ^ Those are electric company, water works,
                    //Those are cases which we can do, i have no idea how to implement the other cases
                    //when the players land on those. At least for now
                case 0: case 2: case 4: case 7: case 10: case 12: case 17: 
                case 20: case 22: case 27: case 30: case 33: case 36: case 38:
                {
                    // cout << "IDK Cases: " << propertyLocation_int << endl;
                    //INDIVIDUAL CASES ARE NOT COMPLETED
                    break;
                }
                //case 5, 15, 25, 35 are railroads
                case 5: case 15: case 25: case 35:
                {
                    string transportName_, transportCost_, transportRent_;
                    getline(strm, transportName_, ',');
                    getline(strm, transportCost_, ',');
                    for(int i = 0; i < 4; i++)
                    {
                        getline(strm, transportRent_, ',');
                        property[propertyLocation_int].setRentAt(i, stoi(transportRent_));
                    }

                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    property[propertyLocation_int].setPropertyName(transportName_);
                    property[propertyLocation_int].setPropertyCost(stoi(transportCost_));
                    break;
                }
                default:
                    // cout << "Colored Property: " << propertyLocation_int << endl;
                    string propertyName_, property_cost_, building_cost_;
                    // string rent_,house1_,house2_,house3_,house4_,hotel_, color_;
                    string rent_, color_;
                    
                    getline(strm, propertyName_, ',');
                    getline(strm, property_cost_, ',');
                    getline(strm, building_cost_, ',');
                    for(int i = 0; i < 6; i++)
                    {
                        getline(strm, rent_, ',');
                        property[propertyLocation_int].setRentAt(i, stoi(rent_));
                    }
                    getline(strm, color_, ',');
                    // getline(strm, rent_, ',');
                    // getline(strm, house1_, ',');
                    // getline(strm, house2_, ',');
                    // getline(strm, house3_, ',');
                    // getline(strm, house4_, ',');
                    // getline(strm, hotel_, ',');

                    
                    
                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    property[propertyLocation_int].setPropertyName(propertyName_);
                    property[propertyLocation_int].setPropertyCost(stoi(property_cost_));
                    property[propertyLocation_int].setBuildingCost(stoi(building_cost_));

                    // property[propertyLocation_int].setRentAt(0, stoi(rent_));
                    // property[propertyLocation_int].setRentAt(1, stoi(house1_));
                    // property[propertyLocation_int].setRentAt(2, stoi(house2_));
                    // property[propertyLocation_int].setRentAt(3, stoi(house3_));
                    // property[propertyLocation_int].setRentAt(4, stoi(house4_));
                    // property[propertyLocation_int].setRentAt(5, stoi(hotel_));

                    property[propertyLocation_int].setColor(color_);
                    break;
            }
        }
    }
    readPropertyFile.close();
}

void Game::getPropertyInfo(int propertyLocation_)
{
    //Issue how will we deal with non properties
    if(!(0 <= propertyLocation_ && propertyLocation_ <= 39))
    {
        cout << "[Error -- getPropertyInfo: Out of bounds]" << endl;
    }
    else
    {
        cout << "[" << propertyLocation_ << "] " << property[propertyLocation_].getPropertyName() << endl;
        cout << "--------------------------------" << endl;
        cout << "Owner: " << property[propertyLocation_].getOwner() << endl;
        cout << "Property Price: $" << property[propertyLocation_].getPropertyCost() << endl;
        
        switch(propertyLocation_)
        {
            case 5: case 15: case 25: case 35:
            {
                property[propertyLocation_].getListOfRentTransport();
                break;
            }
            default:
                cout << "Property Color: " << property[propertyLocation_].getColor() << endl;
                cout << "Building cost: $" << property[propertyLocation_].getBuildingCost() << endl;
                property[propertyLocation_].getListOfRentCP();
                break;
        }
        
        cout << "\nNumber of buildings built: " << property[propertyLocation_].getNumBuildings() << endl;
        cout << "Current Rent Cost: $" << property[propertyLocation_].getRent() << endl << endl;
    }
}


void Game::roll()
{
    srand((unsigned)time(0));
    for(int i = 0; i < 2; i++)
    {
        dice_1 = rand() % 6 + 1;
        dice_2 = rand() % 6 + 1;
    }
    // cout << "dice_1: " << dice_1 << endl;
    // cout << "dice_2: " << dice_2 << endl;
}



void Game::endTurn(string end_)
{
    /*
    The end game function will allow a player to end their turn by typing in "end".
    They current turn will move to the next player and display which player's turn it is.
    */
    string endturn = toupper(end_);
    if(end_ == "END")
    {
        currentTurn = (currentTurn % numPlayers) + 1;
        cout << "It is player " << currentTurn << "'s turn." << endl;
    }
}

void doubleTurn(int dice_1, int dice_2)
{
    /*
    This function will allow the player to roll again if they roll two dice of the same time.
    It will function by taking in both of the dice roll variables and comparing them to each other.
    If they are the same, it will move you and allow you to roll again after performing other tasks.
    */
}

void endGame(string quit_)
{
    /*
    This function will allow the users to end the game whenver they feel like it by typing in quit. This will allow for 
    the users to quit if they wish to but could also allow you to calculate the response if someone wins by setting up
    a condition to activate it in main. It print a message to a text file that will display the results and the winner, 
    along with their balances.
    */
}

void buy(char y_n)
{
    /*
    This function will allow the user to buy the property that they land on if it is unknown. It will obtain the cost of 
    the property from the property array and will then subtract the cost from the player's balance.
    */
}

void trade(string playerName, string propertyoffer, int offer_, string propertywanted)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
}

void buyHouse(string propertyname)
{
    /*
    This function will allow the user to buy a house for one of their properties. It will obtain the house cost from the property
    array and move the rent array down one position. It will also subtract the house cost from the player's balance.
    */
}

void rent(string property)
{
    /*
    This function will allow it so that if the player lands on a property already owned, it will check if it is owned,
    determine how much rent is owed due to the rent array in the property array, and subtract the balance from the player
    while adding that amount to the owner.
    */
}

void waterElectricRent(int rollone, int rolltwo, string propertyname)
{
    /*
    If the player lands on a utility that someone else owns, it determines if they own one or both utility,
    and performs a calculation based on whatever they rolled to land on that spot. The multiplier is changed based
    on if they own one or both properties. This money is subtracted from the player's balance and added to the
    owner's balance.
    */
}

void busRent(string propertyname)
{
    /*
    If the player lands on a bus spot that is already owned by someone else, the player will be charged a rent based
    on how many buses the onwer has. This function will determine how many buses the owner has and determine the rent. 
    The player will lose that amount and the owner will gain that amount.
    */
}

<<<<<<< HEAD
void luxuryTax();
=======
void luxuryTax(int balance)
>>>>>>> 8d07b06f7a04bb9abe0db3698493c2fa4f07ca95
{
    /*
     If the player lands on the luxury tax spot, they will have 75 dollars subtracted from their balance.
    */
}

void incomeTax(int balance)
{
    /*
    If the player lands on this spot, they are given the option of paying either 200 dollars or 10% of their balance. This
    function will allow them to choose and will perform the subtractions from their balance after the player chooses.
    */
}

void jail(char y_n)
{
    /*
    This function will move a player directly to jail. It will then set a boolian to true which will remain true until three turns
    pass or the player succeeds in rolling a double. 
    */
}

void passGo(char y_n)
{
    /*
    When the player passes go, this function will automatically add 200 dollars to their balance.
    */
}

void communityChest(string textfile)
{
    /*
    This function will read the community chest textfile, generate a random number between 1 and 17, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

void chance(string textfile)
{
    /*
    This function will read the chance textfile, generate a random number between 1 and 16, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

