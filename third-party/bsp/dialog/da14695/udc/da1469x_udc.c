/**
 * @file
 * @brief
 *
 * @author  Alexander Kalmuk
 * @date    25.06.2020
 */

#include <config/custom_config_qspi.h>

#include <hw_cpm.h>
#include <hw_usb.h>

#include <assert.h>
#include <string.h>
#include <util/log.h>
#include <util/array.h>
#include <kernel/irq.h>
#include <embox/unit.h>
#include <drivers/usb/gadget/udc.h>
#include <third_party/dialog/da14695/usb_da1469x.h>

EMBOX_UNIT_INIT(da1469x_udc_init);

#define EP0_BUFFER_SIZE 1024

static hw_usb_device_framework_ctrl_req_t usb_setup;

static uint8_t ep0_buffer[EP0_BUFFER_SIZE];

static int da1469x_udc_ep_queue(struct usb_gadget_ep *ep,
	                        struct usb_gadget_request *req) {
	assert(ep && req);

	hw_usb_ep_tx_start(ep->nr, req->buf, req->len);

	return 0;
}

static struct usb_udc da1469x_udc = {
	.name = "da1496x udc",
	.ep_queue = da1469x_udc_ep_queue,
};

static void da1469x_udc_send_control_msg(uint8_t *data, uint8_t size) {
	assert(size <= EP0_BUFFER_SIZE);
	
	log_debug("size = %d", size);
	
	memcpy(ep0_buffer, data, size);
	hw_usb_ep_tx_start(0, ep0_buffer, size);
}

void hw_usb_ep_tx_done(uint8_t ep_nr, uint8_t *buffer) {
	if (ep_nr == 0) {
		hw_usb_ep_rx_enable(0);
		return;
	}
}

void hw_usb_bus_event(HW_USB_BUS_EVENT_TYPE event) {
	switch (event) {
	case UBE_RESET:
		log_debug("Reset event");
		hw_usb_bus_address(0);
		hw_usb_ep_rx_enable(0);
		break;
	default:
		log_error("Unknown event");
		break;
	}
}

void hw_usb_bus_frame(uint16_t frame_nr) {
	(void) frame_nr;
}

void hw_usb_ep_nak(uint8_t ep_nr) {
	if (ep_nr == 0) {
		hw_usb_ep_disable(0, false);
		hw_usb_ep_rx_enable(0);
	}
}

void sys_usb_ext_hook_begin_enumeration(void) {
	hw_usb_ep_configure(0, true, NULL);
	/* TODO We do not configure other endpoints because they are unused currently. */
}

uint8_t *hw_usb_ep_get_rx_buffer(uint8_t ep_nr, bool is_setup, uint16_t *buffer_size) {
	if (ep_nr == 0) {
		if (is_setup) {
			*buffer_size = sizeof(usb_setup);
			return (uint8_t *) &usb_setup;
		} else {
			hw_usb_ep0_stall();
			*buffer_size = 0;
			return NULL;
		}
	}
	return NULL;
}

bool hw_usb_ep_rx_read_by_driver(uint8_t ep_nr) {
	return false;
}

static void da1469x_udc_eq_get_status(void) {
	uint16_t status = 0;
	int ep_nr;

	switch (usb_setup.request_type & HW_USB_DEVICE_FRAMEWORK_RECIP_MASK) {
	case HW_USB_DEVICE_FRAMEWORK_RECIP_DEVICE:
		da1469x_udc_send_control_msg((uint8_t *) &status, 2);
		break;
	case HW_USB_DEVICE_FRAMEWORK_RECIP_ENDPOINT:
		ep_nr = usb_setup.index & ~HW_USB_DEVICE_FRAMEWORK_DIR_IN;

#if 0
		if (ep_nr >= RNDIS_EP_COUNT) {
			hw_usb_ep0_stall();
			break;
		}
#endif
		
		if (hw_usb_ep_is_stalled(ep_nr)) {
			status = 1;
		}
		da1469x_udc_send_control_msg((uint8_t *) &status, 2);
		break;
	default:
		log_error("Unsupported RECIP 0x%x",
			usb_setup.request_type & HW_USB_DEVICE_FRAMEWORK_RECIP_MASK);
		hw_usb_ep0_stall();
		break;
	}
}

static void da1469x_udc_req_set_address(void) {
	log_debug("addr=0x%x", usb_setup.value);
	hw_usb_bus_address(usb_setup.value);
	hw_usb_ep_tx_start(0, NULL, 0);
}

static void da1469x_udc_handle_standard_req(int ep_nr) {
	int ret;

	switch (usb_setup.request) {
	case HW_USB_DEVICE_FRAMEWORK_REQ_GET_STATUS:
		da1469x_udc_eq_get_status();
		break;
	case HW_USB_DEVICE_FRAMEWORK_REQ_SET_ADDRESS:
		da1469x_udc_req_set_address();
		break;
	case HW_USB_DEVICE_FRAMEWORK_REQ_GET_CONFIGURATION:
		/* TODO usb_req_get_configuration(); */
		break;
	case HW_USB_DEVICE_FRAMEWORK_REQ_SET_CONFIGURATION:
		/* TODO usb_req_set_configuration(); */
		break;
	default:
		ret = usb_gadget_setup(da1469x_udc.gadget,
			                   (const struct usb_control_header *) &usb_setup);
		if (ret != 0) {
			log_error("Not implemented req 0x%x", usb_setup.request);
			hw_usb_ep0_stall();
		}
		break;
	}
}

bool hw_usb_ep_rx_done(uint8_t ep_nr, uint8_t *buffer, uint16_t size) {
	if (ep_nr == 0) {
		if (size == 0) {
			return true;
		}

		if (buffer == (uint8_t *) &usb_setup) {
			log_debug("Usb setup packet:");
			log_debug("request_type=0x%02x, request=0x%02x, value=0x%04x, index=0x%04x, length=0x%04x",
				usb_setup.request_type, usb_setup.request, usb_setup.value, usb_setup.index, usb_setup.length);
			log_debug("");
		}
		
		switch (usb_setup.request_type & HW_USB_DEVICE_FRAMEWORK_TYPE_MASK) {
		case HW_USB_DEVICE_FRAMEWORK_TYPE_STANDARD:
			da1469x_udc_handle_standard_req(ep_nr);
			break;
		default:
			log_error("Unknown request");
			break;
		}
	}

	return false;
}

static int da1469x_udc_init(void) {
	usb_da1469x_init();

	usb_gadget_register_udc(&da1469x_udc);

	return 0;
}
