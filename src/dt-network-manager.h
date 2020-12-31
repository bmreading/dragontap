#ifndef DT_NETWORK_MANAGER_H
#define DT_NETWORK_MANAGER_H

#include <glib-object.h>
#include <NetworkManager.h>

G_BEGIN_DECLS

#define DT_NETWORK_MANAGER_TYPE dt_network_manager_get_type ()
G_DECLARE_FINAL_TYPE (DtNetworkManager, dt_network_manager, DT, NETWORK_MANAGER, GObject)

enum 
toggle_type 
{
    TOGGLE_ON,
    TOGGLE_OFF
};

DtNetworkManager *dt_network_manager_new                       (void);

GPtrArray        *dt_network_manager_get_wireguard_connections (DtNetworkManager *self);

gboolean          dt_network_manager_is_connection_active      (DtNetworkManager *self,
                                                                NMConnection     *connection);

void              dt_network_manager_toggle_wireguard          (DtNetworkManager *self,
                                                                NMConnection     *connection);

G_END_DECLS

#endif /* DT_NETWORK_MANAGER_H */


