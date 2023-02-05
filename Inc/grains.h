#ifndef GRAINS_H_
#define GRAINS_H_

#include "grain.h"

class Grains {
private:
	int count = 80;
	Grain grains[80];
public:
	Grains(int(*form_function)(int, int, bool));
	void animate(int y,  float rotation, int screen_rotation);
	void set_form(int(*form_function)(int, int, bool));
	void deleting(int ceil);
	~Grains();
};

#endif /* GRAINTS_H_ */
