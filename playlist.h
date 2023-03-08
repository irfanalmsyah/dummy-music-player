#include <iostream>
#include <string>
#include <vector>
#include "hashTable.h"
using namespace std;

struct PlaylistNode {
    Music* music;
    PlaylistNode* prev;
    PlaylistNode* next;
};

class Playlist {
private:
    string title;
    string description;
    PlaylistNode* head;
    PlaylistNode* tail;
public:
    Playlist() {
        title = "";
        description = "";
        head = nullptr;
        tail = nullptr;
    }

    void setter(string title, string description) {
        this->title = title;
        this->description = description;
    }

    void setHead(PlaylistNode* head) {
        this->head = head;
    }

    void setTail(PlaylistNode* tail) {
        this->tail = tail;
    }

    void addMusic(MusicHashTable& hashTable) {
        string title;
        cin.ignore();
        cout << "Enter the title of the music you want to add:\n";
        getline(cin, title);
        Music* result = hashTable.search(title);
        if (result != NULL) {
            PlaylistNode* node = new PlaylistNode;
            node->music = result;
            node->prev = nullptr;
            node->next = nullptr;
            if (head == nullptr) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                node->prev = tail;
                tail = node;
            }
            cout << "Music added to the playlist: " << title << endl;
        } else {
            cout << "Music not found." << endl;
        }
    }

    void removeMusic() {
        string title;
        cin.ignore();
        cout << "Enter the title of the music you want to remove:\n";
        getline(cin, title);
        PlaylistNode* current = head;
        while (current != nullptr) {
            if (current->music->getTitle() == title) {
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    head = current->next;
                    head->prev = nullptr;
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                cout << "Music removed from the playlist: " << title << endl;
                return;
            }
            current = current->next;
        }
        cout << "Music not found in the playlist." << endl;
    }

    void printPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "Playlist: " << title << " - " << description << endl;
        PlaylistNode* current = head;
        int count = 1;
        while (current != nullptr) {
            current->music->print();
            current = current->next;
            count++;
        }
    }

    void getPlaylistInfo() {
        cout << "Playlist: " << title << " - " << description << endl;
    }

    PlaylistNode *getHead() {
        return head;
    }
    
};

class PlaylistManager {
    public:
        vector<Playlist> playlists;
        Playlist createPlaylist() {
            string title, description;
            cin.ignore();
            cout << "Enter the title of the playlist:\n";
            getline(cin, title);
            cout << "Enter the description of the playlist:\n";
            getline(cin, description);
            Playlist playlist;
            playlist.setter(title, description);
            playlists.push_back(playlist);
            cout << "Playlist created." << endl;
            return playlist;
        }

        void printPlaylists() {
            if (playlists.size() == 0) {
                cout << "No playlist created." << endl;
                return;
            }
            for (int i = 0; i < playlists.size(); i++) {
                cout << i + 1 << ". ";
                playlists[i].getPlaylistInfo();
            }
        }

        Playlist deletePlaylist() {
            int index;
            cout << "Enter the index of the playlist you want to delete:\n";
            cin >> index;
            if (index < 1 || index > playlists.size()) {
                cout << "Invalid index." << endl;
                throw "Invalid index.";
            }
            Playlist playlist = playlists[index - 1];
            playlists.erase(playlists.begin() + index - 1);
            cout << "Playlist deleted." << endl;
            return playlist;
        }

        void addMusicToPlaylist(MusicHashTable& hashTable, int index) {
            if (index < 1 || index > playlists.size()) {
                cout << "Invalid index." << endl;
                return;
            }
            playlists[index - 1].addMusic(hashTable);
        }

        void removeMusicFromPlaylist(int index) {
            if (index < 1 || index > playlists.size()) {
                cout << "Invalid index." << endl;
                return;
            }
            playlists[index - 1].removeMusic();
        }

        void printPlaylist(int index) {
            playlists[index - 1].printPlaylist();
        }

        void printPlaylistInfo(int index) {
            playlists[index - 1].getPlaylistInfo();
        }

        PlaylistNode* getPlaylistHead(int index) {
            return playlists[index - 1].getHead();
        }
};