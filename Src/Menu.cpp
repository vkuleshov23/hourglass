#include "Menu.h"
#include "HourglassColorSettings.h"
#include <stdio.h>

void Menu::processing(uint8_t state, uint32_t ms, float mpu_coordinates_clock, float mpu_coordinates_sand, int32_t encoder_counter) {
	this->swap_screen_if_changed(mpu_coordinates_clock);
	if(this->is_short_state_1(state, ms)) {
		this->short_state_1(ms);
	} else if (this->is_long_state(state, ms)) {
		this->long_state(mpu_coordinates_clock);
	} else if(this->is_short_state(state, ms)) {
		this->short_state(ms);
	}
	this->encoder_state(encoder_counter);
	this->hourglass.animation(mpu_coordinates_clock, mpu_coordinates_sand);
}

void Menu::swap_screen_if_changed(float mpu_coordinates){
	int rotation = mpu_coordinates > 0.0 ? SCREEN_VERTICAL_2  : SCREEN_VERTICAL_1;
	if(this->screen_rotation != rotation) {
		this->screen_rotation = rotation;
		if(this->in_menu()) {
			ILI9341_Set_Rotation(this->screen_rotation);
			this->print_menu_head();
			this->print_menu_body();
		} else {
			if(!this->hourglass.get_print_flag()) {
				if (this->hourglass.swap_screen_rotation(mpu_coordinates))
					this->hourglass.print();
			}
		}
	}
}

bool Menu::is_short_state_1(uint8_t state, uint32_t ms) {
	return (state == 0 && !short_state_Set && (ms - time_Set) > 50);
}

void Menu::short_state_1(uint32_t ms) {
	this->short_state_Set = 1;
	this->long_state_Set = 0;
	this->time_Set = ms;
}

bool Menu::is_long_state(uint8_t state, uint32_t ms) {
	return (state == 0 && !long_state_Set && (ms - time_Set) > 500);
}

void Menu::long_state(float mpu_coordinates) {
	this->long_state_Set = 1;
	this->long_state_execute(mpu_coordinates);
}

void Menu::long_state_execute(float mpu_coordinates) {
	this->change_menu_flag();
	if (this->in_menu()) {
		this->stop_hourglass();
		this->print_menu_head();
		this->print_menu_body();
	} else {
		this->set_hourglass_time_and_preset(mpu_coordinates);
	}
}

void Menu::change_menu_flag() {
	this->set_view = !this->set_view;
}

bool Menu::in_menu() {
	return this->set_view;
}

void Menu::set_hourglass_time_and_preset(float mpu_coordinates){
	hourglass.set_sand_layer();
	hourglass.set_time(int(int(minute)*60) + int(second));
	HourglassColorSettings::set_preset(preset);
	hourglass.set_glass_form(form, mpu_coordinates);
}

void Menu::stop_hourglass() {
	hourglass.set_print_flag(false);
}

void Menu::print_menu_head() {
	ILI9341_Fill_Screen(BCKGRND_COLOR);
	///--- Вывод шапки настроек ---///
	ILI9341_WriteString(50, 25, "НАСТРОЙКИ", Font_15x25, get_head_color(), BCKGRND_COLOR);
	ILI9341_WriteString(77, 70, "Время", Font_15x25, get_head_color(), BCKGRND_COLOR);
	ILI9341_WriteString(60, 100, "мин/сек", Font_15x25, get_head_color(), BCKGRND_COLOR);
	ILI9341_WriteString(35, 170, "Отображение", Font_15x25, get_head_color(), BCKGRND_COLOR);
	ILI9341_WriteString(43,200, "форма/цвет", Font_15x25, get_head_color(), BCKGRND_COLOR);
	//ILI9341_WriteString(10,280, "минимум 10 сек", Font_15x25, RED, WHITE);
}

short Menu::get_head_color() {
	return WHITE;
}

