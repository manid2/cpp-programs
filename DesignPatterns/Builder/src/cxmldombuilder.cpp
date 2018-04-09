/*
 * cxmldom.cpp
 *
 *  Created on: 22-Jan-2018
 *      Author: Mani Kumar
 */

#include <cxmldombuilder.h>

namespace mani_dp {

// 1. Zone ocr version node
ManiXmlDOMVerionNode::ManiXmlDOMVerionNode(int m, int n) :
      m_Major(m), m_Minor(n) {
}

void ManiXmlDOMVerionNode::setVersion(int m, int n) {
   m_Major = (m >= XML_DEFAULT_MAJOR_VERSION ? m : XML_DEFAULT_MAJOR_VERSION);
   m_Minor = (n >= XML_DEFUALT_MINOR_VERSION ? n : XML_DEFUALT_MINOR_VERSION);
}

XMLString ManiXmlDOMVerionNode::build() {
   std::stringstream ss;
   ss << "\t<"   << XML_DOM_VERSION_NODE << ">\n"
      << "\t\t<" << XML_DOM_VER_MAJOR_NODE << ">" << m_Major << "</" << XML_DOM_VER_MAJOR_NODE << ">\n"
      << "\t\t<" << XML_DOM_VER_MINOR_NODE << ">" << m_Minor << "</" << XML_DOM_VER_MINOR_NODE << ">\n"
      << "\t</"  << XML_DOM_VERSION_NODE << ">\n";
   return ss.str();
}

// 2. Zone ocr info node
ManiXmlDOMInfoNode::ManiXmlDOMInfoNode(XMLString info) :
      m_info(info) {
}

void ManiXmlDOMInfoNode::setInfo(XMLString info) {
   m_info = info;
}

XMLString ManiXmlDOMInfoNode::build() {
   std::stringstream ss;
   ss << "\t<" << m_info << "/>\n";
   return ss.str();
}

// 3. Zone ocr root node
ManiXmlDOMRootNode::ManiXmlDOMRootNode(ManiXmlDOMVerionNode *ver, ManiXmlDOMInfoNode *info) :
      m_verNode(ver), m_infoNode(info) {
}

void ManiXmlDOMRootNode::setVersion(ManiXmlDOMVerionNode &version) {
   m_verNode = &version;
}

void ManiXmlDOMRootNode::setInfo(ManiXmlDOMInfoNode &info) {
   m_infoNode = &info;
}

XMLString ManiXmlDOMRootNode::build() {
   std::stringstream ss;
   ss << "<ManiXml>\n" << m_verNode->build() << m_infoNode->build() << "</ManiXml>";
   return ss.str();
}

// 4. Zone ocr DOM
ManiXmlDOM::ManiXmlDOM(ManiXmlDOMRootNode *root) :
      m_rootNode(root) {
}

void ManiXmlDOM::setRoot(ManiXmlDOMRootNode *root) {
   m_rootNode = root;
}

XMLString ManiXmlDOM::build() {
   return m_rootNode->build();
}

}  // end of namespace mani_dp
