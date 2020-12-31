#include <gtk/gtk.h>

#include "dt-application.h"

int
main (int argc, char *argv[])
{
    return g_application_run (G_APPLICATION (dt_application_new ()), argc, argv);
}