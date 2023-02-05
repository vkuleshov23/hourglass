#include <ILI9341.h>
#include <loadingAnimation.h>
#include "HourglassColorSettings.h"
#include "math.h"

LoadingAnimation::LoadingAnimation(float rand) {
	srand(abs(rand) * 100000);
	ILI9341_Fill_Screen(HourglassColorSettings::BackGround());
}

LoadingAnimation::LoadingAnimation(float rand, bool way, bool status) {
	srand(abs(rand) * 100000);
	ILI9341_Fill_Screen(HourglassColorSettings::BackGround());
	this->set_way(way);
	this->set_status(status);
}
float LoadingAnimation::circle(float x) {
	if (x > r) { return 0; }
	float y = sqrt(r*r - float(x*x));
	return status ? y : -y;
}
void LoadingAnimation::drawP(float x, int x_shift, int y_shift, short color){
	if(abs(x) <= r) {
		float y = this->circle(x);
		x = round(x);
		y = round(y);
		int size = 2;
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				ILI9341_Draw_Pixel(x+i+x_shift, y+j+y_shift, color);
			}
		}
		if(ceil(abs(x)) == round(abs(r))) {
			int add = size, prop = ((int(r)*4)/x_shift);
			for(int j = add; j < add+prop+1; j++) {
				for(int i = 0; i < size; i++) {
					ILI9341_Draw_Pixel(x+i+x_shift, y+j+y_shift, color);
					ILI9341_Draw_Pixel(x+i+x_shift, y-j+y_shift, color);
				}
			}
		}
	}
}

float LoadingAnimation::iter(){
	float it = 0.15;
	return way ? it : -it;
}

void LoadingAnimation::print_coil(short color1, short color2){
	int x_center = 119;
	int y_center = 159;
	float x = 0.0;
	r = 1;
	while(r <= x_center){
		if(int(x) == x_center+1 || int(x) == -x_center-1 || abs(int(x)) > r) {
			way = !way;
			status = !status;
		}
		r += 0.021;
		this->drawP(x, x_center, y_center, color1); //0x16f7
		status = !status;
		this->drawP(-x, x_center, y_center, color2);//0xd8ad
		status = !status;
		x += iter();
	}
}

void LoadingAnimation::animation(){
	short color1 = rand()%(0xFFFF-0x8888)+0x8888;
	short color2 = rand()%(0xFFFF-0x8888)+0x8888;
	this->print_coil(color1, color2);
	HAL_Delay(100);
	this->print_coil(HourglassColorSettings::BackGround(), HourglassColorSettings::BackGround());
}
