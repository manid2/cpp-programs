/*
 * cxmlbuilder.h
 *
 *  Created on: 23-Jan-2018
 *      Author: Mani Kumar
 */

#ifndef BUILDER_CXMLBUILDER_H_
#define BUILDER_CXMLBUILDER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <map>
#include <vector>
#include "tinyxml2.h"
//#include <bits/unique_ptr.h>

using namespace std;
using namespace tinyxml2;

namespace mani_dp {

// Forward declarations
class CXmlNode;
class CXmlBuilder;

typedef std::string string;
typedef std::map<string, string> NodeAttributes;
//typedef std::shared_ptr<CXmlNode*> CXmlNodePtr;
typedef CXmlNode* CXmlNodePtr;

// 1. Create the component "interface"
class CXmlComponent {
public:
	virtual ~CXmlComponent() {};
	virtual string toString() const = 0;
};

// 2. Create the `leaf`
class CXmlNode: public CXmlComponent {
public:
	CXmlNode(const string& name);
	CXmlNode addAttribute(const string& attr, const string& val);
	void addValue(const string& value);
	void addChild(CXmlNode child);
	void addChild(const string& name);
	string toString() const;
	string vec2string() const;
	CXmlNode getRootNode() const;

private:
	NodeAttributes m_attributes;
	string m_nodeName;
	string m_nodeValue;
	vector<CXmlNode> m_children;
};

/*
 * 3. Encapsulate the composite into a Builder [DP].
 * Builds an XML tree
 */
class CXmlBuilder {
public:
   CXmlBuilder(const CXmlNode& xmlNode);
   CXmlBuilder(const string& name);
   virtual ~CXmlBuilder(){};

   CXmlNode addChild(const string& name=string());
   CXmlNode addSibling(const string& name=string());
   CXmlNode addParent(const string& name=string());
   CXmlNode build() const;

private:
   CXmlNode m_CurrentXmlNode;
   CXmlNode m_RootXmlNode;
};

static string map2string(NodeAttributes m) {
   string result;
   for (auto it = m.rbegin(); it != m.rend(); ++it) {
      result += " " + (it->first) + "=" + (it->second) + " ";
   }
   result = result.substr(0, result.size() - 1);
   return result;
}

static void execute() {
	CXmlBuilder builder("Order");
	builder.addChild("Order1");
	builder.addChild("Order2");
	builder.addChild("Order3");
	std::cout << builder.build().vec2string();
}

} /* namespace mani_dp */

#endif /* BUILDER_CXMLBUILDER_H_ */
