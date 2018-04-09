/*
 * cxmldom.h
 *
 *  Created on: 22-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef BUILDER_INC_CXMLDOM_
#define BUILDER_INC_CXMLDOM_

#include <iostream>
#include <string>
#include <sstream>

namespace mani_dp {

typedef std::string XMLString;

static const unsigned short XML_DEFAULT_MAJOR_VERSION = 1;
static const unsigned short XML_DEFUALT_MINOR_VERSION = 0;

static const XMLString XML_DOM_ROOT_NODE_NAME("<ManiXml></ManiXml>");

static const XMLString XML_DOM_VERSION_NODE("ManiXmlData_version");
static const XMLString XML_DOM_VER_MAJOR_NODE("major");
static const XMLString XML_DOM_VER_MINOR_NODE("minor");

static const XMLString XML_DOM_INFO_NODE("ManiXml_info");

// forward declarations for faster compilations
class ManiXmlDOMRootNode;
class ManiXmlDOMVerionNode;
class ManiXmlDOMInfoNode;

class ManiXmlDOM;
//class ManiXmlDOMBuilder;

// An interface to make the dom nodes
class ManiXmlDomNodeInterface
{
public:
   virtual ~ManiXmlDomNodeInterface(){};
   virtual XMLString build()=0;
};

class ManiXmlDOMVerionNode: public ManiXmlDomNodeInterface {
public:
   ManiXmlDOMVerionNode(int m = XML_DEFAULT_MAJOR_VERSION, int n = XML_DEFUALT_MINOR_VERSION);
   void setVersion(int m, int n);
   XMLString build();
private:
   int m_Major;
   int m_Minor;
};

class ManiXmlDOMInfoNode: public ManiXmlDomNodeInterface {
public:
   ManiXmlDOMInfoNode(XMLString info = XML_DOM_INFO_NODE);
   void setInfo(XMLString info);
   XMLString build();
private:
   XMLString m_info;
};

class ManiXmlDOMRootNode: public ManiXmlDomNodeInterface {
public:
   ManiXmlDOMRootNode(ManiXmlDOMVerionNode *ver, ManiXmlDOMInfoNode *info);
   void setVersion(ManiXmlDOMVerionNode &version);
   void setInfo(ManiXmlDOMInfoNode &info);
   XMLString build();
private:
   ManiXmlDOMVerionNode *m_verNode;
   ManiXmlDOMInfoNode *m_infoNode;
};

class ManiXmlDOM: public ManiXmlDomNodeInterface {
public:
   ManiXmlDOM(ManiXmlDOMRootNode *root);
   void setRoot(ManiXmlDOMRootNode *root);
   XMLString build();
private:
   ManiXmlDOMRootNode *m_rootNode;
};

static void execute()
{
   ManiXmlDOMVerionNode *verNode = new ManiXmlDOMVerionNode(1, 2);
   ManiXmlDOMInfoNode   *infoNode = new ManiXmlDOMInfoNode("Mani_info");
   ManiXmlDOMRootNode *rootNode = new ManiXmlDOMRootNode(verNode, infoNode);

   ManiXmlDOM *xmlDom = new ManiXmlDOM(rootNode);

   XMLString dom(xmlDom->build());
   std::cout << "\nMani DOM sample\n"
             << dom
             << "\n";
}

}  // end of namespace mani_dp

#endif /* BUILDER_INC_CXMLDOM_ */
