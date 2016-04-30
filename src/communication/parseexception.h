#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H
#include <exception>
#include <QString>

/*!
 * \brief The ParseException class, which is trown if something went wrong during parsing of Json string.
 * \ingroup Communication
 */
class ParseException: public std::exception
{
public:
    //! Constructor
    ParseException(QString error, QString message);
    //! the function used to to throw, inherited
    virtual const char *what() const throw();

    //! getter for the error message.
    QString getError() const;

    QString getMessageThatFailedToParse() const;

private:
    QString messageThatFailedToParse = "Something went wrong during parsing of a message";//!< contains the message that failed to parse
    QString error;
};

#endif // PARSEEXCEPTION_H
