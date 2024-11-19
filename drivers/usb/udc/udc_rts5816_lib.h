/*
 * Copyright (c) 2024 Realtek Semiconductor, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_USB_UDC_RTS5816_LIB_H_
#define ZEPHYR_DRIVERS_USB_UDC_RTS5816_LIB_H_

/*
 * \name  Usb endpoint logic number config
 */
#define USB_EPA_DIR USB_EP_DIR_OUT
#define USB_EPB_DIR USB_EP_DIR_IN
#define USB_EPC_DIR USB_EP_DIR_IN
#define USB_EPD_DIR USB_EP_DIR_IN
#define USB_EPE_DIR USB_EP_DIR_OUT
#define USB_EPF_DIR USB_EP_DIR_IN
#define USB_EPG_DIR USB_EP_DIR_OUT

/*
 * Usb interrupt define
 */

#define USB_LS_LINE_STATE_INT BIT(0)
#define USB_LS_SOF_INT        BIT(1)
#define USB_LS_SUSPEND_INT    BIT(2)
#define USB_LS_RESUME_INT     BIT(3)
#define USB_LS_PORT_RST_INT   BIT(4)
#define USB_LS_L1_SLEEP_INT   BIT(5)
#define USB_LS_L1_RESUME_INT  BIT(6)

#define USB_EP0_INTOKEN_INT           BIT(0)
#define USB_EP0_OUTTOKEN_INT          BIT(1)
#define USB_EP0_DATAPKT_TRANS_INT     BIT(2)
#define USB_EP0_DATAPKT_RECV_INT      BIT(3)
#define USB_EP0_OUT_SHORTPKT_RECV_INT BIT(4)
#define USB_EP0_CTRL_STATUS_END_INT   BIT(5)
#define USB_EP0_SETUP_PACKET_INT      BIT(6)
#define USB_EP0_CTRL_STATUS_INT       BIT(7)

#define IE_LS_OFFSET 0
#define IE_LS_BITS   1
#define IE_LS_MASK   (((1 << 1) - 1) << 0)
#define IE_LS        (IE_LS_MASK)

#define IE_SOF_OFFSET 1
#define IE_SOF_BITS   1
#define IE_SOF_MASK   (((1 << 1) - 1) << 1)
#define IE_SOF        (IE_SOF_MASK)

#define IE_SUSPND_OFFSET 2
#define IE_SUSPND_BITS   1
#define IE_SUSPND_MASK   (((1 << 1) - 1) << 2)
#define IE_SUSPND        (IE_SUSPND_MASK)

#define IE_RESUME_OFFSET 3
#define IE_RESUME_BITS   1
#define IE_RESUME_MASK   (((1 << 1) - 1) << 3)
#define IE_RESUME        (IE_RESUME_MASK)

#define IE_SE0RST_OFFSET 4
#define IE_SE0RST_BITS   1
#define IE_SE0RST_MASK   (((1 << 1) - 1) << 4)
#define IE_SE0RST        (IE_SE0RST_MASK)

#define IE_L1SLEEP_OFFSET 5
#define IE_L1SLEEP_BITS   1
#define IE_L1SLEEP_MASK   (((1 << 1) - 1) << 5)
#define IE_L1SLEEP        (IE_L1SLEEP_MASK)

#define IE_L1RESUME_OFFSET 6
#define IE_L1RESUME_BITS   1
#define IE_L1RESUME_MASK   (((1 << 1) - 1) << 6)
#define IE_L1RESUME        (IE_L1RESUME_MASK)

#define IE_SOF_INTERVAL_OFFSET 7
#define IE_SOF_INTERVAL_BITS   1
#define IE_SOF_INTERVAL_MASK   (((1 << 1) - 1) << 7)
#define IE_SOF_INTERVAL        (IE_SOF_INTERVAL_MASK)

#define USB_BULKOUT_DATAPKT_RECV_INT  BIT(1)
#define USB_BULKOUT_SHORTPKT_RECV_INT BIT(2)
#define USB_BULKIN_TRANS_END_INT      BIT(1)

#define USB_INTOUT_DATAPKT_RECV_INT BIT(1)
#define USB_INTIN_DATAPKT_TRANS_INT BIT(1)

/* Memory Control */
#define EP_MC_INT_DMA_DONE BIT(0)
#define EP_MC_INT_SIE_DONE BIT(5)

