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
    ParseException(QString error, QString message);
    virtual const char *what() const throw();

    QString getError() const;

    QString getMessageThatFailedToParse() const;

private:
    QString messageThatFailedToParse = "Something went wrong during parsing of a message";
    QString error;
};

#endif // PARSEEXCEPTION_H
