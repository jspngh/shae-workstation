#include "simplepathalgorithm_test.h"
#include "json_messages_test.h"

/*!
 * \brief main class to allow testing different test classes.
 *
 */
int main(int argc, char** argv)
{
   int status = 0;
   {
      SimplePathAlgorithm_Test tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   {
      Json_Messages_Test tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   return status;
}
