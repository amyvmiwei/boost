// test_mult_archive_types.cpp 
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdio>
#include <boost/config.hpp>

#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "test_tools.hpp"

// This is a simple class.  It contains a counter of the number
// of objects of this class which have been instantiated.
class A
{
private:
    friend class boost::serialization::access;
    int x;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */){
        ar & BOOST_SERIALIZATION_NVP(x);
    }
public:
    static int count;
    A(){++count;}    // default constructor
    virtual ~A(){--count;}   // default destructor
};


// B is a subclass of A
class B : public A
{
private:
    friend class boost::serialization::access;
    int y;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */){
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
    }
public:
    static int count;
    B() : A() {};
    virtual ~B() {};
};

BOOST_CLASS_EXPORT(A)
BOOST_CLASS_EXPORT(B)

int A::count = 0;

// Run tests by serializing two shared_ptrs into an archive of type
// OARCH, clearing them (deleting the objects) and then reloading the
// objects back from an archive of type OARCH.
template<class OA, class IA>
void test_save_and_load(A * first, A * second)
{
    const char * testfile = tmpnam(NULL);
    BOOST_REQUIRE(NULL != testfile);

    // Save
    {
        std::ofstream os(testfile);
        OA oa(os);
        oa << BOOST_SERIALIZATION_NVP(first);
        oa << BOOST_SERIALIZATION_NVP(second);
    }

    // Clear the pointers, thereby destroying the objects they contain
    first = NULL;
    second = NULL;

    // Load
    {
        std::ifstream is(testfile);
        IA ia(is);
        ia >> BOOST_SERIALIZATION_NVP(first);
        ia >> BOOST_SERIALIZATION_NVP(second);
    }
    BOOST_CHECK(first == second);
	std::remove(testfile);
}

using namespace boost::archive;

// This does the tests
int test_main(int /* argc */, char * /* argv */[])
{
    // Try to save and load pointers to As, to a text archive
    A * a = new A;
    A * a1 = a;
    test_save_and_load<text_oarchive, text_iarchive>(a, a1);

    // Try to save and load pointers to Bs, to a text archive
    B * b = new B;
    B * b1 = b;
    test_save_and_load<text_oarchive, text_iarchive>(b, b1);

    // Try to save and load pointers to As, to an xml archive
    test_save_and_load<xml_oarchive, xml_iarchive>(a, a1);

    // Try to save and load pointers to Bs, to an xml archive
    test_save_and_load<xml_oarchive, xml_iarchive>(b, b1);

    return boost::exit_success;
}
