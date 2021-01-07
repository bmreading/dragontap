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

#include "dt-row.h"
#include "dt-network-manager.h"

struct _DtRow
{
    GtkListBoxRow parent_instance;

    NMConnection *connection;
    GtkLabel *row_label;
    GtkSwitch *on_off_switch;
};

G_DEFINE_TYPE (DtRow, dt_row, GTK_TYPE_LIST_BOX_ROW)

enum 
{
    PROP_0,
    PROP_CONNECTION,
    PROP_LABEL_TEXT,
    PROP_ACTIVE_SWITCH,
    N_PROPS
};

static GParamSpec *properties[N_PROPS];

static void
dt_row_get_property (GObject    *object,
                     guint       prop_id,
                     GValue     *value,
                     GParamSpec *pspec)
{
    DtRow *self = DT_ROW (object);

    switch (prop_id)
    {
        case PROP_CONNECTION:
            g_value_set_object (value, self->connection);
            break;

        case PROP_LABEL_TEXT:
            g_value_set_string (value, gtk_label_get_text (self->row_label));
            break;
        
        case PROP_ACTIVE_SWITCH:
            g_value_set_boolean (value, gtk_switch_get_active (self->on_off_switch));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}

static void
dt_row_set_property (GObject      *object,
                     guint         prop_id,
                     const GValue *value,
                     GParamSpec   *pspec)
{
    DtRow *self = DT_ROW (object);

    switch (prop_id)
    {
        case PROP_CONNECTION:
            self->connection = g_value_dup_object (value);
            break;

        case PROP_LABEL_TEXT:
            gtk_label_set_text (self->row_label, g_value_get_string (value));
            break;
        
        case PROP_ACTIVE_SWITCH:
            gtk_switch_set_active (self->on_off_switch, g_value_get_boolean (value));
            break;
        
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}

static void
dt_row_on_off_switch_state_set_cb (DtRow *self)
{
    DtNetworkManager *network_manager = dt_network_manager_new ();
    dt_network_manager_toggle_wireguard (network_manager, self->connection);
    g_object_unref (network_manager);
}

static void
dt_row_class_init (DtRowClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    object_class->get_property = dt_row_get_property;
    object_class->set_property = dt_row_set_property;

    properties[PROP_CONNECTION] =
        g_param_spec_object ("connection",
                             "Connection",
                             "The NetworkManager Connection associated with the row.",
                             NM_TYPE_CONNECTION,
                             G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

    properties[PROP_LABEL_TEXT] =
        g_param_spec_string ("label-text",
                             "Label text",
                             "The label text displayed inside the row.",
                             "Testing",
                             G_PARAM_READWRITE);

    properties[PROP_ACTIVE_SWITCH] =
        g_param_spec_boolean ("switch-is-active",
                              "Switch is active",
                              "Whether the on/off switch is toggled on.",
                              FALSE,
                              G_PARAM_READWRITE);

    g_object_class_install_properties (object_class,
                                       N_PROPS,
                                       properties);

    gtk_widget_class_set_template_from_resource (widget_class,
                                               "/com/github/bmreading/dragontap/ui/dt-row.ui");

    gtk_widget_class_bind_template_child (widget_class, DtRow, row_label);
    gtk_widget_class_bind_template_child (widget_class, DtRow, on_off_switch);
    gtk_widget_class_bind_template_callback (widget_class, dt_row_on_off_switch_state_set_cb);
}

static void
dt_row_init (DtRow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}

DtRow
*dt_row_new (NMConnection *connection)
{
    // Configure row based-on connection
    DtNetworkManager *network_manager = dt_network_manager_new ();
    gboolean is_active = dt_network_manager_is_connection_active (network_manager, connection);
    const gchar *connection_id = nm_connection_get_id (connection);

    g_object_unref (network_manager);

    return g_object_new (DT_ROW_TYPE,
                         "connection",
                         connection,
                         "label-text",
                         connection_id,
                         "switch-is-active",
                         is_active,
                         NULL);
}
