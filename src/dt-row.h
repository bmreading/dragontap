#ifndef DT_ROW_H
#define DT_ROW_H

#include <gtk/gtk.h>
#include <NetworkManager.h>

G_BEGIN_DECLS

#define DT_ROW_TYPE dt_row_get_type ()
G_DECLARE_FINAL_TYPE (DtRow, dt_row, DT, ROW, GtkListBoxRow)

DtRow *dt_row_new (NMConnection *connection);

G_END_DECLS

#endif /* DT_ROW_H */