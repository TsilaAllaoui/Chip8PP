#include "utilities.h"

QString getAsQStringHex(uint16_t val)
{
	if(val != 0)
		return QString("0x") + QString("%1").arg(val, 0, 16).toUpper();
	return QString("0");
}
