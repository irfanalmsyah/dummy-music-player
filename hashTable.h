#include <iostream>
using namespace std;

class Music {
public:
    string title;
    string artist;
    int yearRelease;
    string spotifyLink;
    int duration;

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
    Music* addMusic() {
        string title, artist, spotifyLink;
        int yearRelease, duration;
        cin.ignore();

        cout << "Enter the title of the music:\n";
        getline(cin, title);

        cout << "Enter the name of the artist:\n";
        getline(cin, artist);

        cout << "Enter the year of release:\n";
        cin >> yearRelease;

        cout << "Enter the spotify link:\n";
        cin >> spotifyLink;

        cout << "Enter the duration (in seconds):\n";
        cin >> duration;

        Music* music = new Music(title, artist, yearRelease, spotifyLink, duration);
        insert(music);
        cout << "Music added." << endl;
        return music;
    }

    Music* removeMusic() {
        string title;
        cin.ignore();
        cout << "Enter the title of the music:\n";
        getline(cin, title);
        Music* music = remove(title);
        if (music == nullptr) {
            cout << "Music not found." << endl;
        }
        else {
            cout << "Music removed." << endl;
        }
        return music;
    }

    void searchMusic() {
        string title;
        cin.ignore();
        cout << "Enter the title of the music:\n";
        getline(cin, title);
        Music* music = search(title);
        if (music == nullptr) {
            cout << "Music not found." << endl;
        }
        else {
            cout << "Music found." << endl;
            music->print();
        }
    }

    void printTop10(MusicHashTable& hashTable) {
        int count = 0;
        cout << "Top 10 musics:\n";
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

    void printAllMusic(MusicHashTable& hashTable) {
        int totalMusic = 0;
        cout << "All musics:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (Music* music : hashTable.table[i]) {
                music->print();
                totalMusic++;
            }
        }
        cout << "Total music in library: " << totalMusic << endl;
    }
};


