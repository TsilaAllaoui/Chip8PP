#pragma once

#include <iostream>
#include <sstream>

#include <QString>

/**
* \desc Convert the value given as parameter as Hex QString
* \param val The value to be converted to a HEx QString 
* \return The converted QString
*/
QString getAsQStringHex(uint16_t val);

/**
* \desc Convert the value given as parameter as Hex QString
* \param val The value to be converted to a HEx QString
* \return The converted QString
*/
uint16_t QStringtoHex(QString val);