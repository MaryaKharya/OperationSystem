#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <set>
#include "TestData.cpp"
#include "../../catch2/catch.hpp"

SCENARIO("Graphic lib tests")
{
	//std::ostringstream out;
    istringstream fileIn("(a|b)*");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.GetTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "01245: 12345 12345 \n12345: 12345 12345 \n");
}

SCENARIO("2")
{
    std::ostringstream out;
    istringstream fileIn("a*|b*");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.GetTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "0134: 123 345 \n123: 123  \n345:  345 \n");
}

SCENARIO("3")
{
    std::ostringstream out;
    istringstream fileIn("a+b+");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "01: 1234  \n1234: 1234 456 \n456:  456 \n");
}

SCENARIO("4")
{
    std::ostringstream out;
    istringstream fileIn("(abc)+");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "012: 34   \n34:  56  \n56:   1278 \n1278: 34   \n");
}

SCENARIO("5")
{
    std::ostringstream out;
    istringstream fileIn("a*c+b*");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "0134: 1234 45679  \n1234: 1234 45679  \n45679:  45679 789 \n789:   789 \n");
}

SCENARIO("6")
{
    std::ostringstream out;
    istringstream fileIn("(a+|b+|c+)+");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "01257: 1234579 1245679 1245789 \n1234579: 1234579 1245679 1245789 \n1245679: 1234579 1245679 1245789 \n1245789: 1234579 1245679 1245789 \n");
}

SCENARIO("7")
{
    std::ostringstream out;
    istringstream fileIn("(a|b)*|a*(a|b)(a|b)");
    ostringstream fileOut;
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    expression.CreateInitialNonDeterministicTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    expression.PrintDeterministicTableWithClosure(fileOut);
    CHECK(fileOut.str() == "0124568911: 1234567891011121315 12345891011121315      \n1234567891011121315: 123456789101112131415 1234589101112131415      \n12345891011121315: 1234589101112131415 1234589101112131415      \n123456789101112131415: 123456789101112131415 1234589101112131415      \n1234589101112131415: 1234589101112131415 1234589101112131415      \n");
}