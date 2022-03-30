#pragma once
#include <QtWidgets/qmainwindow.h>
#include <qpixmap.h>
#include <QLabel>

void setLabelTextBox(QLabel* l, const QString a, QColor background, QColor foreground, const int fontSize, bool isBold, bool isItalic, Qt::Alignment alignment);
void clearLabelTextBox(QLabel* l);