#include "main.h"
#include "portdef.hpp"
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
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t Border, lv_color_t tglBorder) {

    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);
    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].body.border.width = 5;
    btnStyle[0].body.border.color = Border;
    btnStyle[0].body.radius = 4;
    btnStyle[0].text.color = LV_COLOR_MAKE(0, 0, 0);

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].body.border.width = 5;
    btnStyle[1].body.border.color = Border;
    btnStyle[1].body.radius = 4;
    btnStyle[1].text.color = LV_COLOR_MAKE(0, 0, 0);

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 5;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[2].body.radius = 4;
    btnStyle[2].text.color = LV_COLOR_MAKE(255, 255, 255);

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 5;
    btnStyle[3].body.border.color = Border;
    btnStyle[3].body.radius = 4;
    btnStyle[3].text.color = LV_COLOR_MAKE(0, 0, 0);

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

extern bool screenInit;
extern const lv_img_dsc_t field_image;
int selection;
bool recAuton;
bool visionInUse = false;

char textBuffer[100];

lv_style_t * redBtnStyle;
lv_style_t * blueBtnStyle;
lv_style_t * yellowBtnStyle;

lv_style_t whiteShapeStyle;
lv_style_t redShapeStyle;
lv_style_t blueShapeStyle;
lv_style_t yellowShapeStyle;
lv_style_t backgroundStyle;

lv_obj_t * menuScreen;
lv_obj_t * autonScreen;
lv_obj_t * diagScreen;
lv_obj_t * recordScreen;
lv_obj_t * visionScreen;

lv_obj_t * tempButton;
lv_obj_t * menuButton;
lv_obj_t * recAutonButton;
lv_obj_t * toggledBtn;
lv_obj_t * recordableBtn;

lv_obj_t * diagLabel = NULL;
lv_obj_t * recordableLabel;
lv_obj_t * chassisLabel;

lv_obj_t * fieldImage;

static lv_res_t btnOnclickAction(lv_obj_t * btn) {
    uint8_t id = lv_obj_get_free_num(btn);
    switch(id) {
        case 0:
            lv_obj_clean(lv_scr_act());
            diagLabel = NULL;
            if (visionInUse) visionInUse = false;
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
            lv_obj_clean(lv_scr_act());
            drawVision();
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
                    clearVectors();
                    char filename[20];
                    sprintf(filename, "/usd/RecAuton%i.txt", id - 100);
                    bool success = readFromFile(filename);
                    std::cout << "success?  " << success << " " << filename << std::endl;
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
                if (id == 211 && selection >= 0) {
                    clearVectors();
                    startRecordThread();
                    sprintf(textBuffer, "see controller");
                    lv_label_set_text(recordableLabel, textBuffer);
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

void drawScreen() {
    redBtnStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 0, 0), LV_COLOR_MAKE(0, 0, 0),
    LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(255, 0, 0));

    blueBtnStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(0, 0, 0),
    LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 255));

    yellowBtnStyle = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(255, 255, 0), LV_COLOR_MAKE(0, 0, 0),
    LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(255, 255, 0));

    lv_style_copy(&whiteShapeStyle, &lv_style_plain);
    whiteShapeStyle.line.color = LV_COLOR_MAKE(255, 255, 255);
    whiteShapeStyle.line.width = 5;
    whiteShapeStyle.text.color = LV_COLOR_MAKE(255, 255, 255);
    whiteShapeStyle.body.radius = 3;

    lv_style_copy(&redShapeStyle, &lv_style_plain);
    redShapeStyle.body.main_color = LV_COLOR_MAKE(255, 0, 0);
    redShapeStyle.body.grad_color = LV_COLOR_MAKE(255, 0, 0);
    redShapeStyle.body.radius = 0;

    lv_style_copy(&blueShapeStyle, &lv_style_plain);
    blueShapeStyle.body.main_color = LV_COLOR_MAKE(0, 0, 255);
    blueShapeStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
    blueShapeStyle.body.radius = 0;

    lv_style_copy(&yellowShapeStyle, &lv_style_plain);
    yellowShapeStyle.body.main_color = LV_COLOR_MAKE(255, 255, 0);
    yellowShapeStyle.body.grad_color = LV_COLOR_MAKE(255, 255, 0);
    yellowShapeStyle.body.radius = 0;
    
    lv_style_copy(&backgroundStyle, &lv_style_plain);
    backgroundStyle.body.main_color = LV_COLOR_MAKE(0, 0, 0);
    backgroundStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 0);
    backgroundStyle.body.radius = 0;

    menuScreen = lv_obj_create(NULL, NULL);
    autonScreen = lv_obj_create(NULL, NULL);
    diagScreen = lv_obj_create(NULL, NULL);
    recordScreen = lv_obj_create(NULL, NULL);
    visionScreen = lv_obj_create(NULL, NULL);
    
    lv_obj_set_style(menuScreen, &backgroundStyle);
    lv_obj_set_style(autonScreen, &backgroundStyle);
    lv_obj_set_style(diagScreen, &backgroundStyle);
    lv_obj_set_style(recordScreen, &backgroundStyle);
    lv_obj_set_style(visionScreen, &backgroundStyle);

    drawAuton();

    screenInit = true;
}

