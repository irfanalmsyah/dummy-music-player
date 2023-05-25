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
public:
    string title;
    string description;
    PlaylistNode* head;
    PlaylistNode* tail;
    Playlist(string title, string description) {
        this->title = title;
        this->description = description;
        head = nullptr;
        tail = nullptr;
    }

    string getTitle() const {
        return title;
    }

    void setTitle(string title) {
        this->title = title;
    }

    string getDescription() const {
        return description;
    }

    void setDescription(string description) {
        this->description = description;
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

    void setMusic(Music* music) {
        PlaylistNode* node = new PlaylistNode;
        node->music = music;
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
        cout << "Music added to the playlist: " << music->title << endl;
    }

    Music* removeMusic() {
        string title;
        cin.ignore();
        cout << "Enter the title of the music you want to remove:\n";
        getline(cin, title);
        PlaylistNode* current = head;
        while (current != nullptr) {
            if (current->music->title == title) {
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
                Music* music = current->music;
                delete current;
                cout << "Music removed from the playlist: " << title << endl;
                return music;
            }
            current = current->next;
        }
        cout << "Music not found in the playlist." << endl;
        return nullptr;
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

    void removeTail() {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
    }

    ///playlist gui functions///
    Music* addMusictoThisPlaylist(string title, MusicHashTable& hashTable) {
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
            return result;
        } else {
            return nullptr;
        }
    }

    Music* removeMusicfromThisPlaylist(string title) {
        PlaylistNode* current = head;
        while (current != nullptr) {
            if (current->music->title == title) {
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
                Music* music = current->music;
                delete current;
                return music;
            }
            current = current->next;
        }
        return nullptr;
    }

    vector<Music*> getMusics() {
        vector<Music*> musics;
        PlaylistNode* current = head;
        while (current != nullptr) {
            musics.push_back(current->music);
            current = current->next;
        }
        return musics;
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
            Playlist playlist(title, description);
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

        Playlist* deletePlaylist() {
            int index;
            cout << "Enter the index of the playlist you want to delete:\n";
            cin >> index;
            if (index < 1 || index > playlists.size()) {
                cout << "Invalid index." << endl;
                return nullptr;
            }
            Playlist* playlist = new Playlist(playlists[index - 1]);
            playlists.erase(playlists.begin() + index - 1);
            cout << "Playlist deleted." << endl;
            return playlist;
        }
        void addMusicToPlaylist(MusicHashTable& hashtable, Playlist& playlist) {
            playlist.addMusic(hashtable);
        }

        Music* removeMusicFromPlaylist(Playlist& playlist) {
            return playlist.removeMusic();
        }

        void printPlaylist(int index) {
            playlists[index - 1].printPlaylist();
        }

        void printPlaylistInfo(int index) {
            playlists[index - 1].getPlaylistInfo();
        }

        PlaylistNode* getPlaylistHead(int index) {
            return playlists[index - 1].head;
        }

        Playlist* getPlaylist(int index) {
            return &playlists[index - 1];
        }

        /// playlistmanager gui functions ///
        vector<Playlist> getPlaylists() {
            return playlists;
        }
};