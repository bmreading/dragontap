#include "wt-window.h"
#include "wt-application.h"

#include <gtk/gtk.h>

struct _WtWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE (WtWindow, wt_window, GTK_TYPE_APPLICATION_WINDOW)

static void
wt_window_class_init (WtWindowClass *klass)
{
    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass),
                                           "/com/github/wireguard-toggle/ui/wt-window.ui");

}

static void
wt_window_init (WtWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}


WtWindow
*wt_window_new (WtApplication *app)
{
    return g_object_new (WT_WINDOW_TYPE,
                         "application",
                         app,
                         NULL);
}




