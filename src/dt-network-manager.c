#include "dt-network-manager.h"
#include <stdio.h>

struct _DtNetworkManager
{
    GObject parent_instance;
};

G_DEFINE_TYPE (DtNetworkManager, dt_network_manager, G_TYPE_OBJECT)

static void
dt_network_manager_class_init (DtNetworkManagerClass *klass)
{
}

static void
dt_network_manager_init (DtNetworkManager *self)
{
}

DtNetworkManager
*dt_network_manager_new (void)
{
    return g_object_new (DT_NETWORK_MANAGER_TYPE,
                         0);
}

GPtrArray
*dt_network_manager_get_wireguard_connections (DtNetworkManager *self)
{
    NMClient *client = nm_client_new (NULL, NULL);
    const GPtrArray *connections = nm_client_get_connections (client);
    
    GPtrArray *wireguard_connections = g_ptr_array_new ();
    
    for (int i = 0; i < connections[0].len; i++) {
        NMConnection *connection = g_ptr_array_index (connections, i);
        
        if (nm_connection_is_type (connection, "wireguard") == 1) {
            
            gboolean is_active = dt_network_manager_is_connection_active (self, connection);
            
            printf("%s WireGuard connection with id %s found.\n",
                    is_active ? "Active" : "Inactive",
                    nm_connection_get_id(connection));
            
            g_ptr_array_add (wireguard_connections, connection);
        }
    }

    //g_object_unref (client);
    g_ptr_array_unref ((GPtrArray *)connections);

    return wireguard_connections;
}

gboolean
dt_network_manager_is_connection_active (DtNetworkManager *self,
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
            return TRUE;
        }
    }

    g_object_unref (client);
    
    return FALSE;
}

NMActiveConnection
*dt_network_manager_get_active_connection_by_connection (NMConnection *connection)
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

    g_ptr_array_unref ((GPtrArray *)active_connections);
    g_object_unref (client);

    return NULL;
}

void
dt_network_manager_deactivate_wireguard_callback (NMClient         *client,
                                                  GAsyncResult     *result,
                                                  DtNetworkManager *self)
{
    GError *error = NULL;
    
    // Finish the operation
    if (!nm_client_deactivate_connection_finish (client, result, &error))
    {
        g_warning ("Deactivating connection: %s", error->message);
        g_error_free (error);
    }
    else
        g_debug ("Deactivated connection successfully");
}

void
dt_network_manager_activate_wireguard_callback (NMClient         *client,
                                                GAsyncResult     *result,
                                                DtNetworkManager *self)
{
    GError *error = NULL;
    
    // Finish the operation
    if (!nm_client_activate_connection_finish (client, result, &error))
    {
        g_warning ("Activating connection: %s", error->message);
        g_error_free (error);
    }
    else
        g_debug ("Activated connection successfully");
}

void
dt_network_manager_toggle_wireguard (DtNetworkManager *self,
                                     NMConnection     *connection)
{   
    NMClient *client = nm_client_new (NULL, NULL);

    const gboolean is_active = 
        dt_network_manager_is_connection_active (self,
                                                connection);

    if (is_active)
    {
        printf("Found an active connection that was asked to be toggled off\n");

        NMActiveConnection *active_connection = 
            dt_network_manager_get_active_connection_by_connection (connection);

        nm_client_deactivate_connection_async (client,
                                               active_connection,
                                               NULL,
                                               (GAsyncReadyCallback) dt_network_manager_deactivate_wireguard_callback,
                                               self);
    }

    else if (!is_active)
    {
        printf("Found an inactive connection that was asked to be toggled on\n");

        nm_client_activate_connection_async (client,
                                             connection,
                                             NULL,
                                             NULL,
                                             NULL,
                                             (GAsyncReadyCallback) dt_network_manager_activate_wireguard_callback,
                                             self);
    }

    g_object_unref (client);
}

