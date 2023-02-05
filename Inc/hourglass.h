#ifndef _HOURGLASS_H_
#define _HOURGLASS_H_

#include "ILI9341.h"
#include "grains.h"

class Hourglass {
private:

	bool print_flag = false;

	int count = 0;
	int figure_glass_form = 2;
	int form_quantity = 3;
	int screen_rotation = SCREEN_VERTICAL_2;

	static const int y_all = 319;
	static const int y_half = 159;

	static const int x_all = 239;
	static const int x_half = 119;

	static constexpr double proportion = 0.75;

	int shift = 30;
	int swap_animation_time = 1000;
	int sand_swap_animation_time = (swap_animation_time/(y_half-shift));
	int current_sand_swap_animation_time = (swap_animation_time/(y_half-shift));
	int current_sand_layer = shift;
	uint32_t timer = 0;

	Grains grains = Grains(cosine);

	int glass_form(int y, int f, bool clock);
	int glass_form(int y, int f);
	static int module(int y, int f, bool clock);
	static int cosine(int y, int f, bool clock);
	static int sine(int y, int f, bool clock);
	void change_sand_line(int y, int new_y);
	void reset(float swaper);

public:
	Hourglass(float y_coordinate_position){
		this->set_time(10);
		this->swap_screen_rotation(y_coordinate_position);
		this->set_print_flag(false);
		this->print();
	};
	Hourglass(){};
	void invert_print_flag(){ this->print_flag = !this->print_flag; }
	void set_print_flag(bool flag){ this->print_flag = flag; }
	bool get_print_flag() { return this->print_flag; }
	void set_screen_rotation(float swaper);
	void set_glass_form(int form, float swaper);
	void set_glass_form_for_grains();
	void print_sand();
	void print_sand_line(int y, short color);
	void set_time(double time);
	void animation(float swaper,  float rotation);
	void print_hourglass();
	void print();
	void set_sand_layer(int lays);
	void set_sand_layer() { this->current_sand_layer = this->shift; };
	int swap_screen_rotation(float swaper);
	void screen_rotation_sand_fall();

	~Hourglass(){};
};
#endif
