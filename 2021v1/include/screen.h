#pragma once

#ifndef SCREEN_H_
#define SCREEN_H_

#include "main.h"

using namespace pros;

lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
   int id, const char * title);

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor);

void btnSetToggled(lv_obj_t * btn, bool toggled);

static lv_res_t btn_click_action(lv_obj_t * btn);

lv_obj_t * createPage();

#endif
