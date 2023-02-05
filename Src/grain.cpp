#include <ILI9341.h>
#include "grain.h"
#include "HourglassColorSettings.h"
#include <stdlib.h>
#include <math.h>

void Grain::animate(int y, float rotation, int screen_rotation) {
	if(this->start_shifting <= (int)HAL_GetTick()) {
		if(timer + animation_fall_time <= (int)HAL_GetTick()) {
			if(this->animation_counter > this->max_animation_counter) {
				this->animation_counter = 1;
				this->set_coordinates(this->x_center, this->y_center);
				this->set_random_start_shift();
			}
			this->set_random_direction();
			this->set_random_distance();
			this->set_rotation(rotation, screen_rotation);
			this->move_animation(y);
			timer = HAL_GetTick();
		}
	}
}

void Grain::set_rotation(float rotation, int screen_rotation) {
	this->rotation = int(rotation * float(this->x_center/9));
	this->rotation = screen_rotation == SCREEN_VERTICAL_1 ? - this->rotation : this->rotation;
}

void Grain::set_random_start_shift() {
	start_shifting = (int)HAL_GetTick() + (rand()% ((fall_time + 400) - animation_fall_time) + animation_fall_time);
}

void Grain::set_random_direction() {
	this->direction = rand()%3-1;
}

void Grain::set_random_distance() {
	double adding_distance = ((double)(rand()%201 - 100)) * (0.02);
	this->distance = (int)((adding_distance) + (way_in_pixels / max_animation_counter));
}

Grain::Grain() {
	this->set_random_start_shift();
	srand(HAL_GetTick());
}

void Grain::delete_grain(int y){
	if(y > this->y && this->y > y_center) {
		this->draw(HourglassColorSettings::BackGround());
	}
}

void Grain::set_coordinates(int x, int y){
	int r_ = this->form(y, 0, 0);
	int l_ = this->form(y, 1, 0);
	int r = fmax(l_, r_);
	int l = fmin(l_, r_);

	if(x <= l+2) {
		this->x = l+5;
	} else if(x >= r-2){
		this->x = r-5;
	} else {
		this->x = x;
	}
	if(y >= this->max_y) {
		this->y = max_y;
		this->x = x_center;
	} else {
		this->y = y;
	}
}

void Grain::move_animation(int y) {
	this->delete_grain(y);
	if(this->animation_counter == max_animation_counter) {
		this->set_coordinates(this->x, this->max_y);
	} else {
		this->set_coordinates(this->x + this->rotation+this->direction, this->y+this->distance);
	}
		this->draw(HourglassColorSettings::Sand());
	this->animation_counter += 1;
}

void Grain::draw(short color) {
	for(int i = 0; i < this->graint_pixels; i++){
		for(int j = 0; j < this->graint_pixels; j++){
			ILI9341_Draw_Pixel(this->x+i, this->y+j, color);
		}
	}
}
