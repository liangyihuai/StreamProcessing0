//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_TUMBLEWINDOW_H
#define CONTINUOUSPROCESSING_TUMBLEWINDOW_H


#include "SlidingWindow.h"

class TumbleWindow: public SlidingWindow {
private:
    int winLen;
public:
    TumbleWindow(int winLen): SlidingWindow(winLen, winLen){
		if (winLen <= 0) {
			std::cout << "winLen <= 0";
			throw "";
		}
        this->winLen = winLen;
    }

    Window* clone() {
        Window * newWin = new TumbleWindow(this->winLen);
        return newWin;
    }
};

#endif //CONTINUOUSPROCESSING_TUMBLEWINDOW_H
