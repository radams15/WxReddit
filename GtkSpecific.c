#include <gtk/gtk.h>

GtkToolbar* find_toolbar(GtkWidget* parent){
    if (GTK_IS_TOOLBAR(parent)) {
        return parent;
    }

    if (GTK_IS_BIN(parent)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));

        return find_toolbar(child);
    }

    if (GTK_IS_CONTAINER(parent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        do{
            GtkWidget* widget = find_toolbar(children->data);
            if (widget != NULL) {
                return widget;
            }
        }while ((children = g_list_next(children)) != NULL);
    }

    return NULL;
}

void remove_from_parent(GtkWidget* widget){
    GtkWidget* parent = gtk_widget_get_parent(widget);

    if(GTK_IS_CONTAINER(parent)){
        gtk_container_remove(GTK_CONTAINER(parent), widget);
    }
}

void set_unified_toolbar(void* winptr){
    GtkWidget* win = (GtkWidget*) winptr;

    GtkToolbar* toolbar = g_object_ref(find_toolbar(win));
    remove_from_parent(GTK_WIDGET(toolbar));

    GtkWidget* header = gtk_header_bar_new();

    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), toolbar);

    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);

    gtk_widget_set_visible(toolbar, TRUE);
    gtk_widget_set_visible(header, TRUE);

    gtk_window_set_titlebar(GTK_WINDOW(win), header);

    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Wx Reddit");
}