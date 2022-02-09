//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>




ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811 coursework 2: responsive layouts");
    setMinimumSize(320, 320);
    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::resizeEvent(QResizeEvent *event) {
    // modify slot here
    int slot = 10, col = 1, numSlot, contentsHeight;
    int hdHeight = 60;
    int hdWidth = 60;
    int bottomHeight = 120;


    // Do not change !!!
    int width = this->geometry().width();
    int height = this->geometry().height();
    int saWidth = width - 70;


    if (width >= 768 && height < 418 ) {// big device (portrait)

        if  (saWidth >= 768 && height < 418 )// big device (portrait)
            col = 3;
        else col = 2;
        numSlot = col + 1;
        contentsHeight = ((saWidth - numSlot * slot) / col + slot) *
                         (counter / col + 1) + bottomHeight + 3 * slot;
        contents->setGeometry(0, 0, saWidth, contentsHeight);
        scrollArea->setGeometry(QRect(hdWidth + slot, 0, saWidth, height));

    } else if (width <  768 && width >= 482 && height < 350) {// small device (portrait)

        if (saWidth <  768 && saWidth >= 482 && // small device (portrait)
                height < 350)
            col = 2;
        else col = 1;
        numSlot = col + 1;
        contentsHeight = ((saWidth - numSlot * slot) / col + slot) *
                         (counter / col + 1) + bottomHeight + 3 * slot;
        contents->setGeometry(0, 0, saWidth, contentsHeight);
        scrollArea->setGeometry(QRect(hdWidth + slot, 0, saWidth, height));

    } else if (width >= 768) { // big device (landscape)
        col = 3;
        numSlot = col + 1;
        contentsHeight = ((width - numSlot * slot) / col + slot) *
                         (counter / col + 1) + bottomHeight + 5 * slot;
        contents->setGeometry(0, 0, width, contentsHeight);
        scrollArea->setGeometry(QRect(0, (hdHeight + slot) * 2, width, height - 2 * hdHeight));

    } else if (width <  768 && width >= 482) { // small device (landscape)
        col = 2;
        numSlot = col + 1;
        contentsHeight = ((width - numSlot * slot) / col + slot) *
                         (counter / col + 1) + bottomHeight + 4 * slot;
        contents->setGeometry(0, 0, width, contentsHeight);
        scrollArea->setGeometry(QRect(0, (hdHeight + slot) * 1, width, height - 1 * hdHeight));

    } else if (width <  482) { // super small device
        col = 1;
        numSlot = col + 1;
        contentsHeight = ((width - numSlot * slot) / col + slot) *
                         (counter / col + 1) + bottomHeight + 4 * slot;
        contents->setGeometry(0, 0, width, contentsHeight);
        scrollArea->setGeometry(QRect(0, (hdHeight + slot) * 1, width, height - 1 * hdHeight));
    }
}

void ResponsiveWindow::createWidgets() {
    ResponsiveLayout *rl = new ResponsiveLayout();

    // create scroll area and contents widget
    scrollArea =  new QScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contents = new QWidget(scrollArea);
    scrollArea->setWidget(contents);

    // set a new layout cl for content
    ResponsiveLayout *cl = new ResponsiveLayout();
    contents->setLayout(cl);

    // we might have more than one search results and advert
    // add them in layout cl
    cl->addWidget(new ResponsiveLabel(kAdvert));
    counter = 17;
    for(int i = 0; i < counter; i ++) {
        cl->addWidget(new ResponsiveLabel(kSResultImage));
        cl->addWidget(new ResponsiveLabel(kSResultText));
    }

    // bottom small groups
    cl->addWidget(new ResponsiveLabel(kSBackward));
    cl->addWidget(new ResponsiveLabel(kPageNumbers));
    cl->addWidget(new ResponsiveLabel(kSForward));
    cl->addWidget(new ResponsiveLabel(kFooter));

    // menu
    rl->addWidget(new ResponsiveLabel(kMenu));
    // home
    rl->addWidget(new ResponsiveLabel(kHomeLink));
    // search
    rl->addWidget(new ResponsiveLabel(kSOptions));
    rl->addWidget(new ResponsiveLabel(kSQuery));
    rl->addWidget(new ResponsiveLabel(kSButton));
    // top small groups
    rl->addWidget(new ResponsiveLabel(kSignIn));
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));
    // navigator
    rl->addWidget(new ResponsiveLabel(kNavTabs));

    // scroll area
    rl->addWidget(scrollArea);

    this->setLayout(rl);
}


