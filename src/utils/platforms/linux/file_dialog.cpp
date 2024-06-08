#include <iostream>
#include <string>
#include <gtk/gtk.h>

// Function to show file dialog and get selected file path
std::string showFileDialog()
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    std::string filename;

    gtk_init(nullptr, nullptr);

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         NULL,
                                         action,
                                         ("_Cancel"),
                                         GTK_RESPONSE_CANCEL,
                                         ("_Open"),
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *file_path;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        file_path = gtk_file_chooser_get_filename(chooser);
        filename = file_path;
        // manage memory
        g_free(file_path);
    }

    gtk_widget_destroy(dialog);
    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }

    return filename;
}
