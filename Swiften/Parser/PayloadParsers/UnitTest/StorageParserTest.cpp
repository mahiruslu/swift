#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "Swiften/Parser/PayloadParsers/StorageParser.h"
#include "Swiften/Parser/PayloadParsers/UnitTest/PayloadsParserTester.h"

using namespace Swift;

class StorageParserTest : public CppUnit::TestFixture
{
		CPPUNIT_TEST_SUITE(StorageParserTest);
		CPPUNIT_TEST(testParse_Conference);
		CPPUNIT_TEST(testParse_MultipleConferences);
		CPPUNIT_TEST_SUITE_END();

	public:
		StorageParserTest() {}

		void testParse_Conference() {
			PayloadsParserTester parser;

			CPPUNIT_ASSERT(parser.parse(
				"<storage xmlns='storage:bookmarks'>"
					"<conference "
							"name='Council of Oberon' "
							"autojoin='true' jid='council@conference.underhill.org'>"
						"<nick>Puck</nick>"
						"<password>MyPass</password>"
					"</conference>"
				"</storage>"));

			Storage* payload = dynamic_cast<Storage*>(parser.getPayload().get());
			std::vector<Storage::Conference> conferences = payload->getConferences();
			CPPUNIT_ASSERT_EQUAL(1U, conferences.size());
			CPPUNIT_ASSERT_EQUAL(String("Council of Oberon"), conferences[0].name);
			CPPUNIT_ASSERT_EQUAL(JID("council@conference.underhill.org"), conferences[0].jid);
			CPPUNIT_ASSERT(conferences[0].autoJoin);
			CPPUNIT_ASSERT_EQUAL(String("Puck"), conferences[0].nick);
			CPPUNIT_ASSERT_EQUAL(String("MyPass"), conferences[0].password);
		}

		void testParse_MultipleConferences() {
			PayloadsParserTester parser;

			CPPUNIT_ASSERT(parser.parse(
				"<storage xmlns='storage:bookmarks'>"
					"<conference "
							"name='Council of Oberon' "
							"jid='council@conference.underhill.org' />"
					"<conference "
							"name='Tea party' "
							"jid='teaparty@wonderland.lit' />"
				"</storage>"));

			Storage* payload = dynamic_cast<Storage*>(parser.getPayload().get());
			std::vector<Storage::Conference> conferences = payload->getConferences();
			CPPUNIT_ASSERT_EQUAL(2U, conferences.size());
			CPPUNIT_ASSERT_EQUAL(String("Council of Oberon"), conferences[0].name);
			CPPUNIT_ASSERT_EQUAL(JID("council@conference.underhill.org"), conferences[0].jid);
			CPPUNIT_ASSERT_EQUAL(String("Tea party"), conferences[1].name);
			CPPUNIT_ASSERT_EQUAL(JID("teaparty@wonderland.lit"), conferences[1].jid);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(StorageParserTest);
