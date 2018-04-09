/*
 * cxmlbuilder.cpp
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */

#include "cxmlbuilder.h"

namespace mani_dp {

// Xml node, `leaf`
CXmlNode::CXmlNode(const string& name = string()) :
      m_nodeName(name), m_nodeValue("") {
}

CXmlNode CXmlNode::addAttribute(const string& attr, const string& val)
{
   m_attributes[attr] = val;
   return *this;
}

void CXmlNode::addValue(const string& value)
{
   m_nodeValue = value;
   //return *this;
}

void CXmlNode::addChild(CXmlNode child){
	m_children.push_back(child);
	std::cout << "\nAdding: " << child.toString() << endl;
}

void CXmlNode::addChild(const string& name){
	m_children.push_back(CXmlNode(name));
	std::cout << "\nAdding: " << name << endl;
}

CXmlNode CXmlNode::getRootNode() const {
	return (!m_children.empty() ? m_children[0] : CXmlNode(""));
}

string CXmlNode::toString() const {
	string str;
	str = "<" + m_nodeName + map2string(m_attributes) + ">" + m_nodeValue + "</"
			+ m_nodeName + ">";
	return str;
}

string CXmlNode::vec2string() const {
	string str("test ");
	std::cout << "no of children = " << m_children.size() << endl;;
	for (auto&& child : m_children) {
		str += child.toString();
	}
	return str;
}

// Xml builder
CXmlBuilder::CXmlBuilder(const CXmlNode& root) :
      m_RootXmlNode(root), m_CurrentXmlNode(root) {
}

CXmlBuilder::CXmlBuilder(const string& name) {
	m_RootXmlNode = CXmlNode(name);
	m_CurrentXmlNode = m_RootXmlNode;
}

CXmlNode CXmlBuilder::addChild(const string& name) {
	CXmlNode parentNode(m_CurrentXmlNode);
	m_CurrentXmlNode = CXmlNode(name);
	parentNode.addChild(m_CurrentXmlNode);

	std::cout << "--- Adding child node[" << name << "] ---" << endl;
	std::cout << "Root    node: " << m_RootXmlNode.toString() << endl;
	std::cout << "Parent  node: " << parentNode.toString() << endl;
	std::cout << "Current node: " << m_CurrentXmlNode.toString() << endl;
	std::cout << "\n" << endl;

	return m_CurrentXmlNode;
}

CXmlNode CXmlBuilder::build() const {
   return m_CurrentXmlNode.getRootNode();
}

} /* namespace mani_dp */
