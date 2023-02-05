#include <ILI9341.h>
#include "hourglass.h"
#include "HourglassColorSettings.h"
#include "grains.h"
#include <math.h>

int Hourglass::cosine(int y, int f, bool clock) {
	double cos_ = (cos(y*3.1415926/y_all))*(x_half) * 0.8;
	int res = 0;
	double half = (double)x_all / 2;
	if(f == 0) {
		if(y > y_half) {
			cos_ = half - cos_;
		} else {
			cos_ = half + cos_;
		}
		cos_ -= clock ? 0.0 : 1.0;
		res = clock ? floor(cos_) : ceil(cos_);
	} else {
		if(y > y_half) {
			cos_ = half + cos_;
		} else {
			cos_ = half - cos_;
		}
		cos_ += clock ? 0.0 : 1.0;
		res = clock ? ceil(cos_) : floor(cos_);
	}
	return res;
}

int Hourglass::sine(int y, int f, bool clock) {
	double sin_cos = (cos(y*3.1415926/y_all))*(sin(y*3.1415926/y_all))*(x_half)* 1.5;
	double half = (double)x_all / 2;
	int res = 0;
	if(f == 0){
		if(y > y_half){
			sin_cos = half - sin_cos;
		} else {
			sin_cos = half + sin_cos;
		}
		sin_cos -= clock ? 0.0 : 1.0;
		res = clock ? floor(sin_cos) : ceil(sin_cos);
	} else {
		if(y > y_half){
			sin_cos = half + sin_cos;
		} else {
			sin_cos = half - sin_cos;
		}
		sin_cos += clock ? 0.0 : 1.0;
		res = clock ? ceil(sin_cos) : floor(sin_cos);
	}
	return res;
}

int Hourglass::module(int y, int f, bool clock) {
	double mod = 0;
	int res = 0;
	if(f == 0) {
		if(y > y_half) {
			mod = y*proportion;
		} else {
			mod = (y_all-y)*proportion;
		}
		res = clock ? floor(mod) : ceil(mod);
	} else if(f == 1){
		if(y > y_half) {
			mod = (y_all-y)*proportion;
		} else {
			mod = y*proportion;
		}
		res = clock ? ceil(mod) : floor(mod);
	}
	return res;
}

int Hourglass::glass_form(int y, int f, bool clock) {
	int res = 0;
	switch(figure_glass_form){
	case 1:
		res = module(y, f, clock);
		break;
	case 2:
		res = cosine(y, f, clock);
		break;
	case 3:
		res = sine(y, f, clock);
		break;
	default:
		res = cosine(y, f, clock);
		break;
	}
	return res;
}


int Hourglass::glass_form(int y, int f) {
	return this->glass_form(y, f, false);
}

void Hourglass::print_sand_line(int y, short color) {
	int x1 = (int)(glass_form(y,1));
	int x2 = (int)(glass_form(y,0));
	ILI9341_Random_line(x1+2, y, x2-2, y, color);
}

void Hourglass::print_sand() {
	for(int y = 0+shift; y < y_half-1; y++) {
		this->print_sand_line(y, HourglassColorSettings::Sand());
	}
}

void Hourglass::change_sand_line(int y, int new_y) {
	this->print_sand_line(y, HourglassColorSettings::BackGround());
	this->print_sand_line(new_y, HourglassColorSettings::Sand());
}

void Hourglass::set_time(double time) {
	this->current_sand_swap_animation_time = this->sand_swap_animation_time * time;
}

void Hourglass::animation(float swaper, float rotation) {
	if(print_flag){
		this->reset(swaper);
		if(this->current_sand_layer < y_half){
			if(timer + current_sand_swap_animation_time <= HAL_GetTick()) {
				this->change_sand_line(this->current_sand_layer, y_all-this->current_sand_layer+shift-5);
				timer = HAL_GetTick();
				this->current_sand_layer++;
			}
			this->grains.animate(y_all-this->current_sand_layer+shift-5, rotation, this->screen_rotation);
		} else {
			this->grains.deleting(y_half+this->shift-5);
		}
	}
}

