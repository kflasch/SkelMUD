#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>
#include <memory>
#include <sstream>

class Planet;

class Player : public Entity {
public:
    Player();

    Player(int player_id, std::string player_name, std::string player_class, std::string player_race);

    Player(int player_id, std::string player_name);

    int GetID();

    void SetID(int id);

    const std::string &GetPlayerName() const;

    void SetPlayerName(const std::string &name);

    const std::string &GetPlayerClass() const;

    void SetPlayerClass(const std::string &character_class);

    const std::string &GetPlayerRace() const;

    void SetPlayerRace(const std::string &race);

    bool IsVisible();

    void SetVisible(const bool visible);

    void AddItem(std::string item);

    void RemoveItem(std::string item);

    void Send(std::string data);

    std::string GetCommData();

    std::map<std::string, int> GetItems();

protected:
    int m_player_id;
    bool m_visible;
    std::string m_player_name;
    std::string m_class;
    std::string m_race;
    std::stringstream m_send_queue;

private:
    std::map<std::string, int> m_items;
};

#endif // PLAYER_H
