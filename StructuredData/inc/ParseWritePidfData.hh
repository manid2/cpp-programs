// Parse/serialize presence xml & json stub code
#ifndef _PARSE_WRITE_PIDF_DATA_H_
#define _PARSE_WRITE_PIDF_DATA_H_

#include <map>
#include <string>
#include <vector>

// libxml2 includes
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>

//#include <nlohmann/json.hpp>

/*
 * Refer:
 * RFC 3863 - Presence Information Data Format (PIDF)
 * https://tools.ietf.org/html/rfc3863
 */
namespace ParseWritePidfDataNs {

//! Pidf data container
class PidfData {
public:
    PidfData(void) = default;
    PidfData(const std::string &n, const std::string &nl) :
        note(n), noteLang(nl)
    {
    }

    // mutator methods
    void setNote(const std::string &n) { this->note = n; }
    std::string getNote(void) const { return this->note; }

    void setNoteLang(const std::string &nl) { this->noteLang = nl; }
    std::string getNoteLang(void) const { return this->noteLang; }

private:
    std::string note;
    std::string noteLang;
};

//! Pidf writer
class PidfWriter {
public:
    PidfWriter(void) = default;
    PidfWriter(const PidfData &pidf);
    virtual ~PidfWriter();

    // mutator methods
    void setPidfData(const PidfData &pd) { this->pidfData = pd; }
    PidfData getPidfData(void) const { return this->pidfData; }

    //! Pidf data to xml string
    std::string toXmlString(void) /*const*/;

private:
    PidfData pidfData;
    // libxml2 data members
    xmlBufferPtr encodeBuf{0};
    xmlTextWriterPtr writer{0};
};

//! Pidf parsr
class PidfParser {
public:
    PidfParser(void) = default;
    PidfParser(const std::string &ps);
    virtual ~PidfParser();

    // mutator methods
    void setPidfString(const std::string &ps) { this->pidfString = ps; }
    std::string getPidfString(void) const { return this->pidfString; }

    //! Xml string to Pidf data
    PidfData fromXmlString(void) /*const*/;

private:
    // xml sax parser callbacks
    static void startElementNs(void *ctx, const xmlChar *localname,
                               const xmlChar *prefix, const xmlChar *URI,
                               int nb_namespaces, const xmlChar **namespaces,
                               int nb_attributes, int nb_defaulted,
                               const xmlChar **attributes);
    static void endElementNs(void *ctx, const xmlChar *localname,
                             const xmlChar *prefix, const xmlChar *URI);
    static void startElement(void *ctx, const xmlChar *name,
                             const xmlChar **atts);
    static void endElement(void *ctx, const xmlChar *name);
    static void characters(void *ctx, const xmlChar *ch, int len);

private:
    std::string pidfString;
    // output from callbacks
    static PidfData pidfData;
    // libxml2 data members
    xmlParserCtxtPtr parser{0};
    xmlSAXHandler saxHandler{0};
};

} // namespace ParseWritePidfDataNs

#endif /* _PARSE_WRITE_PIDF_DATA_H_ */
