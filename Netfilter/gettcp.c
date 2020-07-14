/*
  netfilter module:
  
  get tcp payload and filter on port
  
  test success on centos6/kernel 2.6.32.x
  
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/netfilter_ipv4.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <net/tcp.h>
#include <linux/errno.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("GPL");
MODULE_DESCRIPTION("gettcp");


#define TCP_KEY   "123456"
unsigned int port = 80;


static unsigned int gettcp(unsigned int hooknum, struct sk_buff * skb, const struct net_device *in, const struct net_device *out, int (*okfn) (struct sk_buff *)) {
	struct iphdr *iph;
	struct tcphdr *tcph;
	unsigned int sport, dport;
	u32 saddr, daddr;
	unsigned char *tcp_data ;
	unsigned char *tail;
	unsigned char *it;
	char *p;
	char req[1024]={'\0'};
	int req_index = 0;

	if (!skb)
	    return NF_ACCEPT;
	iph = ip_hdr(skb);
	if (iph->protocol != IPPROTO_TCP)
	  return NF_ACCEPT;
	tcph = (struct tcphdr *)(skb->data + iph->ihl * 4);
	saddr = ntohl(iph->saddr);
	daddr = ntohl(iph->daddr);
	sport = ntohs(tcph->source);
	dport = ntohs(tcph->dest);
	if (ntohs(tcph->dest) != port)
	    return NF_ACCEPT;

	int length=skb->len-iph->ihl*4-tcph->doff*4;
	if(length==0)
	    return NF_ACCEPT;

	tcp_data = (unsigned char *)((unsigned char *)tcph + (tcph->doff * 4));
	
	
	tail = skb_tail_pointer(skb);
	for (it = tcp_data; it != tail; ++it) {
		char c = *(char *)it;
		if (c == '\0'){
			req[req_index] = c;
			break;
		}

		req[req_index]=c;
		req_index ++;
	}
  printk("TCP DATA:\n%s\n",req);

	if (p = strstr(tcp_data,TCP_KEY) != NULL) 
	{
		printk("Find KEY! \n");
	}

	return NF_ACCEPT;
}

struct nf_hook_ops gettcp_ops = {
	.list = {
		NULL,NULL
	}
	,
	  .hook = gettcp,
	.pf = PF_INET,
	.hooknum = NF_INET_PRE_ROUTING,

	.priority =NF_IP_PRI_FIRST,
}
;

static int __init gettcp_init(void) {
	
	if(nf_register_hook(&gettcp_ops)) {
		
		return -1;
	}
	
	return 0;
}

static void __exit gettcp_exit(void) {
	nf_unregister_hook(&gettcp_ops);
	
}
module_init(gettcp_init);
module_exit(gettcp_exit);