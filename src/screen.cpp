#include "main.h"
#include "screen.hpp"
#include "opcontrol.hpp"
#include "file.hpp"

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
	  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btnOnclickAction);

    return btn;
}

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t Border) {
    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].body.border.width = 5;
    btnStyle[2].body.border.color = Border;
    btnStyle[0].text.color = LV_COLOR_MAKE(0, 0, 0);

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].body.border.width = 5;
    btnStyle[2].body.border.color = Border;
    btnStyle[1].text.color = LV_COLOR_MAKE(255, 255, 255);

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 5;
    btnStyle[2].body.border.color = Border;
    btnStyle[2].text.color = LV_COLOR_MAKE(255, 255, 255);

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 5;
    btnStyle[3].body.border.color = Border;
    btnStyle[3].text.color = LV_COLOR_MAKE(0, 0, 0);;

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
bool recAuton;
bool recSkills;

char text[100];

lv_obj_t * autonScreen = lv_obj_create(NULL, NULL);
lv_obj_t * menuScreen = lv_obj_create(NULL, NULL);
lv_obj_t * diagScreen = lv_obj_create(NULL, NULL);
lv_obj_t * recordScreen = lv_obj_create(NULL, NULL);

lv_obj_t * tempButton;
lv_obj_t * menuButton;
lv_obj_t * recAutonButton;
lv_obj_t * toggledBtn;
lv_obj_t * recordableBtn;

lv_obj_t * autonButtunLabel;
lv_obj_t * diagLabel = NULL;
lv_obj_t * chassisLabel;
lv_obj_t * recordableLabel;

lv_obj_t * fieldImage;

lv_style_t * redStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 0, 0), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(50, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_style_t * blueStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(0, 0, 50), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_style_t * standardStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 255, 0), LV_COLOR_MAKE(0, 0, 0),
LV_COLOR_MAKE(60, 60, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

lv_obj_t * autonObjs = (lv_obj_t *)malloc(sizeof(lv_obj_t) * 7);
lv_obj_t * menuObjs = (lv_obj_t *)malloc(sizeof(lv_obj_t) * 4);

void resetDatastructures() {
  clearVectors(); 
  diagLabel = NULL;
  toggledBtn = nullptr;
  selection = -1;
  recSkills = false;
}

static lv_res_t btnOnclickAction(lv_obj_t * btn) {
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
      lv_obj_clean(lv_scr_act());
      drawRecordable();
      break;
    case 4:
      break;
    case 10:
      if (recAuton) {
        recAuton = false;
        btnSetToggled(recAutonButton, false);
      }
      else {
        recAuton = true;
        btnSetToggled(recAutonButton, true);
      }
      break;
    default:
      if (id >= 100 && id < 112) {
        if (selection != id - 100 && toggledBtn != nullptr) {
          btnSetToggled(toggledBtn, false);
        }
        if (recAuton) {
          char filename[20];
          sprintf(filename, "/usd/RecAuton%i.txt", id - 100);
          bool success = readFromFile(filename);
          std::cout << "success?  " << success << std::endl;
          if (!success) {
            return LV_RES_OK;
          }
          printVectors();
        }

        selection = id - 100;
        toggledBtn = btn;
        btnSetToggled(btn, true);
      }
      else if (id >= 200 && id < 300) {
        if (selection != id - 200 && toggledBtn != nullptr) {
          btnSetToggled(toggledBtn, false);
        }
        recSkills = false;
        if (id == 206) recSkills = true;
        if (id == 211 && selection >= 0) {
          startRecordThread();
          sprintf(text, "see controller");
          lv_label_set_text(recordableLabel, text);
        }
        else {
          selection = id - 200;
          toggledBtn = btn;
          btnSetToggled(btn, true);
        }
      }
      break;
  }
	return LV_RES_OK;
}

//memcpy(&menuObjs[0], tempButton, sizeof(lv_obj_t));

