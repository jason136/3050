#include "main.h"
#include "screen.h"
#include "portdef.h"

using namespace pros;

extern Controller master;
extern Controller partner;
extern Motor front_right_motor;
extern Motor intake;

int autonomousPreSet;

/**
 * Code for controlling screen graphics and such
 * Uses LVGL built into PROS graphics library
 * Under development
 * https://team81k.github.io/ProsLVGLTutorial/
 **/

 lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title, lv_style_t * style) {
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
    setBtnStyle(style, btn);
	  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action);

    return btn;
}

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor) {
    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].body.border.width = 5;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[0].text.color = textColor;

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].body.border.width = 5;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[1].text.color = textColor;

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 5;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[2].text.color = textColor;

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 5;
    btnStyle[3].body.border.color = tglBorder;
    btnStyle[3].text.color = textColor;

    return btnStyle;
}

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn) {
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
}

void btnSetToggled(lv_obj_t * btn, bool toggled) {
    if(toggled != (lv_btn_get_state(btn) >= 2)) lv_btn_toggle(btn);
}

extern const lv_img_dsc_t field_image;
int selection;

lv_obj_t * autonScreen = lv_obj_create(NULL, NULL);
lv_obj_t * menuScreen = lv_obj_create(NULL, NULL);
lv_obj_t * diagScreen = lv_obj_create(NULL, NULL);

lv_obj_t * tempButton;
lv_obj_t * menuButton;
lv_obj_t * toggledBtn;

lv_obj_t * autonButtunLabel;
lv_obj_t * autonLabel;
lv_obj_t * diagLabel = NULL;
lv_obj_t * fieldImage;

lv_style_t * redStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 0, 0), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(100, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_style_t * blueStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(0, 0, 100), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_style_t * standardStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 255, 0), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(80, 80, 40), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_obj_t * autonObjs = (lv_obj_t *)malloc(sizeof(lv_obj_t) * 7);
lv_obj_t * menuObjs = (lv_obj_t *)malloc(sizeof(lv_obj_t) * 4);

static lv_res_t btn_click_action(lv_obj_t * btn) {
		uint8_t id = lv_obj_get_free_num(btn);
    switch(id) {
      case 0:
        lv_obj_clean(lv_scr_act());
        diagLabel = NULL;
        drawMenu();
        break;
      case 1:
        lv_obj_clean(lv_scr_act());
        drawAuton();
        break;
      case 2:
        lv_obj_clean(lv_scr_act());
        drawDiag();
        break;
      case 3:
        break;
      case 4:
        break;
      default:
        if (id >= 100 && id < 150) {
      if (autonomousPreSet != id - 100 && toggledBtn != nullptr) {
        btnSetToggled(toggledBtn, false);
      }
      autonomousPreSet = id - 100;
      toggledBtn = btn;
      btnSetToggled(btn, true);
      char buffer[100];
      sprintf(buffer, "Auton routine \nselected: %i", autonomousPreSet);
      lv_label_set_text(autonLabel, buffer);
      }
    }
		return LV_RES_OK;
}

void loadScreen() {
  drawAuton();
}

void drawMenu() {
  lv_scr_load(menuScreen);

  tempButton = createBtn(lv_scr_act(), 0, 0, 180, 50, 1, "Auton Select", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
  memcpy(&menuObjs[0], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 0, 0, 160, 50, 2, "Diagnostics", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 66);
  memcpy(&menuObjs[1], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 0, 0, 100, 50, 3, "3", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 122);
  memcpy(&menuObjs[2], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 0, 0, 100, 50, 4, "4", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 178);
  memcpy(&menuObjs[3], tempButton, sizeof(lv_obj_t));
}

void drawAuton() {
  lv_scr_load(autonScreen);

  tempButton = createBtn(lv_scr_act(), 45, 10, 100, 50, 101, "1", redStyle);
  memcpy(&autonObjs[0], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 335, 10, 100, 50, 102, "2", blueStyle);
  memcpy(&autonObjs[1], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 45, 70, 100, 50, 103, "3", redStyle);
  memcpy(&autonObjs[2], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 335, 70, 100, 50, 104, "4", blueStyle);
  memcpy(&autonObjs[3], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 45, 130, 100, 50, 105, "5", redStyle);
  memcpy(&autonObjs[4], tempButton, sizeof(lv_obj_t));

  tempButton = createBtn(lv_scr_act(), 335, 130, 100, 50, 106, "6", blueStyle);
  memcpy(&autonObjs[5], tempButton, sizeof(lv_obj_t));
  
  menuButton = createBtn(lv_scr_act(), 20, 184, 140, 50, 0, "Menu", standardStyle);

  tempButton = createBtn(lv_scr_act(), 170, 184, 140, 50, 107, "Skills", standardStyle);
  memcpy(&autonObjs[6], tempButton, sizeof(lv_obj_t));
  
  LV_IMG_DECLARE(field_image);
  lv_obj_t * imageObj = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(imageObj, &field_image);
  lv_obj_set_size(imageObj, 170, 170);
  lv_obj_align(imageObj, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);

	autonLabel = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(autonLabel, "Auton routine \nselected: ");
	lv_obj_align(autonLabel, NULL, LV_ALIGN_IN_RIGHT_MID, -40, 90);
}

void drawDiag() {
  lv_scr_load(diagScreen);
  
  diagLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(diagLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

  menuButton = createBtn(lv_scr_act(), 0, 0, 140, 50, 0, "Menu", standardStyle);
	lv_obj_align(menuButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
}