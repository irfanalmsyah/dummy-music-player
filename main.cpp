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
            << "This is a music player." << endl
            << "Input -1 to undo the last operation." << endl << endl
            << "Enter your choice:" << endl
            << "0: Music Database" << endl
            << "1: Playlist" << endl
            << "2: Playback" << endl
            << "9: Exit" << endl;
        
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
                            hashTable.searchMusic();
                            break;
                        }

                        case 1: {
                            Music* music = hashTable.addMusic();
                            undoStack.addUndo(&hashTable, music, "01");
                            break;
                        }

                        case 2: {
                            Music* removed = hashTable.removeMusic();
                            undoStack.addUndo(&hashTable, removed, "02");
                            break;
                        }

                        case 3: {
                            hashTable.printTop10(hashTable);
                            break;
                        }

                        case 4: {
                            hashTable.printAllMusic(hashTable);
                            break;
                        }

                        case 5:
                            break;

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
                            undoStack.addUndo(&playlistManager);
                            break;
                        }

                        case 2: {
                            Playlist* deletedPlaylist = playlistManager.deletePlaylist();
                            undoStack.addUndo(&playlistManager, deletedPlaylist, "12");
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
                                    << "1: Remove a music from this playlist\n"
                                    << "2: Print playlist\n"
                                    << "3: Back to Playlist Menu\n";
                                cin >> playlistMenuChoice;
                                switch (playlistMenuChoice) {
                                    case 0: {
                                        playlistManager.addMusicToPlaylist(hashTable, *playlist);
                                        undoStack.addUndo(&playlistManager, playlist, "130");
                                        break;
                                    }

                                    case 1: {
                                        Music* removedMusic = playlistManager.removeMusicFromPlaylist(*playlist);
                                        undoStack.addUndo(&playlistManager, playlist, removedMusic);
                                        break;
                                    }

                                    case 2:
                                        playlistManager.printPlaylist(playlistIndex);
                                        break;

                                    case 3:
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

                        case 4:
                            break;

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
                            undoStack.addUndo(&playbackManager);
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
                            Playlist* playlist = playlistManager.getPlaylist(playlistIndex);
                            undoStack.addUndo(&playbackManager, playlist);
                            break;
                        }

                        case 9:
                            break;

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