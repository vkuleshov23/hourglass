#include "HourglassColorSettings.h"

short HourglassColorSettings::BACK_GROUND = 0x0861;
short HourglassColorSettings::SAND = 0xf800;
short HourglassColorSettings::HOURGLASS = 0x4a49;
int HourglassColorSettings::preset_quantity = 4;

void HourglassColorSettings::set_preset(int preset) {
	switch(preset) {
	case 1:
		standart_preset();
		break;
	case 2:
		sakura_preset();
		break;
	case 3:
		blood_preset();
		break;
	case 4:
		nature_preset();
		break;
	default:
		standart_preset();
		break;
	}
}

void HourglassColorSettings::standart_preset() {
	BACK_GROUND = 0x2080;
	SAND = 0xe66a;
	HOURGLASS = 0x0331;
}

void HourglassColorSettings::sakura_preset() {
	BACK_GROUND = 0x2867;
	SAND = 0x9b96;
	HOURGLASS = 0xa01f;
}

void HourglassColorSettings::blood_preset() {
	BACK_GROUND = 0x0861;
	SAND = 0xf800;
	HOURGLASS = 0x4a49;
}

void HourglassColorSettings::nature_preset() {
	BACK_GROUND = 0x0940;
	SAND = 0x2fe0;
	HOURGLASS = 0x53a9;
}
