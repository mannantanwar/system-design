package HingeSystemDesign;

import java.lang.annotation.Target;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

abstract class NotificationObserver{
    abstract public void update(String message);
}
class NotificationService{
    private Map<Integer ,NotificationObserver>observers; // taking map kyuki mwe might do ki kisi specific user ko hi notify krna hai then we can do this
    // iske andar vo value bhi to store krte hi ki jab vo update hoti hai then we call the updae method of all the observers
    private String message ;
    private static NotificationService instance;
    private NotificationService(){
        observers = new HashMap<>();
    }
    public static NotificationService getInstance(){
        if(instance == null) instance = new NotificationService();
        return instance;
    }
    public void notify(int userId, String message){
        if(observers.containsKey(userId)){
            observers.get(userId).update(message);
        }
    }
    public void notifyAll(String message){
        for( Map.Entry<Integer , NotificationObserver> observer: observers.entrySet()){
            observer.getValue().update(message);
        }
    }
    public void addObserver(int userId,  NotificationObserver observer){
        observers.put(userId, observer);
    }
    public void removeObserver(String userId){
        observers.remove(userId);
    }

}
// concerete observers now 
class UserNotificationObserver extends NotificationObserver{
    private int userId;
    public UserNotificationObserver(int userId){
        this.userId = userId;
    }
    @Override
    public void update(String message){
        System.out.println("ntoifiying the user with the User Id "+userId);;
    }
}

// making the user class
class User{
    private UserProfile userProfile;
    private Map<Integer ,SwipeAction> swipeHistory;
    private static int nextId =1;
    private Preference preference;
    private NotificationObserver notificationObserver;
    User(){
        id = nextId++;
        notificationObserver = new UserNotificationObserver(id);
        NotificationService.getInstance().addObserver(id, notificationObserver);
    }
    public Preference getPreference(){
        return preference;
    }
    public int id;
    public boolean hasLiked(int userId){
        if(swipeHistory.containsKey(userId)){
            return true;
        }
        return false;
    }
    public boolean hasDisliked(int userId){
        return !hasLiked(userId);
    }
    public void swipe(int userId, SwipeAction sa){
        swipeHistory.put(userId, sa);
    }
    public UserProfile getUserProfile(){
        return userProfile;
    }
    public int getId(){
        return id;
    }
}
// this is how enums are made on the core level 
class SwipeAction{
    private String action;
    private SwipeAction(String action){
        this.action = action;
    }
    public static final SwipeAction RIGHT= new SwipeAction("RIGHT");
    public static final SwipeAction LEFT= new SwipeAction("LEFT");

}

// Preference class
class Preference {
    private List<Gender> interestedIn;
    private int minAge;
    private int maxAge;
    private double maxDistance; // in kilometers
    private List<String> interests;

    public Preference() {
        interestedIn = new ArrayList<>();
        interests = new ArrayList<>();
        minAge = 18;
        maxAge = 100;
        maxDistance = 100.0;
    }

    public void addGenderPreference(Gender gender) {
        interestedIn.add(gender);
    }

    public void removeGenderPreference(Gender gender) {
        interestedIn.remove(gender);
    }

    public void setAgeRange(int min, int max) {
        minAge = min;
        maxAge = max;
    }

    public void setMaxDistance(double distance) {
        maxDistance = distance;
    }

    public void addInterest(String interest) {
        interests.add(interest);
    }

    public void removeInterest(String interest) {
        interests.remove(interest);
    }

    public boolean isInterestedInGender(Gender gender) {
        return interestedIn.contains(gender);
    }

    public boolean isAgeInRange(int age) {
        return age >= minAge && age <= maxAge;
    }

    public boolean isDistanceAcceptable(double distance) {
        return distance <= maxDistance;
    }

    public List<String> getInterests() {
        return interests;
    }

    public List<Gender> getInterestedGenders() {
        return interestedIn;
    }

    public int getMinAge() {
        return minAge;
    }

