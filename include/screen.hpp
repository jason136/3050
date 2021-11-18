#ifndef SCREEN_H_
#define SCREEN_H_

#include "api.h"

lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title, lv_style_t * style);

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t Border, lv_color_t tglBorder);

void btnSetToggled(lv_obj_t * btn, bool toggled);

void resetDatastructures();

static lv_res_t btnOnclickAction(lv_obj_t * btn);

void drawScreen();

void drawMenu();

void drawAuton();

void drawDiag();
void updateDiag(char * buffer);

void drawRecordable();
void finishRecording();

void drawTow();

class Square {
    public:
        int x;
        int y;
        lv_obj_t * obj;
        
    Square(int inputX, int inputY);
    void drawAt(int inputX, int inputY);
};

#endif
