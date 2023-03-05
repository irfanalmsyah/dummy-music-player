#include <iostream>
using namespace std;

class Music {
private:
    string title;
    string artist;
    int yearRelease;
    string spotifyLink;
    int duration;
public:
    Music() {}

    Music(string title, string artist, int yearRelease, string spotifyLink, int duration) {
        this->title = title;
        this->artist = artist;
        this->yearRelease = yearRelease;
        this->spotifyLink = spotifyLink;
        this->duration = duration;
    }

    string getTitle() const {
        return title;
    }

    void setTitle(string title) {
        this->title = title;
    }

    string getArtist() const {
        return artist;
    }

    void setArtist(string artist) {
        this->artist = artist;
    }

    int getYearRelease() const {
        return yearRelease;
    }

    void setYearRelease(int yearRelease) {
        this->yearRelease = yearRelease;
    }

    string getSpotifyLink() const {
        return spotifyLink;
    }

    void setSpotifyLink(string spotifyLink) {
        this->spotifyLink = spotifyLink;
    }

    string getDuration() const {
        int minutes = duration / 60;
        int seconds = duration % 60;
        string durationString = to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
        return durationString;
    }

    void setDuration(int duration) {
        this->duration = duration;
    }

    void print() {
        cout << getTitle() << " by " << getArtist() << " (" << getYearRelease() << ")" << endl << "Spotify link: " << getSpotifyLink() << endl << "Duration: " << getDuration()  << endl << endl;
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
        int index = hash(music->getTitle());
        table[index].push_back(music);
    }

    Music* search(string title) const {
        int index = hash(title);
        for (Music* music : table[index]) {
            if (music->getTitle() == title) {
                return music;
            }
        }
        return NULL;
    }

    Music* remove(string title) {
        int index = hash(title);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if ((*it)->getTitle() == title) {
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
};


