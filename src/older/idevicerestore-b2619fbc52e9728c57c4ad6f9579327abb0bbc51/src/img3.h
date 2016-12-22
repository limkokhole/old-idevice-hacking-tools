/*
 * img3.h
 * Functions for handling with Apple's IMG3 format
 *
 * Copyright (c) 2012 Nikias Bassen. All Rights Reserved.
 * Copyright (c) 2010 Martin Szulecki. All Rights Reserved.
 * Copyright (c) 2010 Joshua Hill. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef IDEVICERESTORE_IMG3_H
#define IDEVICERESTORE_IMG3_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	kNorContainer = 0x696D6733,  // img3
	kImg3Container = 0x496D6733, // Img3
	k8900Container = 0x30303938, // 8900
	kImg2Container = 0x494D4732  // IMG2
} img3_container;

typedef enum {
	kDataElement = 0x44415441, // DATA
	kTypeElement = 0x54595045, // TYPE
	kKbagElement = 0x4B424147, // KBAG
	kShshElement = 0x53485348, // SHSH
	kCertElement = 0x43455254, // CERT
	kChipElement = 0x43484950, // CHIP
	kProdElement = 0x50524F44, // PROD
	kSdomElement = 0x53444F4D, // SDOM
	kVersElement = 0x56455253, // VERS
	kBordElement = 0x424F5244, // BORD
	kSepoElement = 0x5345504F, // SEPO
	kEcidElement = 0x45434944, // ECID
	kUnknElement = 0x53414c54  // FIXME
} img3_element_type;

typedef struct {
	unsigned int signature;
	unsigned int full_size;
	unsigned int data_size;
	unsigned int shsh_offset;
	unsigned int image_type;
} img3_header;

typedef struct {
	unsigned int signature;
	unsigned int full_size;
	unsigned int data_size;
} img3_element_header;

typedef struct {
	img3_element_header* header;
	img3_element_type type;
	unsigned char* data;
} img3_element;

typedef struct {
	char* data;
	img3_header* header;
	int num_elements;
	img3_element* elements[16];
	int idx_ecid_element;
	int idx_shsh_element;
	int idx_cert_element;
/*	img3_element* type_element;
	img3_element* data_element;
	img3_element* vers_element;
	img3_element* sepo_element;
	img3_element* bord_element;
	img3_element* sepo2_element;
	img3_element* chip_element;
	img3_element* bord2_element;
	img3_element* kbag1_element;
	img3_element* kbag2_element;
	img3_element* ecid_element;
	img3_element* shsh_element;
	img3_element* cert_element;
	img3_element* unkn_element;*/
} img3_file;

void img3_free(img3_file* image);
img3_element* img3_parse_element(char* data);
void img3_free_element(img3_element* element);
img3_file* img3_parse_file(char* data, int size);
int img3_get_data(img3_file* image, char** pdata, int* psize);
int img3_replace_signature(img3_file* image, char* signature);


#ifdef __cplusplus
}s
#endif

#endif
