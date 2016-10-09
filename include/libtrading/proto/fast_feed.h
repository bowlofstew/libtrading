#ifndef	LIBTRADING_FAST_FEED_H
#define	LIBTRADING_FAST_FEED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libtrading/proto/fast_session.h"

#include <sys/socket.h>
#include <sys/types.h>

struct fast_feed {
	struct fast_session	*session;
	struct fast_session_cfg	cfg;

	u64			recv_num;
	char			file[64];
	char			xml[128];
	char			lip[32];
	char			sip[32];
	char			ip[32];
	bool			active;
	int			port;
};

static inline int socket_setopt(int sockfd, int level, int optname, int optval)
{
	return setsockopt(sockfd, level, optname, (void *) &optval, sizeof(optval));
}

static inline struct fast_message *fast_feed_recv(struct fast_feed *feed, int flags)
{
	if (feed->session->reset)
		fast_session_reset(feed->session);

	return fast_session_recv(feed->session, flags);
}

int fast_feed_close(struct fast_feed *feed);
int fast_feed_open(struct fast_feed *feed);

#ifdef __cplusplus
}
#endif

#endif	/* LIBTRADING_FAST_FEED_H */
