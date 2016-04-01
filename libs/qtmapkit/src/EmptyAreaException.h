#ifndef EMPTYAREAEXCEPTION_H
#define EMPTYAREAEXCEPTION_H

#include <QException>

/*!
 * An exception thrown when an area should be returned, but there is none.
 */
class EmptyAreaException : public QException
{
public:
    void raise() const;
    EmptyAreaException* clone() const;
};

#endif // EMPTYAREAEXCEPTION_H

