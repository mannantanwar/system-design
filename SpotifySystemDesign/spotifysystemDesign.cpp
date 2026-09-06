#include<bits/stdc++.h>
using namespace std;

class Song{
    private :
    string title;
    string artist;
    string path ;
    public:
    Song(string title , string artist , string path){
        this->title = title;
        this->path = path;
        this->artist = artist;
    }
    string getTitle(){
        return this->title;
    }
    void setTitle(string title){
        this->title = title;
    }
    string getArtist(){
        return this->artist;
    }
    void setArtist(string artist){
        this->artist = artist;
    }
    string getPath(){
        return this->path;
    }
    void setPath(string path){
        this->path = path;
    }
};
class Playlist{
    private:
    vector<Song *> songs;
    string name ;
    public:
    void addSong(Song * song){
        songs.push_back(song);
    }
    vector<Song*> getSongs(){
        return this->songs;
    }
    int getSize(){
        return songs.size();
    }
    // will be looking for the other mthodsand tgetters and setters later 

};
class PlaylistManager{
    private:
    PlaylistManager(){

    }
    static PlaylistManager* instance;
    unordered_map<string,Playlist *>playlists;

    public:
    static PlaylistManager * getInstance(){
        return instance;
    }
    void addSongToPlaylist(string name , Song * song){
        if(playlists.count(name)){
            playlists[name]->addSong(song);
        }
        else{
            cout<<" no playlist with given name "<<name <<" exists"<<endl;
        }
    }
    Playlist* getPlaylist(string name){
        if(playlists.count(name))return playlists[name];
        else cout<<" invalid name no playlist exists with such name !!"<<endl;
    }
    void createPlaylist(string name){
        playlists[name]=new Playlist();
        cout<<" playlist added"<<endl;
    }
};
PlaylistManager * PlaylistManager:: instance = new PlaylistManager();

// now tie for the 3rd party output device integrationw ith the help of tehdapter design pattern 
class IAudioOutput{
    public:
    virtual void playSong(Song * song)=0;
};
//3rd party bluetoooh device
class BluetoothAPI{
    public:
    void playSongViaBluetooth(){
        cout<<"playing song via the bluetooth 3rd party API"<<endl;
    }
};
class WiredSpeakerAPI{
    public:
    void playSongViaWiredSpeaker(){
        cout<<"playing song via the wired speaker 3rd party API"<<endl;
    }
};
class HeadphonesAPI{
    public:
    void playSongViaHeadphones(){
        cout<<"playing song via the headphones 3rd party API"<<endl;
    }
};
class BluetoothAdapter: public IAudioOutput{
    private :
    BluetoothAPI * bluetooth;
    public:
    void playSong(Song * song) override {
        cout<<"merging the current code and the thhird part apis code to play the song via bluetooth"<<endl;
    }
};
class WiredSpeakerAdapter: public IAudioOutput{
    private :
    WiredSpeakerAPI * wiredSpeaker;
    public:
    void playSong(Song * song) override {
        cout<<"merging the current code and the thhird party apis code to play the song via wired speaker"<<endl;
    }
};

class HeadphonesAdapter: public IAudioOutput{
    private :
    HeadphonesAPI * headphones;
    public:
    void playSong(Song * song) override {
        cout<<"merging the current code and the thhird part apis code to play the song via headphones"<<endl;
    }
};

// ab ye to bnalia but hume ek class vo bhi to banani pdegi jisme audio putout ka object bheje and song and then us object ke hisaab se runtime pr call hojaye method
class AudioEngine{
    public:
    void playSongOnDevice(IAudioOutput* device, Song * song){
        // ab is device me humne jo bhi adapter  object [ass on kia hoga uska play song method call hojyga ]
        device->playSong(song);
    }
};
// ab humko ek alag se class bhi bnani pdegi  to make the connectio n irght ?? ki pehle to humko device se connect to hona hi pdega then only we would play song on it right ??
// now jab hum likhenge ki connect (Device type ) then jo device type bheja hoga uska connect methods call hojyga and we will get th ebject opf that device type which will be done wit the help of the factory design pattern ;
// first of all lets make the class of the enum ypes which will stpre te all of the dvice types 
class DeviceType {
    private:
    string name;
    DeviceType(string name){
        this->name = name;
    }

