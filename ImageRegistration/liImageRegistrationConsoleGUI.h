// generated by Fast Light User Interface Designer (fluid) version 1.0010

#ifndef liImageRegistrationConsoleGUI_h
#define liImageRegistrationConsoleGUI_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <liImageRegistrationConsoleBase.h>
#include <liLightButton.h>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Output.H>

class liImageRegistrationConsoleGUI : public liImageRegistrationConsoleBase {
public:
  liImageRegistrationConsoleGUI();
  Fl_Window *consoleWindow;
  static Fl_Menu_Item menu_[];
private:
  inline void cb_Load_i(Fl_Menu_*, void*);
  static void cb_Load(Fl_Menu_*, void*);
  inline void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  inline void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
public:
  Fl_Group *Connectors;
  Fl_Group *controlsGroup;
  li::LightButton *targetButton;
private:
  inline void cb_targetButton_i(li::LightButton*, void*);
  static void cb_targetButton(li::LightButton*, void*);
  inline void cb_Start_i(Fl_Button*, void*);
  static void cb_Start(Fl_Button*, void*);
public:
  li::LightButton *referenceButton;
private:
  inline void cb_referenceButton_i(li::LightButton*, void*);
  static void cb_referenceButton(li::LightButton*, void*);
  inline void cb_Apply_i(Fl_Button*, void*);
  static void cb_Apply(Fl_Button*, void*);
public:
  li::LightButton *registrationMethodButton;
private:
  inline void cb_Estimated_i(Fl_Button*, void*);
  static void cb_Estimated(Fl_Button*, void*);
public:
  li::LightButton *mappedReferenceButton;
private:
  inline void cb_mappedReferenceButton_i(li::LightButton*, void*);
  static void cb_mappedReferenceButton(li::LightButton*, void*);
public:
  Fl_Group *transformParameters;
  Fl_Value_Input *xTranslation;
  Fl_Value_Input *yTranslation;
  Fl_Value_Input *zTranslation;
  static Fl_Menu_Item menu_1[];
  Fl_Slider *progressSlider;
  Fl_Output *statusTextOutput;
  Fl_Window *aboutWindow;
private:
  inline void cb_Documentation_i(Fl_Button*, void*);
  static void cb_Documentation(Fl_Button*, void*);
public:
  virtual ~liImageRegistrationConsoleGUI();
  virtual void Quit( void );
  virtual void Load( void );
  virtual void ShowTarget( void );
  virtual void ShowReference( void );
  virtual void ShowAbout( void );
  virtual void ShowMappedReference( void );
};
#endif
