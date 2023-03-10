#include <bits/stdc++.h>
#include "undo.h"
using namespace std;

int main() {
    MusicHashTable hashTable;
    PlaylistManager playlistManager;
    PlaybackManager playbackManager;
    UndoStack undoStack;
    int choice;
    do {
        cout 
            << "This is a music player.\n"
            << "Input -1 to undo the last operation.\n"
            << "\nEnter your choice:\n"
            << "0: Music Database\n"
            << "1: Playlist\n"
            << "2: Playback\n"
            << "9: Exit\n";
        
        cin >> choice;
        switch (choice) {
            case 0: {
                int tableChoice;
                do {
                    cout 
                        << "\nEnter your choice:\n"
                        << "0: Search music\n"
                        << "1: Add music\n"
                        << "2: Remove music\n"
                        << "3: Print top 10 musics\n"
                        << "4: Print all musics\n"
                        << "5: Back to Main Menu\n";
                    cin >> tableChoice;

                    switch (tableChoice) {
                        case 0: {
                            string title;
                            cin.ignore();
                            cout << "Enter the title of the music you want to search:\n";
                            getline(cin, title);

                            Music* result = hashTable.search(title);
                            if (result != nullptr) {
                                cout << "Found music: " << result->getTitle()
                                    << " by " << result->getArtist() << " (" << result->getYearRelease() << ")\n";
                            } else {
                                cout << "Music not found.\n";
                            }
                            break;
                        }

                        case 1: {
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
                            hashTable.insert(music);
                            cout << "Music added.\n";
                            undoNode newNode;
                            newNode.choice = "01";
                            newNode.hashTable = &hashTable;
                            newNode.music = music;
                            undoStack.push(&newNode);
                            break;
                        }

                        case 2: {
                            string title;
                            cin.ignore();
                            cout << "Enter the title of the music you want to remove:\n";
                            getline(cin, title);

                            Music* removed = hashTable.remove(title);
                            if (removed != nullptr) {
                                cout << "Music removed.\n";
                            } else {
                                cout << "Music not found.\n";
                            }
                            undoNode newNode;
                            newNode.choice = "02";
                            newNode.hashTable = &hashTable;
                            newNode.music = removed;
                            undoStack.push(&newNode);
                            break;
                        }

                        case 3: {
                            cout << "Top 10 musics:\n";
                            hashTable.printTop10(hashTable);
                            break;
                        }

                        case 4: {
                            cout << "All musics:\n";
                            hashTable.printAllMusic(hashTable);
                            break;
                        }

                        case -1: {
                            undoStack.undo();
                            break;
                        }

                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (tableChoice != 5);
                break;
            }

            case 1: {
                int playlistChoice;
                do {
                    cout 
                        << "\nEnter your choice:\n"
                        << "0: Print playlists\n"
                        << "1: Create playlist\n"
                        << "2: Delete playlist\n"
                        << "3: Select a playlist\n"
                        << "4: Back to Main Menu\n";
                    cin >> playlistChoice;

                    switch (playlistChoice) {
                        case 0: {
                            playlistManager.printPlaylists();
                            break;
                        }

                        case 1: {
                            playlistManager.createPlaylist();
                            undoNode newNode;
                            newNode.choice = "11";
                            newNode.playlistManager = &playlistManager;
                            undoStack.push(&newNode);
                            break;
                        }

                        case 2: {
                            Playlist* deletedPlaylist = playlistManager.deletePlaylist();
                            undoNode newNode;
                            newNode.choice = "12";
                            newNode.playlistManager = &playlistManager;
                            newNode.playlist = deletedPlaylist;
                            undoStack.push(&newNode);
                            break;
                        }

                        case 3: {
                            int playlistIndex;
                            cout << "Enter the index of the playlist you want to select:\n";
                            cin >> playlistIndex;
                            playlistManager.printPlaylistInfo(playlistIndex);
                            Playlist* playlist = playlistManager.getPlaylist(playlistIndex);
                            int playlistMenuChoice;
                            do {
                                cout << "Enter your choice:\n"
                                    << "0: Add a music to this playlist\n"
                                    << "1: Remove a music to this playlist\n"
                                    << "2: Print playlist\n"
                                    << "3: Back to Playlist Menu\n";
                                cin >> playlistMenuChoice;
                                switch (playlistMenuChoice) {
                                    case 0: {
                                        playlistManager.addMusicToPlaylist(hashTable, *playlist);
                                        undoNode newNode;
                                        newNode.choice = "130";
                                        newNode.playlistManager = &playlistManager;
                                        newNode.playlist = playlist;
                                        undoStack.push(&newNode);
                                        break;
                                    }

                                    case 1: {
                                        Music* removedMusic = playlistManager.removeMusicFromPlaylist(*playlist);
                                        undoNode newNode;
                                        newNode.choice = "131";
                                        newNode.playlistManager = &playlistManager;
                                        newNode.playlist = playlist;
                                        newNode.music = removedMusic;
                                        undoStack.push(&newNode);
                                        break;
                                    }

                                    case 2:
                                        playlistManager.printPlaylist(playlistIndex);
                                        break;

                                    case -1: {
                                        undoStack.undo();
                                        break;
                                    }

                                    default:
                                        cout << "Invalid choice. Try again.\n";
                                        break;
                                }
        
                            } while (playlistMenuChoice != 3);
                            break;
                        }

                        case -1: {
                            undoStack.undo();
                            break;
                        }

                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (playlistChoice != 4);
                break;
            }

            case 2: {
                int playbackChoice;
                do {
                    cout 
                        << "\nEnter your choice:\n"
                        << "0: Print playback\n"
                        << "1: Add A Music to Playback\n"
                        << "2: Play A Music from Playback\n"
                        << "3: Add A Playlist to Playback\n"
                        << "9: Back to Main Menu\n";
                    cin >> playbackChoice;

                    switch (playbackChoice) {
                        case 0: {
                            playbackManager.printPlayback();
                            break;
                        }

                        case 1: {
                            playbackManager.addMusic(hashTable);
                            undoNode newNode;
                            newNode.choice = "21";
                            newNode.playbackManager = &playbackManager;
                            undoStack.push(&newNode);
                            break;
                        }

                        case 2: {
                            playbackManager.playMusic();
                            break;
                        }

                        case 3: {
                            int playlistIndex;
                            cout << "Enter the index of the playlist you want to add:\n";
                            cin >> playlistIndex;
                            playlistManager.printPlaylistInfo(playlistIndex);
                            PlaylistNode* playlistHead = playlistManager.getPlaylistHead(playlistIndex);
                            playbackManager.enqueuePlaylist(playlistHead);
                            undoNode newNode;
                            newNode.choice = "23";
                            newNode.playbackManager = &playbackManager;
                            Playlist* playlist = playlistManager.getPlaylist(playlistIndex);
                            newNode.playlist = playlist;
                            undoStack.push(&newNode);
                            break;
                        }

                        case -1: {
                            undoStack.undo();
                            break;
                        }

                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (playbackChoice != 9);
                break;
            }

            case 9: {
                cout << "Goodbye!\n";
                break;
            }
            
            case -1: {
                undoStack.undo();
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 9);
    return 0;
}