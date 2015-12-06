//
// Created by nate on 12/5/15.
//

#ifndef SKELMUD_NODE_H
#define SKELMUD_NODE_H


#include <memory>
#include <map>

class Node {
public:
    Node();
    Node(const std::string &_name) : _name(_name) { }
    std::shared_ptr<Node> GetParent();
    void SetParent(std::shared_ptr<Node> parent);
    std::shared_ptr<Node> GetChild(std::string child_name);
    void AddChild(std::shared_ptr<Node> child);
    void AddChild(std::string name, std::shared_ptr<Node> child);
    std::string GetName();
    void SetName(std::string name);
protected:
    std::shared_ptr<Node> _parent;
    std::map<std::string, std::shared_ptr<Node>> _children;
    std::string _name;
};


#endif //SKELMUD_NODE_H
