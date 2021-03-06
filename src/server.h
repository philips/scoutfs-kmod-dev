#ifndef _SCOUTFS_SERVER_H_
#define _SCOUTFS_SERVER_H_

#define SI4_FMT		"%u.%u.%u.%u:%u"

#define si4_trace_define(name)		\
	__field(__u32, name##_addr)	\
	__field(__u16, name##_port)

#define si4_trace_assign(name, sin)					\
do {									\
	__typeof__(sin) _sin = (sin);					\
									\
	__entry->name##_addr = be32_to_cpu(_sin->sin_addr.s_addr);	\
	__entry->name##_port = be16_to_cpu(_sin->sin_port);		\
} while(0)

#define si4_trace_args(name)			\
	(__entry->name##_addr >> 24),		\
	(__entry->name##_addr >> 16) & 255,	\
	(__entry->name##_addr >> 0) & 255,	\
	__entry->name##_addr & 255,		\
	__entry->name##_port

#define SNH_FMT	"id %llu data_len %u cmd %u flags 0x%x error %u"
#define SNH_ARG(nh) le64_to_cpu((nh)->id), le16_to_cpu((nh)->data_len), \
		    (nh)->cmd, (nh)->flags, (nh)->error

#define snh_trace_define(name)		\
	__field(__u64, name##_id)	\
	__field(__u16, name##_data_len)	\
	__field(__u8, name##_cmd)	\
	__field(__u8, name##_flags)	\
	__field(__u8, name##_error)

#define snh_trace_assign(name, nh)				\
do {								\
	__typeof__(nh) _nh = (nh);				\
								\
	__entry->name##_id = le64_to_cpu(_nh->id);		\
	__entry->name##_data_len = le16_to_cpu(_nh->data_len);	\
	__entry->name##_cmd = _nh->cmd;				\
	__entry->name##_flags = _nh->flags;			\
	__entry->name##_error = _nh->error;			\
} while (0)

#define snh_trace_args(name)						   \
	__entry->name##_id, __entry->name##_data_len, __entry->name##_cmd, \
	__entry->name##_flags, __entry->name##_error

void scoutfs_init_ment_to_net(struct scoutfs_net_manifest_entry *net_ment,
			      struct scoutfs_manifest_entry *ment);
void scoutfs_init_ment_from_net(struct scoutfs_manifest_entry *ment,
				struct scoutfs_net_manifest_entry *net_ment);

int scoutfs_server_setup(struct super_block *sb);
void scoutfs_server_destroy(struct super_block *sb);

#endif
