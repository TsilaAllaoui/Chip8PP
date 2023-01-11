#include "utilities.h"

QString getAsQStringHex(uint16_t val)
{
	if(val != 0)
		return QString("0x") + QString("%1").arg(val, 0, 16).toUpper();
	return QString("0");
}

uint16_t QStringtoHex(QString val)
{
	uint16_t output = 0;
	if (val[0] == '0')
	{
		std::string s = val.toStdString().substr(2, val.toStdString().find(' '));
		std::istringstream iss(s);
		iss >> std::hex >> output;
		return output;
	}
}
