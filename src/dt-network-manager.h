// Copyright (C) 2020 Brian Reading
// 
// This file is part of DragonTap.
// 
// DragonTap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// DragonTap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with DragonTap.  If not, see <http://www.gnu.org/licenses/>.

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