void drawMenu() {
    lv_scr_load(menuScreen);

    tempButton = createBtn(lv_scr_act(), 0, 0, 180, 50, 1, "Auton Select", yellowBtnStyle);
    lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

    tempButton = createBtn(lv_scr_act(), 0, 0, 160, 50, 2, "Diagnostics", yellowBtnStyle);
    lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 66);

    tempButton = createBtn(lv_scr_act(), 0, 0, 180, 50, 3, "Record Auton", yellowBtnStyle);
    lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 122);

    tempButton = createBtn(lv_scr_act(), 0, 0, 120, 50, 4, "Vision", yellowBtnStyle);
    lv_obj_align(tempButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 178);
}

void drawAuton() {
    resetDatastructures();
    lv_scr_load(autonScreen);
    lv_obj_t * buttons[7];

    buttons[0] = createBtn(lv_scr_act(), 45, 10, 100, 50, 100, "1", redBtnStyle);
    buttons[1] = createBtn(lv_scr_act(), 335, 10, 100, 50, 101, "2", blueBtnStyle);
    buttons[2] = createBtn(lv_scr_act(), 45, 68, 100, 50, 102, "3", redBtnStyle);
    buttons[3] = createBtn(lv_scr_act(), 335, 68, 100, 50, 103, "4", blueBtnStyle);
    buttons[4] = createBtn(lv_scr_act(), 45, 126, 100, 50, 104, "5", redBtnStyle);
    buttons[5] = createBtn(lv_scr_act(), 335, 126, 100, 50, 105, "6", blueBtnStyle);
    menuButton = createBtn(lv_scr_act(), 20, 184, 140, 48, 0, "Menu", yellowBtnStyle);
    buttons[6] = createBtn(lv_scr_act(), 170, 184, 140, 48, 106, "Skills", yellowBtnStyle);
    recAutonButton = createBtn(lv_scr_act(), 320, 184, 140, 48, 10, "RecAuton", yellowBtnStyle);

    if (DEFAULT_RECAUTON) {
        recAuton = true;
        btnSetToggled(recAutonButton, true);
    }
    if (DEFAULT_SELECTION > -1) {
        selection = DEFAULT_SELECTION;
        btnSetToggled(buttons[DEFAULT_SELECTION], true);
        toggledBtn = buttons[DEFAULT_SELECTION];
    }

    LV_IMG_DECLARE(field_image);
    lv_obj_t * imageObj = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(imageObj, &field_image);
    lv_obj_set_size(imageObj, 170, 170);
    lv_obj_align(imageObj, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);
}

void drawDiag() {
    lv_scr_load(diagScreen);

    menuButton = createBtn(lv_scr_act(), 0, 0, 140, 50, 0, "Menu", yellowBtnStyle);
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
        sprintf(textBuffer, "milliseconds since start: %i\nbelow only works during opcontrol", pros::millis());
        lv_label_set_text(diagLabel, textBuffer);
    }
}

void drawRecordable() {
    resetDatastructures();
    lv_scr_load(recordScreen);

    selection = -1;
    recordableBtn = createBtn(lv_scr_act(), 0, 0, 160, 50, 211, "Record", yellowBtnStyle);
    lv_obj_align(recordableBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 70);

    recordableLabel = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(recordableLabel, &whiteShapeStyle);
    lv_label_set_text(recordableLabel, "click buttun to record");
    lv_obj_align(recordableLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 140);

    tempButton = createBtn(lv_scr_act(), 240, 10, 100, 50, 200, "1", redBtnStyle);
    tempButton = createBtn(lv_scr_act(), 340, 10, 100, 50, 201, "2", blueBtnStyle);
    tempButton = createBtn(lv_scr_act(), 240, 68, 100, 50, 202, "3", redBtnStyle);
    tempButton = createBtn(lv_scr_act(), 340, 68, 100, 50, 203, "4", blueBtnStyle);
    tempButton = createBtn(lv_scr_act(), 240, 126, 100, 50, 204, "5", redBtnStyle);
    tempButton = createBtn(lv_scr_act(), 340, 126, 100, 50, 205, "6", blueBtnStyle);
    menuButton = createBtn(lv_scr_act(), 20, 184, 140, 48, 0, "Menu", yellowBtnStyle);
    tempButton = createBtn(lv_scr_act(), 300, 184, 140, 48, 206, "recSkills", yellowBtnStyle);
}

void finishRecording() {
    sprintf(textBuffer, "recording complete!");
    lv_label_set_text(recordableLabel, textBuffer);
    resetDatastructures();
}

extern pros::Vision visionSensor;
lv_obj_t * visionWindow;
lv_obj_t * signatureLabel;
vector<lv_obj_t *> rects;

