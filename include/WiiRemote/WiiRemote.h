// -*- C++ -*-
/*!
 * @file  WiiRemote.h
 * @brief Wii Remote RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef WIIREMOTE_H
#define WIIREMOTE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

#include "wiicpp.h"

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class WiiRemote
 * @brief Wii Remote RTC
 *
 */
class WiiRemote
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  WiiRemote(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~WiiRemote();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  is_bar_above
   * - DefaultValue: 1
   */
  int m_is_bar_above;
  /*!
   * 
   * - Name:  aspect_ratio
   * - DefaultValue: 4_3
   */
  std::string m_aspect_ratio;
  /*!
   * 
   * - Name:  virtual_screen_width
   * - DefaultValue: 640
   */
  int m_virtual_screen_width;
  /*!
   * 
   * - Name:  virtual_screen_height
   * - DefaultValue: 480
   */
  int m_virtual_screen_height;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedBooleanSeq m_leds;
  /*!
   */
  InPort<RTC::TimedBooleanSeq> m_ledsIn;
  RTC::TimedBoolean m_rumble;
  /*!
   */
  InPort<RTC::TimedBoolean> m_rumbleIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedBooleanSeq m_buttons;
  /*!
   * Up, Down, Right, Left, One, Two, A, B, Plus, Minus, Home
   */
  OutPort<RTC::TimedBooleanSeq> m_buttonsOut;
  RTC::TimedAngularAcceleration3D m_accel;
  /*!
   */
  OutPort<RTC::TimedAngularAcceleration3D> m_accelOut;
  RTC::TimedOrientation3D m_orientation;
  /*!
   */
  OutPort<RTC::TimedOrientation3D> m_orientationOut;
  RTC::TimedPoint2D m_cursor;
  /*!
   */
  OutPort<RTC::TimedPoint2D> m_cursorOut;
  RTC::TimedLong m_distance;
  /*!
   */
  OutPort<RTC::TimedLong> m_distanceOut;
  RTC::TimedPoint2D m_ir;
  /*!
   */
  OutPort<RTC::TimedPoint2D> m_irOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

  CWii m_Wii;

  int m_numFound;

  int m_is_bar_above_old;
  std::string m_aspect_ratio_old;
  int m_virtual_screen_width_old;
  int m_virtual_screen_height_old;

};


extern "C"
{
  DLL_EXPORT void WiiRemoteInit(RTC::Manager* manager);
};

#endif // WIIREMOTE_H
