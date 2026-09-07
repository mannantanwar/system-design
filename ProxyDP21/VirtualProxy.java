package ProxyDP21;




abstract class IImage {
    abstract void display();
}

class RealImage extends IImage{
    @Override
    public void display(){
        System.out.println("displaying the real omagine by doinh heavy crud opeations ");
    }
}

class ImageProxy extends IImage{
    private RealImage realImage;

    ImageProxy(){
        realImage = null;
    }
    @Override
    public void display(){
        System.out.println("calling the display of the proxy");
        if(realImage == null){
            realImage = new RealImage();
        }
        realImage.display();
    }
}

public class VirtualProxy {
    // client side
    public static void main(String[] args) {
        IImage image = new ImageProxy();
        image.display();
    }
}
