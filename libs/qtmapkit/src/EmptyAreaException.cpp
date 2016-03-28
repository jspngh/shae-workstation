#include "EmptyAreaException.h"

void EmptyAreaException::raise() const
{
    throw *this;
}

EmptyAreaException* EmptyAreaException::clone() const
{
    return new EmptyAreaException(*this);
}