    public int getMaxAge() {
        return maxAge;
    }

    public double getMaxDistance() {
        return maxDistance;
    }
}
enum Gender{
    MALE,
    FEMALE;
}
class Location{
    private double latitude;
    private double longitude;
    public void setLatitude(double latitude){
        this.latitude= latitude;
    }
     public void setLongitude(double longitude){
        this.longitude = longitude;
     }
    public double getDistanceinKM(Location location){
        double earthRadiusKm = 6371;
        double dLat = Math.toRadians(location.latitude - this.latitude);
        double dLon = Math.toRadians(location.longitude - this.longitude);
        double a = Math.sin(dLat / 2) * Math.sin(dLat / 2)
                 + Math.cos(Math.toRadians(this.latitude)) * Math.cos(Math.toRadians(location.latitude))
                 * Math.sin(dLon / 2) * Math.sin(dLon / 2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        return earthRadiusKm * c;
    }
}
class Interest{
    private String name;
    private String category;
    Interest(String name ,String category){
        this.name = name ;
        this.category = category;
    }
}
class UserProfile{
    private String name ;
    private int age ;
    private String bio;
    private List<String> photos;
    private List<Preference>preferences;
    private Location location ;
    private Gender gender;
    private List<Interest>interests;

    public String getName(){
        return name;
    }
    public void setBio(String bio){this.bio = bio;}
    public void setName(String name){
        this.name = name;
    }
    public int getAge(){
        return age;
    }
    public void setAge(int age){
        this.age = age;
    }
    public List<String> getPhotos(){
        return photos;
    }
    public void addPhoto(String photo){
        this.photos.add(photo);
    }
    public List<Preference> getPreferences(){
        return preferences;
    }
    public void setPreferences(List<Preference> preferences){
        this.preferences = preferences;
    }
    public Location getLocation(){
        return location;
    }
    public void setLocation(Location location){
        this.location = location;
    }
    public Gender getGender(){
        return gender;
    }
    public void setGender(Gender gender){
        this.gender = gender;
    }
    public List<Interest> getInterests(){
        return interests;
    }
    public void addInterest(String name , String category){
        Interest interest = new Interest(name , category);
        this.interests.add(interest);
    }

}
// location ke through feed me display karane ki bhot strategies hoskti hai 
abstract class LocationStrategy {
    abstract List<User> findNearbyUsers(double maxDistance, Location location, List<User>users);
}

// now the concrete classes
class BasicLocationStrategy extends LocationStrategy{
    @Override 
    public List<User> findNearbyUsers(double maxDistance , Location location, List<User>users){
        List<User> nearByUsers = new ArrayList<>();
        for( User user : users){
            if(user.getUserProfile().getLocation().getDistanceinKM(location) <=maxDistance){
                nearByUsers.add(user);
            }
        }
        return nearByUsers;
    }
}
class LocationService{
    private LocationStrategy locationStrategy;
    public void setLocationStrategy(LocationStrategy strategy){
        locationStrategy = strategy;
    }
    public List<User> findNearbyUsers(double maxDistance,Location location , List<User>users){
        return locationStrategy.findNearbyUsers(maxDistance, location, users);
    }
}

// now kets implement the matching strategy by using the chain of responsibilty principle
abstract class Matcher{
    abstract double getMatchingScore(User user1 , User user2);
}
enum MatcherType{
    LOCATION,
    INTEREST,
    BASIC;
}

class BasicMatcher extends Matcher{
    private Matcher next = new LocationMatcher();
    @Override 
    public double getMatchingScore(User user1, User user2){
        return 0+next.getMatchingScore(user1, user2);
    }
} 
class LocationMatcher extends Matcher{
    private Matcher next = new InterestMatcher();
    @Override 
    public double getMatchingScore(User user1, User user2){
        return 0+next.getMatchingScore(user1, user2);
    }
}
class InterestMatcher extends Matcher{
    private Matcher next  = null;
    @Override 
    public double getMatchingScore(User user1, User user2){
        return 0;
    }
}
class MatcherFactory{
    public static Matcher createMatcher(MatcherType type){
        if(type.equals(MatcherType.BASIC)){
            return new BasicMatcher();
        }
        else if(type.equals(MatcherType.LOCATION)){
            return new LocationMatcher();
        }
        else{
            return new InterestMatcher();
        }
    }
}

// now only the chatroooms are left
class Message{
    private int senderId;
    private String content;
    private String time;
    Message(int senderId, String content){
        this.senderId= senderId;
        this.content = content;
    }

