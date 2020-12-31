#ifndef DT_WINDOW_H
#define DT_WINDOW_H

#include "dt-application.h"

#include <gtk/gtk.h>

#define DT_WINDOW_TYPE dt_window_get_type ()
G_DECLARE_FINAL_TYPE (DtWindow, dt_window, DT, WINDOW, GtkApplicationWindow)

G_BEGIN_DECLS

DtWindow *dt_window_new (DtApplication *app);

G_END_DECLS

#endif /* DT_WINDOW_H */