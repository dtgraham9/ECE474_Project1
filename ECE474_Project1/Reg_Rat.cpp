#include "Reg_Rat.h"
#include <string>
Reg_Rat::Reg_Rat() {
	busy = false;
	rat = -1;
}
Reg_Rat::Reg_Rat(int val, std::string df_name) {
	busy = false;
	rat = -1;
	value = val;
	name = df_name;
}

std::string  Reg_Rat::Name_Resolver()
{
	if (rat == -1) {
		return name;
	}
	else {
		return "RS" + std::to_string(rat);
	}
}
