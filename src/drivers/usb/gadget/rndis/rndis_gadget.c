/**
 * @file
 * @brief
 *
 * @author  Alexander Kalmuk
 * @date    25.06.2020
 */

#include <string.h>
#include <embox/unit.h>
#include <drivers/usb/gadget/rndis_desc.h>
#include <drivers/usb/gadget/gadget.h>

EMBOX_UNIT_INIT(rndis_gadget_init);

#define RNDIS_EP_BULK_TX 1
#define RNDIS_EP_BULK_RX 2
#define RNDIS_EP_INT_TX  3

static const struct usb_desc_endpoint int_ep_desc = {
	.b_length            = sizeof (struct usb_desc_endpoint),
	.b_desc_type         = USB_DESC_TYPE_ENDPOINT,
	.b_endpoint_address  = 0x80 | RNDIS_EP_INT_TX, // in
	.bm_attributes       = USB_DESC_ENDP_TYPE_INTR,
	.w_max_packet_size   = 8,
	.b_interval          = 1,
};

static const struct usb_desc_endpoint bulk_ep_tx_desc = {
	.b_length            = sizeof (struct usb_desc_endpoint),
	.b_desc_type         = USB_DESC_TYPE_ENDPOINT,
	.b_endpoint_address  = 0x80 | RNDIS_EP_BULK_TX, // in
	.bm_attributes       = USB_DESC_ENDP_TYPE_BULK,
	.w_max_packet_size   = 64,
	.b_interval          = 0,
};

static const struct usb_desc_endpoint bulk_ep_rx_desc = {
	.b_length            = sizeof (struct usb_desc_endpoint),
	.b_desc_type         = USB_DESC_TYPE_ENDPOINT,
	.b_endpoint_address  = 0x0 | RNDIS_EP_BULK_RX, // out
	.bm_attributes       = USB_DESC_ENDP_TYPE_BULK,
	.w_max_packet_size   = 64,
	.b_interval          = 0,
};

static const struct usb_desc_common_header *rndis_descs[] = {
	(struct usb_desc_common_header *) &rndis_config_desc,
	(struct usb_desc_common_header *) &iad_descriptor,
	(struct usb_desc_common_header *) &rndis_interface0_desc,
	(struct usb_desc_common_header *) &int_ep_desc,
	(struct usb_desc_common_header *) &interface0_functional_desc[0],
	(struct usb_desc_common_header *) &interface0_functional_desc[1],
	(struct usb_desc_common_header *) &interface0_functional_desc[2],
	(struct usb_desc_common_header *) &interface0_functional_desc[3],
	(struct usb_desc_common_header *) &rndis_interface1_desc,
	(struct usb_desc_common_header *) &bulk_ep_tx_desc,
	(struct usb_desc_common_header *) &bulk_ep_rx_desc,
	NULL,
};

static struct usb_gadget rndis_gadget = {
	.strings = {
		[RNDIS_MANUFACTURER_STR_INDEX] = "Embox",
		[RNDIS_PRODUCT_STR_INDEX] = "Embox RNDIS",
		[RNDIS_SERIAL_STR_INDEX] = "0123456789",
		[RNDIS_CONFIGURATION_STR_INDEX] = "Embox RNDIS Configuration",
		[RNDIS_MS_OS_STR_INDEX] = "Unknown",
	},
	.descs = rndis_descs,
};

static int rndis_gadget_init(void) {
	memcpy(&rndis_gadget.device_desc, &rndis_device_desc,
		   sizeof rndis_gadget.device_desc);

	usb_gadget_register(&rndis_gadget);

	return 0;
}
