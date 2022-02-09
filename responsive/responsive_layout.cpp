//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

int kSlot = 10;

int kNumImg = 0;
int kImgX = 0;
int kImgY = 0;
int kImgWidth = 0;
int kImgHeight = 0;
int kHUsedSpace = 0;
int kVUsedSpace = 0;

double kHdHeight = 60.0;
double kHdWidth = 60.0;


void headerLayout(const QRect &r, ResponsiveLabel *label, int status) {
    double numHUnit = 0.0;
    double unitWidth = 0.1 * (r.width() - kSlot);

    if (status == 3) { // horizontal layout
        numHUnit = 1.0;
        kHdWidth = numHUnit * unitWidth - kSlot;
        kHdHeight = 60;
    } else if (status == 4) {
        numHUnit = 1.5;
        kHdWidth = numHUnit * unitWidth - kSlot;
        kHdHeight = 60.0;
    } else if (status == 5) {
        numHUnit = 3.0;
        kHdWidth = numHUnit * unitWidth - kSlot;
        kHdHeight = 60.0;
    } else if (status == 1 || status == 2) { // vertical layout
        kHdWidth = 60.0;
        kHdHeight = 0.20 * (r.height() - kSlot) - kSlot;
    }

    // set menu label
    if (label -> text() ==  kMenu)
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set home label
    else if (label -> text() ==  kHomeLink && (status == 1 || status == 2 || status == 3))
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set search option label
    else if (label -> text() ==  kSOptions && (status == 3 || status == 4))
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set search box label
    else if (label -> text() ==  kSQuery && (status == 3 || status == 4 || status == 5)) {
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             4 * unitWidth - kSlot, kHdHeight);
        kHUsedSpace += (4 - numHUnit) * unitWidth;
    }
    // set search btn label
    else if (label -> text() ==  kSButton)
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set sign in label
    else if (label -> text() ==  kSignIn && (status == 1 || status == 2 || status == 3))
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set shopping basket btn label
    else if (label -> text() ==  kShoppingBasket && status != 5)
        label -> setGeometry(kHUsedSpace + r.x(), kVUsedSpace + r.y(),
                             kHdWidth, kHdHeight);
    // set navigation label
    else if (label -> text() == kNavTabs && status == 3)
        label -> setGeometry(kSlot + r.x(), kHdHeight + 2 * kSlot + r.y(),
                             r.width() - 2 * kSlot, kHdHeight);
    // otherwise: disappear label by moving out of bounds
    else {
        label -> setGeometry (-1, -1, 0, 0);
        return;
    }

    if (status == 3 || status == 4 || status == 5)
        kHUsedSpace += numHUnit * unitWidth;
    else if (status == 1 || status == 2)
        kVUsedSpace = kVUsedSpace + kHdHeight + kSlot;
}



void mainbdLayout (const QRect &r, ResponsiveLabel *label, int status) {
    /** try to modify the numbers of col for corresponding resolution
     * Don't forget to change col size in setGeometry func. and resizeEvent
     * from responsive_window.cpp
     */
    int col = 3, numSlot = col + 1;
    if (status == 1) {
        col = 3;
        numSlot = col + 1;
    } else if (status == 2) {
        col = 2;
        numSlot = col + 1;
    } else if (status == 3) {
        col = 3;
        numSlot = col + 1;
    } else if (status == 4) {
        col = 2;
        numSlot = col + 1;
    } else if (status == 5) {
        col = 1;
        numSlot = col + 1;
    }


    /** set advert, result image, and corresponding description label
     */
    if (label -> text() == kSResultImage) { // result image label
        kImgWidth = (r.width() - numSlot * kSlot) / col;
        kImgX = (kNumImg % col + 1) * kSlot + kNumImg % col *
                (r.width() - numSlot * kSlot) / col + r.x();
        kImgY = (kNumImg / col) * (kSlot + kImgWidth) + kSlot + r.y();
        kImgHeight = kImgWidth / 4 * 3 - kSlot;

        label -> setGeometry(kImgX, kImgY, kImgWidth, kImgHeight);
    } else if (label -> text() == kAdvert) { // advertisement label
        label -> setGeometry(kSlot, kSlot, (r.width() - (numSlot * kSlot)) / col,
                             (r.width() - (numSlot * kSlot)) / col);
        kNumImg++;
    } else if (label -> text() == kSResultText ) { // result text label
        int textX = kImgX;
        int textY = kImgY + kImgHeight + kSlot;
        int textWidth = kImgWidth;
        int textHeight = kImgWidth / 4;

        label -> setGeometry(textX, textY, textWidth, textHeight);
        ++kNumImg;
    }

    /** set backword, forward, page numbers, and footer
     */
    else if (label -> text() == kSBackward ) // backwark btn label
        label -> setGeometry(kSlot + r.x(),
                             kImgY + kImgHeight + (kImgWidth / 4) + (kSlot * 2) + r.y(),
                             60, 60);
    else if (label -> text() == kSForward ) // forward btn label
        label -> setGeometry(r.width() - kSlot - 60 + r.x(),
                             kImgY + kImgHeight + (kImgWidth / 4) + (kSlot * 2) + r.y(),
                             60, 60);
    else if (label -> text() == kPageNumbers) // page numbers label
        label -> setGeometry(2 * kSlot + 60 + r.x(),
                             kImgY + kImgHeight + (kImgWidth / 4) + (kSlot * 2) + r.y(),
                             r.width() - 4 * kSlot - 2 * 60, 60);
    else if (label -> text() == kFooter) // footer label
        label -> setGeometry(kSlot + r.x(),
                             kImgY + kImgHeight + (kImgWidth / 4) + (kSlot * 3) + 60 + r.y(),
                             r.width() - 2 * kSlot, 60);
}



// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r ) { // our layout should fit inside r
    // change the size of header button
    kHdHeight = 60.0;
    kHdWidth = 60.0;

    // Do not change !!!
    kHUsedSpace = kSlot;
    kVUsedSpace = kSlot;
    kNumImg = 0;

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            int status = 1;
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            /** header would be move to left when height of window is smaller
             *  than a row of searching result
             */
            else if (r.width()  >= 768 && // big device (portrait)
                     r.height() < 418)
                status = 1;
            else if (r.width()  <  768 && r.width() >= 482 && // small device (portrait)
                     r.height() < 350)
                status = 2;
            else if (r.width() >= 768) // big device (landscape)
                status = 3;
            else if (r.width() <  768 && r.width() >= 482) // small device (landscape)
                status = 4;
            else if (r.width() <  482) // super small device
                status = 5;

            headerLayout (r, label, status);
            mainbdLayout (r, label, status);
        } catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }

}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {

    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {

    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {

    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {

    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {

    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {

    return QSize(320, 320);
}

ResponsiveLayout::~ResponsiveLayout() {

    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

