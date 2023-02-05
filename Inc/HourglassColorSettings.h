
#ifndef HOURGLASSCOLORSETTINGS_H_
#define HOURGLASSCOLORSETTINGS_H_

class HourglassColorSettings {
private:
	static short BACK_GROUND;
	static short SAND;
	static short HOURGLASS;
	static int preset_quantity;
public:
	HourglassColorSettings(){};
	static void set_preset(int preset);
	static void standart_preset();
	static void sakura_preset();
	static void blood_preset();
	static void nature_preset();
	static short BackGround() { return BACK_GROUND; };
	static short Sand() { return SAND; };
	static short HourGlass() { return HOURGLASS; };
	~HourglassColorSettings(){};
};

#endif /* HOURGLASSCOLORSETTINGS_H_ */
