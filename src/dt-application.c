/**
 * Copyright (C) 2020 Brian Reading
 * 
 * This file is part of DragonTap.
 * 
 * DragonTap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DragonTap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DragonTap.  If not, see <http://www.gnu.org/licenses/>.
 */

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
dt_application_show_about (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       user_data)
{
    GdkPixbuf *app_logo = gdk_pixbuf_new_from_file ("data/icons/hicolor/scalable/apps/dt.svg",
                                                     NULL);

    GdkPixbuf *app_logo_scaled = gdk_pixbuf_scale_simple (app_logo,
                                                          125, 125,
                                                          GDK_INTERP_BILINEAR);

    GtkAboutDialog *about_dialog = GTK_ABOUT_DIALOG (gtk_about_dialog_new ());
    gtk_about_dialog_set_program_name (about_dialog, "DragonTap");
    gtk_about_dialog_set_copyright (about_dialog, "© 2020 Brian Reading");
    gtk_about_dialog_set_license_type (about_dialog, GTK_LICENSE_GPL_3_0),
    gtk_about_dialog_set_logo (about_dialog, app_logo_scaled);
    gtk_about_dialog_set_version (about_dialog, "0.1"),
    gtk_about_dialog_set_comments (about_dialog, "A graphical interface for "
                                                 "WireGuard connections \n"
                                                 "configured by NetworkManager.");

    gtk_dialog_run (GTK_DIALOG (about_dialog));
}

static GActionEntry app_entries[] = {
  { "about", dt_application_show_about, NULL, NULL, NULL }
};

static void
dt_application_init (DtApplication *app)
{
    g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries, G_N_ELEMENTS (app_entries), app);
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