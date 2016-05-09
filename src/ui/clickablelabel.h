#include <QLabel>

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

/*!
 * \brief The ClickableLabel class
 * \ingroup Ui
 */
class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    //! \brief Basic constructor for clickable label.
    explicit ClickableLabel( const QString& text="", int position = 0, QWidget* parent=0 );
    //! \brief Basic deconstructor for clickable label.
    ~ClickableLabel();
signals:
    //! \brief Clicked signal with position in queue.
    void clicked(int position);
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    int position;
};
#endif // CLICKABLELABEL_H
