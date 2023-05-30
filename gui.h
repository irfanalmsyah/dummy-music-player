#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QString>
#include "undo.h"

class MainMenu : public QWidget
{
    Q_OBJECT

private:
    // data structures
    MusicHashTable musicHashTable;
    PlaylistManager playlistManager;
    PlaybackManager playbackManager;
    Playlist *selectedPlaylist;
    PlaylistNode *selectedPlaylistNode;
    UndoStack undoStack;
    undoNode *undoNodePtr;

    // stacked widget
    QStackedWidget *stackedWidget;

    // main menu widgets
    QLabel *mainMenuLabel;
    QPushButton *mainmenuDatabaseButton;
    QPushButton *mainmenuPlaylistButton;
    QPushButton *mainmenuPlaybackButton;
    QPushButton *mainmenuExitButton;
    QPushButton *mainmenuUndoButton;

    // database menu widgets
    QLabel *databaseLabel;
    QPushButton *databaseSearchButton;
    QPushButton *databaseAddButton;
    QPushButton *databaseRemoveButton;
    QPushButton *databasePrintButton;
    QPushButton *databasePrintAllButton;
    QPushButton *databaseBackButton;

    // search music widgets
    QLabel *searchMusicLabel;
    QLineEdit *searchMusicLineEdit;
    QPushButton *searchMusicButton;
    QPushButton *searchMusicBackButton;

    // add music widgets
    QLabel *addMusicTitleLabel;
    QLineEdit *addMusicTitleLineEdit;
    QLabel *addMusicArtistLabel;
    QLineEdit *addMusicArtistLineEdit;
    QLabel *addMusicYearReleaseLabel;
    QLineEdit *addMusicYearReleaseLineEdit;
    QLabel *addMusicSpotifyLinkLabel;
    QLineEdit *addMusicSpotifyLinkLineEdit;
    QLabel *addMusicDurationLabel;
    QLineEdit *addMusicDurationLineEdit;
    QPushButton *addMusicAddButton;
    QPushButton *addMusicBackButton;

    // remove music widgets
    QLabel *removeMusicLabel;
    QLineEdit *removeMusicLineEdit;
    QPushButton *removeMusicButton;
    QPushButton *removeMusicBackButton;

    // playlist menu widgets
    QLabel *playlistLabel;
    QPushButton *playlistPrintButton;
    QPushButton *playlistCreateButton;
    QPushButton *playlistDeleteButton;
    QPushButton *playlistSelectButton;
    QPushButton *playlistBackButton;

    // create playlist widgets
    QLabel *createPlaylistTitleLabel;
    QLineEdit *createPlaylistTitleLineEdit;
    QLabel *createPlaylistDescriptionLabel;
    QLineEdit *createPlaylistDescriptionLineEdit;
    QPushButton *createPlaylistCreateButton;
    QPushButton *createPlaylistBackButton;

    // Delete playlist widgets
    QLabel *deletePlaylistLabel;
    QLineEdit *deletePlaylistLineEdit;
    QPushButton *deletePlaylistButton;
    QPushButton *deletePlaylistBackButton;

    // Select playlist widgets
    QLabel *selectPlaylistLabel;
    QLineEdit *selectPlaylistLineEdit;
    QPushButton *selectPlaylistButton;
    QPushButton *selectPlaylistBackButton;

    // selected playlist menu widgets
    QLabel *selectedPlaylistLabel;
    QPushButton *selectedPlaylistAddmusicButton;
    QPushButton *selectedPlaylistRemovemusicButton;
    QPushButton *selectedPlaylistPrintButton;
    QPushButton *selectedPlaylistBackButton;

    // add music to playlist widgets
    QLabel *addMusicToPlaylistLabel;
    QLineEdit *addMusicToPlaylistLineEdit;
    QPushButton *addMusicToPlaylistButton;
    QPushButton *addMusicToPlaylistBackButton;

    // remove music from playlist widgets
    QLabel *removeMusicFromPlaylistLabel;
    QLineEdit *removeMusicFromPlaylistLineEdit;
    QPushButton *removeMusicFromPlaylistButton;
    QPushButton *removeMusicFromPlaylistBackButton;

    // playback menu widgets
    QLabel *playbackLabel;
    QPushButton *playbackPrintButton;
    QPushButton *playbackAddMusicButton;
    QPushButton *playbackPlayMusicButton;
    QPushButton *playbackAddPlaylistButton;
    QPushButton *playbackBackButton;

    // add music to playback widgets
    QLabel *addMusicToPlaybackLabel;
    QLineEdit *addMusicToPlaybackLineEdit;
    QPushButton *addMusicToPlaybackButton;
    QPushButton *addMusicToPlaybackBackButton;

