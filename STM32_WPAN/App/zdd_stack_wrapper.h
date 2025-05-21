/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : zdd_stack_wrapper.h
 * Description        : Header for ZDD wrapper.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ZDD_STACK_WRAPPER_H
#define ZDD_STACK_WRAPPER_H

#include "ble_types.h"
#include "stm_list.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  BLE_ZDD_WRAP_HCI_DISCONNECTION_COMPLETE_EVT,
  BLE_ZDD_WRAP_HCI_HARDWARE_ERROR_EVT,
  BLE_ZDD_WRAP_HCI_LE_META_EVT_CONNECTION_UPDATE_COMPLETE_SUBEVT,
  BLE_ZDD_WRAP_HCI_LE_META_EVT_HCI_LE_PHY_UPDATE_COMPLETE_SUBEVT,
  BLE_ZDD_WRAP_HCI_LE_META_EVT_HCI_LE_ENHANCED_CONNECTION_COMPLETE_SUBEVT,
  BLE_ZDD_WRAP_HCI_LE_META_EVT_HCI_LE_CONNECTION_COMPLETE_SUBEVT,
  BLE_ZDD_WRAP_CONN_HANDLE_EVT,
  BLE_ZDD_WRAP_DISCON_HANDLE_EVT,
  BLE_ZDD_WRAP_TUNNELING_TUNNZDTSNPDU_WRITE_EVT,
  BLE_ZDD_WRAP_TUNNELING_TUNNZDTSNPDU_INDICATE_ENABLED_EVT,
  BLE_ZDD_WRAP_TUNNELING_TUNNZDTSNPDU_INDICATE_DISABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519AES_WRITE_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519AES_INDICATE_ENABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519AES_INDICATE_DISABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519SHA_WRITE_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519SHA_INDICATE_ENABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_SECURITY25519SHA_INDICATE_DISABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_P256SHA_WRITE_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_P256SHA_INDICATE_ENABLED_EVT,
  BLE_ZDD_WRAP_ZDDSECURITY_P256SHA_INDICATE_DISABLED_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_FORMNETWORK_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_JOINNETWORK_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_PERMITJOIN_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_LEAVENETWORK_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_COMMSTATUS_READ_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_COMMSTATUS_NOTIFY_ENABLED_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_COMMSTATUS_NOTIFY_DISABLED_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_MANAGEJOINER_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_COMMIDENTITY_WRITE_EVT,
  BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_FINDBIND_WRITE_EVT,
  BLE_ZDD_WRAP_SERVER_CONFIRMATION_EVT,

} BLE_ZDD_WRAP_Opcode_evt_t;

typedef struct {
  uint8_t *pPayload;
  uint8_t Length;
} BLE_ZDD_WRAP_Data_t;

typedef struct {
  BLE_ZDD_WRAP_Opcode_evt_t     Opcode;
  BLE_ZDD_WRAP_Data_t           DataTransfered;
  uint16_t                      ConnectionHandle;
  uint16_t                      AttributeHandle;
  uint8_t                       ServiceInstance;
  /* Specific BLE_ZDD_WRAP_HCI_LE_META_EVT_HCI_LE_CONNECTION_COMPLETE_SUBEVT fields */
  uint16_t                      ConnInterval;
  /* Specific BLE_ZDD_WRAP_ZIGBEEDIRECTCOMM_COMMSTATUS_READ_EVT fields */
  uint16_t                      ZigbeedirectcommSvcHdle;
  uint16_t                      CommidentityCharHdle;
} ZDD_Stack_Notification_evt_t;

typedef enum {
  ZDD_BLE_WRAP_TUNNELING_TUNNZDTSNPDU_UPDATEVALUE_EVT,
  ZDD_BLE_WRAP_ZDDSECURITY_SECURITY25519AES_UPDATEVALUE_EVT,
  ZDD_BLE_WRAP_ZDDSECURITY_SECURITY25519SHA_UPDATEVALUE_EVT,
  ZDD_BLE_WRAP_ZDDSECURITY_SECURITY_P256SHA_UPDATEVALUE_EVT,
  ZDD_BLE_WRAP_ZIGBEEDIRECTCOMM_COMMSTATUS_UPDATEVALUE_EVT,
  ZDD_BLE_WRAP_BLE_START_ADVERTISING_EVT,
  ZDD_BLE_WRAP_BLE_STOP_ADVERTISING_EVT,
  ZDD_BLE_WRAP_OS_SHCEDULE_ZDD_TASK_EVT,

} ZDD_BLE_WRAP_Opcode_evt_t;

