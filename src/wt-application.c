#include <gtk/gtk.h>

#include "wt-application.h"
#include "wt-window.h"

struct _WtApplication
{
    GtkApplication parent;
};

G_DEFINE_TYPE (WtApplication, wt_application, GTK_TYPE_APPLICATION);

static void
wt_application_activate (GApplication *app)
{
    WtWindow *window;
    window = wt_window_new (WT_APPLICATION (app));
    gtk_window_present (GTK_WINDOW (window));
}

static void
wt_application_init (WtApplication *app)
{
}

static void
wt_application_class_init (WtApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->activate = wt_application_activate;
}

WtApplication
*wt_application_new (void)
{
    return g_object_new (WT_APPLICATION_TYPE,
                         "application-id",
                         "com.github.wireguard-toggle",
                         "flags",
                         G_APPLICATION_HANDLES_OPEN,
                         NULL);
}