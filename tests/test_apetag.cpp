#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <stdio.h>
#include <tag.h>
#include <tstringlist.h>
#include <tbytevectorlist.h>
#include <tpropertymap.h>
#include <apetag.h>
#include <tdebug.h>
#include "utils.h"

using namespace std;
using namespace TagLib;

class TestAPETag : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestAPETag);
  CPPUNIT_TEST(testIsEmpty);
  CPPUNIT_TEST(testIsEmpty2);
  CPPUNIT_TEST(testPropertyInterface1);
  CPPUNIT_TEST(testPropertyInterface2);
  CPPUNIT_TEST_SUITE_END();

public:

  void testIsEmpty()
  {
    APE::Tag tag;
    CPPUNIT_ASSERT(tag.isEmpty());
    tag.addValue("COMPOSER", "Mike Oldfield");
    CPPUNIT_ASSERT(!tag.isEmpty());
  }

  void testIsEmpty2()
  {
    APE::Tag tag;
    CPPUNIT_ASSERT(tag.isEmpty());
    tag.setArtist("Mike Oldfield");
    CPPUNIT_ASSERT(!tag.isEmpty());
  }

  void testPropertyInterface1()
  {
	  APE::Tag tag;
	  PropertyMap dict = tag.properties();
	  CPPUNIT_ASSERT(dict.isEmpty());
	  dict["ARTIST"] = String("artist 1");
	  dict["ARTIST"].append("artist 2");
	  dict["TRACKNUMBER"].append("17");
	  tag.setProperties(dict);
	  CPPUNIT_ASSERT_EQUAL(String("17"), tag.itemListMap()["TRACK"].values()[0]);
	  CPPUNIT_ASSERT_EQUAL(2u, tag.itemListMap()["ARTIST"].values().size());
	  CPPUNIT_ASSERT_EQUAL(String("artist 1"), tag.artist());
	  CPPUNIT_ASSERT_EQUAL(17u, tag.track());
  }

  void testPropertyInterface2()
  {
    APE::Tag tag;
    APE::Item item1 = APE::Item("TRACK", "17");
    tag.setItem("TRACK", item1);

    APE::Item item2 = APE::Item();
    item2.setType(APE::Item::Binary);
    tag.setItem("TESTBINARY", item2);

    PropertyMap properties = tag.properties();
    CPPUNIT_ASSERT_EQUAL(1u, properties.unsupportedData().size());
    CPPUNIT_ASSERT(properties.contains("TRACKNUMBER"));
    CPPUNIT_ASSERT(!properties.contains("TRACK"));
    CPPUNIT_ASSERT(tag.itemListMap().contains("TESTBINARY"));

    tag.removeUnsupportedProperties(properties.unsupportedData());
    CPPUNIT_ASSERT(!tag.itemListMap().contains("TESTBINARY"));

    APE::Item item3 = APE::Item("TRACKNUMBER", "29");
    tag.setItem("TRACKNUMBER", item3);
    properties = tag.properties();
    CPPUNIT_ASSERT_EQUAL(2u, properties["TRACKNUMBER"].size());
    CPPUNIT_ASSERT_EQUAL(String("17"), properties["TRACKNUMBER"][0]);
    CPPUNIT_ASSERT_EQUAL(String("29"), properties["TRACKNUMBER"][1]);

  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestAPETag);

