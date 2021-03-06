//
// Created by nate on 6/12/16.
//

#include "../Skexml/SkexmlParser.h"
#include "../Skexml/Node.h"
#include "SkexmlTest.h"
#include <vector>

void SkexmlTest::go()
{
    std::shared_ptr<Node> node = std::make_shared<Node>("Parent");
    node->AddAttribute("AnAttribute", "First");
    node->AddAttribute("AnotherAttribute", "Second");
    node->AddList("ListOfThings", "One;Two;Three");
    std::vector<std::string> vector_list = {"Four", "Five", "Six"};
    node->AddList("List2", vector_list);
    std::shared_ptr<Node> childNode = std::make_shared<Node>("ChildNode");
    std::shared_ptr<Node> childNode2 = std::make_shared<Node>("ChildNode2");
    childNode->AddAttribute("ChildAttribute", "CHILD");
    childNode2->AddAttribute("ChildAttribute2", "CHILD2");
    std::shared_ptr<Node> childNode3 = std::make_shared<Node>("ChildNode3");
    childNode3->AddAttribute("ThisIsAttribute", "ASDF");
    childNode3->AddAttribute("AnotherAttribute", "FDSA");
    node->AddChild(childNode);
    node->AddChild(childNode2);
    childNode2->AddChild(childNode3);
    SkexmlParser::BuildSkeXML("/home/skelton/SkelMUD/SkelMUD/SkelMUD/Skexml/sample.sml", node);
    std::shared_ptr<Node> out_node = SkexmlParser::Parse("/home/skelton/SkelMUD/SkelMUD/SkelMUD/Skexml/sample.sml");
    Node final = *out_node;
    Node child2 = *final.GetChild("ChildNode2");
    Node test = *final.GetChild("List2");
    auto more_items = final.GetListAttribute("List2");
    auto list_items = final.GetListAttribute("ListOfThings");
    int x = 1;
}