    public String getContent(){
        return content ;
    }
}
class ChatRoom{
    private int id;
    private static int nextId=1;
    private List<Message>messages;
    private List<Integer>participantIds;
    public ChatRoom( int user1Id, int user2Id) {
        id = nextId++;
        participantIds = new ArrayList<>();
        participantIds.add(user1Id);
        participantIds.add(user2Id);
        messages = new ArrayList<>();
    }
    public void addMessage(int senderId, String content){
        Message message = new Message(senderId, content);
        messages.add(message);
    }
    public void displayChat(){
        for(Message message : messages){
            System.out.println(message.getContent());
        }
    }
    public boolean hasParticipant(int userId){
        for( Integer id : participantIds){
            if(id == userId)return true;
        }
        return false;
    }

}
// facade DP
class DatingApp{
    private List<User> users;
    private List<ChatRoom>rooms;
    private static  Matcher matcher;
    private LocationService locationService;
    private DatingApp() {
        users = new ArrayList<>();
        rooms = new ArrayList<>();
         // Default to location-based matcher
        matcher = MatcherFactory.createMatcher(MatcherType.LOCATION);
        locationService= new LocationService();
    }
    private static DatingApp instance;
    public static DatingApp getInstance(){
        if(instance == null) instance = new DatingApp();
        return instance;
    }
    public List<User> showUsers(Location location, double maxDistance){
        locationService.setLocationStrategy(new BasicLocationStrategy());
        List<User> nearbyUsers = locationService.findNearbyUsers(maxDistance, location, users);
        return nearbyUsers;
    }
    public boolean swipe(User user1, User Targetuser, SwipeAction swipeAction){
        user1.swipe(Targetuser.getId(), swipeAction);
        // checking if it is a match or not 
        if(Targetuser.hasLiked(user1.getId()) && swipeAction.equals(SwipeAction.RIGHT)){
            // then it is match 
            
            ChatRoom room = new ChatRoom(user1.getId(), Targetuser.getId());
            rooms.add(room);

            // notiication bhi bhejde kya 
             // Notify both users
            NotificationService.getInstance().notify(user1.getId(), "You have a new match with " + Targetuser.getUserProfile().getName() + "!");
            NotificationService.getInstance().notify(Targetuser.getId(), "You have a new match with " + user1.getUserProfile().getName() + "!");
            return true;
        }
        return false;
    }
    public User createUser(String username){
        User user = new User();
        users.add(user);
        return user;
    }
    public User getUserById(int id ){
        for( User user : users){
            if(user.getId() == id)return user;
        }
        return null;
    }
    public ChatRoom getChatRoom( int user1, int user2){
        for( ChatRoom room : rooms){
            if(room.hasParticipant(user1) && room.hasParticipant(user2)){
                return room;
            }
        }
        return null;
    }
    public void sendMessage(int senderId, int  receiverId, String content) {
        ChatRoom chatRoom = getChatRoom(senderId, receiverId);
        if (chatRoom == null) {
            System.out.println("No chat room found between these users.");
            return;
        }

         // Notify the receiver
        chatRoom.addMessage(senderId, content);
        NotificationService.getInstance().notify(receiverId, "New message from " + getUserById(senderId).getUserProfile().getName());
    }
    // public void displayUser(int userId) {
    //     User user = getUserById(userId);
    //     if (user == null) {
    //         System.out.println("User not found.");
    //         return;
    //     }
    //     user.displayProfile();
    // }

