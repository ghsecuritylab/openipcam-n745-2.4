/*
 *  obexftp/client.h: ObexFTP client library
 *
 *  Copyright (c) 2002 Christian W. Zuckschwerdt <zany@triq.net>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *     
 */

#ifndef OBEXFTP_CLIENT_H
#define OBEXFTP_CLIENT_H

#ifdef SWIG
%module obexftp
%{
#include "obexftp.h"
#include "client.h"
#include <inttypes.h>
%}
#endif
     
#include <inttypes.h>
#include <sys/stat.h>
#include <time.h>
#include <openobex/obex.h>
#include "obexftp.h"
#include "uuid.h"

#ifdef __cplusplus
extern "C" {
#endif


/* quirks */

#define OBEXFTP_LEADING_SLASH	0x01	/* used in get (and alike) */
#define OBEXFTP_TRAILING_SLASH	0x02	/* used in list */
#define OBEXFTP_SPLIT_SETPATH	0x04	/* some phones dont have a cwd */

#define OBEXFTP_USE_LEADING_SLASH(x)	((x & OBEXFTP_LEADING_SLASH) != 0)
#define OBEXFTP_USE_TRAILING_SLASH(x)	((x & OBEXFTP_TRAILING_SLASH) != 0)
#define OBEXFTP_USE_SPLIT_SETPATH(x)	((x & OBEXFTP_SPLIT_SETPATH) != 0)

/* dont disable leading slashes unless you disable split setpath */
#define DEFAULT_OBEXFTP_QUIRKS	\
	(OBEXFTP_LEADING_SLASH | OBEXFTP_TRAILING_SLASH | OBEXFTP_SPLIT_SETPATH)
#define DEFAULT_CACHE_TIMEOUT 180	/* 3 minutes */
#define DEFAULT_CACHE_MAXSIZE 10240	/* 10k */


/* types */

typedef struct stat_entry stat_entry_t;
struct stat_entry {
	char name[256];
	mode_t mode;
	int size;
	time_t mtime;
};

typedef struct cache_object cache_object_t;
struct cache_object
{
	cache_object_t *next;
	int refcnt;
	time_t timestamp;
	int size;	/* or uint32_t */
	char *name;
	char *content;	/* or uint8_t */
	stat_entry_t *stats;	/* only if its a parsed directory */
};

typedef struct obexftp_client
{
	/* state */
	obex_t *obexhandle;
	int finished;
	int success;
	int obex_rsp;
	int mutex;	/* should be using pthreads for this */
	int quirks;
	/* client */
	obexftp_info_cb_t infocb;
	void *infocb_data;
	/* transfer */
	int fd; /* used in put body */
	char *target_fn; /* used in get body */
	uint32_t buf_size;
	uint32_t buf_pos;
	const uint8_t *buf_data;
	uint8_t *stream_chunk;
	uint32_t apparam_info;
	/* persistence */
	cache_object_t *cache;
	int cache_timeout;
	int cache_maxsize;
} obexftp_client_t;


/* session */

/*@null@*/ obexftp_client_t *obexftp_cli_open(int transport,
				 /*@null@*/ /*const*/ obex_ctrans_t *ctrans,
				 /*@null@*/ obexftp_info_cb_t infocb,
				 /*@null@*/ void *infocb_data);

void obexftp_cli_close(/*@only@*/ /*@out@*/ /*@null@*/ obexftp_client_t *cli);

int obexftp_cli_connect_uuid(obexftp_client_t *cli, const char *device, int port, const uint8_t uuid[]);

#define	obexftp_cli_connect(cli, device, port) \
	obexftp_cli_connect_uuid(cli, device, port, UUID_FBS)

int obexftp_cli_disconnect(obexftp_client_t *cli);


/* transfer */

int obexftp_setpath(obexftp_client_t *cli, /*@null@*/ const char *name, int create);

#define	obexftp_chpath(cli, name) \
	obexftp_setpath(cli, name, 0)

#define	obexftp_mkpath(cli, name) \
	obexftp_setpath(cli, name, 1)

#define	obexftp_cdup(cli) \
	obexftp_setpath(cli, NULL, 0)

#define	obexftp_cdtop(cli) \
	obexftp_setpath(cli, "", 0)

int obexftp_put(obexftp_client_t *cli, const char *filename);

int obexftp_put_file(obexftp_client_t *cli, const char *localname,
		     const char *remotename);

int obexftp_put_data(obexftp_client_t *cli, const char *data, int size,
		     const char *remotename);

int obexftp_del(obexftp_client_t *cli, const char *name);

int obexftp_info(obexftp_client_t *cli, uint8_t opcode);

int obexftp_list(obexftp_client_t *cli,
		 /*@null@*/ const char *localname,
		 /*@null@*/ const char *remotename);

int obexftp_get(obexftp_client_t *cli,
		/*@null@*/  const char *localname,
		const char *remotename);

int obexftp_rename(obexftp_client_t *cli,
		   const char *sourcename,
		   const char *targetname);


/* compatible directory handling */

void *obexftp_opendir(obexftp_client_t *cli, const char *name);

int obexftp_closedir(void *dir);

stat_entry_t *obexftp_readdir(void *dir);

stat_entry_t *obexftp_stat(obexftp_client_t *cli, const char *name);


#ifdef __cplusplus
}
#endif

#endif /* OBEXFTP_CLIENT_H */

