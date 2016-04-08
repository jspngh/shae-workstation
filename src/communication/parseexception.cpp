#include "parseexception.h"

ParseException::ParseException(QString error, QString message):
    error(error), messageThatFailedToParse(message)
{

}

const char *ParseException::what() const throw()
{
    return QString("Something went wrong during parsing of the message: ").append(this->messageThatFailedToParse).toStdString().c_str();

}

QString ParseException::getError() const
{
    return error;
}

QString ParseException::getMessageThatFailedToParse() const
{
    return messageThatFailedToParse;
}
