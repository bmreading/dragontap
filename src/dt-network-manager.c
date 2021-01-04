/**
 * Copyright (C) 2020 Brian Reading
 * 
 * This file is part of DragonTap.
 * 
 * DragonTap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DragonTap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DragonTap.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dt-network-manager.h"
#include <stdio.h>

struct _DtNetworkManager
{
    GObject parent_instance;

    NMClient *client;
};

G_DEFINE_TYPE (DtNetworkManager, dt_network_manager, G_TYPE_OBJECT)

static void
dt_network_manager_dispose (GObject *object)
{
    DtNetworkManager *self = DT_NETWORK_MANAGER (object);
    g_clear_object (&self->client);

    G_OBJECT_CLASS (dt_network_manager_parent_class)->dispose (object);
}

static void
dt_network_manager_finalize (GObject *object)
{
    DtNetworkManager *self = DT_NETWORK_MANAGER (object);

    g_free (self->client);

    G_OBJECT_CLASS (dt_network_manager_parent_class)->finalize (object);
}

static void
dt_network_manager_class_init (DtNetworkManagerClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->dispose = dt_network_manager_dispose;
    object_class->finalize = dt_network_manager_finalize;
}

static void
dt_network_manager_init (DtNetworkManager *self)
{
    self->client = nm_client_new (NULL, NULL);
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
    //NMClient *client = nm_client_new (NULL, NULL);

    const GPtrArray *connections = nm_client_get_connections (self->client);
    
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
    //NMClient *client = nm_client_new (NULL, NULL);
    
    const GPtrArray *active_connections = 
        nm_client_get_active_connections (self->client);
    
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

    //g_object_unref (client);
    
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
    //NMClient *client = nm_client_new (NULL, NULL);

    const gboolean is_active = 
        dt_network_manager_is_connection_active (self,
                                                connection);

    if (is_active)
    {
        printf("Active connection was asked to be toggled off");

        NMActiveConnection *active_connection = 
            dt_network_manager_get_active_connection_by_connection (connection);

        nm_client_deactivate_connection_async (self->client,
                                               active_connection,
                                               NULL,
                                               (GAsyncReadyCallback) dt_network_manager_deactivate_wireguard_callback,
                                               self);
    }

    else if (!is_active)
    {
        g_warning("Inactive connection was asked to be toggled on");

        nm_client_activate_connection_async (self->client,
                                             connection,
                                             NULL,
                                             NULL,
                                             NULL,
                                             (GAsyncReadyCallback) dt_network_manager_activate_wireguard_callback,
                                             self);
    }

    //g_object_unref (client);
}

