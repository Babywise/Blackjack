#include "helperfunctions.h"

void setLabelTextBox(QLabel* l, const QString a, QColor background, QColor foreground, const int fontSize, bool isBold, bool isItalic, Qt::Alignment alignment)
{
    l->setText(a);
    QPalette p = l->palette();
    /* https://stackoverflow.com/questions/2749798/qlabel-set-color-of-text-and-background */
    l->setAutoFillBackground(true);
    p.setColor(l->backgroundRole(), background);
    p.setColor(l->foregroundRole(), foreground);

    l->setPalette(p);
    QFont f;
    f.setPointSize(fontSize);
    f.setBold(isBold); 
    f.setItalic(isItalic);
    l->setFont(f);
    l->setAlignment(alignment);
}



void clearLabelTextBox(QLabel* l)
{
    l->setText("");
    l->setPalette(*(new QPalette()));

}