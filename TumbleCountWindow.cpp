#include "stdafx.h"
#include "TumbleCountWindow.h"


TumbleCountWindow::TumbleCountWindow(unsigned int countLen):countLen(countLen){
}

unsigned TumbleCountWindow::getLen() const {
	return countLen;
}

unsigned int TumbleCountWindow::getSliding() const{
	return countLen;
}

TumbleCountWindow::~TumbleCountWindow()
{
}