void drawVision() {
    lv_scr_load(visionScreen);
    visionInUse = true;
    std::cout << "vision sensor port: " << visionSensor.get_port() << std::endl;
    std::cout << visionSensor.get_port() << std::endl;

    lv_obj_t * visionOuter = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_style(visionOuter, &whiteShapeStyle);
    lv_obj_set_pos(visionOuter, 140, 7);
    lv_obj_set_size(visionOuter, 330, 225);

    visionWindow = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_style(visionWindow, &backgroundStyle);
    lv_obj_set_pos(visionWindow, 145, 12);
    lv_obj_set_size(visionWindow, 320, 215);

    signatureLabel = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(signatureLabel, &whiteShapeStyle);
    lv_obj_align(signatureLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    menuButton = createBtn(lv_scr_act(), 5, 184, 130, 48, 0, "Menu", yellowBtnStyle);

    pros::Task drawVisionThread(drawVisionLoop);
}

void drawVisionLoop(void * param) {
    while (visionInUse) {
        int redSigs, blueSigs, yellowSigs = 0;

        // delete old rects
        int sigCount = visionSensor.get_object_count();
        int rectsSize = rects.size();

        if (rectsSize > sigCount) {
            for (int x = 0; x < rectsSize - sigCount; x++) {
                lv_obj_set_pos(rects.at(rectsSize - 1 - x), 200, 200);
                lv_obj_set_size(rects.at(rectsSize - 1 - x), 1, 1);
                lv_obj_del(rects.at(rectsSize - 1 - x));
                rects.pop_back();
                lv_obj_set_top(visionWindow, true);
            }
        }
        else if (rectsSize < sigCount) {
            for (int x = 0; x < sigCount - rectsSize; x++) {
                lv_obj_t * rect = lv_obj_create(lv_scr_act(), NULL);
                rects.insert(rects.begin(), rect);
            }
        }

        std::cout << "sigCout: " << sigCount << " vector size: " << rects.size() << std::endl;

        // loop over and edit rects
        for (int x = 0; x < sigCount; x++) {

            pros::vision_object_s_t detectedObject = visionSensor.get_by_size(x);

            if (detectedObject.signature == 1) {
                lv_obj_set_style(rects.at(x), &redShapeStyle);
                redSigs += 1;
            }
            else if (detectedObject.signature == 2) {
                lv_obj_set_style(rects.at(x), &blueShapeStyle);
                blueSigs += 1; 
            }
            else if (detectedObject.signature == 3) {
                lv_obj_set_style(rects.at(x), &yellowShapeStyle);
                yellowSigs += 1; 
            }
            
            lv_obj_set_pos(rects.at(x), 145 + detectedObject.left_coord, 12 + detectedObject.top_coord);
            lv_obj_set_size(rects.at(x), detectedObject.width, detectedObject.height);
        }

        sprintf(textBuffer, "Red Sigs: \n%i\n\nBlue Sigs: \n%i\n\nYellow Sigs: \n%i\n\n", redSigs, blueSigs, yellowSigs);
        lv_label_set_text(signatureLabel, textBuffer);
        redSigs = 0;
        blueSigs = 0;
        yellowSigs = 0;

        if (!visionInUse) return;            
        pros::delay(20);
    }
}

// int percentComplete;
// int eyerightX;
// int eyerightY;
// int eyeleftX;
// int eyeleftY;

// lv_obj_t * leftEye;
// lv_obj_t * rightEye;

// void drawTow() {
//     lv_scr_load(towScreen);

//     static lv_point_t leftEyePoints[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60} };
//     static lv_point_t rightEyePoints[] = { {100, 100}, {100, 150}, {150, 150}, {150, 100} };

//     updateTow(&leftEyePoints[0], &rightEyePoints[0]);
// }

// void updateTow(lv_point_t leftPoints[], lv_point_t rightPoints[]) {
//     /*
//     inputs must be in the following form:
//     leftInputs: 
//     [point1X, point1Y]
//     [point2X, point2Y]
//     [point3X, point3Y]
//     [point4X, point4Y]
//     rightInputs: 
//     [point1X, point1Y]
//     [point2X, point2Y]
//     [point3X, point3Y]
//     [point4X, point4Y]
//     */

//     leftEye = lv_line_create(lv_scr_act(), NULL);
//     rightEye = lv_line_create(lv_scr_act(), NULL);

//     lv_line_set_points(leftEye, leftPoints, 4);
//     lv_line_set_points(rightEye, rightPoints, 4);

//     lv_obj_set_style(leftEye, &whiteShapeStyle);
//     lv_obj_set_style(rightEye, &whiteShapeStyle);

//     lv_obj_align(leftEye, NULL, LV_ALIGN_CENTER, 0, 0);
//     lv_obj_align(rightEye, NULL, LV_ALIGN_CENTER, 100, 100);
// }

// void towCastChanges(int * leftInputs, int * rightInputs) {

    
// }

//https://docs.lvgl.io/latest/en/html/widgets/objmask.html

void resetDatastructures() {
    clearVectors(); 
    rects.clear();
    diagLabel = NULL;
    toggledBtn = nullptr;
    selection = DEFAULT_SELECTION;
}