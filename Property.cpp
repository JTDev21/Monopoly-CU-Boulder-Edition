#include "Property.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

using namespace std;

Property::Property()
{
    propertyLocation = 0;
    propertyName = "";
    owner = "none";
    propertyCost = 0;
    buildingCost = 0;
    for(int i = 0; i < 6; i++)
    {
        rentArr[i] = 0;
    }
    color = "white"; //<-- White just have all the colors
    numBuildings = 0;
}

void Property::setPropertyLocation(int propertyLocation_)
{
    propertyLocation = propertyLocation_;
}

void Property::setPropertyName(string propertyName_)
{
    propertyName = propertyName_;
}

// We may have an issue how will we address whether the Owner exist for a particular property
// I'll leave this issue out for now
void Property::setOwner(string username_)
{
    owner = username_;
}

void Property::setPropertyCost(int propertyCost_)
{
    propertyCost = propertyCost_;
}

void Property::setBuildingCost(int buildingCost_)
{
    buildingCost = buildingCost_;
}

void Property::setRentAt(int i, int rent_)
{
    if(!(0 <= i && 0 < 6))
    {
        cout << "[Error -- setRentAt] Specified index is out of bounds" << endl;
    }
    else
    {
        rentArr[i] = rent_;
    }
}

void Property::setColor(string color_)
{
    color = color_;
}

void Property::setNumBuildings(int numBuildings_)
{
    numBuildings = numBuildings_;
}


// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// //Accessors Section
int Property::getPropertyLocation()
{
    return propertyLocation;
}

string Property::getPropertyName()
{
    return propertyName;
}

string Property::getOwner()
{
    return owner;
}

int Property::getPropertyCost()
{
    return propertyCost;
}

int Property::getBuildingCost()
{
    return buildingCost;
}

int Property::getListOfRent()
{
    cout << setw(15) << "Rent Cost" << endl;
    cout << "-------------------------" << endl;
    for(int i = 0; i < 6; i++)
    {
        if(i == 5)
        {
            cout << "(5) Building (Hotel): $" << rentArr[5] << endl;
        }
        else
        {
            cout << "(" << i << ") Building(s): $" << rentArr[i] << endl;
        }
    }
}

int Property::getRent()
{
    return rentArr[numBuildings];
}

string Property::getColor()
{
    return color;
}

int Property::getNumBuildings()
{
    return numBuildings;
}
