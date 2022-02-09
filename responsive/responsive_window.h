//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVEWINDOW_H
#define RESPONSIVEWINDOW_H

#include <QWidget>
#include <QScrollArea>

class ResponsiveWindow: public QWidget {

public:
    ResponsiveWindow();

protected:
    void resizeEvent(QResizeEvent *event);
    void createWidgets();

private:
    QScrollArea* scrollArea;
    QWidget* contents;
    int counter;
};


#endif //RESPONSIVEWINDOW_H
