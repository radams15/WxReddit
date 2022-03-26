#include <gtk/gtk.h>

#ifdef USE_HANDY

#include <handy.h>

#endif

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

GtkWidget* toolbar_to_headerbar(GtkToolbar* toolbar){
    remove_from_parent(GTK_WIDGET(toolbar));

#ifdef USE_HANDY
    HdyHeaderBar* header = hdy_header_bar_new();
#else
    GtkHeaderBar* header = gtk_header_bar_new();
#endif

    GList *children = gtk_container_get_children(GTK_CONTAINER(toolbar));
    do{
        GtkWidget* child = g_object_ref(children->data);

        remove_from_parent(child);

#ifdef USE_HANDY
        hdy_header_bar_pack_start(header, child);
#else
        gtk_header_bar_pack_start(header, child);
#endif
    }while ((children = g_list_next(children)) != NULL);

#ifdef USE_HANDY
    hdy_header_bar_set_show_close_button(header, TRUE);
    hdy_header_bar_set_title(header, "WxReddit");
#else
    gtk_header_bar_set_show_close_button(header, TRUE);
    gtk_header_bar_set_title(header, "WxReddit");
#endif

    gtk_widget_set_visible(header, TRUE);

    return GTK_WIDGET(header);
}

void tweak(void* window){
    GtkWidget* win = (GtkWidget*) window;

#ifdef USE_HEADERBAR
    GtkToolbar* toolbar = g_object_ref(find_toolbar(win));

    GtkWidget * header = toolbar_to_headerbar(toolbar);

    gtk_window_set_titlebar(GTK_WINDOW(win), header);
#endif
}

void gtk_tweak_setup(){
#ifdef USE_HANDY
    hdy_init();
#endif
}