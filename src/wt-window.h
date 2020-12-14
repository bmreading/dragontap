#ifndef WT_WINDOW_H
#define WT_WINDOW_H

#include "wt-application.h"

#include <gtk/gtk.h>

#define WT_WINDOW_TYPE wt_window_get_type ()
G_DECLARE_FINAL_TYPE (WtWindow, wt_window, WT, WINDOW, GtkApplicationWindow)

G_BEGIN_DECLS

WtWindow
*wt_window_new (WtApplication *app);

G_END_DECLS

#endif