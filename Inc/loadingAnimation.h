#include "ILI9341.h"
#include "HourglassColorSettings.h"

#ifndef LOADINGANIMATION_H_
#define LOADINGANIMATION_H_

class LoadingAnimation {
private:
	bool way = true;
	bool status = true;
	float r = 1;
public:
	LoadingAnimation(float rand);
	LoadingAnimation(float rand, bool way, bool status);
	void set_way(bool way) { this->way = way;};
	void set_status(bool status) { this->status = status;};
	float iter();
	float circle(float x);
	void animation();
	void print_coil(short color1, short color2);
	void drawP(float x, int x_shift, int y_shift, short color);
	~LoadingAnimation(){};
};

#endif /* LOADINGANIMATION_H_ */
