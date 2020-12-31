#include "dt-window.h"
#include "dt-application.h"
#include "dt-row.h"
#include "dt-network-manager.h"

#include <gtk/gtk.h>

struct _DtWindow
{
    GtkApplicationWindow parent_instance;

    GtkWidget *list_box;
};

G_DEFINE_TYPE (DtWindow, dt_window, GTK_TYPE_APPLICATION_WINDOW)

static void
dt_window_fill_list_box (DtWindow *self)
{
    DtNetworkManager *network_manager = dt_network_manager_new ();

    GPtrArray *wireguard_connections = 
        dt_network_manager_get_wireguard_connections (network_manager);

    for (int i = 0; i < wireguard_connections[0].len; i++)
    {
        NMConnection *connection = g_ptr_array_index (wireguard_connections, i);
        DtRow *connection_row = dt_row_new (connection);
        
        gtk_list_box_insert (GTK_LIST_BOX (self->list_box), GTK_WIDGET (connection_row), -1);
    }

    g_ptr_array_unref (wireguard_connections);
    g_object_unref (network_manager);

    gtk_widget_show_all (self->list_box);
}

DtWindow
*dt_window_new (DtApplication *app)
{
    return g_object_new (DT_WINDOW_TYPE,
                         "application",
                         app,
                         NULL);
}

static void
dt_window_class_init (DtWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class,
                                           "/com/github/bmreading/dragontap/ui/dt-window.ui");
    
    gtk_widget_class_bind_template_child (widget_class, DtWindow, list_box);
}

static void
dt_window_init (DtWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    dt_window_fill_list_box (self);
}



