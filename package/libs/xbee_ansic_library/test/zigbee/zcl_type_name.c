/*
 * Copyright (c) 2010-2012 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

// Unit test for zcl_type_name() in zcl_types.c

#include <stdio.h>

#include "zigbee/zcl_types.h"
#include "../unittest.h"

const char *expected_name[] = {
	"NO_DATA",
	"INVALID_0x01",
	"INVALID_0x02",
	"INVALID_0x03",
	"INVALID_0x04",
	"INVALID_0x05",
	"INVALID_0x06",
	"INVALID_0x07",
	"GENERAL_8BIT",
	"GENERAL_16BIT",
	"GENERAL_24BIT",
	"GENERAL_32BIT",
	"GENERAL_40BIT",
	"GENERAL_48BIT",
	"GENERAL_56BIT",
	"GENERAL_64BIT",
	"LOGICAL_BOOLEAN",
	"INVALID_0x11",
	"INVALID_0x12",
	"INVALID_0x13",
	"INVALID_0x14",
	"INVALID_0x15",
	"INVALID_0x16",
	"INVALID_0x17",
	"BITMAP_8BIT",
	"BITMAP_16BIT",
	"BITMAP_24BIT",
	"BITMAP_32BIT",
	"BITMAP_40BIT",
	"BITMAP_48BIT",
	"BITMAP_56BIT",
	"BITMAP_64BIT",
	"UNSIGNED_8BIT",
	"UNSIGNED_16BIT",
	"UNSIGNED_24BIT",
	"UNSIGNED_32BIT",
	"UNSIGNED_40BIT",
	"UNSIGNED_48BIT",
	"UNSIGNED_56BIT",
	"UNSIGNED_64BIT",
	"SIGNED_8BIT",
	"SIGNED_16BIT",
	"SIGNED_24BIT",
	"SIGNED_32BIT",
	"SIGNED_40BIT",
	"SIGNED_48BIT",
	"SIGNED_56BIT",
	"SIGNED_64BIT",
	"ENUM_8BIT",
	"ENUM_16BIT",
	"INVALID_0x32",
	"INVALID_0x33",
	"INVALID_0x34",
	"INVALID_0x35",
	"INVALID_0x36",
	"INVALID_0x37",
	"FLOAT_SEMI",
	"FLOAT_SINGLE",
	"FLOAT_DOUBLE",
	"INVALID_0x3B",
	"INVALID_0x3C",
	"INVALID_0x3D",
	"INVALID_0x3E",
	"INVALID_0x3F",
	"INVALID_0x40",
	"STRING_OCTET",
	"STRING_CHAR",
	"STRING_LONG_OCTET",
	"STRING_LONG_CHAR",
	"INVALID_0x45",
	"INVALID_0x46",
	"INVALID_0x47",
	"ARRAY",
	"INVALID_0x49",
	"INVALID_0x4A",
	"INVALID_0x4B",
	"STRUCT",
	"INVALID_0x4D",
	"INVALID_0x4E",
	"INVALID_0x4F",
	"SET",
	"BAG",
	"INVALID_0x52",
	"INVALID_0x53",
	"INVALID_0x54",
	"INVALID_0x55",
	"INVALID_0x56",
	"INVALID_0x57",
	"INVALID_0x58",
	"INVALID_0x59",
	"INVALID_0x5A",
	"INVALID_0x5B",
	"INVALID_0x5C",
	"INVALID_0x5D",
	"INVALID_0x5E",
	"INVALID_0x5F",
	"INVALID_0x60",
	"INVALID_0x61",
	"INVALID_0x62",
	"INVALID_0x63",
	"INVALID_0x64",
	"INVALID_0x65",
	"INVALID_0x66",
	"INVALID_0x67",
	"INVALID_0x68",
	"INVALID_0x69",
	"INVALID_0x6A",
	"INVALID_0x6B",
	"INVALID_0x6C",
	"INVALID_0x6D",
	"INVALID_0x6E",
	"INVALID_0x6F",
	"INVALID_0x70",
	"INVALID_0x71",
	"INVALID_0x72",
	"INVALID_0x73",
	"INVALID_0x74",
	"INVALID_0x75",
	"INVALID_0x76",
	"INVALID_0x77",
	"INVALID_0x78",
	"INVALID_0x79",
	"INVALID_0x7A",
	"INVALID_0x7B",
	"INVALID_0x7C",
	"INVALID_0x7D",
	"INVALID_0x7E",
	"INVALID_0x7F",
	"INVALID_0x80",
	"INVALID_0x81",
	"INVALID_0x82",
	"INVALID_0x83",
	"INVALID_0x84",
	"INVALID_0x85",
	"INVALID_0x86",
	"INVALID_0x87",
	"INVALID_0x88",
	"INVALID_0x89",
	"INVALID_0x8A",
	"INVALID_0x8B",
	"INVALID_0x8C",
	"INVALID_0x8D",
	"INVALID_0x8E",
	"INVALID_0x8F",
	"INVALID_0x90",
	"INVALID_0x91",
	"INVALID_0x92",
	"INVALID_0x93",
	"INVALID_0x94",
	"INVALID_0x95",
	"INVALID_0x96",
	"INVALID_0x97",
	"INVALID_0x98",
	"INVALID_0x99",
	"INVALID_0x9A",
	"INVALID_0x9B",
	"INVALID_0x9C",
	"INVALID_0x9D",
	"INVALID_0x9E",
	"INVALID_0x9F",
	"INVALID_0xA0",
	"INVALID_0xA1",
	"INVALID_0xA2",
	"INVALID_0xA3",
	"INVALID_0xA4",
	"INVALID_0xA5",
	"INVALID_0xA6",
	"INVALID_0xA7",
	"INVALID_0xA8",
	"INVALID_0xA9",
	"INVALID_0xAA",
	"INVALID_0xAB",
	"INVALID_0xAC",
	"INVALID_0xAD",
	"INVALID_0xAE",
	"INVALID_0xAF",
	"INVALID_0xB0",
	"INVALID_0xB1",
	"INVALID_0xB2",
	"INVALID_0xB3",
	"INVALID_0xB4",
	"INVALID_0xB5",
	"INVALID_0xB6",
	"INVALID_0xB7",
	"INVALID_0xB8",
	"INVALID_0xB9",
	"INVALID_0xBA",
	"INVALID_0xBB",
	"INVALID_0xBC",
	"INVALID_0xBD",
	"INVALID_0xBE",
	"INVALID_0xBF",
	"INVALID_0xC0",
	"INVALID_0xC1",
	"INVALID_0xC2",
	"INVALID_0xC3",
	"INVALID_0xC4",
	"INVALID_0xC5",
	"INVALID_0xC6",
	"INVALID_0xC7",
	"INVALID_0xC8",
	"INVALID_0xC9",
	"INVALID_0xCA",
	"INVALID_0xCB",
	"INVALID_0xCC",
	"INVALID_0xCD",
	"INVALID_0xCE",
	"INVALID_0xCF",
	"INVALID_0xD0",
	"INVALID_0xD1",
	"INVALID_0xD2",
	"INVALID_0xD3",
	"INVALID_0xD4",
	"INVALID_0xD5",
	"INVALID_0xD6",
	"INVALID_0xD7",
	"INVALID_0xD8",
	"INVALID_0xD9",
	"INVALID_0xDA",
	"INVALID_0xDB",
	"INVALID_0xDC",
	"INVALID_0xDD",
	"INVALID_0xDE",
	"INVALID_0xDF",
	"TIME_TIMEOFDAY",
	"TIME_DATE",
	"TIME_UTCTIME",
	"INVALID_0xE3",
	"INVALID_0xE4",
	"INVALID_0xE5",
	"INVALID_0xE6",
	"INVALID_0xE7",
	"ID_CLUSTER",
	"ID_ATTRIB",
	"ID_BACNET_OID",
	"INVALID_0xEB",
	"INVALID_0xEC",
	"INVALID_0xED",
	"INVALID_0xEE",
	"INVALID_0xEF",
	"IEEE_ADDR",
	"SECURITY_KEY",
	"INVALID_0xF2",
	"INVALID_0xF3",
	"INVALID_0xF4",
	"INVALID_0xF5",
	"INVALID_0xF6",
	"INVALID_0xF7",
	"INVALID_0xF8",
	"INVALID_0xF9",
	"INVALID_0xFA",
	"INVALID_0xFB",
	"INVALID_0xFC",
	"INVALID_0xFD",
	"INVALID_0xFE",
	"UNKNOWN"
};

void t_zcl_type_name( void)
{
	char error[40];
	int i;

	for (i = 0; i < 256; ++i)
	{
		sprintf( error, "Wrong name for type 0x%02X", i);
		test_string( zcl_type_name( i), expected_name[i], error);
	}
}

int main( int argc, char *argv[])
{
	int failures = 0;

	failures += DO_TEST( t_zcl_type_name);

	return test_exit( failures);
}