package ProxyDP21;

class User {
    private String name ;
    public boolean premiumMemebership;

    User(String name , boolean premiumMemebership){
        this. name = name;
        this.premiumMemebership= premiumMemebership;
    }   
}
abstract class IDocReader{
    abstract void readDoc( String pswd);
}

class RealDocReader extends IDocReader{
    private User user;
    RealDocReader(User user){
        this.user = user;
    }
    @Override
    public void readDoc( String pswd){
        if(!user.premiumMemebership){
            System.out.println("Access denied as user does not have the premium membership");
        }
        else{
            System.out.println("userr authenticated with the password " +pswd);
            System.out.println("reading the docs");
        }
    }
}

class DocReaderProxy extends IDocReader{
    private User user;
    private RealDocReader realDocReader;
    DocReaderProxy(User user){
        this.user = user;
        realDocReader = new RealDocReader(user); // this is the fast loading is jaise hi ye class call hoogi ye jaake connect hojyga new classs se unlike the virtualy prxy which implementes the lazy loading 
    }
    @Override
    public void readDoc( String pswd){
        System.out.println("caling the doc reader of the real class through the proxy");
        realDocReader.readDoc( pswd);
    }
}

public class ProtectionProxy {
    public static void main(String[] args) {
        // client side cod eover here 
        User user1 = new User("Mannan", false);
        User user2 = new User("Anushka", true);

        IDocReader reader = new DocReaderProxy(user2);
        reader.readDoc("abc123");

        reader = new DocReaderProxy(user1); // old DocReaderProxy(user2) object is now unreferenced -> eligible for GC
        reader.readDoc("abc321");

    }
}