void Hourglass::reset(float swaper) {
	//---ТОЛЬКО В ТАКОМ ПОРЯДКЕ!!!!!!!!---//
	if(this->swap_screen_rotation(swaper)){
		this->grains.deleting(y_half+this->shift-5);
		this->screen_rotation_sand_fall();
		this->set_sand_layer(this->shift + y_half - current_sand_layer);
		count++;
	}
	//------------------------------------//
}

int Hourglass::swap_screen_rotation(float swaper) {
	int rotation = swaper > 0.0 ? SCREEN_VERTICAL_2  : SCREEN_VERTICAL_1;
	if(this->screen_rotation != rotation) {
		this->screen_rotation = rotation;
		ILI9341_Set_Rotation(this->screen_rotation);
		return 1;
	}
	return 0;
}

void Hourglass::set_screen_rotation(float swaper) {
	this->screen_rotation = swaper > 0.0 ? SCREEN_VERTICAL_2  : SCREEN_VERTICAL_1;
}

void Hourglass::screen_rotation_sand_fall() {
	int layers = this->current_sand_layer - this->shift;
	int swaps = this->y_half - layers;
	for(int y = 4; y < swaps; y++) {
		this->change_sand_line(y, y+layers);
	}

	if(current_sand_layer != y_half){ //без этого условия y_half+y == y_half+y+layers (нижняя чаша просто начинает заполняться песком полностью)
		layers = y_half-current_sand_layer;
		swaps =  y_half-layers;
		for (int y = 0; y <= swaps-4; y++) {
			this->change_sand_line(y_half+y, y_half+y+layers);
		}
	}
	this->print_hourglass();
}

void Hourglass::set_sand_layer(int lays) {
	this->current_sand_layer = lays;
}

void Hourglass::print_hourglass() {
	for(int y = 0; y < y_all; y++) {
		ILI9341_Draw_Pixel((int)(glass_form(y,1, true)), y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,1, true)) - 1, y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,1, true)) - 2, y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,1, true)) - 3, y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,0, true)), y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,0, true)) + 1, y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,0, true)) + 2, y, HourglassColorSettings::HourGlass());
		ILI9341_Draw_Pixel((int)(glass_form(y,0, true)) + 3, y, HourglassColorSettings::HourGlass());
	}
	ILI9341_Random_line(glass_form(0,1, true), 0, glass_form(0,0, true), 0, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(1,1, true), 1, glass_form(1,0, true), 1, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(2,1, true), 2, glass_form(2,0, true), 2, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(3,1, true), 3, glass_form(3,0, true), 3, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(y_all-1,1, true), y_all-1, glass_form(y_all-1,0, true), y_all-1, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(y_all-2,1, true), y_all-2, glass_form(y_all-2,0, true), y_all-2, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(y_all-3,1, true), y_all-3, glass_form(y_all-3,0, true), y_all-3, HourglassColorSettings::HourGlass());
	ILI9341_Random_line(glass_form(y_all-4,1, true), y_all-4, glass_form(y_all-4,0, true), y_all-4, HourglassColorSettings::HourGlass());
	ILI9341_Draw_Vertical_Line(119, 160, 2, HourglassColorSettings::BackGround());
	ILI9341_Draw_Vertical_Line(120, 160, 2, HourglassColorSettings::BackGround());
}

void Hourglass::print() {
	ILI9341_Fill_Screen(HourglassColorSettings::BackGround());
	this->print_hourglass();
	this->print_sand();
}

void Hourglass::set_glass_form(int form, float swaper){
	this->figure_glass_form = form;
	this->set_sand_layer(shift);
	this->swap_screen_rotation(swaper);
	this->set_glass_form_for_grains();
	this->print();
}

void Hourglass::set_glass_form_for_grains(){
	switch(figure_glass_form){
	case 1:
		grains.set_form(module);
		break;
	case 2:
		grains.set_form(cosine);
		break;
	case 3:
		grains.set_form(sine);
		break;
	default:
		grains.set_form(cosine);
		break;
	}
}
