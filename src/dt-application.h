#ifndef DT_APPLICATION_H
#define DT_APPLICATION_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DT_APPLICATION_TYPE dt_application_get_type ()
G_DECLARE_FINAL_TYPE (DtApplication, dt_application, DT, APPLICATION, GtkApplication)

DtApplication
*dt_application_new (void);

G_END_DECLS

#endif /* DT_APPLICATION_H */