typedef struct {
  uint8_t *pPayload;
  uint8_t Length;
} ZDD_BLE_WRAP_Data_t;

typedef struct {
  uint16_t    PanId;
  uint16_t    NwkAddr;
  bool        PJoin;
} ZDD_BLE_WRAP_AdvData_t;

typedef struct {
  ZDD_BLE_WRAP_Opcode_evt_t     Opcode;
  ZDD_BLE_WRAP_Data_t           Data;
  /* Specific ZDD_BLE_WRAP_BLE_START_ADVERTISING_EVT fields */
  ZDD_BLE_WRAP_AdvData_t       AdvData;

} BLE_App_Notification_evt_t;

/* Exported functions prototypes ---------------------------------------------*/

/* Handler used to map the BLE stack to the ZDD stack */
/* Calls from BLE Apps -> ZDD stack (porting)         */
void ZDD_Stack_Notification(ZDD_Stack_Notification_evt_t *pNotification);

/* Handler used to map the ZDD stack to the BLE stack  */
/* Calls from ZDD stack (porting) -> BLE Apps          */
bool BLE_App_Notification(BLE_App_Notification_evt_t *pNotification);

/* Exposed to keep the application OS agnostic */
void Zdd_Task(void);
// Handler to manage ACI attributes
SVCCTL_EvtAckStatus_t handle_zdd_aci_gatt_atribute_modif(aci_gatt_attribute_modified_event_rp0 *attribute_modified,SVCCTL_EvtAckStatus_t ret);
void zdd_port_disconnect_zvd(struct ZigBeeT *zb);
void zdd_port_update_status(struct ZigBeeT *zb, uint8_t *bindata, uint8_t binlen);
bool zdd_port_send_tun_data(struct ZigBeeT *zb, uint8_t *bindata, uint8_t binlen);
void initialize_zdd_ble_asynch_event_queue(void);
tBleStatus write_zdd_bd_address(void);
void zdd_generate_bd_addr(void);
bool initialize_gap_gatt_interface(void);
void initialize_zdd_port_info(void);
bool zdd_port_open_process(struct ZigBeeT *zb, const char *adapter_name, const char *virtual_path,
    const char *virtual_sniffer);
void zdd_port_disconnect_zvd(struct ZigBeeT *zb);
void zdd_gatt_services_init(void);
void zdd_port_disable_advert(struct ZigBeeT *zb);
void zdd_port_disconnect_zvd(struct ZigBeeT *zb);
void zdd_port_update_advert(struct ZigBeeT *zb, uint16_t pan_id, uint16_t nwk_addr, bool pjoin);
void disconnect_zdd_port_zvd(void);
// Zdd task
void zdd_port_task(void);
// Wrapper function to set the active thread name
void set_active_thread_name(const char *name);
// Function to retrieve the BleAsynchEventQueue
tListNode* get_ble_asynch_event_queue(void);
// Wrapper function to clear the active thread name
void clear_active_thread_name(void);
// Wrapper function to update the handler
void  update_zdd_port_handle(uint16_t conn_handle);
// Wrapper function to check connection handle
bool check_zdd_connection_handle(uint16_t conn_handle);
// Wrapper function to handle read request
bool handle_zdd_read_request(uint16_t attribute_handle);
// Wrapper function to handle unhandled events
void handle_unhandled_event(uint16_t line_number);
// Wrapper function to handle new connection
bool handle_new_zdd_connection(void);
// Wrapper function to write ZDD
bool processWriteForZdd(aci_gatt_write_permit_req_event_rp0 *write_perm_req);
// Wrapper function to check active write parameter
bool check_zdd_write_active(void); 
// Wrapper function to update the active write
void update_zdd_write_active(void);

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
