#include <iostream>
#include <string>
#include "playlist.h"
using namespace std;

struct PlaybackNode{
    Music* music;
    PlaybackNode* next;
};

class PlaybackManager{
    private:
        PlaybackNode* front;
        PlaybackNode* rear;
    public:
        PlaybackManager() {
            front = NULL;
            rear = NULL;
        }
        void enqueue(Music* music){
            PlaybackNode* newNode = new PlaybackNode;
            newNode->music = music;
            newNode->next = NULL;
            if(front == NULL){
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }
        Music* dequeue(){
            if(front == NULL){
                cout << "Queue is empty" << endl;
                return NULL;
            } else {
                PlaybackNode* temp = front;
                Music* x = temp->music;
                front = front->next;
                delete temp;
                return x;
            }
        }
        void printPlayback(){
            cout << "the Playback queue is:" << endl;
            if (front == NULL) {
                cout << "empty" << endl;
            } else {
                PlaybackNode* temp = front;
                int i = 1;
                while (temp != NULL) {
                    cout << i << ". " << temp->music->getTitle() << " - " << temp->music->getArtist() << endl;
                    temp = temp->next;
                    i++;
                }
                cout << endl;
            }
        }
        void addMusic(MusicHashTable& hashTable){
            string title;
            cin.ignore();
            cout << "Enter the title of the music you want to add:\n";
            getline(cin, title);
            Music* result = hashTable.search(title);
            if (result != NULL) {
                enqueue(result);
                cout << "Music added to the playback: " << title << endl;
            } else {
                cout << "Music not found." << endl;
            }
        }
        void playMusic(){
            Music* x = dequeue();
            if(x != NULL){
                cout << "Now playing: " << x->getTitle() << " - " << x->getArtist() << endl;
            }
        }

        void enqueuePlaylist(PlaylistNode* head){
            PlaylistNode* current = head;
            while (current != nullptr) {
                enqueue(current->music);
                current = current->next;
            }
        }
};