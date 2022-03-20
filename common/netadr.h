/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#ifndef NETADR_H
#define NETADR_H

#include "build.h"
#include STDINT_H

typedef enum
{
	NA_UNUSED,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX,
	NA_IP6,
	NA_MULTICAST_IP6, // all nodes multicast
} netadrtype_t;

#define NETADR_T_SIZE 20

// Original structure:
// typedef struct netadr_s
// {
// 	netadrtype_t	type;
// 	unsigned char	ip[4];
// 	unsigned char	ipx[10];
// 	unsigned short	port;
// } netadr_t;

typedef struct netadr_s
{
	union
	{
		struct
		{
#if XASH_LITTLE_ENDIAN
			uint16_t type6;
			uint16_t port6;
#elif XASH_BIG_ENDIAN
			uint16_t port6;
			uint16_t type6;
#else
#error
#endif
		};
		uint32_t type;
	};
	union
	{
		struct
		{
			uint16_t ip6[8];
		};

		struct
		{
			uint8_t  ip[4];
			uint8_t  ipx[10];
			uint16_t port;
		};
	};
} netadr_t;

extern int _check_netadr_t_size[sizeof( netadr_t ) == NETADR_T_SIZE ? 1 : -1];

#endif//NETADR_H
