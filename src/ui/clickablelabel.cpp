#include "clickablelabel.h"
#include <QLabel>
#include <QDebug>

ClickableLabel::ClickableLabel(const QString &text, int position, QWidget *parent)
    : QLabel(parent)
{
    setText(text);
    this->position = position;
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked(position);
}

