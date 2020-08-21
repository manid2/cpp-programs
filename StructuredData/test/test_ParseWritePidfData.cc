// frn 4115 dummy implementation test code
#include "test_precomp.hh"
#include "ParseWritePidfData.hh"

#include <fstream>

namespace {

//=============================================================================
// test helper functions
//=============================================================================
// TBD: stubs

//=============================================================================
// test_ParseWritePidfData - ParseWritePidfData test fixture
//=============================================================================
// TBD: stubs, required only if initial data is reused across tests

//=============================================================================
// ParseWritePidfData - test cases
//=============================================================================

TEST(ParseWritePidfData_PidfWriter, WriteXml)
{
    // publish-presence-update-presence-source-Offline
    ParseWritePidfDataNs::PidfData pidfData("Offline", "en");
    ParseWritePidfDataNs::PidfWriter pidfWriter(pidfData);
    std::string pidfXmlString(pidfWriter.toXmlString());

    std::ofstream outFile("pidf-data-xml-v0.xml");
    outFile << pidfXmlString;

    SUCCEED() << "pass, out=[" << pidfXmlString << "]" << std::endl;
}

TEST(ParseWritePidfData_PidfParser, ParseXml)
{
    // fetch-presence-of-contact-available
    std::string pidfString("<dm:note xml:lang=\"en\"> Available </dm:note>");
    ParseWritePidfDataNs::PidfParser pidfParser(pidfString);
    ParseWritePidfDataNs::PidfData pidfData(pidfParser.fromXmlString());

    std::stringstream ss;
    ss << "PidfData {"
       << "note=[" << pidfData.getNote() << "], "
       << "noteLang=[" << pidfData.getNoteLang() << "]"
       << "}";
    std::ofstream outFile("pidf-data-text-v0.txt");
    outFile << ss.str();

    SUCCEED() << "pass, out=[" << ss.str() << "]" << std::endl;
}

} // namespace
