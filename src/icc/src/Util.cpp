#include "Util.h"

bool util::is_printable_ascii(const char input)
{
	return input >= 20 && input < 127;
}
