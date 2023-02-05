#ifndef MENU_H_
#define MENU_H_

#include "stdio.h"
#include "hourglass.h"

class Menu {
private:

	int screen_rotation = SCREEN_VERTICAL_2;

	bool		set_view	= false;
	uint8_t		param_set	= 0;
	uint8_t 	max_params	= 4;

	uint8_t		minute	 = 0;
	uint8_t		minute_x = 65;
	uint8_t		minute_y = 130;

	uint8_t		second	 = 10;
	uint8_t		second_x = 127;
	uint8_t		second_y = 130;

	uint8_t		max_form = 3;
	uint8_t		form	 = 2;
	uint8_t		form_x   = 56;
	uint8_t		form_y   = 235;

	uint8_t 	max_preset = 4;
	uint8_t 	preset	   = 3;
	uint8_t		preset_x   = 130;
	uint8_t		preset_y   = 235;

	uint8_t		short_state_Set = 0;
	uint8_t		long_state_Set	= 0;
	uint32_t	time_Set	    = 0;

	int32_t	prevCounter = 0;

	char minute_char[4] = {0,};
	char second_char[4] = {0,};
	char preset_char[4] = {0,};
	char form_char[4]	  = {0,};

	Hourglass hourglass;

	void swap_screen_if_changed(float mpu_coordinates);
	bool is_short_state_1(uint8_t state, uint32_t ms);
	void short_state_1(uint32_t ms);
	bool is_long_state(uint8_t state, uint32_t ms);
	void long_state(float mpu_coordinates);
	bool is_short_state(uint8_t state, uint32_t ms);
	void long_state_execute(float mpu_coordinates);
	void change_menu_flag();
	bool in_menu();
	void set_hourglass_time_and_preset(float mpu_coordinates);
	void stop_hourglass();
	void print_menu_head();
	short get_head_color();
	void print_menu_body();
	short get_body_color(uint8_t pos);
	void short_state(uint32_t ms);
	void short_state_execute(uint32_t ms);
	void select_next_param();
	void encoder_state(int32_t encoder_counter);
	bool encoder_changed(int32_t encoder_counter);
	bool encoder_increment(int32_t encoder_counter);
	bool encoder_decrement(int32_t encoder_counter);
	void encoder_add();
	void encoder_sub();
	void encoder_change_menu(bool add_or_sub);
	void minute_changing(bool add_or_sub);
	void second_changing(bool add_or_sub);
	void form_changing(bool add_or_sub);
	void preset_changing(bool add_or_sub);


public:

	void processing(uint8_t state, uint32_t ms, float mpu_coordinates_clock, float mpu_coordinates_sand, int32_t encoder_counter);

	Menu(float mpu_coordinates) {
		this->hourglass = Hourglass(mpu_coordinates); // Отрисовка часов с учетом mpu6050
	}
	virtual ~Menu() {}
};

#endif /* MENU_H_ */
