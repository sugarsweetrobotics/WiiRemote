// -*- C++ -*-
/*!
 * @file  WiiRemote.cpp
 * @brief Wii Remote RTC
 * @date $Date$
 *
 * $Id$
 */

#include "WiiRemote.h"

// Module specification
// <rtc-template block="module_spec">
static const char* wiiremote_spec[] =
  {
    "implementation_id", "WiiRemote",
    "type_name",         "WiiRemote",
    "description",       "Wii Remote RTC",
    "version",           "1.0.0",
    "vendor",            "Sugar Sweet Robotics",
    "category",          "Input",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.is_bar_above", "1",
    "conf.default.aspect_ratio", "4_3",
    "conf.default.virtual_screen_width", "640",
    "conf.default.virtual_screen_height", "480",
    // Widget
    "conf.__widget__.is_bar_above", "text",
    "conf.__widget__.aspect_ratio", "ordered_list",
    "conf.__widget__.virtual_screen_width", "ordered_list",
    "conf.__widget__.virtual_screen_height", "ordered_list",
    // Constraints
    "conf.__constraints__.aspect_ratio", "4_3, 16_9",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
WiiRemote::WiiRemote(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ledsIn("leds", m_leds),
    m_rumbleIn("rumble", m_rumble),
    m_buttonsOut("buttons", m_buttons),
    m_accelOut("accel", m_accel),
    m_orientationOut("orientation", m_orientation),
    m_cursorOut("cursor", m_cursor),
    m_distanceOut("distance", m_distance),
    m_irOut("ir", m_ir)

    // </rtc-template>

{
  m_numFound = 0;
}

/*!
 * @brief destructor
 */
WiiRemote::~WiiRemote()
{
}



RTC::ReturnCode_t WiiRemote::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("leds", m_ledsIn);
  addInPort("rumble", m_rumbleIn);
  
  // Set OutPort buffer
  addOutPort("buttons", m_buttonsOut);
  addOutPort("accel", m_accelOut);
  addOutPort("orientation", m_orientationOut);
  addOutPort("cursor", m_cursorOut);
  addOutPort("distance", m_distanceOut);
  addOutPort("ir", m_irOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("is_bar_above", m_is_bar_above, "1");
  bindParameter("aspect_ratio", m_aspect_ratio, "4_3");
  bindParameter("virtual_screen_width", m_virtual_screen_width, "640");
  bindParameter("virtual_screen_height", m_virtual_screen_height, "480");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t WiiRemote::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t WiiRemote::onActivated(RTC::UniqueId ec_id)
{
  if (m_numFound == 0) {
    for (int i = 0;i < 3;i++) {
      std::cout << "[RTC::WiiRemote] Please turn on your WiiRemote." << std::endl;
      m_numFound = m_Wii.Find(1);
      if (m_numFound == 1) {
	break;
      }
    }

    if (m_numFound != 1) {
      std::cout << "[RTC::WiiRemote] Can not find Wii Remote." << std::endl;
      return RTC_ERROR;
    }

    std::cout << "[RTC::WiiRemote] Wii Remote Found." << std::endl;
    m_Wii.Connect();
  } else {
    // Reload Wiimotes.
    m_Wii.GetWiimotes();
  }

  m_buttons.data.length(11);
  m_is_bar_above_old = !m_is_bar_above;
  if (m_aspect_ratio ==  "4_3") {
    m_aspect_ratio_old = "16_9";
  } else {
    m_aspect_ratio_old = "4_3";
  }
  m_virtual_screen_width = 0;
  m_virtual_screen_height = 0;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t WiiRemote::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t WiiRemote::onExecute(RTC::UniqueId ec_id)
{
  std::vector<CWiimote>& m_Wiimotes = m_Wii.GetWiimotes(0);
  CWiimote& wiimote = m_Wiimotes[0];

  if (m_is_bar_above != m_is_bar_above_old) {
    if (m_is_bar_above) {
      wiimote.IR.SetBarPosition(CIR::BAR_ABOVE);
    } else {
      wiimote.IR.SetBarPosition(CIR::BAR_BELOW);
    }
  }
  m_is_bar_above_old = m_is_bar_above;

  if (m_aspect_ratio != m_aspect_ratio_old) {
    if (m_aspect_ratio == "4_3") {
      wiimote.IR.SetAspectRatio(CIR::ASPECT_4_3);
    } else if (m_aspect_ratio == "16_9") {
      wiimote.IR.SetAspectRatio(CIR::ASPECT_16_9);
    } else {
      std::cout << "[RTC::WiiRemote] Unknow aspect ratio." << std::endl;
      return RTC_ERROR;
    }
  }
  m_aspect_ratio_old = m_aspect_ratio;

  if ((m_virtual_screen_width != m_virtual_screen_width_old) || 
      (m_virtual_screen_height != m_virtual_screen_height_old)) {
    wiimote.IR.SetVres(m_virtual_screen_width, m_virtual_screen_height);
  }
  m_virtual_screen_width_old = m_virtual_screen_width;
  m_virtual_screen_height_old = m_virtual_screen_height;

  if (m_ledsIn.isNew()) {
    m_ledsIn.read();
    int led = 0;
    int flag[4] = {CWiimote::LED_1, CWiimote::LED_2, CWiimote::LED_3, CWiimote::LED_4};
    for (unsigned int i = 0;i < 4 || i < m_leds.data.length();i++) {
      led |= flag[i];
    }
    wiimote.SetLEDs(led);
  }

  if (m_rumbleIn.isNew()) {
    m_rumbleIn.read();
    if (m_rumble.data) {
      wiimote.SetRumbleMode(CWiimote::ON);
    } else {
      wiimote.SetRumbleMode(CWiimote::OFF);
    }
  }

  const int buttons[] = {
    CButtons::BUTTON_UP, CButtons::BUTTON_DOWN, CButtons::BUTTON_RIGHT, CButtons::BUTTON_LEFT,
    CButtons::BUTTON_ONE, CButtons::BUTTON_TWO, CButtons::BUTTON_A, CButtons::BUTTON_B,
    CButtons::BUTTON_PLUS, CButtons::BUTTON_MINUS, CButtons::BUTTON_HOME };

  float r, p, y;
  int i;
  if (m_Wii.Poll()) {
    switch(wiimote.GetEvent()) {
    case CWiimote::EVENT_EVENT:
      for (i = 0;i < 11;i++) {
	if (wiimote.Buttons.isPressed(buttons[i])) {
	  m_buttons.data[i] = true;
	} else {
	  m_buttons.data[i] = false;
	}
      }
      m_buttonsOut.write();
      
      if (!wiimote.isUsingACC()) {
	wiimote.SetMotionSensingMode(CWiimote::ON);
      }

      wiimote.Accelerometer.GetOrientation(p, r, y);
      m_orientation.data.p = p; m_orientation.data.y = y; m_orientation.data.r = r;
      m_orientationOut.write();
      
      wiimote.Accelerometer.GetRawOrientation(p, r);
      m_accel.data.aax = r; m_accel.data.aay = p; m_accel.data.aaz = 0;
      m_accelOut.write();

      if (!wiimote.isUsingIR()) {
	wiimote.IR.SetMode(CIR::ON);
      }
      
      if (wiimote.isUsingIR()) {
	std::vector<CIRDot>& dots = wiimote.IR.GetDots();
	std::vector<CIRDot>::iterator it;
	int x, y;
	for (it = dots.begin(); it != dots.end(); ++it) {
	  if ((*it).isVisible()) {
	    (*it).GetCoordinate(x, y);
	    m_ir.data.x = x; m_ir.data.y = y;
	    m_irOut.write();
	    
	    wiimote.IR.GetCursorPosition(x, y);
	    m_cursor.data.x = x; m_cursor.data.y = y;
	    m_cursorOut.write();

	    m_distance.data = wiimote.IR.GetDistance();
	    m_distanceOut.write();
	  }
	}
      }

      break;
      
    case CWiimote::EVENT_STATUS:
      //HandleStatus(wiimote);
      break;
      
    case CWiimote::EVENT_DISCONNECT:
    case CWiimote::EVENT_UNEXPECTED_DISCONNECT:
      //HandleDisconnect(wiimote);
      //reloadWiimotes = 1;
      m_Wiimotes = m_Wii.GetWiimotes();
      break;
      
    case CWiimote::EVENT_READ_DATA:
      //HandleReadData(wiimote);
      break;
      
    case CWiimote::EVENT_NUNCHUK_INSERTED:
      //HandleNunchukInserted(wiimote);
      //reloadWiimotes = 1;
      m_Wiimotes = m_Wii.GetWiimotes();
      break;
      
    case CWiimote::EVENT_CLASSIC_CTRL_INSERTED:
      //HandleClassicInserted(wiimote);
      //reloadWiimotes = 1;
      m_Wiimotes = m_Wii.GetWiimotes();
      break;
      
    case CWiimote::EVENT_GUITAR_HERO_3_CTRL_INSERTED:
      //HandleGH3Inserted(wiimote);
      //reloadWiimotes = 1;
      m_Wiimotes = m_Wii.GetWiimotes();
      break;
      
    case CWiimote::EVENT_MOTION_PLUS_INSERTED:
      cout << "Motion Plus inserted." << endl;
      break;
      
    case CWiimote::EVENT_BALANCE_BOARD_INSERTED:
      cout << "Balance Board connected.\n"  << endl;
      break;
      
    case CWiimote::EVENT_BALANCE_BOARD_REMOVED:
      cout << "Balance Board disconnected.\n"  << endl;
      break;
      
    case CWiimote::EVENT_NUNCHUK_REMOVED:
    case CWiimote::EVENT_CLASSIC_CTRL_REMOVED:
    case CWiimote::EVENT_GUITAR_HERO_3_CTRL_REMOVED:
    case CWiimote::EVENT_MOTION_PLUS_REMOVED:
      cout << "An expansion was removed." << endl;
      //HandleStatus(wiimote);
      //reloadWiimotes = 1;
      m_Wiimotes = m_Wii.GetWiimotes();
      break;
      
    default:
      break;
    } // switch
  }
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t WiiRemote::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WiiRemote::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void WiiRemoteInit(RTC::Manager* manager)
  {
    coil::Properties profile(wiiremote_spec);
    manager->registerFactory(profile,
                             RTC::Create<WiiRemote>,
                             RTC::Delete<WiiRemote>);
  }
  
};