    public:
    static DeviceType* const BLUETOOTH;
    static DeviceType* const WIRED;
    static DeviceType* const SPEAKER;
    static DeviceType* const HEADPHONE;

    string getName(){
        return name;
    }
};
DeviceType* const DeviceType::BLUETOOTH = new DeviceType("BLUETOOTH");
DeviceType* const DeviceType::WIRED = new DeviceType("WIREDSPEAKER");
DeviceType* const DeviceType::HEADPHONE = new DeviceType("HEADPHONE");

// now the time for the device manager class that would be managing the connect method which would give us the connecttion to the diveice type we want and would bring us that object of the device upon wheich we will be calling the play song mehtod
class DeviceFactory{
    public :
    IAudioOutput * createDevice(DeviceType * deviceType){
        string name = deviceType->getName();
        if(name =="BLUETOOTH" ){
            return new BluetoothAdapter();
        }
        else if(name == "WIREDSPEAKER"){
            return new WiredSpeakerAdapter();
        }
        else{
            return new HeadphonesAdapter();
        }
    }
};
class DeviceManager{
    private:
    DeviceManager(){};
    static DeviceManager* instance;
    DeviceFactory * factory;
    IAudioOutput * device;    
    public: 
    static DeviceManager * getInstance(){
        return instance;
    }
    IAudioOutput * connect (DeviceType * deviceType){
        if(device)delete this->device;
        cout<< " connecting to the device you mentioned"<<endl;
        this->device = factory->createDevice(deviceType);
    }
    IAudioOutput * getDevice(){
        return this->device;
    }
};
DeviceManager * DeviceManager:: instance =new DeviceManager();

// now time for making the playingstrategy as mentioned it can be sequential , random and the cusom 
class PlayingStrategy{
    public: 
    virtual Song * next()=0;
    virtual bool hasNext()=0;
    virtual bool hasPrev()=0;
    virtual Song * previous()=0;
    virtual void setPlaylist(Playlist * playlist)=0;
};
class SequentialStrategy: public PlayingStrategy{
    private :
    int currentIndex;
    Playlist * currentPlaylist;
    public :
    void setPlaylist(Playlist* playlist){
        this -> currentPlaylist = playlist;
    }
     bool hasNext() override {
        return ((currentIndex + 1) < currentPlaylist->getSize());
    }

    // Next in Loop
    Song* next() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex + 1;
        return currentPlaylist->getSongs()[currentIndex];
    }

    bool hasPrev() override {
        return (currentIndex - 1 > 0);
    }

    // previous in Loop
    Song* previous() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex - 1;
        return currentPlaylist->getSongs()[currentIndex];
    }
};
class RandomStrategy: public PlayingStrategy{
     private :
    int currentIndex;
    Playlist * currentPlaylist;
    public :
    void setPlaylist(Playlist* playlist){
        this -> currentPlaylist = playlist;
    }
     bool hasNext() override {
        return ((currentIndex + 1) < currentPlaylist->getSize());
    }

    // Next in Loop
    Song* next() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex + 1;
        return currentPlaylist->getSongs()[currentIndex];
    }

    bool hasPrev() override {
        return (currentIndex - 1 > 0);
    }

    // previous in Loop
    Song* previous() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex - 1;
        return currentPlaylist->getSongs()[currentIndex];
    }
};
class CustomStrategy: public PlayingStrategy{
     private :
    int currentIndex;
    Playlist * currentPlaylist;
    public :
    void setPlaylist(Playlist* playlist){
        this -> currentPlaylist = playlist;
    }
     bool hasNext() override {
        return ((currentIndex + 1) < currentPlaylist->getSize());
    }

    // Next in Loop
    Song* next() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex + 1;
        return currentPlaylist->getSongs()[currentIndex];
    }

    bool hasPrev() override {
        return (currentIndex - 1 > 0);
    }

    // previous in Loop
    Song* previous() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        currentIndex = currentIndex - 1;
        return currentPlaylist->getSongs()[currentIndex];
    }
};
 // ab startegy bana to li lekin is ko manage bhi to krna pdega like we would hav e to call the getstrategy method to bring out the straegy we want
