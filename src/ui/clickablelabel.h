#include <QLabel>

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H


class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel( const QString& text="", int position = 0, QWidget* parent=0 );
    ~ClickableLabel();
signals:
    void clicked(int position);
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    int position;
};
#endif // CLICKABLELABEL_H
