#ifndef VIEW_H
#define VIEW_H

#include "main_window.h"
#include "dialog_input.h"

class View {
public:
    View() {}
    ~View() {}
    
    MainWindow window;
    DialogInput dialog;
};

#endif  // VIEW_H