//
// Created by nate on 11/13/15.
//

#ifndef SKELMUD_CONNECTION_H
#define SKELMUD_CONNECTION_H

#include <string>
#include <list>
#include "Network.h"
#include "Accounts/Account.h"
#include "States/GameState.h"

class Player;

class GameState;

enum GameStates : short;

class Connection {
public:
    Connection(DataSocket &dataSocket) : dataSocket(dataSocket), id(-1) { }

private:
    void connectionThread();
    DataSocket dataSocket;
    bool is_connected;
    bool state_changed;
    bool m_advanced_prompt;
    int id;
    std::string m_send_buffer;
    std::shared_ptr<GameState> m_state;
    std::list<std::string> m_receive_buffer;
    std::string owner_ip;
    Account account;
    std::string username;
    std::string password;
    std::string character_race;
    std::string character_class;
    std::string character_name;
    int prompt_tick;
    std::string m_prompt;
    bool logged_in;
    std::shared_ptr<Player> m_player;
    int offset;

public:
    Connection();
    void Run();
    void Send(char* output);
    void AddOutput(std::string output);
    void FlushOutput();
    void UpdatePrompt();
    void Close();
    void SetState(const GameStates &connection_state, std::shared_ptr<GameData> game_data);
    std::shared_ptr<GameState> GetState();
    SOCKET GetSocket();
    std::string GetNextReceived();
    std::string GetIP();
    bool IsConnected();
    bool IsStateChanged();
    void ResetStateChanged();
    int GetID();
    void SetID(int connection_id);
    Account GetAccount();
    std::string GetUsername();
    std::string GetPassword();
    void SetAccount(Account account);
    void SetUsername(std::string username);
    void SetPassword(std::string password);
    std::string GetPrompt();
    bool IsPromptTick();
    void SetLoggedIn(bool logged);
    bool IsLoggedIn();
    const std::string &GetCharacterRace() const;
    void SetCharacterRace(const std::string &character_race);
    const std::string &GetCharacterClass() const;
    void SetCharacterClass(const std::string &character_class);
    const std::string &GetCharacterName() const;
    void SetCharacterName(const std::string &character_name);
    void SetPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Player> GetPlayer();
    void AdvancedPrompt(bool state);
};

#endif //SKELMUD_CONNECTION_H
