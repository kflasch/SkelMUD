#include "Game.h"
#include "File.h"
#include "States/PlayingState.h"
#include "States/LoginState.h"
#include "Sender.h"
#include "Format.h"
#include "States/CreateCharacterState.h"
#include "States/BuildingState.h"
#include <iostream>
#include <algorithm>
#include <thread>

#ifndef _WIN32
#include <sstream>
#include <unistd.h>
#include <mutex>

#endif

Game::Game() {
    isRunning = true;
    Logger::Debug("Setting up GameData");
    m_game_data = std::make_shared<GameData>();
    connection_id = 0;
    Logger::Debug("Initializing States");
    initStates();
}

std::mutex Game::game_mutex;

Game::~Game() {

}

void Game::Start() {
    std::thread listener(&Game::listenerThread, this);
    listener.detach();
    std::list<int> disconnected;
    while(isRunning) {
        std::map<int, std::shared_ptr<Connection>> connection_map = m_game_data->GetAllConnections();
        for(auto connection_map_entry : connection_map)
        {
            std::lock_guard<std::mutex> lock(Game::game_mutex);
            std::shared_ptr<Connection> connection = connection_map_entry.second;
            if(!connection->IsConnected())
            {
                m_game_data->EraseConnection(connection->GetID());
                std::stringstream ss;
                ss << connection->GetIP() << " has disconnected (connection dropped)";
                Logger::Info(ss.str());
                continue;
            }
            if(connection->IsPromptTick()) {
                std::shared_ptr<GameState> state = state_map[connection->GetState()];
                connection->SetPrompt(state->GetPrompt(connection));
                Sender::UpdatePrompt(connection);
                //Sender::Send(state->GetPrompt(connection), connection);
//                Sender::Send(Format::SAVE + Format::UP + Format::FRONT_LINE + state->GetPrompt(connection) + Format::RESTORE,
//                             connection);
            }
            std::string received = connection->GetNextReceived();
            Utils::RemoveEndline(received);
            connection->FlushOutput();
            if(received == "")
                continue;
            std::stringstream ss;
            ss << "Received data (" << connection->GetIP() << "): " << received;
            Logger::Debug(ss.str());
            state_map[connection->GetState()]->processInput(received, connection);
            if(connection->IsStateChanged())
            {
                state_map[connection->GetState()]->init(connection);
                connection->ResetStateChanged();
            }
            // Sender::Send("\r\n", connection);
            // Sender::Send(state_map[connection->GetState()]->GetPrompt(connection), connection);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Game::listenerThread() {
    ServerSocket socket(m_game_data->GetConfiguration().GetPort());
    socket.Listen();
    while(isRunning) {
        DataSocket dataSocket = socket.Accept();
        auto connection = std::make_shared<Connection>(dataSocket);
        connection->SetState(USERNAME);
        state_map[USERNAME]->init(connection);
        connection->ResetStateChanged();
        // Sender::Send(connection->GetPrompt(), connection);
        std::lock_guard<std::mutex> guard(Game::game_mutex);
        // TODO: connection_id temporary for debugging
        // TODO: eventually connection_id could increment beyond the size of int
        connection->SetID(connection->GetSocket());
        ++connection_id;
        m_game_data->AddConnection(connection);
        connection->Run();
    }
}

void Game::initStates() {
    state_map[USERNAME] = std::make_shared<LoginState>(m_game_data);
    state_map[PLAYING] = std::make_shared<PlayingState>(m_game_data);
    state_map[CHARACTERCREATION] = std::make_shared<CreateCharacterState>(m_game_data);
    state_map[BUILDING] = std::make_shared<BuildingState>(m_game_data);
}
