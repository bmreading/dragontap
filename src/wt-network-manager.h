#ifndef WT_NETWORK_MANAGER_H
#define WT_NETWORK_MANAGER_H

#include <glib-object.h>
#include <NetworkManager.h>
#include <stdbool.h>

G_BEGIN_DECLS

#define WT_TYPE_NETWORK_MANAGER wt_network_manager_get_type ()
G_DECLARE_FINAL_TYPE (WtNetworkManager, wt_network_manager, WT, NETWORK_MANAGER, GObject)

enum 
toggle_type 
{
    TOGGLE_ON=1,
    TOGGLE_OFF=0
};

WtNetworkManager 
*wt_network_manager_new (void);

GPtrArray 
*wt_network_manager_get_wireguard_connections (WtNetworkManager *self);

bool
wt_network_manager_is_connection_active (WtNetworkManager *self,
                                         NMConnection     *connection);

void
wt_network_manager_toggle_wireguard (WtNetworkManager *self,
                                     NMConnection     *connection,
                                     enum toggle_type  tog);

G_END_DECLS

#endif


