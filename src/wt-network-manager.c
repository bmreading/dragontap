#include "wt-network-manager.h"
#include <stdbool.h>
#include <stdio.h>

struct _WtNetworkManager
{
    GObject parent_instance;
};

G_DEFINE_TYPE (WtNetworkManager, wt_network_manager, G_TYPE_OBJECT)

static void
wt_network_manager_class_init (WtNetworkManagerClass *klass)
{
}

static void
wt_network_manager_init (WtNetworkManager *self)
{
}

WtNetworkManager
*wt_network_manager_new (void)
{
    return g_object_new (WT_TYPE_NETWORK_MANAGER,
                         0);
}

GPtrArray
*wt_network_manager_get_wireguard_connections (WtNetworkManager *self)
{
    NMClient *client;
    
	client = nm_client_new (NULL, NULL);
    const GPtrArray *connections = nm_client_get_connections (client);
    
    GPtrArray *wireguard_connections = g_ptr_array_new ();
    
    for (int i = 0; i < connections[0].len; i++) {
        NMConnection *connection = g_ptr_array_index (connections, i);
        
        if (nm_connection_is_type (connection, "wireguard") == 1) {
            
            bool is_active = wt_network_manager_is_connection_active (self, connection);
            
            printf("%s WireGuard connection with id %s found.\n",
                    is_active ? "Active" : "Inactive",
                    nm_connection_get_id(connection));
            
            g_ptr_array_add (wireguard_connections, connection);
        }
    }
    
    return wireguard_connections;
}

bool
wt_network_manager_is_connection_active (WtNetworkManager *self,
                                         NMConnection     *connection)
{
    NMClient *client = nm_client_new (NULL, NULL);
    
    const GPtrArray *active_connections = 
        nm_client_get_active_connections (client);
    
    for (int i = 0; i < active_connections[0].len; i++)
    {
        NMActiveConnection *active_connection = 
            g_ptr_array_index (active_connections, i);
                
        const char *active_connection_id = 
            nm_active_connection_get_id (active_connection);
        
        const char *connection_id = 
            nm_connection_get_id (connection);
        
        if (strcmp (active_connection_id, connection_id) == 0) {
            return true;
        }
    }
    
    return false;
}

NMActiveConnection
*wt_network_manager_get_active_connection_by_connection (NMConnection *connection)
{
    NMClient *client = nm_client_new (NULL, NULL);
    
    const GPtrArray *active_connections = 
        nm_client_get_active_connections (client);
    
    for (int i = 0; i < active_connections[0].len; i++)
    {
        NMActiveConnection *active_connection = 
            g_ptr_array_index (active_connections, i);
                
        const char *active_connection_id = 
            nm_active_connection_get_id (active_connection);
        
        const char *connection_id = 
            nm_connection_get_id (connection);
        
        if (strcmp (active_connection_id, connection_id) == 0) {
            return active_connection;
        }
    }

    return NULL;
}

void
wt_network_manager_toggle_wireguard_callback (NMClient         *client,
                                              GAsyncResult     *result,
                                              WtNetworkManager *self)
{
    GError *error = NULL;
    
    // Finish the operation
    if (!nm_client_deactivate_connection_finish (client, result, &error))
        g_warning ("Deactivating connection: %s", error->message);
    else
        g_debug ("Deactivated connection successfully");
    
    g_error_free (error);
}


void
wt_network_manager_toggle_wireguard (WtNetworkManager *self,
                                     NMConnection     *connection,
                                     enum toggle_type  tog)
{
    char tog_type[4];
    if(tog == 1) {
        strcpy(tog_type, "On");
    }
    else {
        strcpy(tog_type, "Off");
    }
    printf("Wireguard Should be Toggled as %s\n", tog_type);
    
    NMClient *client = nm_client_new (NULL, NULL);

    bool is_active = 
        wt_network_manager_is_connection_active (self,
                                                connection);

    if ((is_active == true) && (tog == 0))
    {
        printf("Found an active connection that was asked to be toggled off\n");

        NMActiveConnection *active_connection = 
            wt_network_manager_get_active_connection_by_connection (connection);

        
        nm_client_deactivate_connection_async (client,
                                               active_connection,
                                               NULL,
                                               (GAsyncReadyCallback) wt_network_manager_toggle_wireguard_callback,
                                               self);

        // bool damn = 1;
        // damn = nm_client_deactivate_connection (client, active_connection, NULL, NULL);
    }
    else if ((is_active == false) && (tog == 1))
    {
        nm_client_activate_connection_async (client,
                                             connection,
                                             NULL,
                                             NULL,
                                             NULL,
                                             NULL,
                                             NULL);
    }
}

