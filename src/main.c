#include <gtk/gtk.h>

#include "wt-application.h"

int
main (int argc, char *argv[])
{
    return g_application_run (G_APPLICATION (wt_application_new ()), argc, argv);
}