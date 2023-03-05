#include <iostream>
#include "playback.h"
using namespace std;

struct undoNode {
    string choice;
    Music* music;
    MusicHashTable* hashTable;
    int playlistIndex;
    PlaylistManager* playlistManager;
    PlaybackManager* playbackManager;
    undoNode* next;
};


class UndoStack {
    private:
        undoNode* top;
    
    public:
        UndoStack() {
            top = nullptr;
        }
        
        ~UndoStack() {
            while (top != nullptr) {
                undoNode* temp = top;
                top = top->next;
                delete temp;
            }
        }

        void push(undoNode* newNode) {
            newNode->next = top;
            top = newNode;
        }

        undoNode* pop() {
            if (isEmpty()) {
                cout << "Stack is empty" << endl;
            }
            else {
                undoNode* temp = top;
                top = top->next;
                string choice = temp->choice;
                return temp;
            }
        }

        bool isEmpty() {
            return top == nullptr;
        }

        void printStack() {
            if (isEmpty()) {
                cout << "Stack is empty" << endl;
            }
            else {
                undoNode* temp = top;
                while (temp != nullptr) {
                    cout << temp->choice << endl;
                    temp = temp->next;
                }
            }
        }

        void undo() {
            undoNode* temp = pop();
            string choice = temp->choice;
            if (choice == "01") {
                bool removed = temp->hashTable->remove(temp->music->getTitle());
                cout << removed << endl;
                if (removed) {
                    cout << "Adding music " << temp->music->getTitle() << " is undone." << endl;
                }
                delete temp;
            } else if (choice == "02") {
                temp->hashTable->insert(temp->music);
                cout << "Deleting music " << temp->music->getTitle() << " is undone." << endl;
            } else if (choice == "11") {
                temp->playlistManager->playlists.pop_back();
                cout << "Adding playlist is undone." << endl;
            } else if (choice == "12") {
                // undo delete playlist
            } else if (choice == "130") {
                // undo add music to the selected playlist
            } else if (choice == "131") {
                // undo remove music from the selected playlist
            } else if (choice == "21") {
                // undo add music to the playback queue
            } else if (choice == "23") {
                // undo add playlist too the playback queue
            }
        }
};