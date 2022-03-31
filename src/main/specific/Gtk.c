#include <gtk/gtk.h>

#ifdef USE_HANDY

#include <handy.h>

#endif

GtkWidget* find_toolbar(GtkWidget* parent){
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

GtkWidget* find_notebook(GtkWidget* parent){
    if (GTK_IS_NOTEBOOK(parent)) {
        return parent;
    }

    if (GTK_IS_BIN(parent)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));

        return find_notebook(child);
    }

    if (GTK_IS_CONTAINER(parent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        do{
            GtkWidget* widget = find_notebook(children->data);
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

GtkWidget* notebook_to_stack_switcher(GtkNotebook* notebook){
    GtkWidget* out = gtk_grid_new();

    remove_from_parent(GTK_WIDGET(notebook));

    GtkStack* stack = GTK_STACK(gtk_stack_new());

    GList *children = gtk_container_get_children(GTK_CONTAINER(notebook));
    do{
        GtkWidget* child = g_object_ref(children->data);

        remove_from_parent(child);

        if(!GTK_IS_BOX(child)){
            printf("A\n");
            gtk_stack_add_titled(stack, child, "nb", "Notebook");
            gtk_widget_set_visible(child, TRUE);
        }

    }while ((children = g_list_next(children)) != NULL);


    GtkStackSwitcher* switcher = GTK_STACK_SWITCHER(gtk_stack_switcher_new());
    gtk_stack_switcher_set_stack(switcher, stack);

    gtk_grid_attach(GTK_GRID(out), switcher, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(out), stack, 0, 1, 1, 1);

    gtk_widget_show_all(GTK_WIDGET(out));
    return GTK_WIDGET(out);
}

void tweak(void* window){
    GtkWidget* win = (GtkWidget*) window;

#ifdef USE_HEADERBAR
    GtkToolbar* toolbar = GTK_TOOLBAR(g_object_ref(find_toolbar(win)));

    GtkWidget * header = toolbar_to_headerbar(toolbar);

    gtk_window_set_titlebar(GTK_WINDOW(win), header);
#endif

#ifdef USE_STACK
    GtkWidget* notebook = g_object_ref(find_notebook(win));
    GtkBox* box = gtk_widget_get_parent(notebook);

    GtkWidget* ss = notebook_to_stack_switcher(GTK_NOTEBOOK(notebook));

    gtk_container_add(GTK_CONTAINER(box), GTK_WIDGET(ss));
#endif
}

void gtk_tweak_setup(){
#ifdef USE_HANDY
    hdy_init();

    hdy_style_manager_set_color_scheme (hdy_style_manager_get_default (),
                                        HDY_COLOR_SCHEME_PREFER_LIGHT);
#endif
}