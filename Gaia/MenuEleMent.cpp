#include"stdafx.h"
#include"MenuElement.h"

MenuElement::MenuElement() {
}


MenuElement::~MenuElement() {
}
bool MenuElement::operator<(const MenuElement& e)const {
	return this->myID < e.myID;
}