// generated by Fast Light User Interface Designer (fluid) version 1.0011

#ifndef liFluoroscopyCArmMobileGUI_h
#define liFluoroscopyCArmMobileGUI_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "liFluoroscopyCArmMobile.h"
#include "liCommandEvents.h"
#include <FL/Fl_Roller.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Adjuster.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

class FluoroscopyCArmMobileGUI {
  li::FluoroscopyCArmMobile::Pointer m_Unit;
public:
  FluoroscopyCArmMobileGUI();
  Fl_Window *controlWindow;
  Fl_Roller *cranCaudRoller;
private:
  inline void cb_cranCaudRoller_i(Fl_Roller*, void*);
  static void cb_cranCaudRoller(Fl_Roller*, void*);
public:
  Fl_Value_Output *cranCaudValueOutput;
  Fl_Roller *raoLaoRoller;
private:
  inline void cb_raoLaoRoller_i(Fl_Roller*, void*);
  static void cb_raoLaoRoller(Fl_Roller*, void*);
public:
  Fl_Value_Output *raoLaoValueOutput;
private:
  inline void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
  inline void cb_1_i(Fl_Button*, void*);
  static void cb_1(Fl_Button*, void*);
public:
  Fl_Roller *azimuthRoller;
private:
  inline void cb_azimuthRoller_i(Fl_Roller*, void*);
  static void cb_azimuthRoller(Fl_Roller*, void*);
public:
  Fl_Value_Output *azimuthValueOutput;
private:
  inline void cb_2_i(Fl_Button*, void*);
  static void cb_2(Fl_Button*, void*);
public:
  Fl_Adjuster *cranioCaudalPositionAdjuster;
private:
  inline void cb_cranioCaudalPositionAdjuster_i(Fl_Adjuster*, void*);
  static void cb_cranioCaudalPositionAdjuster(Fl_Adjuster*, void*);
public:
  Fl_Value_Output *cranioCaudalPositionValueOutput;
private:
  inline void cb_3_i(Fl_Button*, void*);
  static void cb_3(Fl_Button*, void*);
public:
  Fl_Adjuster *lateralPositionAdjuster;
private:
  inline void cb_lateralPositionAdjuster_i(Fl_Adjuster*, void*);
  static void cb_lateralPositionAdjuster(Fl_Adjuster*, void*);
public:
  Fl_Value_Output *lateralPositionValueOutput;
private:
  inline void cb_4_i(Fl_Button*, void*);
  static void cb_4(Fl_Button*, void*);
  inline void cb_5_i(Fl_Button*, void*);
  static void cb_5(Fl_Button*, void*);
  inline void cb_6_i(Fl_Button*, void*);
  static void cb_6(Fl_Button*, void*);
  inline void cb_FOV_i(Fl_Check_Button*, void*);
  static void cb_FOV(Fl_Check_Button*, void*);
  static Fl_Menu_Item menu_Detector[];
  inline void cb_Up_i(Fl_Menu_*, void*);
  static void cb_Up(Fl_Menu_*, void*);
  inline void cb_Down_i(Fl_Menu_*, void*);
  static void cb_Down(Fl_Menu_*, void*);
public:
  Fl_Value_Input *sourceToFilmDistanceValueInput;
private:
  inline void cb_sourceToFilmDistanceValueInput_i(Fl_Value_Input*, void*);
  static void cb_sourceToFilmDistanceValueInput(Fl_Value_Input*, void*);
  static Fl_Menu_Item menu_Configuration[];
  inline void cb_TIPS_i(Fl_Menu_*, void*);
  static void cb_TIPS(Fl_Menu_*, void*);
  inline void cb_TIPS1_i(Fl_Menu_*, void*);
  static void cb_TIPS1(Fl_Menu_*, void*);
public:
  Fl_Value_Input *detectorDiameterValueInput;
private:
  inline void cb_detectorDiameterValueInput_i(Fl_Value_Input*, void*);
  static void cb_detectorDiameterValueInput(Fl_Value_Input*, void*);
public:
  Fl_Value_Output *fieldOfViewValueOutput;
  virtual ~FluoroscopyCArmMobileGUI();
  void Show(void);
  void Hide(void);
  void SetFluoroscopyUnit( li::FluoroscopyCArmMobile * unit );
  virtual void SetUnitGeometricParameters(double stfd,double vps);
};
#endif
