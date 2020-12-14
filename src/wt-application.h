#ifndef WT_APPLICATION_H
#define WT_APPLICATION_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define WT_APPLICATION_TYPE wt_application_get_type ()
G_DECLARE_FINAL_TYPE (WtApplication, wt_application, WT, APPLICATION, GtkApplication)

WtApplication
*wt_application_new (void);

G_END_DECLS
#endif