    public void displayChatRoom(int user1Id, int user2Id) {
        ChatRoom chatRoom = getChatRoom(user1Id, user2Id);
        if (chatRoom == null) {
            System.out.println("No chat room found between these users.");
            return;
        }
        chatRoom.displayChat();
    }
}
public class HingeSystemDesign {
    public static void main(String[] args) {
        // Get the dating app instance
        DatingApp app = DatingApp.getInstance();

         // Create users
        User user1 = app.createUser("user1");
        User user2 = app.createUser("user2");

        // Set user1 profile
        UserProfile profile1 = user1.getUserProfile();
        profile1.setName("Rohan");
        profile1.setAge(28);
        profile1.setGender(Gender.MALE);
        profile1.setBio("I am a software developer");
        profile1.addPhoto("rohan_photo1.jpg");
        profile1.addInterest("Coding", "Programming");
        profile1.addInterest("Travel", "Lifestyle");
        profile1.addInterest("Music", "Entertainment");

        // Setup user1 preferences
        Preference pref1 = user1.getPreference();
        pref1.addGenderPreference(Gender.FEMALE);
        pref1.setAgeRange(25, 30);
        pref1.setMaxDistance(10.0);
        pref1.addInterest("Coding");
        pref1.addInterest("Travel");

        // Setup user2 profile
        UserProfile profile2 = user2.getUserProfile();
        profile2.setName("Neha");
        profile2.setAge(27);
        profile2.setGender(Gender.FEMALE);
        profile2.setBio("Art teacher who loves painting and traveling.");
        profile2.addPhoto("neha_photo1.jpg");
        profile2.addInterest("Painting", "Art");
        profile2.addInterest("Travel", "Lifestyle");
        profile2.addInterest("Music", "Entertainment");

         // Setup user2 preferences
        Preference pref2 = user2.getPreference();
        pref2.addGenderPreference(Gender.MALE);
        pref2.setAgeRange(27, 30);
        pref2.setMaxDistance(15.0);
        pref2.addInterest("Coding");
        pref2.addInterest("Movies");

        // Set location for user1
        Location location1 = new Location();
        location1.setLatitude(1.01);
        location1.setLongitude(1.02);
        profile1.setLocation(location1);

         // Set location for user2 (Close to user1, within 5km)
        Location location2 = new Location();
        location2.setLatitude(1.03);
        location2.setLongitude(1.04);
        profile2.setLocation(location2);

        // // Display user profiles
        // System.out.println("---- User Profiles ----");
        // app.displayUser("user1");
        // app.displayUser("user2");

        // Find nearby users for user1 (within 5km)
        System.out.println("\n---- Nearby Users for user1 (within 5km) ----");
        List<User> nearbyUsers = app.showUsers(user1.getUserProfile().getLocation(), 5.0);
        System.out.println("Found " + nearbyUsers.size() + " nearby users");
        for (User user : nearbyUsers) {
            System.out.println("- " + user.getUserProfile().getName() + " (" + user.getId() + ")");
        }

        // User1 swipes right on User2
        System.out.println("\n---- Swipe Actions ----");
        System.out.println("User1 swipes right on User2");
        app.swipe(user1, user2, SwipeAction.RIGHT);

         // User2 swipes right on User1 (creating a match)
        System.out.println("User2 swipes right on User1");
        app.swipe(user2, user1, SwipeAction.RIGHT);

        // Send messages in the chat room
        System.out.println("\n---- Chat Room ----");
        app.sendMessage(user1.getId(), user2.getId(), "Hi Neha, Kaise ho?");
        
        app.sendMessage(user2.getId(), user1.getId(), "Hi Rohan, Ma bdiya tum btao");
        
        // Display the chat room
        app.displayChatRoom(user1.getId(), user2.getId());
        
    }
}
