#include "parseexception_test.h"

ParseException_Test::ParseException_Test()
{

}

void ParseException_Test::initTestCase(){

}

void ParseException_Test::cleanUpTestCase()
{

}

void ParseException_Test::testConstructor()
{
    ParseException e = ParseException("error", "message");
    QVERIFY(e.getError() == "error");
    QVERIFY(e.getMessageThatFailedToParse() == "message");
}


void ParseException_Test::testThrow()
{
    int count =0;
    try{
        throw ParseException("error", "message");
    }
    catch(ParseException e){
        count++;
    }
    QVERIFY(count == 1 );
}