class StrategyType {
    private:
    string name;
    StrategyType(string name){
        this->name = name;
    }

    public:
    static StrategyType* const SEQUENTIAL;
    static StrategyType* const CUSTOM;
    static StrategyType* const RANDOM;

    string getName(){
        return name;
    }
};
StrategyType* const StrategyType::SEQUENTIAL = new StrategyType("SEQUENTIAL");
StrategyType* const StrategyType::CUSTOM = new StrategyType("CUSTOM");
StrategyType* const StrategyType::RANDOM = new StrategyType("RANDOM");

class StrategyManager{
    private:
    SequentialStrategy * sequential;
    RandomStrategy * random ;
    CustomStrategy * custom ;
    StrategyManager(){
        sequential = new SequentialStrategy();
        random = new RandomStrategy();
        custom = new CustomStrategy();
    }
    static StrategyManager * instance ;
    public:
    static StrategyManager * getInstance(){
        return instance;
    }
    PlayingStrategy * getStrategy( StrategyType * type){
        string name = type->getName();
        if(name == "SEQUENTIAL"){
            return sequential;
        }
        else if(name == "RANDOM"){
            return random;
        }
        else{
            return custom;
        }
    }
};
StrategyManager * StrategyManager :: instance= new StrategyManager();

// now time to build the facade design pattern  for the spotify app 
class SpotifyFacade{
    private :
    PlayingStrategy * strategy ;
    Playlist * currPlaylist;
    DeviceManager * deviceManager = DeviceManager:: getInstance();
    StrategyManager* strategyManager= StrategyManager::getInstance();
    AudioEngine * audioEngine;
    PlaylistManager * playlistManager = PlaylistManager::getInstance();
    static SpotifyFacade * instance ;
    SpotifyFacade(){
        strategy=nullptr;
        currPlaylist= nullptr;
        audioEngine= new AudioEngine();
    }
    public :
    static SpotifyFacade * getInstance(){
        return instance;
    }
    void setStrategy(StrategyType* type)   {
        strategy = strategyManager->getStrategy(type);
    }
    void connectDevice(DeviceType * type){
        deviceManager->connect(type);
    }
    void loadPlaylist(string name ){
        currPlaylist= playlistManager->getPlaylist(name);
        if(!strategy){
            throw runtime_error("set the playing strategy before setting the playlist");
        }
        else strategy->setPlaylist(currPlaylist);
    }
    void playSong(Song * song){
        if(!deviceManager->getDevice())throw runtime_error("slect the output devce first");
        audioEngine->playSongOnDevice(deviceManager->getDevice(),song);
    }
    void playNext(){
        if(!currPlaylist)throw runtime_error("set playlist first before playing the next song");
        if(strategy->hasNext()){
            Song * song = strategy->next();
            playSong(song);
        }
    }
    void playPrev(){
        if(!currPlaylist)throw runtime_error("set playlist first before playing the next song");
        if(strategy->hasPrev()){
            Song * song = strategy->previous();
            playSong(song);
        }
    }
    void playAllSongs(){
        if(!currPlaylist)throw runtime_error("set the playlist first");
        while(strategy->hasNext()){
            Song * nextSong = strategy->next();
            playSong(nextSong);
        }
    }
};
SpotifyFacade * SpotifyFacade::instance = new SpotifyFacade();
class MusicPlayerApplication {
private:
    static MusicPlayerApplication* instance;
    vector<Song*> songLibrary;
    MusicPlayerApplication() {}

public:
    static MusicPlayerApplication* getInstance() {
        if (!instance) {
            instance = new MusicPlayerApplication();
        }
        return instance;
    }

    void createSongInLibrary(const string& title, const string& artist,
                                const string& path) {
        Song* newSong = new Song(title, artist, path);
        songLibrary.push_back(newSong);
    }

    Song* findSongByTitle(const string& title) {
        for (Song* s : songLibrary) {
            if (s->getTitle() == title) {
                return s;
            }
        }
        return nullptr;
    }
    void createPlaylist(const string& playlistName) {
        PlaylistManager::getInstance()->createPlaylist(playlistName);
    }