void Menu::print_menu_body() {

	snprintf(minute_char, 4, "%2d", minute);
	snprintf(second_char, 4, "%2d", second);
	ILI9341_WriteString(minute_x, minute_y, minute_char, Font_15x25, get_body_color(0), BCKGRND_COLOR);
	ILI9341_WriteString(second_x, second_y, second_char, Font_15x25, get_body_color(1), BCKGRND_COLOR);
	snprintf(form_char, 4, "%2d", form);
	ILI9341_WriteString(form_x, form_y, form_char, Font_15x25, get_body_color(2), BCKGRND_COLOR);
	snprintf(preset_char, 4, "%2d", preset);
	ILI9341_WriteString(preset_x, preset_y, preset_char, Font_15x25, get_body_color(3), BCKGRND_COLOR);
}

short Menu::get_body_color(uint8_t pos) {
	return (this->param_set == pos) ? RED : BLUE;
}

bool Menu::is_short_state(uint8_t state, uint32_t ms) {
	return (state == 1 && short_state_Set && (ms - time_Set) > 50);
}

void Menu::short_state(uint32_t ms) {
	this->short_state_Set = 0;
	this->time_Set = ms;
	this->short_state_execute(ms);
}

void Menu::short_state_execute(uint32_t ms) {
	if(!this->long_state_Set) {
		if(this->in_menu()) {
			this->select_next_param();
			this->print_menu_body();
		} else {
			this->hourglass.invert_print_flag();
		}
	}
}

void Menu::select_next_param() {
	this->param_set = (this->param_set+1)%max_params;
}

void Menu::encoder_state(int32_t encoder_counter) {
	if(this->in_menu()) {
		if(this->encoder_changed(encoder_counter)){
			if(this->encoder_increment(encoder_counter)){
				this->encoder_add();
			} else if(this->encoder_decrement(encoder_counter)){
				this->encoder_sub();
			}
			this->print_menu_body();
			this->prevCounter = encoder_counter;
		}
	}
}

bool Menu::encoder_changed(int32_t encoder_counter) {
	return (encoder_counter != this->prevCounter);
}

bool Menu::encoder_increment(int32_t encoder_counter){
	return ((encoder_counter-this->prevCounter)==1||(encoder_counter-this->prevCounter<-1));
}

bool Menu::encoder_decrement(int32_t encoder_counter){
	return ((encoder_counter-this->prevCounter)==-1||(encoder_counter-this->prevCounter>1));
}

void Menu::encoder_add() {
	this->encoder_change_menu(true);
}

void Menu::encoder_sub() {
	this->encoder_change_menu(false);
}

void Menu::encoder_change_menu(bool add_or_sub) {
	switch(this->param_set) {
	case 0:
		this->minute_changing(add_or_sub);
		break;
	case 1:
		this->second_changing(add_or_sub);
		break;
	case 2:
		this->form_changing(add_or_sub);
		break;
	case 3:
		this->preset_changing(add_or_sub);
		break;
	}
}

void Menu::minute_changing(bool add_or_sub) {
	this->minute += add_or_sub ? 1 : -1;
	if(this->minute == 255) {
		this->minute = add_or_sub ?  0 : 59;
	}
	this->minute %= 60;
	if(this->minute == 0 && this->second < 10) this->second = 10;
}

void Menu::second_changing(bool add_or_sub) {
	this->second += add_or_sub ? 1 : -1;
	if(this->second == 255) {
		this->second = add_or_sub ? (this->minute == 0 ? 10 : 0) : 59;
	}
	this->second %= 60;
	if(this->minute == 0 && this->second < 10) add_or_sub ? this->second = 10 : this->second = 59;
}

void Menu::form_changing(bool add_or_sub) {
	this->form += add_or_sub ? 1 : -1;
	if(add_or_sub == true) {
		if (this->form > this->max_form) this->form = 1;
	} else {
		if (this->form < 1) this->form = 3;
	}

}

void Menu::preset_changing(bool add_or_sub) {
	this->preset += add_or_sub ? 1 : -1;
	if(add_or_sub == true) {
		if (this->preset > this->max_preset) this->preset = 1;
	} else {
		if (preset < 1) preset = 4;
	}
}
