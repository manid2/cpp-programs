// Parse/serialize presence xml & json stub code
#include "ParseWritePidfData.hh"
#include <strings.h>

namespace ParseWritePidfDataNs {

// xml doc constants
const std::string XML_VERSION("1.0");
const std::string XML_DOC_ENCODING("UTF-8");

//-- pidf writer
PidfWriter::PidfWriter(const PidfData &pidf) : pidfData(pidf)
{
    // TBD: throw error on null
    this->encodeBuf = xmlBufferCreate();
    this->writer = xmlNewTextWriterMemory(encodeBuf, 0);
}

PidfWriter::~PidfWriter()
{
    if (this->encodeBuf)
        xmlBufferFree(this->encodeBuf);
    if (this->writer)
        xmlFreeTextWriter(this->writer);
}

std::string PidfWriter::toXmlString(void) /*const*/
{
    // write example pidf xml data using libxml2
    int return_code = 0;

    // start xml doc
    return_code = xmlTextWriterStartDocument(this->writer, XML_VERSION.c_str(),
                                             XML_DOC_ENCODING.c_str(), NULL);

    return_code = xmlTextWriterStartElement(writer, (xmlChar *) "presence");

    return_code = xmlTextWriterWriteAttribute(
        writer, (xmlChar *) "xmlns", (xmlChar *) "urn:ietf:params:xml:ns:pidf");

    // encode pidf data to xml
    {
        // <dm:note xml:lang="en">Offline</dm:note>
        // write start tag <dm:note>
        return_code = xmlTextWriterStartElementNS(
            this->writer, reinterpret_cast<const xmlChar *>("dm"),
            reinterpret_cast<const xmlChar *>("note"), NULL);

        // write 'xml:lang' attribute <dm:note xml:lang='en'>
        return_code = xmlTextWriterWriteAttributeNS(
            this->writer, reinterpret_cast<const xmlChar *>("xml"),
            reinterpret_cast<const xmlChar *>("lang"), NULL,
            reinterpret_cast<const xmlChar *>(
                this->getPidfData().getNoteLang().c_str()));

        // write content 'Offline'
        return_code = xmlTextWriterWriteRaw(
            this->writer, reinterpret_cast<const xmlChar *>(
                              this->getPidfData().getNote().c_str()));

        // write end tag </dm:note>
        return_code = xmlTextWriterEndElement(this->writer);
    }

    // end xml doc
    return_code = xmlTextWriterEndDocument(this->writer);

    // copy encoded pidf xml to out string
    std::string pidfXmlString(
        reinterpret_cast<const char *>(encodeBuf->content),
        this->encodeBuf->use);
    return pidfXmlString;
}

//-- pidf parser
PidfData PidfParser::pidfData;

PidfParser::PidfParser(const std::string &ps) : pidfString(ps)
{
    // register sax parser callbacks
    this->saxHandler.initialized = XML_SAX2_MAGIC; // force parsing as SAX2.
    this->saxHandler.startElementNs = PidfParser::startElementNs;
    this->saxHandler.endElementNs = PidfParser::endElementNs;
    this->saxHandler.characters = PidfParser::characters;

    this->parser = xmlNewParserCtxt();
    if (this->parser) {
        this->parser->sax = &this->saxHandler;
    }
}

PidfParser::~PidfParser() { xmlCleanupParser(); }

PidfData PidfParser::fromXmlString(void) /*const*/
{
    xmlSAXUserParseMemory(this->parser->sax, this->parser,
                          this->pidfString.c_str(),
                          (int) this->pidfString.size());
    return PidfParser::pidfData;
}

void PidfParser::startElementNs(void *ctx, const xmlChar *name,
                                const xmlChar *prefix, const xmlChar *URI,
                                int nb_namespaces, const xmlChar **namespaces,
                                int nb_attributes, int nb_defaulted,
                                const xmlChar **atts)
{
    // if 'dm:note' start tag
    if (strcasecmp((const char *) name, "note") == 0) {
        // extract 'xml:lang' attribute from 'note' element
        if (atts) {
            /* Refer
             *   specification:
             * http://xmlsoft.org/html/libxml-parser.html#startElementNsSAX2Func
             *   sample: https://stackoverflow.com/a/25688162
             */
            const int fields = 5; // fields in attributes array, => [localname,
                                  // prefix, URI, value, end]
            size_t size = 0;      // attribute value size
            const char **attributes =
                (const char **) atts; // alias to attributes parameter
            for (int i = 0; i < nb_attributes; ++i) {
                const char *localname = attributes[i * fields + 0];
                const char *prefix = attributes[i * fields + 1];
                /* uncomment when used */
                // const char *URI = attributes[i * fields + 2];
                const char *value_start = attributes[i * fields + 3];
                const char *value_end = attributes[i * fields + 4];
                std::string value;
                if (((strcasecmp((char *) prefix, "xml") == 0) &&
                     (strcasecmp((char *) localname, "lang") == 0))) {
                    size = value_end - value_start;
                    value.assign(value_start, size);
                }
                PidfParser::pidfData.setNoteLang(value);
            }
        }
    }
}

void PidfParser::endElementNs(void *ctx, const xmlChar *localname,
                              const xmlChar *prefix, const xmlChar *URI)
{
    // do nothing
}

void PidfParser::characters(void *ctx, const xmlChar *ch, int len)
{
    std::string value(ch, ch + len);
    PidfParser::pidfData.setNote(value);
}

} // namespace ParseWritePidfDataNs
