#ifndef GRAIN_H_
#define GRAIN_H_

#include <stdio.h>

class Grain {
private:
	int graint_pixels = 2;
	int start_shifting = 0;
	int timer = 0;
	int fall_time = 360;
	int animation_fall_time = fall_time/30;
	int way_in_pixels = 160;
	int max_animation_counter = fall_time / animation_fall_time;
	int distance = (int)(way_in_pixels / max_animation_counter);
	int animation_counter = 1;
	int x_center = 123;
	int y_center = 160;
	int x = x_center;
	int y = y_center;
	int direction = 0;
	int rotation = 0;
	int(*form)(int, int, bool) = NULL;

	int max_y = 313;
public:
	Grain();
	void set_form(int(*form_function)(int, int, bool)) {
		form = form_function;
	}
	void set_rotation(float roatation, int screen_rotation);
	void set_random_start_shift();
	void set_random_direction();
	void set_random_distance();
	void set_coordinates(int x, int y);
	void animate(int y, float rotation, int screen_rotation);
	void move_animation(int y);
	void delete_grain(int y);
	void draw(short color);
	~Grain(){};
};

#endif /* GRAIN_H_ */