    // add playlist to playback widgets
    QLabel *addPlaylistToPlaybackLabel;
    QLineEdit *addPlaylistToPlaybackLineEdit;
    QPushButton *addPlaylistToPlaybackButton;
    QPushButton *addPlaylistToPlaybackBackButton;

public:
    MainMenu(QWidget *parent = nullptr) : QWidget(parent)
    {
        // create stacked widget
        stackedWidget = new QStackedWidget;

        // create mainmenu widgets
        QWidget *mainMenuWidget = new QWidget;
        mainMenuLabel = new QLabel("Main Menu");
        mainmenuDatabaseButton = new QPushButton("Music Database");
        mainmenuPlaylistButton = new QPushButton("Playlist");
        mainmenuPlaybackButton = new QPushButton("Playback");
        mainmenuExitButton = new QPushButton("Exit");
        mainmenuUndoButton = new QPushButton("Undo");

        // create mainmenu layout
        QVBoxLayout *mainMenuLayout = new QVBoxLayout;
        mainMenuLayout->addWidget(mainMenuLabel);
        mainMenuLayout->addWidget(mainmenuDatabaseButton);
        mainMenuLayout->addWidget(mainmenuPlaylistButton);
        mainMenuLayout->addWidget(mainmenuPlaybackButton);
        mainMenuLayout->addWidget(mainmenuExitButton);
        mainMenuLayout->addWidget(mainmenuUndoButton);
        mainMenuWidget->setLayout(mainMenuLayout);

        // create database widgets
        QWidget *databaseWidget = new QWidget;
        databaseLabel = new QLabel("Database");
        databaseSearchButton = new QPushButton("Search music");
        databaseAddButton = new QPushButton("Add music");
        databaseRemoveButton = new QPushButton("Remove music");
        databasePrintButton = new QPushButton("Print top 10 musics");
        databasePrintAllButton = new QPushButton("Print all musics");
        databaseBackButton = new QPushButton("Back to main menu");

        // create database layout
        QVBoxLayout *databaseLayout = new QVBoxLayout;
        databaseLayout->addWidget(databaseLabel);
        databaseLayout->addWidget(databaseSearchButton);
        databaseLayout->addWidget(databaseAddButton);
        databaseLayout->addWidget(databaseRemoveButton);
        databaseLayout->addWidget(databasePrintButton);
        databaseLayout->addWidget(databasePrintAllButton);
        databaseLayout->addWidget(databaseBackButton);
        databaseWidget->setLayout(databaseLayout);

        // create search music widgets
        QWidget *searchMusicWidget = new QWidget;
        searchMusicLabel = new QLabel("Enter the title of the music you want to search:");
        searchMusicLineEdit = new QLineEdit;
        searchMusicButton = new QPushButton("Search");
        searchMusicBackButton = new QPushButton("Back to database");

        // create search music layout
        QVBoxLayout *searchMusicLayout = new QVBoxLayout;
        searchMusicLayout->addWidget(searchMusicLabel);
        searchMusicLayout->addWidget(searchMusicLineEdit);
        searchMusicLayout->addWidget(searchMusicButton);
        searchMusicLayout->addWidget(searchMusicBackButton);
        searchMusicWidget->setLayout(searchMusicLayout);

        // create add music widgets
        QWidget *addMusicWidget = new QWidget;
        addMusicTitleLabel = new QLabel("Enter the title of the music you want to add:");
        addMusicTitleLineEdit = new QLineEdit;
        addMusicArtistLabel = new QLabel("Enter the artist of the music you want to add:");
        addMusicArtistLineEdit = new QLineEdit;
        addMusicYearReleaseLabel = new QLabel("Enter the year release of the music you want to add:");
        addMusicYearReleaseLineEdit = new QLineEdit;
        addMusicSpotifyLinkLabel = new QLabel("Enter the spotify link of the music you want to add:");
        addMusicSpotifyLinkLineEdit = new QLineEdit;
        addMusicDurationLabel = new QLabel("Enter the duration of the music you want to add:");
        addMusicDurationLineEdit = new QLineEdit;
        addMusicAddButton = new QPushButton("Add");
        addMusicBackButton = new QPushButton("Back to database");

        // create add music layout
        QVBoxLayout *addMusicLayout = new QVBoxLayout;
        addMusicLayout->addWidget(addMusicTitleLabel);
        addMusicLayout->addWidget(addMusicTitleLineEdit);
        addMusicLayout->addWidget(addMusicArtistLabel);
        addMusicLayout->addWidget(addMusicArtistLineEdit);
        addMusicLayout->addWidget(addMusicYearReleaseLabel);
        addMusicLayout->addWidget(addMusicYearReleaseLineEdit);
        addMusicLayout->addWidget(addMusicSpotifyLinkLabel);
        addMusicLayout->addWidget(addMusicSpotifyLinkLineEdit);
        addMusicLayout->addWidget(addMusicDurationLabel);
        addMusicLayout->addWidget(addMusicDurationLineEdit);
        addMusicLayout->addWidget(addMusicAddButton);
        addMusicLayout->addWidget(addMusicBackButton);
        addMusicWidget->setLayout(addMusicLayout);

        // create remove music widgets
        QWidget *removeMusicWidget = new QWidget;
        removeMusicLabel = new QLabel("Enter the title of the music you want to remove:");
        removeMusicLineEdit = new QLineEdit;
        removeMusicButton = new QPushButton("Remove");
        removeMusicBackButton = new QPushButton("Back to database");

        // create remove music layout
        QVBoxLayout *removeMusicLayout = new QVBoxLayout;
        removeMusicLayout->addWidget(removeMusicLabel);
        removeMusicLayout->addWidget(removeMusicLineEdit);
        removeMusicLayout->addWidget(removeMusicButton);
        removeMusicLayout->addWidget(removeMusicBackButton);
        removeMusicWidget->setLayout(removeMusicLayout);

        // create playlist menu widgets
        QWidget *playlistWidget = new QWidget;
        playlistLabel = new QLabel("Playlist");
        playlistPrintButton = new QPushButton("Print playlists");
        playlistCreateButton = new QPushButton("Create playlist");
        playlistDeleteButton = new QPushButton("Delete playlist");
        playlistSelectButton = new QPushButton("Select a playlist");
        playlistBackButton = new QPushButton("Back to main menu");

        // create playlist menu layout
        QVBoxLayout *playlistLayout = new QVBoxLayout;
        playlistLayout->addWidget(playlistLabel);
        playlistLayout->addWidget(playlistPrintButton);
        playlistLayout->addWidget(playlistCreateButton);
        playlistLayout->addWidget(playlistDeleteButton);
        playlistLayout->addWidget(playlistSelectButton);
        playlistLayout->addWidget(playlistBackButton);
        playlistWidget->setLayout(playlistLayout);

        // create create playlist widgets
        QWidget *createPlaylistWidget = new QWidget;
        createPlaylistTitleLabel = new QLabel("Enter the title of the playlist:");
        createPlaylistTitleLineEdit = new QLineEdit;
        createPlaylistDescriptionLabel = new QLabel("Enter the description of the playlist:");
        createPlaylistDescriptionLineEdit = new QLineEdit;
        createPlaylistCreateButton = new QPushButton("Create");
        createPlaylistBackButton = new QPushButton("Back to playlist menu");

        // create create playlist layout
        QVBoxLayout *createPlaylistLayout = new QVBoxLayout;
        createPlaylistLayout->addWidget(createPlaylistTitleLabel);
        createPlaylistLayout->addWidget(createPlaylistTitleLineEdit);
        createPlaylistLayout->addWidget(createPlaylistDescriptionLabel);
        createPlaylistLayout->addWidget(createPlaylistDescriptionLineEdit);
        createPlaylistLayout->addWidget(createPlaylistCreateButton);
        createPlaylistLayout->addWidget(createPlaylistBackButton);
        createPlaylistWidget->setLayout(createPlaylistLayout);

        // create delete playlist widgets
        QWidget *deletePlaylistWidget = new QWidget;
        deletePlaylistLabel = new QLabel("Enter the index of the playlist you want to delete:");
        deletePlaylistLineEdit = new QLineEdit;
        deletePlaylistButton = new QPushButton("Delete");
        deletePlaylistBackButton = new QPushButton("Back to playlist menu");

        // create delete playlist layout
        QVBoxLayout *deletePlaylistLayout = new QVBoxLayout;
        deletePlaylistLayout->addWidget(deletePlaylistLabel);
        deletePlaylistLayout->addWidget(deletePlaylistLineEdit);
        deletePlaylistLayout->addWidget(deletePlaylistButton);
        deletePlaylistLayout->addWidget(deletePlaylistBackButton);
        deletePlaylistWidget->setLayout(deletePlaylistLayout);

        // create select playlist widgets
        QWidget *selectPlaylistWidget = new QWidget;
        selectPlaylistLabel = new QLabel("Enter the index of the playlist you want to select:");
        selectPlaylistLineEdit = new QLineEdit;
        selectPlaylistButton = new QPushButton("Select");
        selectPlaylistBackButton = new QPushButton("Back to playlist menu");

        // create select playlist layout
        QVBoxLayout *selectPlaylistLayout = new QVBoxLayout;
        selectPlaylistLayout->addWidget(selectPlaylistLabel);
        selectPlaylistLayout->addWidget(selectPlaylistLineEdit);
        selectPlaylistLayout->addWidget(selectPlaylistButton);
        selectPlaylistLayout->addWidget(selectPlaylistBackButton);
        selectPlaylistWidget->setLayout(selectPlaylistLayout);

        // create selected playlist menu widgets
        QWidget *selectedPlaylistWidget = new QWidget;
        selectedPlaylistLabel = new QLabel("");
        selectedPlaylistAddmusicButton = new QPushButton("Add a music to this playlist");
        selectedPlaylistRemovemusicButton = new QPushButton("Remove a music from this playlist");
        selectedPlaylistPrintButton = new QPushButton("Print playlist");
        selectedPlaylistBackButton = new QPushButton("Back to playlist menu");

        // create selected playlist menu layout
        QVBoxLayout *selectedPlaylistLayout = new QVBoxLayout;
        selectedPlaylistLayout->addWidget(selectedPlaylistLabel);
        selectedPlaylistLayout->addWidget(selectedPlaylistAddmusicButton);
        selectedPlaylistLayout->addWidget(selectedPlaylistRemovemusicButton);
        selectedPlaylistLayout->addWidget(selectedPlaylistPrintButton);
        selectedPlaylistLayout->addWidget(selectedPlaylistBackButton);
        selectedPlaylistWidget->setLayout(selectedPlaylistLayout);

        // create add music to playlist widgets
        QWidget *addMusicToPlaylistWidget = new QWidget;
        addMusicToPlaylistLabel = new QLabel("Enter the title of the music you want to add:");
        addMusicToPlaylistLineEdit = new QLineEdit;
        addMusicToPlaylistButton = new QPushButton("Add");
        addMusicToPlaylistBackButton = new QPushButton("Back to selected playlist menu");

        // create add music to playlist layout
        QVBoxLayout *addMusicToPlaylistLayout = new QVBoxLayout;
        addMusicToPlaylistLayout->addWidget(addMusicToPlaylistLabel);
        addMusicToPlaylistLayout->addWidget(addMusicToPlaylistLineEdit);
        addMusicToPlaylistLayout->addWidget(addMusicToPlaylistButton);
        addMusicToPlaylistLayout->addWidget(addMusicToPlaylistBackButton);
        addMusicToPlaylistWidget->setLayout(addMusicToPlaylistLayout);

        // create remove music from playlist widgets
        QWidget *removeMusicFromPlaylistWidget = new QWidget;
        removeMusicFromPlaylistLabel = new QLabel("Enter the title of the music you want to remove:");
        removeMusicFromPlaylistLineEdit = new QLineEdit;
        removeMusicFromPlaylistButton = new QPushButton("Remove");
        removeMusicFromPlaylistBackButton = new QPushButton("Back to selected playlist menu");

        // create remove music from playlist layout
        QVBoxLayout *removeMusicFromPlaylistLayout = new QVBoxLayout;
        removeMusicFromPlaylistLayout->addWidget(removeMusicFromPlaylistLabel);
        removeMusicFromPlaylistLayout->addWidget(removeMusicFromPlaylistLineEdit);
        removeMusicFromPlaylistLayout->addWidget(removeMusicFromPlaylistButton);
        removeMusicFromPlaylistLayout->addWidget(removeMusicFromPlaylistBackButton);
        removeMusicFromPlaylistWidget->setLayout(removeMusicFromPlaylistLayout);

        // create playback menu widgets
        QWidget *playbackWidget = new QWidget;
        playbackLabel = new QLabel("Playback menu");
        playbackPrintButton = new QPushButton("Print playback");
        playbackAddMusicButton = new QPushButton("Add a music to playback");
        playbackPlayMusicButton = new QPushButton("Play a music from playback");
        playbackAddPlaylistButton = new QPushButton("Add a playlist to playback");
        playbackBackButton = new QPushButton("Back to main menu");

        // create playback menu layout
        QVBoxLayout *playbackLayout = new QVBoxLayout;
        playbackLayout->addWidget(playbackLabel);
        playbackLayout->addWidget(playbackPrintButton);
        playbackLayout->addWidget(playbackAddMusicButton);
        playbackLayout->addWidget(playbackPlayMusicButton);
        playbackLayout->addWidget(playbackAddPlaylistButton);
        playbackLayout->addWidget(playbackBackButton);
        playbackWidget->setLayout(playbackLayout);

        // creae add music to playback widgets
        QWidget *addMusicToPlaybackWidget = new QWidget;
        addMusicToPlaybackLabel = new QLabel("Enter the title of the music you want to add:");
        addMusicToPlaybackLineEdit = new QLineEdit;
        addMusicToPlaybackButton = new QPushButton("Add");
        addMusicToPlaybackBackButton = new QPushButton("Back to playback menu");

        // create add music to playback layout
        QVBoxLayout *addMusicToPlaybackLayout = new QVBoxLayout;
        addMusicToPlaybackLayout->addWidget(addMusicToPlaybackLabel);
        addMusicToPlaybackLayout->addWidget(addMusicToPlaybackLineEdit);
        addMusicToPlaybackLayout->addWidget(addMusicToPlaybackButton);
        addMusicToPlaybackLayout->addWidget(addMusicToPlaybackBackButton);
        addMusicToPlaybackWidget->setLayout(addMusicToPlaybackLayout);

        // create add playlist to playback widgets
        QWidget *addPlaylistToPlaybackWidget = new QWidget;
        addPlaylistToPlaybackLabel = new QLabel("Enter the index of the playlist you want to add:");
        addPlaylistToPlaybackLineEdit = new QLineEdit;
        addPlaylistToPlaybackButton = new QPushButton("Add");
        addPlaylistToPlaybackBackButton = new QPushButton("Back to playback menu");

        // create add playlist to playback layout
        QVBoxLayout *addPlaylistToPlaybackLayout = new QVBoxLayout;
        addPlaylistToPlaybackLayout->addWidget(addPlaylistToPlaybackLabel);
        addPlaylistToPlaybackLayout->addWidget(addPlaylistToPlaybackLineEdit);
        addPlaylistToPlaybackLayout->addWidget(addPlaylistToPlaybackButton);
        addPlaylistToPlaybackLayout->addWidget(addPlaylistToPlaybackBackButton);
        addPlaylistToPlaybackWidget->setLayout(addPlaylistToPlaybackLayout);

        // add widgets to stacked widget
        stackedWidget->addWidget(mainMenuWidget);
        stackedWidget->addWidget(databaseWidget);
        stackedWidget->addWidget(searchMusicWidget);
        stackedWidget->addWidget(addMusicWidget);
        stackedWidget->addWidget(removeMusicWidget);
        stackedWidget->addWidget(playlistWidget);
        stackedWidget->addWidget(createPlaylistWidget);
        stackedWidget->addWidget(deletePlaylistWidget);
        stackedWidget->addWidget(selectPlaylistWidget);
        stackedWidget->addWidget(selectedPlaylistWidget);
        stackedWidget->addWidget(addMusicToPlaylistWidget);
        stackedWidget->addWidget(removeMusicFromPlaylistWidget);
        stackedWidget->addWidget(playbackWidget);
        stackedWidget->addWidget(addMusicToPlaybackWidget);
        stackedWidget->addWidget(addPlaylistToPlaybackWidget);

        // add stacked widget to main layout
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(stackedWidget);
        setLayout(mainLayout);

        // set main layout and window title
        setWindowTitle("Music Player");
        setLayout(mainLayout);

        // main menu connections
        connect(mainmenuDatabaseButton, SIGNAL(clicked()), this, SLOT(goToDatabase()));
        connect(mainmenuPlaylistButton, SIGNAL(clicked()), this, SLOT(goToPlaylist()));
        connect(mainmenuPlaybackButton, SIGNAL(clicked()), this, SLOT(goToPlayback()));
        connect(mainmenuExitButton, SIGNAL(clicked()), this, SLOT(exit()));
        connect(mainmenuUndoButton, SIGNAL(clicked()), this, SLOT(undo()));

        // database menu connections
        connect(databaseSearchButton, SIGNAL(clicked()), this, SLOT(goToSearchMusic()));
        connect(databaseAddButton, SIGNAL(clicked()), this, SLOT(goToAddMusic()));
        connect(databaseRemoveButton, SIGNAL(clicked()), this, SLOT(goToRemoveMusic()));
        connect(databasePrintButton, SIGNAL(clicked()), this, SLOT(printTop10Musics()));
        connect(databasePrintAllButton, SIGNAL(clicked()), this, SLOT(printAllMusics()));
        connect(databaseBackButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));

