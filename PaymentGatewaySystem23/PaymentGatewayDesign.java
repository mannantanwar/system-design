package PaymentGatewaySystem23;

import java.util.Random;

class PayementRequest{
    public String sender;
    public String receiver;
    public String currency;
    public double amount;
    public PayementRequest(String name , String sender ,String receiver , double amount, String currency){
        this.sender = sender;
        this.receiver = receiver;
        this.amount = amount;
        this.currency = currency;
    }
}

abstract class IBankingSystem{
    abstract boolean processPayment(double amount);
}

abstract class PaymentGateway{
    protected IBankingSystem bs;
    public abstract boolean initiatePayment(PayementRequest pr);
    public abstract boolean validatePayment(PayementRequest pr);
    public abstract boolean confirmPayment(PayementRequest pr);
    public boolean processPayment(PayementRequest request) {
        if (!validatePayment(request)) {
            System.out.println("[PaymentGateway] Validation failed for " + request.sender + ".");
            return false;
        }
        if (!initiatePayment(request)) {
            System.out.println("[PaymentGateway] Initiation failed for " + request.sender + ".");
            return false;
        }
        if (!confirmPayment(request)) {
            System.out.println("[PaymentGateway] Confirmation failed for " + request.sender + ".");
            return false;
        }
        return true;
    }
}

class PaytmBankingSystem extends IBankingSystem{
    private Random rand = new Random();

    public PaytmBankingSystem() {}

    @Override
    public boolean processPayment(double amount) {
        // Simulate 20% success
        int r = rand.nextInt(100);
        return r < 80;
    }
}
class RazorPayBankingSystem extends IBankingSystem{
    private Random rand = new Random();

    public RazorPayBankingSystem() {}

    @Override
    public boolean processPayment(double amount) {
        // Simulate 20% success
        int r = rand.nextInt(100);
        return r < 90;
    }
}


// now time to define the various payment gateways 
class PaytmGateway extends PaymentGateway{
    public PaytmGateway(){
        this.bs = new PaytmBankingSystem();
    }
    @Override
    public boolean initiatePayment(PayementRequest pr){
        return bs.processPayment(pr.amount);
    }

    @Override
    public boolean validatePayment(PayementRequest pr){
        if(pr.amount < 0  && !pr.currency.equals("INR"))return false;
        return true;
        
    }
    public boolean confirmPayment(PayementRequest pr){
        return true;// har case me payement confirm hojygi 
    }

}
class RazorPayGateway extends PaymentGateway{
    public RazorPayGateway(){
        this.bs = new RazorPayBankingSystem();
    }
    @Override
    public boolean initiatePayment(PayementRequest pr){
        return bs.processPayment(pr.amount);
    }

    @Override
    public boolean validatePayment(PayementRequest pr){
        if(pr.amount < 0  && !pr.currency.equals("INR"))return false;
        return true;
        
    }
    public boolean confirmPayment(PayementRequest pr){
        return true;// har case me payement confirm hojygi 
    }

}
class PaymentGatewayProxy extends PaymentGateway {
    private PaymentGateway realGateway;
    private int retries;

    public PaymentGatewayProxy(PaymentGateway gateway, int maxRetries) {
        this.realGateway = gateway;
        this.retries     = maxRetries;
    }

    @Override
    public boolean processPayment(PayementRequest request) {
        boolean result = false;
        for (int attempt = 0; attempt < retries; ++attempt) {
            if (attempt > 0) {
                System.out.println("[Proxy] Retrying payment (attempt " + (attempt+1)
                        + ") for " + request.sender + ".");
            }
            result = realGateway.processPayment(request);
            if (result) break;
        }
        if (!result) {
            System.out.println("[Proxy] Payment failed after " + retries
                    + " attempts for " + request.sender + ".");
        }
        return result;
    }

    @Override
    public boolean validatePayment(PayementRequest request) {
        return realGateway.validatePayment(request);
    }

    @Override
    public boolean initiatePayment(PayementRequest request) {
        return realGateway.initiatePayment(request);
    }

    @Override
    public boolean confirmPayment(PayementRequest request) {
        return realGateway.confirmPayment(request);
    }
}
class GatewayType {
    private String name;

    private GatewayType(String name) {
        this.name = name;
    }

    public static final GatewayType PAYTM = new GatewayType("PAYTM");
    public static final GatewayType RAZORPAY = new GatewayType("RAZORPAY");

    public String getName() {
        return name;
    }
}
class PaymentGatewayFactory{
    public PaymentGateway getGateway(GatewayType type){
        if(type == GatewayType.PAYTM){
            return new PaymentGatewayProxy(new PaytmGateway(),3);
        }
        else if(type == GatewayType.RAZORPAY){
            return new PaymentGatewayProxy(new PaytmGateway(),3);
        }
        return null;
    }
}

class PaymentService{
    private PaymentGateway gateway;
    private PaymentGatewayFactory factory;
    // have to make this class a singleton class
    private PaymentService(){
        this.factory = new PaymentGatewayFactory();
    }
    private static PaymentService instance = new PaymentService();
    public static PaymentService getInstance(){
        return instance;
    }
    public void setGateway(GatewayType type){
        this.gateway = factory.getGateway(type);
    }
    public boolean processPayment(PayementRequest pr, GatewayType type){
        setGateway(type);
        return gateway.processPayment(pr);
    }

}

class PaymentController{
    private PaymentService ps = PaymentService.getInstance();
    public boolean handlePayment(PayementRequest pr , GatewayType type){
        return ps.processPayment(pr, type);
    }
}
public class PaymentGatewayDesign {
    public static void main(String[] args) {
        PaymentController controller = new PaymentController();
        PayementRequest pr = new PayementRequest("Mannan", "Anushka", "Dineout", 5000,"INR");
        controller.handlePayment(pr, GatewayType.PAYTM);
    }
}
