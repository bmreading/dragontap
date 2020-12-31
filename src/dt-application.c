#include <gtk/gtk.h>

#include "dt-application.h"
#include "dt-window.h"

struct _DtApplication
{
    GtkApplication parent_instance;
};

G_DEFINE_TYPE (DtApplication, dt_application, GTK_TYPE_APPLICATION);

static void
dt_application_activate (GApplication *app)
{
    DtWindow *window;
    window = dt_window_new (DT_APPLICATION (app));
    gtk_window_present (GTK_WINDOW (window));
}

static void
dt_application_init (DtApplication *app)
{
}

static void
dt_application_class_init (DtApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->activate = dt_application_activate;
}

DtApplication
*dt_application_new (void)
{
    return g_object_new (DT_APPLICATION_TYPE,
                         "application-id",
                         "com.github.bmreading.dragontap",
                         "flags",
                         G_APPLICATION_HANDLES_OPEN,
                         NULL);
}