        // search music connections
        connect(searchMusicButton, SIGNAL(clicked()), this, SLOT(searchMusic()));
        connect(searchMusicBackButton, SIGNAL(clicked()), this, SLOT(goToDatabase()));

        // add music connections
        connect(addMusicBackButton, SIGNAL(clicked()), this, SLOT(goToDatabase()));
        connect(addMusicAddButton, SIGNAL(clicked()), this, SLOT(addMusic()));

        // remove music connections
        connect(removeMusicBackButton, SIGNAL(clicked()), this, SLOT(goToDatabase()));
        connect(removeMusicButton, SIGNAL(clicked()), this, SLOT(removeMusic()));

        // playlist menu connections
        connect(playlistPrintButton, SIGNAL(clicked()), this, SLOT(printPlaylists()));
        connect(playlistCreateButton, SIGNAL(clicked()), this, SLOT(goToCreatePlaylist()));
        connect(playlistDeleteButton, SIGNAL(clicked()), this, SLOT(goToDeletePlaylist()));
        connect(playlistSelectButton, SIGNAL(clicked()), this, SLOT(goToSelectPlaylist()));
        connect(playlistBackButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));

        // create playlist connections
        connect(createPlaylistCreateButton, SIGNAL(clicked()), this, SLOT(createPlaylist()));
        connect(createPlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToPlaylist()));

        // delete playlist connections
        connect(deletePlaylistButton, SIGNAL(clicked()), this, SLOT(deletePlaylist()));
        connect(deletePlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToPlaylist()));

        // select playlist connections
        connect(selectPlaylistButton, SIGNAL(clicked()), this, SLOT(selectPlaylist()));
        connect(selectPlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToPlaylist()));

        // selected playlist menu connections
        connect(selectedPlaylistAddmusicButton, SIGNAL(clicked()), this, SLOT(goToAddMusicToPlaylist()));
        connect(selectedPlaylistRemovemusicButton, SIGNAL(clicked()), this, SLOT(goToRemoveMusicFromPlaylist()));
        connect(selectedPlaylistPrintButton, SIGNAL(clicked()), this, SLOT(printCurrentPlaylist()));
        connect(selectedPlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToPlaylist()));

        // add music to playlist connections
        connect(addMusicToPlaylistButton, SIGNAL(clicked()), this, SLOT(addMusicToPlaylist()));
        connect(addMusicToPlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToSelectedPlaylist()));

        // remove music from playlist connections
        connect(removeMusicFromPlaylistButton, SIGNAL(clicked()), this, SLOT(removeMusicFromPlaylist()));
        connect(removeMusicFromPlaylistBackButton, SIGNAL(clicked()), this, SLOT(goToSelectedPlaylist()));

        // playback menu connections
        connect(playbackPrintButton, SIGNAL(clicked()), this, SLOT(printPlayback()));
        connect(playbackAddMusicButton, SIGNAL(clicked()), this, SLOT(goToAddMusicToPlayback()));
        connect(playbackPlayMusicButton, SIGNAL(clicked()), this, SLOT(playMusicFromPlayback()));
        connect(playbackAddPlaylistButton, SIGNAL(clicked()), this, SLOT(goToAddPlaylistToPlayback()));
        connect(playbackBackButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));

        // add music to playback connections
        connect(addMusicToPlaybackButton, SIGNAL(clicked()), this, SLOT(addMusicToPlayback()));
        connect(addMusicToPlaybackBackButton, SIGNAL(clicked()), this, SLOT(goToPlayback()));

        // add playlist to playback connections
        connect(addPlaylistToPlaybackButton, SIGNAL(clicked()), this, SLOT(addPlaylistToPlayback()));
        connect(addPlaylistToPlaybackBackButton, SIGNAL(clicked()), this, SLOT(goToPlayback()));
    }

