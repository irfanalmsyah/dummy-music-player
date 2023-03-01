#include <bits/stdc++.h>
#include "playback.h"
using namespace std;

int main() {
    MusicHashTable hashTable;
    PlaylistManager playlistManager;
    PlaybackManager playbackManager;
    int choice;
    do {
        cout 
            << "\nEnter your choice:\n"
            << "0: Music Database\n"
            << "1: Playlist\n"
            << "2: Playback\n"
            << "9: Exit\n";
        
        cin >> choice;
        switch (choice) {
            case 0:
                int tableChoice;
                do {
                    cout 
                        << "\nEnter your choice:\n"
                        << "0: Search music\n"
                        << "1: Add music\n"
                        << "2: Remove music\n"
                        << "3: Print top 10 musics\n"
                        << "4: Back to Main Menu\n";
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
                            break;
                        }

                        case 2: {
                            string title;
                            cin.ignore();
                            cout << "Enter the title of the music you want to remove:\n";
                            getline(cin, title);

                            bool removed = hashTable.remove(title);
                            if (removed) {
                                cout << "Music removed.\n";
                            } else {
                                cout << "Music not found.\n";
                            }
                            break;
                        }

                        case 3: {
                            cout << "Top 10 musics:\n";
                            hashTable.printTop10(hashTable);
                            break;
                        }

                        case 4:
                            break;

                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (tableChoice != 4);
                break;

            case 1:
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
                        case 0:
                            playlistManager.printPlaylists();
                            break;

                        case 1: {
                            playlistManager.createPlaylist();
                            break;
                        }

                        case 2: {
                            playlistManager.deletePlaylist();
                            break;
                        }

                        case 3: {
                            int playlistIndex;
                            cout << "Enter the index of the playlist you want to select:\n";
                            cin >> playlistIndex;
                            playlistManager.printPlaylistInfo(playlistIndex);
                            int playlistMenuChoice;
                            do {
                                cout << "Enter your choice:\n"
                                    << "0: Add music\n"
                                    << "1: Remove music\n"
                                    << "2: Print playlist\n"
                                    << "3: Back to Playlist Menu\n";
                                cin >> playlistMenuChoice;
                                switch (playlistMenuChoice) {
                                    case 0: {
                                        playlistManager.addMusicToPlaylist(hashTable, playlistIndex);
                                        break;
                                    }

                                    case 1: {
                                        playlistManager.removeMusicFromPlaylist(playlistIndex);
                                        break;
                                    }

                                    case 2:
                                        playlistManager.printPlaylist(playlistIndex);
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        cout << "Invalid choice. Try again.\n";
                                        break;
                                }
                            } while (playlistMenuChoice != 3);
                            break;
                        }

                        case 4:
                            break;

                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (playlistChoice != 4);
                break;

            case 2:
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
                        case 0:
                            playbackManager.printPlayback();
                            break;

                        case 1: {
                            playbackManager.addMusic(hashTable);
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
                            break;
                        }
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (playbackChoice != 9);
                break;

            case 9:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 9);
    return 0;
}