void drawMenu() {
  lv_scr_load(menuScreen);

  tempButton = createBtn(lv_scr_act(), 0, 0, 180, 50, 1, "Auton Select", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  tempButton = createBtn(lv_scr_act(), 0, 0, 160, 50, 2, "Diagnostics", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 66);

  tempButton = createBtn(lv_scr_act(), 0, 0, 180, 50, 3, "Record Auton", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 122);

  tempButton = createBtn(lv_scr_act(), 0, 0, 100, 50, 4, "4", standardStyle);
  lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 178);
}

void drawAuton() {
  resetDatastructures();
  lv_scr_load(autonScreen);

  tempButton = createBtn(lv_scr_act(), 45, 10, 100, 50, 100, "1", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 10, 100, 50, 101, "2", blueStyle);

  tempButton = createBtn(lv_scr_act(), 45, 68, 100, 50, 102, "3", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 68, 100, 50, 103, "4", blueStyle);

  tempButton = createBtn(lv_scr_act(), 45, 126, 100, 50, 104, "5", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 126, 100, 50, 105, "6", blueStyle);

  menuButton = createBtn(lv_scr_act(), 20, 184, 140, 48, 0, "Menu", standardStyle);

  tempButton = createBtn(lv_scr_act(), 170, 184, 140, 48, 106, "Skills", standardStyle);

  recAutonButton = createBtn(lv_scr_act(), 320, 184, 140, 48, 10, "RecAuton", standardStyle);

  recAuton = true;
  btnSetToggled(recAutonButton, true);

  LV_IMG_DECLARE(field_image);
  lv_obj_t * imageObj = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(imageObj, &field_image);
  lv_obj_set_size(imageObj, 170, 170);
  lv_obj_align(imageObj, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);
}

void drawDiag() {
  lv_scr_load(diagScreen);

  menuButton = createBtn(lv_scr_act(), 0, 0, 140, 50, 0, "Menu", standardStyle);
  lv_obj_align(menuButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

  diagLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(diagLabel, "");
  lv_obj_align(diagLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 15);

  chassisLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(chassisLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 68);
}

void updateDiag(char * chassisData) {
  if (diagLabel != NULL) {
    lv_label_set_text(chassisLabel, chassisData);
    sprintf(text, "milliseconds since start: %i\nbelow only works during opcontrol", pros::millis());
    lv_label_set_text(diagLabel, text);
  }
}

void drawRecordable() {
  resetDatastructures();
  lv_scr_load(recordScreen);

  selection = -1;
  recordableBtn = createBtn(lv_scr_act(), 0, 0, 160, 50, 211, "Record", standardStyle);
  lv_obj_align(recordableBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 70);

  recordableLabel = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(recordableLabel, "click buttun to record");
  lv_obj_align(recordableLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 140);

  tempButton = createBtn(lv_scr_act(), 245, 10, 100, 50, 200, "1", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 10, 100, 50, 201, "2", blueStyle);

  tempButton = createBtn(lv_scr_act(), 245, 68, 100, 50, 202, "3", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 68, 100, 50, 203, "4", blueStyle);

  tempButton = createBtn(lv_scr_act(), 245, 126, 100, 50, 204, "5", redStyle);

  tempButton = createBtn(lv_scr_act(), 335, 126, 100, 50, 205, "6", blueStyle);

  menuButton = createBtn(lv_scr_act(), 20, 184, 140, 48, 0, "Menu", standardStyle);

  tempButton = createBtn(lv_scr_act(), 300, 184, 140, 48, 206, "recSkills", standardStyle);
}

void finishRecording() {
    sprintf(text, "recording complete!");
    lv_label_set_text(recordableLabel, text);
    resetDatastructures();
}

void Square::drawAt(int inputX, int inputY) {
  x = inputX;
  y = inputY;
  pros::screen::draw_rect(x, y, x + 50, y + 50);
}