    void addSongToPlaylist(const string& playlistName,
                            const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found in library.");
        }
        PlaylistManager::getInstance()
            ->addSongToPlaylist(playlistName, song);
    }

    void connectAudioDevice(DeviceType* deviceType) {
        SpotifyFacade::getInstance()->connectDevice(deviceType);
    }

    void selectPlayStrategy(StrategyType *strategyType) {
        SpotifyFacade::getInstance()->setStrategy(strategyType);
    }

    void loadPlaylist(const string& playlistName) {
        SpotifyFacade::getInstance()->loadPlaylist(playlistName);
    }

    void playSingleSong(const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found.");
        }
        SpotifyFacade::getInstance()->playSong(song);
    }

    // void pauseCurrentSong(const string& songTitle) {
    //     Song* song = findSongByTitle(songTitle);
    //     if (!song) {
    //         throw runtime_error("Song \"" + songTitle + "\" not found.");
    //     }
    //     SpotifyFacade::getInstance()->pauseSong(song);
    // }

    void playAllTracksInPlaylist() {
        SpotifyFacade::getInstance()->playAllSongs();
    }

    void playPreviousTrackInPlaylist() {
        SpotifyFacade::getInstance()->playPrev();
    }

    // void queueSongNext(const string& songTitle) {
    //     Song* song = findSongByTitle(songTitle);
    //     if (!song) {
    //         throw runtime_error("Song \"" + songTitle + "\" not found.");
    //     }
    //     MusicPlayerFacade::getInstance()->enqueueNext(song);
    // }
};

MusicPlayerApplication* MusicPlayerApplication::instance = nullptr;

int main() {
    try {
        auto application = MusicPlayerApplication::getInstance();

        // Populate library
        application->createSongInLibrary("Kesariya",  "Arijit Singh",  "/music/kesariya.mp3");
        application->createSongInLibrary("Chaiyya Chaiyya",   "Sukhwinder Singh",  "/music/chaiyya_chaiyya.mp3");
        application->createSongInLibrary("Tum Hi Ho",  "Arijit Singh",  "/music/tum_hi_ho.mp3");
        application->createSongInLibrary("Jai Ho",  "A. R. Rahman",  "/music/jai_ho.mp3");
        application->createSongInLibrary("Zinda",  "Siddharth Mahadevan",  "/music/zinda.mp3");

        // Create playlist and add songs
        application->createPlaylist("Bollywood Vibes");
        application->addSongToPlaylist("Bollywood Vibes", "Kesariya");
        application->addSongToPlaylist("Bollywood Vibes", "Chaiyya Chaiyya");
        application->addSongToPlaylist("Bollywood Vibes", "Tum Hi Ho");
        application->addSongToPlaylist("Bollywood Vibes", "Jai Ho");

        // Connect device
        application->connectAudioDevice(DeviceType::BLUETOOTH);

        //Play/pause a single song
        application->playSingleSong("Zinda");
        // application->pauseCurrentSong("Zinda");
        application->playSingleSong("Zinda");  // resume

        cout << "\n-- Sequential Playback --\n";
        application->selectPlayStrategy(StrategyType::SEQUENTIAL);
        application->loadPlaylist("Bollywood Vibes");
        application->playAllTracksInPlaylist();

        cout << "\n-- Random Playback --\n";
        application->selectPlayStrategy(StrategyType::RANDOM);
        application->loadPlaylist("Bollywood Vibes");
        application->playAllTracksInPlaylist();

        cout << "\n-- Custom Queue Playback --\n";
        application->selectPlayStrategy(StrategyType::CUSTOM);
        application->loadPlaylist("Bollywood Vibes");
        // application->queueSongNext("Kesariya");
        // application->queueSongNext("Tum Hi Ho");
        application->playAllTracksInPlaylist();

        cout << "\n-- Play Previous in Sequential --\n";
        application->selectPlayStrategy(StrategyType::SEQUENTIAL);
        application->loadPlaylist("Bollywood Vibes");
        application->playAllTracksInPlaylist();

        application->playPreviousTrackInPlaylist();
        application->playPreviousTrackInPlaylist();

    } catch (const exception& error) {
        cerr << "Error: " << error.what() << endl;
    }
    return 0;
}