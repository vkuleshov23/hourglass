#include "grains.h"
#include "grain.h"

Grains::Grains(int(*form_function)(int, int, bool)) {
	this->set_form(form_function);
}

void Grains::animate(int y,  float rotation, int screen_rotation){
	for(int i = 0; i < this->count; i++) {
		(this->grains[i]).animate(y, rotation, screen_rotation);
	}
}

void Grains::set_form(int(*form_function)(int, int, bool)) {
	for(int i = 0; i < this->count; i++) {
			(this->grains[i]).set_form(form_function);
		}
}

void Grains::deleting(int ceil){
	for(int i = 0; i < this->count; i++) {
		(this->grains[i]).delete_grain(ceil);
	}
}

Grains::~Grains() {}