public slots:
    // navigation slots
    void goToMainMenu()
    {
        stackedWidget->setCurrentIndex(0);
    }
    void goToDatabase()
    {
        stackedWidget->setCurrentIndex(1);
    }
    void goToSearchMusic()
    {
        stackedWidget->setCurrentIndex(2);
    }
    void goToAddMusic()
    {
        stackedWidget->setCurrentIndex(3);
    }
    void goToRemoveMusic()
    {
        stackedWidget->setCurrentIndex(4);
    }
    void goToPlaylist()
    {
        stackedWidget->setCurrentIndex(5);
    }
    void goToCreatePlaylist()
    {
        stackedWidget->setCurrentIndex(6);
    }
    void goToDeletePlaylist()
    {
        stackedWidget->setCurrentIndex(7);
    }
    void goToSelectPlaylist()
    {
        stackedWidget->setCurrentIndex(8);
    }
    void goToSelectedPlaylist()
    {
        stackedWidget->setCurrentIndex(9);
    }
    void goToAddMusicToPlaylist()
    {
        stackedWidget->setCurrentIndex(10);
    }
    void goToRemoveMusicFromPlaylist()
    {
        stackedWidget->setCurrentIndex(11);
    }
    void goToPlayback()
    {
        stackedWidget->setCurrentIndex(12);
    }
    void goToAddMusicToPlayback()
    {
        stackedWidget->setCurrentIndex(13);
    }
    void goToAddPlaylistToPlayback()
    {
        stackedWidget->setCurrentIndex(14);
    }

    // search music slot
    void searchMusic()
    {
        string title = searchMusicLineEdit->text().toStdString();
        Music *music = musicHashTable.search(title);

        if (music == nullptr)
        {
            QMessageBox::information(this, "Error", "Music not found!");
        }
        else
        {
            string musicInfo = "Title: " + music->getTitle() + "\nArtist: " + music->getArtist() + "\nYear Release: " + to_string(music->getYearRelease()) + "\nSpotify Link: " + music->getSpotifyLink() + "\nDuration: " + music->strDuration();
            QMessageBox::information(this, "Music Info", QString::fromStdString(musicInfo));
        }
    }

    // add music slot
    void addMusic()
    {
        string title = addMusicTitleLineEdit->text().toStdString();
        string artist = addMusicArtistLineEdit->text().toStdString();
        int yearRelease = addMusicYearReleaseLineEdit->text().toInt();
        string spotifyLink = addMusicSpotifyLinkLineEdit->text().toStdString();
        int duration = addMusicDurationLineEdit->text().toInt();

        Music *music = new Music(title, artist, yearRelease, spotifyLink, duration);
        musicHashTable.insert(music);

        undoStack.addUndo(&musicHashTable, music, "01");

        QMessageBox::information(this, "Success", "Music added successfully!");
    }

    // remove music slot
    void removeMusic()
    {
        string title = removeMusicLineEdit->text().toStdString();
        Music *music = musicHashTable.search(title);

        if (music == nullptr)
        {
            QMessageBox::information(this, "Error", "Music not found!");
        }
        else
        {
            music = musicHashTable.remove(title);
            undoStack.addUndo(&musicHashTable, music, "02");
            QMessageBox::information(this, "Success", "Music removed successfully!");
        }
    }

    // print top 10 musics slot
    void printTop10Musics()
    {
        vector<Music *> top10 = musicHashTable.getTop10();
        string message = "";
        for (int i = 0; i < top10.size(); i++)
        {
            message += to_string(i + 1) + ". " + top10[i]->getTitle() + " by " + top10[i]->getArtist() + " (" + to_string(top10[i]->getYearRelease()) + ")\n";
        }
        QMessageBox::information(this, "Top 10 Musics", QString::fromStdString(message));
    }

    // print all musics slot
    void printAllMusics()
    {
        vector<Music *> allMusics = musicHashTable.getAllMusics();
        string message = "";
        for (int i = 0; i < allMusics.size(); i++)
        {
            message += to_string(i + 1) + ". " + allMusics[i]->getTitle() + " by " + allMusics[i]->getArtist() + " (" + to_string(allMusics[i]->getYearRelease()) + ")\n";
        }
        QMessageBox::information(this, "All Musics", QString::fromStdString(message));
    }

    // print playlists slot
    void printPlaylists()
    {
        vector<Playlist> playlists = playlistManager.getPlaylists();
        if (playlists.size() == 0)
        {
            QMessageBox::information(this, "Empty", "No playlists created!");
        }
        else
        {
            string message = "";
            for (int i = 0; i < playlists.size(); i++)
            {
                message += to_string(i + 1) + ". Playlist: " + playlists[i].getTitle() + " - " + playlists[i].getDescription() + "\n";
            }
            QMessageBox::information(this, "Playlists", QString::fromStdString(message));
        }
    }

    // create playlist slot
    void createPlaylist()
    {
        string title = createPlaylistTitleLineEdit->text().toStdString();
        string description = createPlaylistDescriptionLineEdit->text().toStdString();
        Playlist playlist(title, description);
        playlistManager.playlists.push_back(playlist);

        undoStack.addUndo(&playlistManager);

        QMessageBox::information(this, "Success", "Playlist created successfully!");
    }

    // delete playlist slot
    void deletePlaylist()
    {
        int index = deletePlaylistLineEdit->text().toInt();
        vector<Playlist> playlists = playlistManager.getPlaylists();
        if (index < 1 || index > playlists.size())
        {
            QMessageBox::information(this, "Error", "Invalid index!");
        }
        else
        {
            Playlist *deletedPlaylist = &playlistManager.playlists[index - 1];
            playlistManager.playlists.erase(playlistManager.playlists.begin() + index - 1);
            undoStack.addUndo(&playlistManager, deletedPlaylist, "12");
            QMessageBox::information(this, "Success", "Playlist deleted successfully!");
        }
    }

    // select playlist slot
    void selectPlaylist()
    {
        int index = selectPlaylistLineEdit->text().toInt();
        int size = playlistManager.playlists.size();
        if (index < 1 || index > size)
        {
            QMessageBox::information(this, "Error", "Invalid index!");
        }
        else
        {
            selectedPlaylist = &playlistManager.playlists[index - 1];
            string title = selectedPlaylist->getTitle();
            string description = selectedPlaylist->getDescription();

            QString message = QString::fromStdString("Playlist selected: " + title + " - " + description);

            selectedPlaylistLabel->setText(message);
            goToSelectedPlaylist();
        }
    }

    // add music to playlist slot
    void addMusicToPlaylist()
    {
        string title = addMusicToPlaylistLineEdit->text().toStdString();
        Music *result = selectedPlaylist->addMusictoThisPlaylist(title, musicHashTable);
        if (result == nullptr)
        {
            QMessageBox::information(this, "Error", "Music not found!");
        }
        else
        {
            // get music title
            string musicTitle = result->getTitle();
            undoStack.addUndo(&playlistManager, selectedPlaylist, "130");
            QMessageBox::information(this, "Success", QString::fromStdString(musicTitle + " added to playlist!"));
        }
    }

    // remove music from playlist slot
    void removeMusicFromPlaylist()
    {
        string title = removeMusicFromPlaylistLineEdit->text().toStdString();
        Music *result = selectedPlaylist->removeMusicfromThisPlaylist(title);
        if (result == nullptr)
        {
            QMessageBox::information(this, "Error", "Music not found!");
        }
        else
        {
            // get music title
            string musicTitle = result->getTitle();
            undoStack.addUndo(&playlistManager, selectedPlaylist, result);
            QMessageBox::information(this, "Success", QString::fromStdString(musicTitle + " removed from playlist!"));
        }
    }

    // print current playlist slot
    void printCurrentPlaylist()
    {
        int i = 1;
        string message = "";
        PlaylistNode *current = selectedPlaylist->head;
        while (current != nullptr)
        {

            message += to_string(i) + ". " + current->music->getTitle() + " by " + current->music->getArtist() + " (" + to_string(current->music->getYearRelease()) + ")\n";
            current = current->next;
            i++;
        }
        QMessageBox::information(this, "Current Playlist", QString::fromStdString(message));
    }

    // print playbacks slot
    void printPlayback()
    {
        int i = 1;
        string message = "the Playback queue is: \n";
        if (playbackManager.getFront() == nullptr)
        {
            QMessageBox::information(this, "Empty", "No musics in the queue!");
        }
        else
        {
            PlaybackNode *current = playbackManager.getFront();
            while (current != nullptr)
            {
                message += to_string(i) + ". " + current->music->getTitle() + " by " + current->music->getArtist() + " (" + to_string(current->music->getYearRelease()) + ")\n";
                current = current->next;
                i++;
            }
            QMessageBox::information(this, "Playback", QString::fromStdString(message));
        }
    }

    // add music to playback slot
    void addMusicToPlayback()
    {
        string title = addMusicToPlaybackLineEdit->text().toStdString();
        Music *result = playbackManager.addMusictoThisPlayback(title, musicHashTable);
        if (result == nullptr)
        {
            QMessageBox::information(this, "Error", "Music not found!");
        }
        else
        {
            // get music title
            string musicTitle = result->getTitle();
            undoStack.addUndo(&playbackManager);
            QMessageBox::information(this, "Success", QString::fromStdString(musicTitle + " added to playback!"));
        }
    }

    // play music from playback slot
    void playMusicFromPlayback()
    {
        Music *result = playbackManager.playMusicfromThisPlayback();
        if (result == nullptr)
        {
            QMessageBox::information(this, "Error", "No musics in the queue!");
        }
        else
        {
            string musicTitle = result->getTitle();
            string musicArtist = result->getArtist();
            QMessageBox::information(this, "Success", QString::fromStdString("Now playing: " + musicTitle + " - " + musicArtist));
        }
    }

    // add playlist to playback slot
    void addPlaylistToPlayback()
    {
        int index = addPlaylistToPlaybackLineEdit->text().toInt();
        PlaylistNode *playlistHead = playlistManager.playlists[index - 1].head;
        playbackManager.enqueuePlaylist(playlistHead);
        Playlist *addedPlaylist = &playlistManager.playlists[index - 1];
        undoStack.addUndo(&playbackManager, addedPlaylist);
        QMessageBox::information(this, "Success", "Playlist added to playback!");
    }

    // exit slot
    void exit()
    {
        QMessageBox::information(this, "Exit", "Goodbye!");
        QApplication::quit();
    }

    // undo slot
    void undo()
    {
        if (undoStack.isEmpty())
        {
            QMessageBox::information(this, "Error", "No actions to undo!");
        }
        else
        {
            undoNodePtr = undoStack.pop();
            string choice = undoNodePtr->choice;
            // undo add music
            if (choice == "01")
            {
                bool removed = undoNodePtr->hashTable->remove(undoNodePtr->music->title);
                if (removed)
                {
                    QMessageBox::information(this, "Success", "Adding music " + QString::fromStdString(undoNodePtr->music->title) + " is undone.");
                }
                else
                {
                    QMessageBox::information(this, "Error", "Music not found!");
                }
            }

            // undo remove music
            else if (choice == "02")
            {
                undoNodePtr->hashTable->insert(undoNodePtr->music);
                QMessageBox::information(this, "Success", "Removing music " + QString::fromStdString(undoNodePtr->music->title) + " is undone.");
            }

            // undo create playlist
            else if (choice == "11")
            {
                undoNodePtr->playlistManager->playlists.pop_back();
                QMessageBox::information(this, "Success", "Adding playlist is undone.");
            }

            // undo remove playlist
            else if (choice == "12")
            {
                undoNodePtr->playlistManager->playlists.push_back(*undoNodePtr->playlist);
                QMessageBox::information(this, "Success", "Removing playlist is undone.");
            }

            // undo add music to playlist
            else if (choice == "130")
            {
                undoNodePtr->playlist->removeTail();
                QMessageBox::information(this, "Success", "Adding music to playlist is undone.");
            }

            // undo remove music from playlist
            else if (choice == "131")
            {
                undoNodePtr->playlist->setMusic(undoNodePtr->music);
                QMessageBox::information(this, "Success", "Removing music from playlist is undone.");
            }

            // undo add music to playback
            else if (choice == "21")
            {
                undoNodePtr->playbackManager->dequeue();
                QMessageBox::information(this, "Success", "Adding music to playback is undone.");
            }

            // undo add playlist to playback
            else if (choice == "23")
            {
                PlaylistNode *head = undoNodePtr->playlist->head;
                while (head != nullptr)
                {
                    undoNodePtr->playbackManager->dequeue();
                    head = head->next;
                }
                QMessageBox::information(this, "Success", "Adding playlist to playback is undone.");
            }
        }
    }
};