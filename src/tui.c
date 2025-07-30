#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h> 

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

FILE *log = fopen("/var/log/nbautofix.log", "a");
fprintf(log, "Operation performed: %s\n", operation_name);

/*

void execute_command(const char* cmd) {

    printw("Executing: %s\n", cmd);
    fprintf("Executing: %s\n, &log")
    refresh();
    system(cmd);
}

*/ 
void cleanup_curses() {
    endwin();
}

void show_submenu(const char* title) {
    clear();
    mvprintw(LINES / 2 - 1, COLS / 2 - strlen(title) / 2, "%s", title);
    mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Реализация функционала на этом этапе");
    refresh();
    napms(2000); 
}

int main() {
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    atexit(cleanup_curses);
    curs_set(0);

    
    char *choices[] = {
        "Fix network issues",
        "Fix GUI issues",
        "Other issue type",
        "Install additional tools (like DE)",
        "Install basic tools to recompile kernel",
        "Exit"
    };
    int n_choices = ARRAY_SIZE(choices);

    ITEM **my_items = calloc(n_choices + 1, sizeof(ITEM *));
    for (int i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], "");
    my_items[n_choices] = NULL;

    MENU *my_menu = new_menu(my_items);
    WINDOW *menu_win = newwin(10, 50, (LINES - 10) / 2, (COLS - 50) / 2);
    
    keypad(menu_win, TRUE);
    set_menu_win(my_menu, menu_win);
    set_menu_sub(my_menu, derwin(menu_win, 6, 48, 3, 1));
    set_menu_mark(my_menu, "> ");

    
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, (50 - 10) / 2, "NBAutoFix");
    mvwaddch(menu_win, 2, 0, ACS_LTEE);
    mvwhline(menu_win, 2, 1, ACS_HLINE, 48);
    mvwaddch(menu_win, 2, 49, ACS_RTEE);

    post_menu(my_menu);
    wrefresh(menu_win);

    
    int c;
    while ((c = wgetch(menu_win)) {
        switch (c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: 
                ITEM *cur = current_item(my_menu);
                int idx = item_index(cur);
                
                if (idx == n_choices - 1) 
                    goto end;
                
                
                switch (idx) {
                    case 0: // Network
                        show_submenu("Сеть: диагностика и исправление");
                        
                        // Switching GENERIC kernel to kernel with integrated drivers 
                        // Checking rc.conf 
                    
                        break;
                    case 1: 
                        show_submenu("Fixing GUI issues");
                        
                        break;
                    case 2: 
                        show_submenu("Other system issues");
          
                        // Analisation logs /var/log/messages and checking packages (cvs checkout)
                    
                        break;
                    case 3: 
                        show_submenu("Install DE");
                        
                        break;
                    case 4: 
                        show_submenu("Kernel tools");
                        
                        // Install kernel sources and requirements.  
                        
                        break;
                }
              
                wclear(stdscr);
                refresh();
                post_menu(my_menu);
                wrefresh(menu_win);
                break;
            case 'q':
                goto end;
        }
    }

end:
    unpost_menu(my_menu);
    for (int i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    free_menu(my_menu);
    delwin(menu_win);
    return 0;
}
