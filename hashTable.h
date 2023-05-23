#include <iostream>
using namespace std;

class Music {
public:
    string title;
    string artist;
    int yearRelease;
    string spotifyLink;
    int duration;
    
    Music() {}

    Music(string title, string artist, int yearRelease, string spotifyLink, int duration) {
        this->title = title;
        this->artist = artist;
        this->yearRelease = yearRelease;
        this->spotifyLink = spotifyLink;
        this->duration = duration;
    }

    string strDuration() const {
        int minutes = duration / 60;
        int seconds = duration % 60;
        string durationString = to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
        return durationString;
    }

    void print() {
        cout << title << " by " << artist << " (" << yearRelease << ")" << endl 
        << "Spotify link: " << spotifyLink << endl 
        << "Duration: " << strDuration() << endl << endl;
    }
};

const int TABLE_SIZE = 100;

class MusicHashTable {
private:
    vector<Music*> table[TABLE_SIZE];

    int hash(string title) const {
        int hash = 0;
        for (char c : title) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }
public:
    MusicHashTable() {}

    void insert(Music* music) {
        int index = hash(music->title);
        table[index].push_back(music);
    }

    Music* search(string title) const {
        int index = hash(title);
        for (Music* music : table[index]) {
            if (music->title == title) {
                return music;
            }
        }
        return NULL;
    }

    Music* remove(string title) {
        int index = hash(title);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if ((*it)->title == title) {
                Music* music = *it;
                table[index].erase(it);
                return music;
            }
        }
        return nullptr;
    }

    void printTop10(MusicHashTable& hashTable) {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (Music* music : hashTable.table[i]) {
                music->print();
                count++;
                if (count == 10) {
                    return;
                }
            }
        }
    }

    // print all music in the hash table
    void printAllMusic(MusicHashTable& hashTable) {
        int totalMusic = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (Music* music : hashTable.table[i]) {
                music->print();
                totalMusic++;
            }
        }
        cout << "Total music in library: " << totalMusic << endl;
    }


};


