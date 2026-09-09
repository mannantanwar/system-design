package BridgeDP;

abstract class Car{
    private Engine engine;
    Car(Engine engine){
        this.engine = engine ;
    }
    public Engine getEngine(){
        return engine;
    }
    public   abstract void drive();
}
abstract class Engine{
    public abstract  void start();
}

class SUV extends Car{
    SUV(Engine engine){
        super(engine);
    }
    @Override 
    public void drive(){
        System.out.println("driving SUV with engine");
        super.getEngine().start();
    }
}
class sedan extends Car{
    sedan(Engine engine){
        super(engine);
    }
    @Override 
    public void drive(){
        System.out.println("driving sedan with engine");
        super.getEngine().start();
    }
}

class PetrolEngine extends Engine{
    @Override 
    public void start(){
        System.out.println("starting car with the petrol engine ");
    }
}
class BatteryEngine extends Engine{
    @Override 
    public void start(){
        System.out.println("starting car with the battery engine ");
    }
}
public class BridgeDesignPattern {
    public static void main(String[] args) {
        Engine petrolEngine = new PetrolEngine();
        Engine batteryEngine = new BatteryEngine();
        Car suv = new SUV(petrolEngine);
        Car sedan = new sedan(batteryEngine);
        suv.drive();
        sedan.drive();
    }
}
