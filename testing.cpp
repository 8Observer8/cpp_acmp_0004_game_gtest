#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <sstream>

class LogicError : public std::logic_error {
public:

    LogicError( int argument ) : std::logic_error( "" ), m_argument( argument ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    int m_argument;
    std::string m_message;
};

class OutOfRange : public LogicError {
public:

    OutOfRange( int argument, int beginOfRange, int endOfRange ) : LogicError( argument ) {
        std::string str_argument, str_beginOfRange, str_endOfRange;

        str_argument = intToString( argument );
        str_beginOfRange = intToString( beginOfRange );
        str_endOfRange = intToString( endOfRange );

        m_message = "Argument " + str_argument + " doesn't hit in the range [" +
                str_beginOfRange + ", " + str_endOfRange + "]";
    }

private:

    std::string intToString( int number ) {
        std::stringstream stream;
        stream << number;
        return stream.str( );
    }
};

int game( int n )  throw (OutOfRange);

TEST( test001, normalTest ) {
    int input = 0;
    int expected = 99;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = game( input );
                    });
    ASSERT_EQ( expected, actual );
}

TEST( test002, normalTest) {
    int input = 1;
    int expected = 198;

    int actual = 0;
    ASSERT_NO_THROW({
                         actual = game( input );
                     });
    ASSERT_EQ( expected, actual );
}

TEST( test003, normalTest ) {
    int input = 8;
    int expected = 891;

    int actual = 0;
    ASSERT_NO_THROW({
                         actual = game( input );
                     });
    ASSERT_EQ( expected, actual );
}

TEST( test004, normalTest ) {
    int input = 9;
    int expected = 990;

    int actual = 0;
    ASSERT_NO_THROW({
                         actual = game( input );
                     });
    ASSERT_EQ( expected, actual );
}

TEST( test005, exceptionTest) {
    int input = -1;

    ASSERT_THROW({
                     game( input );
                 }, OutOfRange);
}

TEST( test006, exceptionTest ) {
    int input = 10;

    ASSERT_THROW({
                     game( input );
                 }, OutOfRange);
}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}