/**
 * \name Usb endpoint  define
 */
#define USB_EP0_MPS        (0x40)
#define USB_BULK_MPS_HS    (0x0200)
#define USB_BULK_MPS_FS    (0x0040)
#define USB_INT_EPG_MPS    (0x80)
#define USB_INT_EPC_MPS_HS (0x80)
#define USB_INT_EPC_MPS_FS (0x40)
#define USB_INT_EPD_MPS    (0x40)

#define USB_EP_DATA_ID_DATA0 0
#define USB_EP_DATA_ID_DATA1 1

enum rts_ep_nums {
	EP0,
	EPA,
	EPB,
	EPC,
	EPD,
	EPE,
	EPF,
	EPG,
	MAX_NUM_EP
};

enum event_type {
	EVT_SETUP,
	EVT_CTRL_DIN,
	EVT_CTRL_DOUT,
	EVT_STATUS,
	EVT_XFER,
	EVT_DOUT,
	EVT_DIN,
	EVT_DONE,
};

typedef struct {
	mem_addr_t u2sie_sys_base;
	mem_addr_t u2sie_ep_base;
	mem_addr_t u2mc_ep_base;
	mem_addr_t usb2_ana_base;
} USB_TypeDef;

void rts_usb_phy_init(const USB_TypeDef *usb);

void rts_usb_connect_hs(const USB_TypeDef *usb);
void rts_usb_connect_fs(const USB_TypeDef *usb);
bool rts_usb_test_hs(const USB_TypeDef *usb);
void rts_usb_disconnect(const USB_TypeDef *usb);

void rts_usb_set_devaddr(const USB_TypeDef *usb, uint8_t dev_addr);
uint8_t rts_usb_get_devaddr(const USB_TypeDef *usb);

void rts_usb_trg_rsumK(const USB_TypeDef *usb);

void rts_ep_set_int_en(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field, bool enable);
bool rts_ep_get_int_en(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);
bool rts_ep_get_int_sts(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);
void rts_ep_clr_int_sts(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);

void rts_ls_set_int_en(const USB_TypeDef *usb, uint32_t int_field, bool enable);
bool rts_ls_get_int_en(const USB_TypeDef *usb, uint32_t int_field);
bool rts_ls_get_int_sts(const USB_TypeDef *usb, uint32_t int_field);
void rts_ls_clr_int_sts(const USB_TypeDef *usb, uint32_t int_field);

void rts_mc_set_int_en(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field, bool enable);
bool rts_mc_get_int_en(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);
bool rts_mc_get_int_sts(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);
void rts_mc_clr_int_sts(const USB_TypeDef *usb, uint8_t ep_idx, uint32_t field);

void rts_ep_rst(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_ep_cfg_mps(const USB_TypeDef *usb, uint8_t ep_idx, uint16_t mps);
uint16_t rts_ep_get_mps(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_ep_cfg_en(const USB_TypeDef *usb, uint8_t ep_idx, bool en);
void rts_ep_cfg_lnum(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t ep_lnum);
void rts_ep_nakout(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_ep_fifo_flush(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_ep_fifo_en(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_ep_force_toggle(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t data);
void rts_ep_stall(const USB_TypeDef *usb, uint8_t ep_idx, bool set);
uint16_t rts_ep_rx_bc(const USB_TypeDef *usb, uint8_t ep_idx);

void rts_ep0_get_setup_pkt(const USB_TypeDef *usb, uint8_t *setup_buf, size_t len);
void rts_ep0_start_rx(const USB_TypeDef *usb);
int rts_ep0_start_tx_sub(const USB_TypeDef *usb, const uint8_t *data, size_t trans_len);
void rts_ep0_hsk(const USB_TypeDef *usb);
int rts_ctrl_handle_recv_sub(const USB_TypeDef *usb, uint8_t *buf, size_t len);

void rts_bulk_stopdma(const USB_TypeDef *usb, uint8_t ep_idx);
void rts_bulkin(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t *data, uint16_t len);
void rts_bulkout_startdma(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t *data, uint16_t len);
uint8_t rts_intout(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t *data);
void rts_intin(const USB_TypeDef *usb, uint8_t ep_idx, uint8_t *buf, uint16_t len);

#endif /* ZEPHYR_DRIVERS_USB_UDC_RTS5816_LIB_H_ */
